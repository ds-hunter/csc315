#include "huffman.h"
#include <iomanip>
#include <math.h>

Huffman::Huffman(Hash CharHash, int BytesRead)
{
    MinHeap *Heap = new MinHeap();
    hash1 = CharHash;
    NumofBytes = BytesRead;
    InputHash(CharHash, *Heap);
    Node *l, *r;
    while(Heap->size() != 1)
    {
        // Remove 2 lowest freq nodes on heap
        Node Node1 = Heap->removeMin();
        Node Node2 = Heap->removeMin();
        l = new Node();
        r = new Node();

        // Get data from old nodes
        l->count = Node1.count;
        r->count = Node2.count;
        l->key = Node1.key;
        r->key = Node2.key;
        l->direction = 0;
        r->direction = 1;
        l->LeftChild = Node1.LeftChild;
        l->RightChild = Node1.RightChild;
        r->LeftChild = Node2.LeftChild;
        r->RightChild = Node2.RightChild;

        // Combine them into a single node
        Heap->add(l, r);
    }
    node = Heap->top();
}

Huffman::Huffman(ifstream& fin)
{

    MinHeap Heap;
    Hash CharHash;
    fin.seekg(0, ios::beg);
    NumofBytes = CharHash.readHistogram(fin);
    //NumofChar = fin.get();
    InputHash(CharHash, Heap);
    Node *l, *r;
    while(Heap.size() != 1)
    {
        // Remove 2 lowest freq nodes on heap
        Node Node1 = Heap.removeMin();
        Node Node2 = Heap.removeMin();
        l = new Node();
        r = new Node();

        // Get frequency from old nodes
        l->count = Node1.count;
        r->count = Node2.count;
        l->key = Node1.key;
        r->key = Node2.key;
        l->LeftChild = Node1.LeftChild;
        l->RightChild = Node1.RightChild;
        r->LeftChild = Node2.LeftChild;
        r->RightChild = Node2.RightChild;
        l->direction = 0;
        r->direction = 1;

        // Combine them into a single node
        Heap.add(l, r);
    }
    node = Heap.top();
}

void Huffman::InputHash(Hash CharHash, MinHeap &Heap)
{
    NumofChar = 0;
    for(int i = 0; i < 255; i++)
    {
        if (CharHash[i] > 0)
        {
            Heap.add(CharHash[i], char(i));
            OccurenceTable.insert(pair<char, int>(char(i), CharHash[i]));
            NumofChar++;
        }
    }
}

void Huffman::OutputTable(ofstream& fout, Node *nodePass)
{
    if(fout.tellp() < 1)
    {
        fout.write((char *) &NumofChar, sizeof(int));
    }
    if (nodePass->RightChild == nullptr && nodePass->LeftChild == nullptr)
    {
        fout.write((char *) &nodePass->key, sizeof(char));
        fout.write((char *) &nodePass->count, sizeof(int));
        return;
    }
    OutputTable(fout, nodePass->LeftChild);
    OutputTable(fout, nodePass->RightChild);
}

