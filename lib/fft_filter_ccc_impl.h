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

#ifndef INCLUDED_TUJASDR_FFT_FILTER_CCC_IMPL_H
#define INCLUDED_TUJASDR_FFT_FILTER_CCC_IMPL_H

#include <tujasdr/fft_filter_ccc.h>
#include <NE10/NE10.h>

namespace gr {
  namespace tujasdr {

    class fft_filter_ccc_impl : public fft_filter_ccc
    {
     private:
        unsigned int d_N; // FFT size
        unsigned int d_L; // Number of new input samples consumed per data block
        unsigned int d_P; // Length of h(n), our kernel
        
        std::vector<gr_complex> d_H; // freq domain taps
        std::vector<gr_complex> d_X; // freq domain input
        std::vector<gr_complex> d_y; // freq domain input
        
        ne10_fft_cfg_float32_t d_fft_cfg;
     public:
      fft_filter_ccc_impl(int decimation, const std::vector<gr_complex> &taps);
      ~fft_filter_ccc_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace tujasdr
} // namespace gr

#endif /* INCLUDED_TUJASDR_FFT_FILTER_CCC_IMPL_H */
