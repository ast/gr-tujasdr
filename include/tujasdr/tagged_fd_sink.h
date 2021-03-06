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


#ifndef INCLUDED_TUJASDR_TAGGED_FD_SINK_H
#define INCLUDED_TUJASDR_TAGGED_FD_SINK_H

#include <tujasdr/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
    namespace tujasdr {
        
        /*!
         * \brief <+description of block+>
         * \ingroup tujasdr
         *
         */
        class TUJASDR_API tagged_fd_sink : virtual public gr::tagged_stream_block
        {
        public:
            typedef boost::shared_ptr<tagged_fd_sink> sptr;
            
            /*!
             * \brief Return a shared_ptr to a new instance of tujasdr::tagged_fd_sink.
             *
             * To avoid accidental use of raw pointers, tujasdr::tagged_fd_sink's
             * constructor is in a private implementation
             * class. tujasdr::tagged_fd_sink::make is the public interface for
             * creating new instances.
             */
            static sptr make(const int fd, const std::string& len_tag_key="packet_len");
        };
        
    } // namespace tujasdr
} // namespace gr

#endif /* INCLUDED_TUJASDR_TAGGED_FD_SINK_H */
