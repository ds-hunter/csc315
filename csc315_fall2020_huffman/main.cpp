/**************************************************************************//**
 * @file main.cpp
 *
 * @brief The main function for the program
 *
 * @author: Anthony Benitez
 * @author: Daniel Hunter
 *
 * @par Class:
 * CSC315 Data Structures
 *
 * @date:   Fall 2020
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include "hash.h"
#include "huffman.h"
#include <iomanip>

using namespace std;

/**************************************************************************//**
 * @brief The main program function loop
 *
 * @param[in] argc - The count of arguments in the program
 * @param[in] argv - The string values of each argument
 *
 ******************************************************************************/
int main(int argc, char **argv)
{    
    // Process command-line arguments
    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " -e originalfile encodedfile" << endl;
        cerr << "       " << argv[0] << " -d encodedfile decodedfile" << endl;
        return -1;
    }
    //store arguments into variables and create hash table for histogram
    char *encodedFilename = argv[2];
    char *decodedFilename = argv[3];
    char byte;
    Hash charHash;

    // Attempt to open the original/encoded file.
    ifstream fin(encodedFilename, ios::in | ios::binary);
    if (!fin.is_open())
    {
	//if file does not open, then report error and exit program
        cerr << "Error: unable to open " << encodedFilename << endl;
        return -2;
    }

    // Attempt to open the output file
    ofstream fout(decodedFilename, ios::out | ios::binary);
    if (!fout.is_open())
    {
	// if file does not open, then report error and exit program
        cerr << "Error: unable to open " << decodedFilename << endl;
        return -2;
    }

    //if the first argument is an e then follow the encoding procedure
    if(argv[1][1] == 'e')
    {
       // output user interface
       int bytesRead = 0;
       cout << "Huffman Encoder Pass 1" << endl;
       cout << "----------------------" << endl;
       // Read characters from the original file and get frequencies.
       byte = fin.get();
       while (byte != istream::traits_type::eof())
       {
          charHash.increment(byte);
          byte = fin.get();
	  //Increase number of bytes / characters read
          bytesRead++;
       }
       // output more user interface
       cout << "Read " << bytesRead << " bytes from " << encodedFilename <<", found " << 
           charHash.size() << " code words" << endl << endl;
       // Call huffman constructor to create huffman tree
       Huffman huffman(charHash, bytesRead);
       //output huffman table statistics and codes
       fout.seekp(0, ios::beg);
       huffman.OutputTable(fout, huffman.node);
       huffman.GenerateCodes(huffman.node);
       // encode the file with the huffman codes
       huffman.EncodeFile(fin, fout);
       //outpt the rest of the user interface with the statistics
       cout << huffman;
       cout << "Huffman Encoder Pass 2" << endl;
       cout << "----------------------" << endl;
       cout << "Wrote " << (int(fout.tellp()) - (huffman.CharCount() * 5 + 1)) << " encoded bytes to " << decodedFilename << " ("
	<< fout.tellp() << " bytes including histogram)" << endl;
       cout << "Huffman Coding Statistics" << endl << "----------------------" << endl;
       cout << "Compression ratio = " << setprecision(2) << (double(fout.tellp())/double(bytesRead))*100 << "%" << endl;
       cout << "Entropy = " << huffman.Entropy(bytesRead) << endl;
       cout << "Average bits per symbol in Huffman coding = " << huffman.BitAverage() << endl;
       cout << "Coding efficiency = " << "0.00%" << endl;
    }
    //if the first argument is an d then follow the decoding procedure
    else if(argv[1][1] == 'd')
    {
       cout << "Huffman Decoder" << endl << "----------------" << endl;
       //call huffman constructor to read in histogram and create huffman tree
       Huffman huffman(fin);
       //output user interface
       fin.seekg(0,ios::end);
       cout << "Read " << (int(fin.tellg()) - (huffman.CharCount() * 5 + 1)) << " encoded bytes from " << encodedFilename << " ("
       << fin.tellg() << " bytes including histogram)" << endl;
       //call huffman decoder to decode the encoded file
       huffman.DecodeFile(fin, fout);
       //output statistics for user interface
       cout <<" decoded bytes to " << decodedFilename << endl;
       cout << "Compression ratio = " << setprecision(4) << (double(fin.tellg())/double(fout.tellp()))*100 << "%" << endl;
    }
    
    //close the files
    fin.close();

    fout.close();

    return 0;
}
