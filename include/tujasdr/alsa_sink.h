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


#ifndef INCLUDED_TUJASDR_ALSA_SINK_H
#define INCLUDED_TUJASDR_ALSA_SINK_H

#include <tujasdr/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
    namespace tujasdr {
        
        /*!
         * \brief ALSA sink for TujaSDR board
         * \ingroup tujasdr
         *
         */
        class TUJASDR_API alsa_sink : virtual public gr::sync_block
        {
        public:
            typedef boost::shared_ptr<alsa_sink> sptr;
            
            /*!
             * \brief Return a shared_ptr to a new instance of tujasdr::alsa_sink.
             *
             * To avoid accidental use of raw pointers, tujasdr::alsa_sink's
             * constructor is in a private implementation
             * class. tujasdr::alsa_sink::make is the public interface for
             * creating new instances.
             */
            // TODO: change string to by reference
            // TODO: change name of blocks to reflect type
            static sptr make(unsigned int sample_rate,
                             const std::string device_name = "",
                             unsigned int frames_per_period = 2048);
        };
        
    } // namespace tujasdr
} // namespace gr

#endif /* INCLUDED_TUJASDR_ALSA_SINK_H */
