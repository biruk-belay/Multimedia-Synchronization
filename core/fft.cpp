#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include "kiss_fft.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <map>
//#include "most_occuring.h"
//#include "fft.h"
//#include "t.h"
#include "func_engine.h"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979324
#endif

extern	kiss_fft_cpx in[N];
extern  kiss_fft_cpx out[N];



int main(void)

{
	char buffer[N];
	char buffer_int;
//	int array [offset_num];
        int array_index = 0;
	string str ="";
     	int time = 0 ;
        int offset_num =0;
	string line;
	int popular ;
	int size_main;
	int size_ref;

	char* ptr = loadWAV("Kinde_recording.wav", size_main);
	//int * ptrr = mono_to_stereo(ptr,size);
	char* ptr_ref = loadWAV("Biruk_recording.wav", size_ref);
	mono_to_stereo_main(ptr_ref, size_ref);
	mono_to_stereo(ptr, size_main);

	
	ifstream file_ref("temp_ref", ios::binary);
        ifstream file("temp_main", ios::binary);
	ofstream csv("out.csv", ios::out | ios::ate);
        ofstream offset("offset", ios::out | ios::ate );
        ifstream offset_read ("offset", ios::in);
        ofstream csv_ref ("out_ref.csv", ios::out | ios::ate);
        multimap <string, int> ref, original;
        ifstream offset_read_2 ("offset", ios::in);
     

	while (!file.eof()) {

	file.read(buffer,N);
	fft(buffer);
	str = max_freq (out);
	original.insert(pair<string,int> (str, time));
	csv   <<  str << ";" << time << "\n"; 
	//cout  << "\t "<< time << " Seconds  \n";
	time++;
}   	time = 0;


	while (!file_ref.eof()) {

	file_ref.read(buffer,N);
	fft(buffer);
        str = max_freq (out);
	ref.insert(pair<string,int> (str, time));
	csv_ref   <<  str << ";" << time << "\n";
	time++;        
}

	 pair <multimap<string, int> :: iterator, multimap<string, int>:: iterator> pp;

         for (   multimap<string, int> :: iterator it2= ref.begin(); it2!=ref.end(); ++it2) {

//	pair <multimap<string, int> :: iterator, multimap<string, int>:: iterator> pp;
        pp = original.equal_range((*it2).first);

	for (multimap<string, int> :: iterator it = pp.first; it!=pp.second; ++it)
	{//cout << (*it).first << " " << ((*it).second-(*it2).second) <<  endl;
	if (((*it).second-(*it2).second)>= 0)
	offset<< ((*it).second-(*it2).second) << endl;
	}
}	offset.close();

//	offset_num = wc -l offset;

	while (getline(offset_read, str)) {
	//offset_read.read(buffer_int, 4);
	offset_num++;
	//cout << str << endl;
}
	
//	ifstream offset_read_2 ("offset", ios::in);
	 int array [offset_num];
 	
  //	string line;
	put_to_array (array);

	
 cout << offset_num << " is the offset" << endl;

popular = most_occuring (array, offset_num);
 
cout << "the most popular number is " << popular * 0.023219955 ;
//	cout<< array[2200] << endl; 

 return 0;
}
