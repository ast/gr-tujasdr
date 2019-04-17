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
#include <volk/volk.h>
#include "fft_filter_ccc_impl.h"

namespace gr {
    namespace tujasdr {
        
        fft_filter_ccc::sptr
        fft_filter_ccc::make(int decimation, const std::vector<gr_complex> &taps)
        {
            return gnuradio::get_initial_sptr
            (new fft_filter_ccc_impl(decimation, taps));
        }
        
        /*
         * The private constructor
         */
        fft_filter_ccc_impl::fft_filter_ccc_impl(int decimation, const std::vector<gr_complex> &taps)
        : d_N(4069),
        gr::sync_block("fft_filter_ccc",
        gr::io_signature::make(1, 1, sizeof(gr_complex)),
                       gr::io_signature::make(1, 1, sizeof(gr_complex)))
        {
            // Init Ne10 library
            ne10_result_t res = ne10_init();
            assert(res == NE10_OK);
            
            d_L = d_N - (unsigned int)taps.size()  + 1;
            
            d_fft_cfg = ne10_fft_alloc_c2c_float32_neon(d_N);
            
            std::vector<gr_complex> h = taps; // time domain taps
            
            h.resize(d_N, 0);
            d_H.resize(d_N, 0);
            d_X.resize(d_N, 0);
            d_y.resize(d_N, 0);
            // Transform taps to frequency domain
            ne10_fft_c2c_1d_float32_neon((ne10_fft_cpx_float32_t*)d_H.data(),
                                         (ne10_fft_cpx_float32_t*)h.data(),
                                         d_fft_cfg, 0);
            
            // Is it like this?
            set_output_multiple(d_L);
            set_history(d_P - 1);
        }
        
        /*
         * Our virtual destructor.
         */
        fft_filter_ccc_impl::~fft_filter_ccc_impl()
        {
            ne10_fft_destroy_c2c_float32(d_fft_cfg);
        }
        
        int
        fft_filter_ccc_impl::work(int noutput_items,
                                  gr_vector_const_void_star &input_items,
                                  gr_vector_void_star &output_items)
        {
            const gr_complex *in = (const gr_complex *) input_items[0];
            gr_complex *out = (gr_complex *) output_items[0];
            
            // Take input to freq domain
            ne10_fft_c2c_1d_float32_neon((ne10_fft_cpx_float32_t*)d_X.data(),
                                         (ne10_fft_cpx_float32_t*) in,
                                         d_fft_cfg, 0);
            
            //volk_32fc_x2_multiply_32fc(lv_32fc_t* cVector, const lv_32fc_t* aVector, const lv_32fc_t* bVector, unsigned int num_points);
            
            // Multiply wity taps
            volk_32fc_x2_multiply_32fc((lv_32fc_t*) d_X.data(),
                                       (const lv_32fc_t*) d_X.data(),
                                       (const lv_32fc_t*) d_H.data(),
                                       d_N);
            
            
            ne10_fft_c2c_1d_float32_neon((ne10_fft_cpx_float32_t*)d_y.data(),
                                         (ne10_fft_cpx_float32_t*) d_X.data(),
                                         d_fft_cfg, 1); // inverse
            
            // 
            for (int n = d_P - 1, i = 0; n < d_N; n++, i++) {
                out[i] = d_y[n];
            }
            
            // FFT
            //ne10_fft_c2c_1d_float32_neon(out, in, cfg, 0); // Call the FP32 C2C NEON implementation directly
            // IFFT
            //ne10_fft_c2c_1d_float32_neon(out, in, cfg, 1);
            
            printf("fft got: %d\n", noutput_items);
            
            // Do <+signal processing+>
            
            // Tell runtime system how many output items we produced.
            return noutput_items;
        }
        
    } /* namespace tujasdr */
} /* namespace gr */

