/* -*- c++ -*- */
/* 
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "tagged_fd_sink_impl.h"

#include <sys/types.h>
#include <sys/socket.h>

#include <stdexcept>

namespace gr {
    namespace tujasdr {
        
        tagged_fd_sink::sptr
        tagged_fd_sink::make(const int fd, const std::string& len_tag_key)
        {
            return gnuradio::get_initial_sptr(new tagged_fd_sink_impl(fd, len_tag_key));
        }
        
        /*
         * The private constructor
         */
        tagged_fd_sink_impl::tagged_fd_sink_impl(const int fd, const std::string& len_tag_key)
        : d_fd(fd), gr::tagged_stream_block("tagged_fd_sink",
                                  gr::io_signature::make(1, 1, sizeof(unsigned char)),
                                  gr::io_signature::make(0, 0, 0),
                                  len_tag_key)
        {
        }
        
        /*
         * Our virtual destructor.
         */
        tagged_fd_sink_impl::~tagged_fd_sink_impl()
        {}
        
        int
        tagged_fd_sink_impl::work(int noutput_items,
                                     gr_vector_int &ninput_items,
                                     gr_vector_const_void_star &input_items,
                                     gr_vector_void_star &output_items)
        {
            const unsigned char *in = (const unsigned char *) input_items[0];
            
            // printf("in: %d out %d\n", ninput_items[0], noutput_items);
            
            // No blocking
            // We prefer packet loss to blocking
            ssize_t err;
            //err = write(d_fd, in, (size_t)ninput_items[0]);
            err = send(d_fd, in, (size_t)ninput_items[0], MSG_DONTWAIT);
            if(err < 0) {
                perror("tagged_fd_sink: write");
            }
            
            // Tell runtime system how many output items we consumed.
            // Should be 0 because we are sinking.
            return noutput_items;
        }
        
    } /* namespace tujasdr */
} /* namespace gr */
