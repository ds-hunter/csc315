/**************************************************************************//**
 * @file hash.h
 *
 * @brief The header for the hash class
 *
 * @author: Anthony Benitez
 * @author: Daniel Hunter
 *
 * @par Class:
 * CSC315 Data Structures
 *
 * @date:   Fall 2020
 ******************************************************************************/
#ifndef __HASH_H
#define __HASH_H

#include <vector>
#include <ostream>
#include <fstream>

/***************************************************************************//**
 * @class Hash
 *
 * @brief The class for the direct hash table for ascii values in the range
 * 0-255.
 ******************************************************************************/
//! Hash
class Hash {
    private:
	// actual table for the hash
	//!variable hashTable
        int hashTable[255];
    public:
	//!Constructor
        Hash();
	//!Memberfunction for increment
        int increment(char b);
	//!Memberfunction for decrement
        int decrement(char b);
	//!Memberfunction for overload
        int operator[](int i);
	//!Memberfunction for Writing Histogram
        void writeHistogram(std::ofstream &out);
	//!Memberfunction for Reading Histogram
        int readHistogram(std::ifstream &in);
	//!Memberfunction for Output overload
        friend std::ostream& operator<<(std::ostream& os, Hash obj);
	//!Memberfunction for size
        int size();
};

#endif
