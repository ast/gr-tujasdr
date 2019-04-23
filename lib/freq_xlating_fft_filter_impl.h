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

#ifndef INCLUDED_TUJASDR_FREQ_XLATING_FFT_FILTER_IMPL_H
#define INCLUDED_TUJASDR_FREQ_XLATING_FFT_FILTER_IMPL_H

#include <tujasdr/freq_xlating_fft_filter.h>
#include <tujasdr/rotator_cc.h>
#include <gnuradio/filter/fft_filter_ccc.h>


namespace gr {
    namespace tujasdr {
        
        class freq_xlating_fft_filter_impl : public freq_xlating_fft_filter
        {
        private:
            std::vector<gr_complex>  d_taps;            // prototype taps
            unsigned int             d_decimation;
            float                    d_center_freq;
            float                    d_sampling_freq;
            bool                     d_updated;
            
            // Sub-blocks
            gr::filter::fft_filter_ccc::sptr  d_fft_filter;
            gr::tujasdr::rotator_cc::sptr     d_rotator;
            
        public:
            freq_xlating_fft_filter_impl(unsigned int decimation,
                                         const std::vector<gr_complex> &taps,
                                         float center_freq,
                                         float sampling_freq);
            ~freq_xlating_fft_filter_impl();
            
            void set_center_freq(float center_freq);
            float center_freq() const;
            
            void set_taps(const std::vector<gr_complex> &taps);
            std::vector<gr_complex> taps() const;
        };

    } // namespace tujasdr
} // namespace gr

#endif /* INCLUDED_TUJASDR_FREQ_XLATING_FFT_FILTER_IMPL_H */

