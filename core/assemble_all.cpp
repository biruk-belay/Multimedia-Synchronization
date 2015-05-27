#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include "kiss_fft.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <map>
#include "func_engine.h"

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979324
#endif

extern	kiss_fft_cpx in[N];
extern  kiss_fft_cpx out[N];

/*
    This function is the heart of the program. Here is where everything is put together... What is referred to as "Main file" in the
    comment is the original file and the reference file is the file which is supposed to be part of the main file and whose delay
    we are trying to calculate

*/

string run_all(void)

{
    char buffer[N];

    string str ="";
    int time = 0 ;
    int offset_num =0;
    string line;
    float popular ;
    int size_main;
    int size_ref;

    FILE* file_main = fopen( "temp_main", "wb" ); // file to write the mono output of the main file
    FILE* file2 = fopen( "temp_ref", "wb" );      // file to write the mono output of the reference file

    char* ptr = loadWAV("Zigzan_69.wav", size_main); // ptr to raw audio data of main file

    char* ptr_ref = loadWAV("Zigzan.wav", size_ref); // ptr to raw audio data of reference file

    mono_to_stereo(ptr_ref, size_ref,file_main); // change the main stereo file into mono and write data to file pointed by file_main
    mono_to_stereo(ptr, size_main, file2);       // change reference stereo file into mono and write data to file pointed by file2


        ifstream file_ref ("temp_ref", ios::binary); // stream to read from the mono reference file
        ifstream file ("temp_main", ios::binary);    // stream to read from the mono main file

        ofstream offset ("offset", ios::out | ios::ate );
        ifstream offset_read ("offset", ios::in);

        multimap <string, int> ref, original; // a container to store concatenated strings of the indexes of the highest frequencies
                                              // with their respective slots


/*
  After reading the mono file, perform fft then select the indexes of the max frequencies  and write it to the continer
  Since we are chopping the mono file in chunks of size N we must keep track of which chunk the highest frequencies represent
  the time variable does exactly that. It is incremented for every chunk.

*/
        while (!file.eof()) {

    file.read(buffer,N);
    fft(buffer);
    str = max_freq (out);
    original.insert(pair<string,int> (str, time));
   // csv   <<  str << ";" << time << "\n";
    //cout  << "\t "<< time << " Seconds  \n";
    time++;
}   	time = 0;


    while (!file_ref.eof()) {

    file_ref.read(buffer,N);
    fft(buffer);
        str = max_freq (out);
    ref.insert(pair<string,int> (str, time));
   // csv_ref   <<  str << ";" << time << "\n";
    time++;
}

    /*
    In this section there is another continer which contains a pair of containers, one container of the main file and one contianer
    of the referecne file.

    We associate these two to find a match between them. So for every string entry of the reference container the main container is checked
    for matches. If a match is found between the strings then the time value (integer entry) of the refernce is subtracted from
    the corresponding main value (integer entry). The value is written to a file named offset.

    For example

       Reference container           Main Container
       -----------------            ----------------
        154781 | 10               215487101 | 49
        123654 | 11               123654    | 50
      65214782 | 12                    .    |
      854120023| 13                    .    |
                                       .    |
                                 854120023  | 86


  We have 2 matches from the table. The first match is 123645 so the difference of the corresponding time values i.e 50-11 = 39 is written to offset
 again the difference of the time values of the second match 854120023, which is 86-13 = 73 is written to the offset file.

 This way all the matches and all their corresponding time differences are recorded

*/
     pair <multimap<string, int> :: iterator, multimap<string, int>:: iterator> pp;
         for (   multimap<string, int> :: iterator it2= ref.begin(); it2!=ref.end(); ++it2) {

            pp = original.equal_range((*it2).first);

            for (multimap<string, int> :: iterator it = pp.first; it!=pp.second; ++it)
     {

    if (((*it).second-(*it2).second)>= 0)
    offset<< ((*it).second-(*it2).second) << endl;
    }
}	offset.close();



   // Find out the total number of matches, which are already written to the offset

    while (getline(offset_read, str)) {
       offset_num++;
   }


    /*
       The values in the offset file are all strings. for computation purposes we need to change them to integer and store
       them in an array. The following 2 lines of code does exactly that

    */

    int array [offset_num]; // define an array of size equal to number of entries in the offset file
    put_to_array (array);   // change string value to integer and store it in the array


/*
    The most_occuring function, as its name implies, calculates the most occuring time differnce from the array
    the most occuring time value is likely to be the true delay between the main file and the offset

*/
    popular = most_occuring (array, offset_num);


    /*
    Finally the delay is calculated and the integer is converted back to string
    Where did the 0.02323... number come from ???

    here is the secret behind that number

    our WAV file is sampled at 44100 samples per second and it is encoded with 2 bytes so that gives us 44100*2 = 88200 bytes/sec
    In simple terms we have 88200 bytes of data in one second. We are working with a chunk which is 2048 bytes.
    So what is the duration of a 2048 bytes of data ?

    it would be 2048/88200 = 0.023219955 sec

    If our most_occuring function returns a value of 1000, it means the delay between the main file and the reference file is 1000
    chunks or reference file is a snippet of the main file after 1000 chunks. In terms of time it means the reference file matches
    the main file after 1000*0.023219955 = 23.219 seconds.

    */

    std::ostringstream buff;
    buff<<(popular* 0.023219955);

    return buff.str();

}
