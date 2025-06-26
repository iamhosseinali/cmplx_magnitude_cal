#include <iostream>
#include <cmath>
#include "ap_int.h"
#include "ap_fixed.h"
#include "hls_stream.h"

using namespace hls;

#define FFT_LENGTH       1024
#define IMG_REAL_WIDTH   16

typedef struct {
    ap_int<IMG_REAL_WIDTH> imaginary;
    ap_int<IMG_REAL_WIDTH> real;
} inDataType;

typedef struct {
    ap_ufixed<IMG_REAL_WIDTH * 2, IMG_REAL_WIDTH> tDATA;
    ap_uint<1> tLAST;
} outDataType;

void mag_cal(stream<inDataType>& in, stream<outDataType>& out);

int main() {
    stream<inDataType> in_stream;
    stream<outDataType> out_stream;

    for (int i = 0; i < FFT_LENGTH; i++) {
        inDataType sample;
        sample.real = i % 128;              // test pattern
        sample.imaginary = (i * 2) % 128;    // test pattern
        in_stream.write(sample);
    }

    mag_cal(in_stream, out_stream);

    for (int i = 0; i < FFT_LENGTH; i++) {
        outDataType result = out_stream.read();

        // Reconstruct expected value using float math
        float real = float(i % 128);
        float imag = float((i * 2) % 128);
        float expected = std::sqrt(real * real + imag * imag);

        float output = result.tDATA.to_float();
        float error = std::abs(output - expected);

        std::cout << "Sample " << i << ": |R+jI| = " << output
                  << ", expected = " << expected
                  << ", error = " << error
                  << ", tLAST = " << result.tLAST << "\n";

        if (error > 0.3f) {
            std::cout << "ERROR too large at sample " << i << "\n";
            return 1;
        }
    }

    std::cout<<"Test completed successfully.\n";
    return 0;
}
