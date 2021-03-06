# Copyright 2011,2012,2016,2018,2019 Free Software Foundation, Inc.
#
# This file was generated by gr_modtool, a tool from the GNU Radio framework
# This file is a part of gr-tujasdr
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX
list(APPEND tujasdr_sources
    alsa.c
    single_pole_low_pass.cc
    fast_sine_osc.cc
    agc_cc_impl.cc
    alsa_sink_impl.cc
    alsa_source_impl.cc
    complex_to_mag_squared_log_vcb_impl.cc
    fast_sine_source_c_impl.cc
    mono_sink_impl.cc
    mono_source_impl.cc
    opus_encoder_f_impl.cc
    single_pole_low_pass_ff_impl.cc
    sum_real_imag_cc_impl.cc
    tagged_fd_sink_impl.cc
    rotator_cc_impl.cc
    freq_xlating_fft_filter_impl.cc
)

set(tujasdr_sources "${tujasdr_sources}" PARENT_SCOPE)
if(NOT tujasdr_sources)
    MESSAGE(STATUS "No C++ sources... skipping lib/")
    return()
endif(NOT tujasdr_sources)

add_library(gnuradio-tujasdr SHARED ${tujasdr_sources})

target_link_libraries(
  gnuradio-tujasdr
  gnuradio::gnuradio-runtime
  ${ALSA_LIBRARIES}
  ${OPUS_LIBRARIES}
  ${NE10_LIBRARIES}
)

target_include_directories(gnuradio-tujasdr
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
  PUBLIC $<INSTALL_INTERFACE:include>
  ${NE10_INCLUDE_DIRS}
  ${ALSA_INCLUDE_DIRS}
  ${OPUS_INCLUDE_DIRS}
)
set_target_properties(gnuradio-tujasdr PROPERTIES DEFINE_SYMBOL "gnuradio_tujasdr_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-tujasdr PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-tujasdr)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

# If your unit tests require special include paths, add them here
#include_directories()
# List all files that contain Boost.UTF unit tests here
list(APPEND test_tujasdr_sources
)
# Anything we need to link to for the unit tests go here
list(APPEND GR_TEST_TARGET_DEPS gnuradio-tujasdr)

if(NOT test_tujasdr_sources)
    MESSAGE(STATUS "No C++ unit tests... skipping")
    return()
endif(NOT test_tujasdr_sources)

foreach(qa_file ${test_tujasdr_sources})
    GR_ADD_CPP_TEST("tujasdr_${qa_file}"
        ${CMAKE_CURRENT_SOURCE_DIR}/${qa_file}
    )
endforeach(qa_file)
