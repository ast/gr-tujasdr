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

#include <gnuradio/io_signature.h>
#include "freq_xlating_fft_filter_impl.h"

#include <gnuradio/blocks/rotator.h>

namespace gr {
    namespace tujasdr {
        
        freq_xlating_fft_filter::sptr
        freq_xlating_fft_filter::make(unsigned int decimation,
                                      const std::vector<gr_complex> &taps,
                                      float center_freq,
                                      float sampling_freq)
        {
            return gnuradio::get_initial_sptr
            (new freq_xlating_fft_filter_impl(decimation,
                                              taps,
                                              center_freq,
                                              sampling_freq));
        }
        
        
        /*
         * The private constructor
         */
        freq_xlating_fft_filter_impl::freq_xlating_fft_filter_impl(unsigned int decimation,
                                                                   const std::vector<gr_complex> &taps,
                                                                   float center_freq,
                                                                   float sampling_freq)
        : d_decimation(decimation),
        d_center_freq(center_freq),
        d_sampling_freq(sampling_freq),
        gr::hier_block2("freq_xlating_fft_filter",
                        gr::io_signature::make(1, 1, sizeof(gr_complex)),
                        gr::io_signature::make(1, 1, sizeof(gr_complex)))
        {
            
            d_fft_filter = gr::filter::fft_filter_ccc::make(decimation, taps);
            d_rotator = gr::tujasdr::rotator_cc::make(2 * M_PI * center_freq / sampling_freq);
            
            // Connect things up
            connect(self(), 0, d_fft_filter, 0);
            connect(d_fft_filter, 0, d_rotator, 0);
            connect(d_rotator, 0, self(), 0);
        }
        
        /*
         * Our virtual destructor.
         */
        freq_xlating_fft_filter_impl::~freq_xlating_fft_filter_impl()
        {
        }
        
        void
        freq_xlating_fft_filter_impl::set_center_freq(float center_freq) {
            d_center_freq = center_freq;
        }
        
        float
        freq_xlating_fft_filter_impl::center_freq() const {
            return d_center_freq;
        }
        
        void
        freq_xlating_fft_filter_impl::set_taps(const std::vector<gr_complex> &taps) {
            
        }
        
        std::vector<gr_complex>
        freq_xlating_fft_filter_impl::taps() const {
            return d_fft_filter->taps();
        }
        
        
    } /* namespace tujasdr */
} /* namespace gr */

