############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project cmplx_magnitude_cal
set_top mag_cal
add_files cmplx_magnitude_cal/src/main.cpp
add_files -tb cmplx_magnitude_cal/src/tb.cpp
open_solution "solution1"
set_part {xc7z010clg400-1} -tool vivado
create_clock -period 10 -name default
#source "./cmplx_magnitude_cal/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl vhdl -format ip_catalog -description "An IP to calculate the magnitude of incomming complex numbers stream. " -vendor "Taksun" -version "1.0.0"
