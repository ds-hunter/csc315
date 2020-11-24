/**************************************************************************//**
 * @file heap.h
 *
 * @brief The header for the heap class
 *
 * @author: Anthony Benitez
 * @author: Daniel Hunter
 *
 * @par Class:
 * CSC315 Data Structures
 *
 * @date:   Fall 2020
 ******************************************************************************/
#ifndef __HEAP_H
#define __HEAP_H

#include <string.h>   // for memcpy
#include <exception>  // for exception
#include <algorithm>  // for swap
#include <iostream>   // for cout

//!struct Node
struct Node
{
    //!variable count
    int count;
    //!variable key
    char key;
    //!variable direction
    int direction;
    //!variable LeftChild
    Node *LeftChild = nullptr;
    //!variable RightChild
    Node *RightChild = nullptr;
};

/********************************************************************//**
 * @class MinHeap
 **********************************************************************/
//! MinHeap
class MinHeap
{
    //!variable capacity
    int capacity;
    //!variable Size
    int Size;
    //!variable items
    Node *items;

    // Helper functions for calculating children and parents
    //!Memberfunction getLeftChildIndex
    int getLeftChildIndex(int parentIndex) { return 2 * parentIndex ; }
    //!Memberfunction getRightChildIndex
    int getRightChildIndex(int parentIndex) { return 2 * parentIndex + 1 ; }
    //!Memberfunction getParentIndex
    int getParentIndex(int childIndex) { return childIndex / 2 ; }

    // Helper functions to answer questions about ancestors and descendants
    //!Memberfunction hasLeftChild
    bool hasLeftChild(int index) { return getLeftChildIndex(index) < Size ; }
    //!Memberfunction hasRightChild
    bool hasRightChild(int index) { return getRightChildIndex(index) < Size ; }
    //!Memberfunction hasParent
    bool hasParent(int index) { return getParentIndex(index) > 0 ; }

    // Helper functions to return values of parent and children
    //!Memberfunction leftChild
    int leftChild(int index) { return items[getLeftChildIndex(index)].count ; }
    //!Memberfunction rightChild
    int rightChild(int index) { return items[getRightChildIndex(index)].count ; }
    //!Memberfunction parent
    int parent(int index) { return items[getParentIndex(index)].count ; }

    // Increase the heap size when it is full
    //!Memberfunction growCapacity
    void growCapacity();
    // Swap items in the heap
    //!Memberfunction swap
    void swap(int, int);
    // Starting at the root, move an item down into the heap until it's right
    //!Memberfunction heapifyDown
    void heapifyDown();
    // Starting at the end of the heap, move an item up until it's right
    //!Memberfunction heapifyUp
    void heapifyUp();

    public:
    //!Constructor
    MinHeap(int cap = 256);
    //!Deconstructor
    ~MinHeap();

    // Check the top of the heap
    //!Memberfunction top
    Node* top();
    // Remove and return the top of the heap
    //!Memberfunction removeMin
    Node removeMin();
    // Add an item to the heap
    //!Memberfunction add(int,char)
    void add(int, char);
    //!Memberfunction add(Node, Node)
    void add(Node *, Node *);
    // Return the number of items in the heap
    //!Memberfunction size
    int size() const;

    //Sort
    //!Memberfunction sort
    Node *sort();
};
#endif
