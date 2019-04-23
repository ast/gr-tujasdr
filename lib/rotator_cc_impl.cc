/* -*- c++ -*- */
/*
 * Copyright 2019 Albin Stigö.
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

#include <cmath>
#include <gnuradio/io_signature.h>
#include "rotator_cc_impl.h"

namespace gr {
    namespace tujasdr {
        
        rotator_cc::sptr
        rotator_cc::make(float phase_inc)
        {
            return gnuradio::get_initial_sptr
            (new rotator_cc_impl(phase_inc));
        }
        
        
        /*
         * The private constructor
         */
        rotator_cc_impl::rotator_cc_impl(float phase_inc)
        : gr::sync_block("rotator_cc",
        gr::io_signature::make(1, 1, sizeof(sizeof(gr_complex))),
                         gr::io_signature::make(1, 1, sizeof(sizeof(gr_complex))))
        {
            set_phase_inc(phase_inc);
        }
        
        /*
         * Our virtual destructor.
         */
        rotator_cc_impl::~rotator_cc_impl()
        {
        }
        
        void
        rotator_cc_impl::set_phase_inc(float phase_inc)
        {
            // TODO: things will probably go crazy here without a mutex
            // float w = d_frequency * (2 * M_PI / d_sample_rate);
            // Init state
            // gr::thread::scoped_lock guard(d_mutex);
            d_u = 1.;
            d_v = 0.;
            d_k1 = tanf(phase_inc/2);
            d_k2 = 2 * d_k1 / (1 + d_k1 * d_k1);
        }
        
        int
        rotator_cc_impl::work(int noutput_items,
                              gr_vector_const_void_star &input_items,
                              gr_vector_void_star &output_items)
        {
            const gr_complex *in = (const gr_complex *) input_items[0];
            gr_complex *out = (gr_complex *) output_items[0];
            
            for (int i=0; i<noutput_items; i++) {
                out[i] = in[i] * next();
            }
            
            // Tell runtime system how many output items we produced.
            return noutput_items;
        }
        
    } /* namespace tujasdr */
} /* namespace gr */

