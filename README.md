# mag_cal – Complex Magnitude Calculator (HLS)

This module computes the **magnitude of complex numbers** in a streaming fashion using **Xilinx Vivado HLS**. It is designed to be synthesizable into an **AXI4-Stream-compatible IP core** for FPGA integration.

---

## Overview

Given a stream of complex numbers represented by 16-bit signed integers for both real and imaginary components, this module calculates the **magnitude** using the formula:

```

|Z| = sqrt(Re² + Im²)

````

The result is a 32-bit **unsigned fixed-point** value with fractional precision.

---

## Features

- Input via **AXI4-Stream** (`inDataType`)
- Output via **AXI4-Stream** (`outDataType`)
- Fully pipelined for 1-sample-per-cycle throughput
- Configurable precision and FFT size

---


```

* `tDATA`: 32-bit unsigned fixed-point (16 int + 16 frac bits)
* `tLAST`: AXIS signal marking the last sample in the stream

---

## Configuration

Modify these macros to tune the design:

```cpp
#define FFT_LENGTH      1024   // Number of complex samples per batch
#define IMG_REAL_WIDTH  16     // Bit-width for real and imaginary parts
```

---

## Testbench

A simple testbench should:

1. Populate `hls::stream<inDataType>` with 1024 samples
2. Call `mag_cal(input_stream, output_stream)`
3. Read results and validate against `sqrt(real² + imag²)`

---

## Interfaces

* **Input stream**: `S_AXIS` (AXIS slave)
* **Output stream**: `M_AXIS` (AXIS master)
* **Control**: `ap_ctrl_none` (always-on, no control interface)


---

## Recreating the HLS project
Step 1: Open Vivado HLS Command Prompt. 

Step 2: Change the directory to ip_repo\HLS folder, e.q.

``` cd c:\...\project_name\ip_repo\HLS ``` 


Step 3: source the script.tcl: 

``` vivado_hls -f HLS_IP_1\solution1\script.tcl ``` 

