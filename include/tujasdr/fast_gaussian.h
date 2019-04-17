/* -*- c++ -*- */
/* 
 * Copyright 2019 <+YOU OR YOUR COMPANY+>.
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


#ifndef INCLUDED_TUJASDR_FAST_GAUSSIAN_H
#define INCLUDED_TUJASDR_FAST_GAUSSIAN_H

#include <tujasdr/api.h>
#include <tujasdr/moving_average.h>

namespace gr {
    namespace tujasdr {
        namespace kernel {
            
            /*!
             * \brief <+description+>
             *
             */
            class TUJASDR_API fast_gaussian
            {
            private:
                // Longer gives better approximation
                const unsigned int d_num_avgs = 4;
                std::vector<moving_average> d_avgs;
            public:
                fast_gaussian(unsigned int length) {
                    unsigned int per_moving_average = length / d_num_avgs;
                    assert(per_moving_average < 256);
                    for(int n = 0; n < d_num_avgs; n++) {
                        d_avgs.push_back(moving_average(per_moving_average));
                    }
                }
                ~fast_gaussian() {};
                
                inline float filter(float x) {
                    // a few times through a moving average
                    // gives a nice approximation of a gaussian response.
                    x = d_avgs[0].filter(x);
                    x = d_avgs[1].filter(x);
                    x = d_avgs[2].filter(x);
                    x = d_avgs[3].filter(x);
                    return x;
                }
            };
        } // namespace kernel
    } // namespace tujasdr
} // namespace gr

#endif /* INCLUDED_TUJASDR_FAST_GAUSSIAN_H */

