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

#ifndef INCLUDED_TUJASDR_ROTATOR_CC_IMPL_H
#define INCLUDED_TUJASDR_ROTATOR_CC_IMPL_H

#include <tujasdr/rotator_cc.h>
#include <gnuradio/thread/thread.h>

namespace gr {
    namespace tujasdr {
        
        class rotator_cc_impl : public rotator_cc
        {
        private:
            float d_v;
            float d_u;
            float d_k1;
            float d_k2;
            
            // mutable gr::thread::mutex d_mutex; // protects internal data access.
            
            inline void update() {
                float tmp;
                tmp = d_u - d_k1 * d_v;
                d_v = d_v + d_k2 * tmp;
                d_u = tmp - d_k1 * d_v;
            }
            
            inline gr_complex next() {
                gr_complex c = gr_complex(d_u, d_v);
                update();
                return c;
            }
            
        public:
            rotator_cc_impl(float phase_inc);
            ~rotator_cc_impl();
            
            void set_phase_inc(float phase_inc);
            
            // Where all the action really happens
            int work(
                     int noutput_items,
                     gr_vector_const_void_star &input_items,
                     gr_vector_void_star &output_items
                     );
        };
        
    } // namespace tujasdr
} // namespace gr

#endif /* INCLUDED_TUJASDR_ROTATOR_CC_IMPL_H */

