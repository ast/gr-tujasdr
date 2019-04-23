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

#ifndef INCLUDED_TUJASDR_ROTATOR_CC_H
#define INCLUDED_TUJASDR_ROTATOR_CC_H

#include <tujasdr/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
    namespace tujasdr {
        
        /*!
         * \brief <+description of block+>
         * \ingroup tujasdr
         *
         */
        class TUJASDR_API rotator_cc : virtual public gr::sync_block
        {
        public:
            typedef boost::shared_ptr<rotator_cc> sptr;
            
            /*!
             * \brief Return a shared_ptr to a new instance of tujasdr::rotator_cc.
             *
             * To avoid accidental use of raw pointers, tujasdr::rotator_cc's
             * constructor is in a private implementation
             * class. tujasdr::rotator_cc::make is the public interface for
             * creating new instances.
             */
            static sptr make(float phase_inc);
            
            virtual void set_phase_inc(float phase_inc) = 0;
        };
        
    } // namespace tujasdr
} // namespace gr

#endif /* INCLUDED_TUJASDR_ROTATOR_CC_H */

