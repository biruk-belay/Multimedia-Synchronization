#include <iostream>
#include "kiss_fft.h"
#include <fstream>
#include <sstream>

#ifndef N

#define N 2048
#endif
#define max_extracted_freq 3

//        kiss_fft_cpx in[N];
//        kiss_fft_cpx out[N];

std::string max_freq (kiss_fft_cpx out[]);
void fft(char * buffer);
void  put_to_array ( int* array);
void max (int array[], int out[], int size);
char* loadWAV(const char* fn, int & size);
void mono_to_stereo (char *data, int size,FILE * file);
//void mono_to_stereo_main (char *data, int size);
int most_occuring(int array[], int size);
