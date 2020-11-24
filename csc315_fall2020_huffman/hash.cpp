/**************************************************************************//**
 * @file hash.cpp
 *
 * @brief The hash function file for the hash class
 *
 * @author: Anthony Benitez
 * @author: Daniel Hunter
 *
 * @par Class:
 * CSC315 Data Structures
 *
 * @date:   Fall 2020
 ******************************************************************************/
#include "hash.h"
#include <iostream>
#include <string>

using namespace std;

/***************************************************************************//**
 * @brief The constructor for the hash class. Sets all values in the hash table
 * to 0 by default.
 ******************************************************************************/
Hash::Hash()
{
    for (int i = 0; i < 255; i++)
    {
        hashTable[i] = 0;
    }
}

/***************************************************************************//**
 * @brief Increments the frequency of the character in the hash table.
 *
 * @param [in] b - The character to increase in the hash.
 ******************************************************************************/
int Hash::increment(char b)
{
    int i = int(b) % 255;
    hashTable[i] = hashTable[i] + 1;

    return hashTable[i];
}

/***************************************************************************//**
 * @brief Decrements the frequency of the character in the hash table.
 *
 * @param [in] b - The character to decrease in the hash.
 ******************************************************************************/
int Hash::decrement(char b)
{
    int i = int(b) % 255;
    hashTable[i] = hashTable[i] - 1;

    return hashTable[i];
}

/***************************************************************************//**
 * @brief Returns the frequency of the character in the hash table.
 *
 * @param [in] i - The int to access the specific array values
 ******************************************************************************/
int Hash::operator[](int i)
{
    return hashTable[i % 255];
}

/***************************************************************************//**
 * @brief Outputs the frequency of all characters in the hash table.
 *
 * @param [in/out] os - output operator
 * @param [in] obj - The character hash
 ******************************************************************************/
std::ostream& operator<<(std::ostream& os, Hash obj) {
    string character;
    cout << "ASCII Code" << endl;
    for (int i = 0; i < 255; i++)
    {
        if (obj[i] > 0)
        {
            character = char(i);
            if (character == "\n")
                character = "ENTER";
            cout << i << "\t" << "( " << character << " ) \tOccurences: "
                << obj[i] << endl; 
        }
    }
    return os;
}

/***************************************************************************//**
 * @brief Writes histogram to a file, char/frequency
 *
 * @param [in/out] out - ofstream for outputing the histogram
 ******************************************************************************/
void Hash::writeHistogram(std::ofstream &out) {
    for (int i = 0; i < 255; i++)
    {
        if (hashTable[i] > 0)
        {
	    //if there exists an occurence of the character then output the
	    //character and how many occurences
            out << char(i) << hashTable[i];
        }
    }
}

/***************************************************************************//**
 * @brief reads histogram to a huffman tree, char/frequency
 *
 * @param [in/out] int - ifstream for reading in the file
 ******************************************************************************/
int Hash::readHistogram(std::ifstream &in) {
    //Initialize variables
    int freq;
    char character;
    int count;
    int bytes = 0;
    //read in the first in which contains the number of characters there are
    in.read((char *) &count, sizeof(int));

    //while before the predetermined end of the histogram keep reading in the character
    //then the int
    while (in.tellg() != (unsigned int)((sizeof(int) + count * (sizeof(char) + sizeof(int)))))
    {
        in.read((char *) &character, sizeof(char));
        in.read((char*) &freq, sizeof(int));
        bytes += freq;
        hashTable[int(character)] = freq;
    }
    //return how many characters there are overall
    return bytes;
}

/***************************************************************************//**
 * @brief Returns the amount of items that have a frequency > 0 in the
 * hash table.
 ******************************************************************************/
int Hash::size()
{
    int size = 0;

    for (auto i : hashTable)
       if (i > 0) 
           size++;

    return size;
}
