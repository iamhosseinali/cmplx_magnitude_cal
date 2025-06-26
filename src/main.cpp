#include <ap_int.h>
#include <ap_fixed.h>
#include <hls_math.h>
#include <hls_stream.h>

using namespace hls;

#define FFT_LENGTH 		1024
#define IMG_REAL_WIDTH 	16

typedef struct{
	ap_int<IMG_REAL_WIDTH> imaginary;
	ap_int<IMG_REAL_WIDTH> real;
}inDataType;

typedef struct {
	ap_ufixed<IMG_REAL_WIDTH*2,IMG_REAL_WIDTH> tDATA;
	ap_uint<1> tLAST;
}outDataType;


void mag_cal(stream<inDataType >&in, stream<outDataType >&out) {
#pragma HLS DATA_PACK variable=in struct_level
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis register both port=out name=M_AXIS
#pragma HLS INTERFACE axis register both port=in name=S_AXIS

	inDataType in_data;
	outDataType out_data;
	ap_int<IMG_REAL_WIDTH> real_in,imag_in;
	ap_uint<IMG_REAL_WIDTH*2> temp_r,temp_i;
	ap_ufixed<IMG_REAL_WIDTH*2,IMG_REAL_WIDTH*2> temp_sum;

	for(int i=0;i<FFT_LENGTH;i++)
	{
#pragma HLS PIPELINE
		in_data = in.read();
		real_in = in_data.real;
		imag_in = in_data.imaginary;

		temp_r = real_in * real_in;
		temp_i = imag_in * imag_in;
		temp_sum = temp_r + temp_i;

		out_data.tDATA = sqrt(temp_sum);
		if(i==FFT_LENGTH-1) out_data.tLAST = 1; else out_data.tLAST = 0;
		out.write(out_data);
	}
}