bool Huffman::InputTable(ifstream& fin, MinHeap &Heap)
{
    char key;
    int count;
    int pos = NumofChar;
    //NumofChar = fin.get();
    while(NumofChar != 0)
    {
        key = fin.get();
        count = fin.get();
        Heap.add(count, key);
        NumofChar--;
    }
    if(fin.tellg() == (4 + pos*5))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Huffman::GenerateCodes(Node *n, string code)
{
    //char key;

    // Generate the huffman code for the current leaf node/key
    if (n->LeftChild == nullptr && n->RightChild == nullptr)
    {
        code += to_string(n->direction);
        code.erase(code.begin()+0);
        CodeTable.insert({n->key, code});
        OccurenceTable.insert({n->key, n->count});
        code.clear();
        return;
    }

    code += to_string(n->direction);
    GenerateCodes(n->LeftChild, code);
    GenerateCodes(n->RightChild, code);
}

void Huffman::DisplayCodes()
{
    map<char, string>::iterator it;

    for (it = CodeTable.begin(); it != CodeTable.end(); it++)
    {
        cout << it->first << " | " << it->second << endl;
    }
}

int Count(char i)
{
    //return hash1[int(i)];
    return 0;
}

void Huffman::EncodeFile(ifstream& fin, ofstream& fout)
{
    fin.clear();
    fin.seekg(0, ios::beg);
    fout.seekp(sizeof(int) + NumofChar * (sizeof(char) + sizeof(int)), ios::beg);
    //cout << fout.tellp() << endl;
    unsigned short int writer = 0;
    char reader;
    //Node *direction = node;
    map<char, string>::iterator it;
    string bits;
    int path;

    while(!fin.eof())
    {
        while(bits.size() < 16 && !fin.eof())
        {
            fin.read((char *) &reader, sizeof(char));
            //reader = fin.get();
            it = CodeTable.begin();
            while(it->first != reader && it != CodeTable.end())
            {
                it++;
            }
            if(it == CodeTable.end())
            {
                cout << "didn't find" << endl;
            }
            bits += it->second;
            //cout << it->second << " ";
            //cout << "made it to bits" << endl;
        }
        //cout << endl;
        //Still need to figure out how to write an uneven amount of bits
        if(fin.eof())
        {
            //cout << "reached eof " << endl;
            //return;
            int i = 0;
            while(bits.size() > 0)
            {
                path = int(bits[0]) - 48;
                //cout << path << " " << bits.size() << endl;
                if(path == 0)
                {
                    writer = writer & 65534;
                }
                else
                {
                    writer = writer | 1;
                }
                //Possibly need to read back some bits to output these ones or add spaces possibly?
                writer = writer << 1;
                i++;
                bits.erase(0,1);
            }
            writer = writer << (15 - i);
            fout.write((char *) &writer, sizeof(writer));
            return;
        }
        else
        {
            //cout << bits << endl;
            for(int j = 0; j < 16;  j++)
            {
                path = int(bits[j]) - 48;
                //cout << path;
                if(path == 0)
                {
                    writer = writer & 65534;
                }
                else
                {
                    writer = writer | 1;
                }
                if(j < 15)
                {
                    writer = writer << 1;
                }
            }
            bits.erase(0,16);
            /*if(!bits.empty())
            {
                cout << endl << bits << endl;
            }
            else
            {
                cout << endl << "Nothing" << endl;
            }*/
            fout.write((char *) &writer, sizeof(writer));
            writer = 0;
        }
    }
    return;
}

int Huffman::CharCount() 
{
    return NumofChar;
}

double Huffman::Entropy(int bytesRead)
{
    double val = 0;
    double prob;
    for(auto p : OccurenceTable)
    {
        prob = (double(p.second) / double(bytesRead)) * 100;
        val += prob * log2(prob);
        //cout << prob << " " << val << endl;
    }
    return val/100;
}

double Huffman::BitAverage()
{
    double prob, indSize;
    double aveSize = 0;
    for( auto p : CodeTable)
    {
        for(auto q : OccurenceTable)
        {
            if(p.first == q.first)
            {
                prob = ((double(q.second)) / double(NumofBytes)) * 100;
                indSize = double(p.second.size());
                aveSize += prob * indSize;
            }
        }
    }
    return aveSize / 100;
}

/***************************************************************************//**
 * @brief Decodes a huffman encoded file and writes to an outfile.                                                       
 ******************************************************************************/
void Huffman::DecodeFile(ifstream& fin, ofstream& fout)
{
    //move the cursor to the spot at the end of the histogram
    int totalBits = fin.tellg() * 4;
    fin.clear();
    fin.seekg(sizeof(int) + NumofChar * (sizeof(char) + sizeof(int)), ios::beg);
    fout.seekp(0, ios::beg);
    
    // Variables
    unsigned short int reader;
    map<char, string>::iterator it;
    string bits, decodedBitstring;
    int bytes = 0, diffInBits = 0, bitsRead = 0;
    //int histSize = NumofChar + (NumofChar + 1) * 2; // Includes the NumofChar at the beginning of file

    // Get full bitstring of the file  (Reading in too many bits..)
    while (!fin.eof())
    {
        fin.read((char *) &reader, sizeof(unsigned short int)); // Read 16 bits
        bits += ToBitstring(reader);
        bitsRead += 16;
    }
    
    // Get the difference in bits from the file vs what is actually read, subtract
    // extra bits from output
    diffInBits = abs(bitsRead - totalBits);
    //cout << "TOTAL BITS IN FILE: " << totalBits << " | " << totalBits/4 << " bytes" <<  endl;
    //cout << "BITS READ: " << bitsRead << " | " << bitsRead/4 << " bytes" << endl;
    //cout << "DIFFERENCE: " << diffInBits << endl;
    //cout << "BITS BEFORE DELETION: " << bits << endl;
    bits.erase(bits.begin()+(totalBits-diffInBits), bits.end());
    //cout << "BITS AFTER DELETION: " << bits << endl;
    DecodeBitstring(bits, decodedBitstring, bytes);
    cout << "Wrote " << decodedBitstring.size();
    fout << decodedBitstring;
    fin.clear();
    return;
}

/***************************************************************************//**
 * @brief Makes a string representation of 4 bytes.                                                          
 ******************************************************************************/
string Huffman::ToBitstring(unsigned short int bits)
{
    unsigned short int bit;
    string bitstring = "";

    for (int i = 0; i < 16; i++)
    {
        bit = bits >> 15;
        bitstring += char(bit + 48);                                                                
        bits = bits << 1;
    }

    return bitstring;
}

/***************************************************************************//**
 * @brief Decodes a huffman-encoded bitstring                                                       
 ******************************************************************************/
void Huffman::DecodeBitstring(string bitstring, string &decoded, int &bytes)
{   
    Node *p = node;
    string::iterator c;

    for (c = bitstring.begin(); c != bitstring.end(); c++)
    {
	if(bytes == NumofBytes)
	{
	   return;
	}
	if (*c == '1')
            p = p->RightChild;
        if (*c == '0')
            p = p->LeftChild;

        if (p->LeftChild == nullptr && p->RightChild == nullptr)
        {
	    //Might have issue with eof or /n
            decoded += p->key;
            p = node;
	    bytes++;
	    /*for(auto q : CodeTable)
	    if(p->key == q.first)
	    {
	       bitstring.erase(0,q.second.size());
	       cout << "-> " << bitstring << endl;
	    }*/
        }
    }

    return;
}

/*
string Huffman::DecodeBitstring(string bitstring)
{   
    Node *p = node;
    string decoded = "";
    string::iterator c;

    for (c = bitstring.begin(); c != bitstring.end(); c++)
    {
        if (*c == '1')
            p = p->RightChild;
        if (*c == '0')
            p = p->LeftChild;

        if (p->LeftChild == nullptr && p->RightChild == nullptr)
        {
            //Might have issue with eof or /n
            decoded += p->key;
            p = node;
        }
    }

    return decoded;
}*/

/***************************************************************************//**
 * @brief Outputs the huffman table with histogram statistics to the screen.                                                     
 ******************************************************************************/
ostream& operator<<(ostream &os, Huffman obj)
{
    double prob = 0.00;
    os << fixed << setw(4) << setprecision(2) << setfill(' ');
    os << "Huffman Code Table" << endl;
    os << "------------------" << endl;
    os << "ASCII Code" << "\t   Probability (%)" << "\tHuffman Code" << fixed << setprecision(2) << endl;
    for (auto p : obj.CodeTable)
    {
        //prob = double(obj.Count(p.first));
        for (auto q : obj.OccurenceTable)
        {
            if(p.first == q.first)
            {
                prob = (double(q.second) / double(obj.NumofBytes)) * 100;
            }
        }
        //prob = 0 / obj.NumofBytes;
        if (p.first == '\n')
            os << int(p.first) << "   ( \\n )" << "\t\t" << prob << "%" << "\t\t   " << p.second << endl;
        else
            os << int(p.first) << "   ( " << p.first << " )" << "\t\t" << prob << "%" << "\t\t   " << p.second << endl;
        /*
           if (p.first == '\n')
           os << int(p.first) << "\t( \\n )"<< "\t\t\t\t" << 
        //double(obj.OccurenceTable[p.first]) / obj.NumofChar << "\t\t\t" <<
        p.second << endl;
        else
        os << int(p.first) << "\t( " << p.first << " )" << "\t\t\t\t" << 
        //double(obj.OccurenceTable[p.first]) / obj.NumofChar << "\t\t\t" <<
        p.second << endl;
        */
    }

    os << endl;

    return os;
}
