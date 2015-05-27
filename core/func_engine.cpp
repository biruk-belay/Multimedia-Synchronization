//#include "fft.h"
#include <sstream>
#include "func_engine.h"
using namespace std ;

/*

  Kiss_fft is the library that is used in this project to perform fft
  Therefore it is necessary to define a global object of type Kiss_fft_cpx class to hold the complex frequency amplitudes

*/

kiss_fft_cpx in[N];
        kiss_fft_cpx out[N];
	ifstream offset_read_2 ("offset", ios::in);

    /*
    This function takes in an array of frequency amplitudes and selects the array indexes of the highest frequencies whose number is decided by the constant
    max_extracted_freq. Then it concatenates these numbers as stringstream

    For example if the 1st, 5th, 15th and 18th frequencies from the array have the highest values in decreasing order
    the function returns  a string 151518

*/

string max_freq (kiss_fft_cpx out[])

{

        int mag [max_extracted_freq];    // value to store magnitude
        int maximum =0; // value to store maximum
        int index =0;   // value to store the index of maximum  
        int arg =max_extracted_freq;     // total number of maximum numbers to extract
        int array_index =0; // incremental index of the return array
        string str = "";
        ostringstream ss;


	        while (arg >0)
{
        for (int i=0; i< N; i++) {

          if (out[i].r > maximum)
        {       maximum = out[i].r; index = i;}
}
        mag[array_index] = index;
        out[index].r = 0;
        arg--;
       // printf("%i\n", index);
        array_index++;
        maximum =0;


}
        for (int i =0 ; i<max_extracted_freq; i++)
        //cout << mag[i] << " ";
        ss <<  mag[i];
        str = ss.str();

//      cout << str;
        return str;

}

/*
    This function takes an int array of some size and returns the number which occurs the most in the array.

*/


int most_occuring(int array[], int size) {
    int i,j,a[5];

int popular = a[0];
int temp=0, tempCount, count=1;

        for (i=0;i<size;i++)
    {
        tempCount = 0;
        temp=array[i];
        tempCount++;
            for(j=i+1;j<size;j++)
        {
            if(array[j] == temp)
            {
                tempCount++;
                if(tempCount > count)
                {
                    popular = temp;
                count = tempCount;
                }
            }
        }
    }
        return popular;
}


/*

    This function perfroms N point fft accepting data from a character pointer. The data is first copied to an array kiss_fft_cpx in
    then the output is stored in kiss_fft_cpx out. Both of these arrays have size N.


*/
void fft(char * buffer)
{

        string str = "" ;
        size_t i;
        for ( i = 0; i < N; i++)
        in[i].r = buffer[i]; in[i].i = 0;
        kiss_fft_cfg cfg;

        if ((cfg = kiss_fft_alloc(N, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
  {
    //size_t i;
    kiss_fft(cfg, in, out);
    free(cfg);
 }

  else

  {
    printf("not enough memory?\n");
    exit(-1);
}}





/*
This function reads strings from file, converts it to integer and stores it in an array

*/


void put_to_array(int * array) {
	std::string line; 
//	int array_index =0;
	 while (getline(offset_read_2, line ) )
        {
        istringstream iss( line );
        int number;
        while( iss >> number )
       * array = number;
        array++;
        cout << number << endl;


}
}

/*
    After the header of the WAV file is stripped the raw data, which is originally stereo need to be changed in to a mono file.
    The process involves averaging the Right and Left values and writes them as 16 bit integers into a file pointed by file
    pointer parameter.

*/

void mono_to_stereo (char *data, int size, FILE * file) {

         //FILE* file2 = fopen( "temp_ref", "wb" );
	 char buffer [4];
         short left, right, mono;

        for (int i = 0, j =0 ; i<size ; j++,i+=4)     {

        left =  (((*(int *)&(data[i]) & 0xFF)) | ((*(int *)&(data[i+1])) <<8) & (0xFF <<8));
        right = (((*(int *)&(data[i+2]) & 0xFF)) |  ((*(int *)&(data[i+3])) <<8) & (0xFF <<8));

        mono = (left+ right)/2;
        buffer [0] = mono &0xFF;
        buffer [1] = (mono >>8)& 0xFF;

fwrite( buffer, 1, 2, file);

//      cout << left  << " " << right << endl;
        }
}


/*
    This function loads the WAV file reads through the header and finally returns the pointer to the start of the raw audio data
    It also passes the size of the file to a value passed in reference.

*/

char* loadWAV(const char* fn /*, int& chan, int& samplerate, int& bps*/, int& size){

        char buffer[4];
        ifstream in(fn, ios::binary);
         in.read(buffer, 4);

        //cout << to_int(buffer,4);
        //ChunkID "RIFF"
        //cout << buffer;
        if(strncmp(buffer, "RIFF", 4) != 0){
                cerr << "this is not a valid wave file";
                return NULL;
        }
        in.read(buffer,4);
        //ChunkSize 
        in.read(buffer,4);
        //Format "WAVE"
        in.read(buffer,4);
        // "fmt "
        in.read(buffer,4);
        // 16
        in.read(buffer,2);
        // 1
        in.read(buffer,2);
        // NUMBER OF CHANNELS
      //  chan = ((buffer [0]) & 0XFF) | ((buffer[1]<<8) & (0XFF<<8));

        in.read(buffer,4);
        // SAMPLE RATE
    //    samplerate = ((buffer [0]) & 0XFF) | ((buffer[1]<<8) & (0XFF<<8)) | ((buffer[2] <<16) & (0XFF<<16)) | ((buffer[3]<<24) & (0XFF<<24));

        in.read(buffer,4);
        // ByteRate
        in.read(buffer,2);
        // BlockAlign

        in.read(buffer,2);
       // bits per sample

        //bps = ((buffer [0]) & 0XFF) | ((buffer[1]<<8) & (0XFF<<8));

        in.read(buffer,4);

       //size = convertToInt(buffer,4);
        in.read(buffer,4);
        // Subchunk2

        size = ((buffer [0]) & 0XFF) | ((buffer[1]<<8) & (0XFF<<8)) | ((buffer[2] <<16) & (0XFF<<16)) | ((buffer[3]<<24) & (0XFF<<24));
        //cout << size << "  " << "\n";        

        char * data = new char[size];
//      int * data_2;

        in.read(data,size);
        //data_2 = data;

        return data;
}
