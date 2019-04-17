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
#include "tujavolk.h"
#include "sum_real_imag_cc_impl.h"

namespace gr {
    namespace tujasdr {
        
        sum_real_imag_cc::sptr
        sum_real_imag_cc::make()
        {
            return gnuradio::get_initial_sptr(new sum_real_imag_cc_impl());
        }
        
        /*
         * The private constructor
         */
        sum_real_imag_cc_impl::sum_real_imag_cc_impl()
        : gr::sync_block("sum_real_imag_cc",
                         gr::io_signature::make(1, 1, sizeof(gr_complex)),
                         gr::io_signature::make(1, 1, sizeof(float)))
        { }
        
        /*
         * Our virtual destructor.
         */
        sum_real_imag_cc_impl::~sum_real_imag_cc_impl()
        {
        }
        
        int
        sum_real_imag_cc_impl::work(int noutput_items,
                                    gr_vector_const_void_star &input_items,
                                    gr_vector_void_star &output_items)
        {
            const gr_complex *in = (const gr_complex *) input_items[0];
            float *out = (float *) output_items[0];
            
            volk_32fc_sum_parts_32f_neon(out, in, noutput_items);
            
            // Tell runtime system how many output items we produced.
            return noutput_items;
        }
        
    } /* namespace tujasdr */
} /* namespace gr */
