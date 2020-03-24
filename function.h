#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdio.h>
#include <tiffio.h>
#include <cmath>
#include <png.h>
#include "mat_complex.h"
#include "mat_float.h"
#include "mat_uint8.h"

#define PNG_BYTES_TO_CHECK	8
#define HAVE_ALPHA			1
#define NOT_HAVE_ALPHA		0

MatComplex read_tiff(string path);
bool f_pwf(const MatComplex & HH,const MatComplex & HV,const MatComplex & VV, int N, MatFloat &Y);
bool f_rs(const MatComplex & HH,const MatComplex & HV, int N, MatFloat & Y);
float get_T_PWF(int p, float Pfa, int maxIter=500, double ep=1e-5, double x0=1);
bool write_png_file(string filename , MatUint8 out);

#endif