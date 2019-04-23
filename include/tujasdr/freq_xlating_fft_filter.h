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

#ifndef INCLUDED_TUJASDR_FREQ_XLATING_FFT_FILTER_H
#define INCLUDED_TUJASDR_FREQ_XLATING_FFT_FILTER_H

#include <tujasdr/api.h>
#include <gnuradio/hier_block2.h>

namespace gr {
    namespace tujasdr {
        
        /*!
         * \brief <+description of block+>
         * \ingroup tujasdr
         *
         */
        class TUJASDR_API freq_xlating_fft_filter : virtual public gr::hier_block2
        {
        public:
            typedef boost::shared_ptr<freq_xlating_fft_filter> sptr;
            
            /*!
             * \brief Return a shared_ptr to a new instance of tujasdr::freq_xlating_fft_filter.
             *
             * To avoid accidental use of raw pointers, tujasdr::freq_xlating_fft_filter's
             * constructor is in a private implementation
             * class. tujasdr::freq_xlating_fft_filter::make is the public interface for
             * creating new instances.
             */
            static sptr make(unsigned int decimation,
                             const std::vector<gr_complex> &taps,
                             float center_freq,
                             float sampling_freq);
            
            virtual void set_center_freq(float center_freq) = 0;
            virtual float center_freq() const = 0;
            
            virtual void set_taps(const std::vector<gr_complex> &taps) = 0;
            virtual std::vector<gr_complex> taps() const = 0;
        };
    } // namespace tujasdr
} // namespace gr

#endif /* INCLUDED_TUJASDR_FREQ_XLATING_FFT_FILTER_H */

