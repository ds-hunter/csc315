#ifndef __HUFFMAN_H
#define __HUFFMAN_H

#include <fstream>
#include <iostream>
#include <string>
#include "heap.h"
#include "hash.h"
#include <map>

using namespace std;

class Huffman
{
   int NumofChar, NumofBytes;
   map<char, string> CodeTable;
   Hash hash1;
   map<char, int> OccurenceTable;
   //string bits;
   //ofstream fout;
public:
   Node *node;
   Huffman(Hash, int);
   Huffman(ifstream& fin);


   void InputHash(Hash, MinHeap &);
   void OutputTable(ofstream& fout, Node *);
   bool InputTable(ifstream& fin, MinHeap &Heap);
   void EncodeFile(ifstream& fin, ofstream& fout);
   void DecodeFile(ifstream& fin, ofstream& fout);
   void GenerateCodes(Node *, string code = "");
   int Count(char);
   int CharCount();
   double Entropy(int);
   double BitAverage();
   //void GenerateCodes(Node *n, string code, int calls)
   void DisplayCodes();
   string ToBitstring(unsigned short int);
   void DecodeBitstring(string, string &, int &);
   friend std::ostream& operator<<(std::ostream& os, Huffman obj);
};

#endif
