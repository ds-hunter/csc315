/**************************************************************************//**
 * @file heap.cpp
 *
 * @brief The heap function file for the heap class
 *
 * @author: Anthony Benitez
 * @author: Daniel Hunter
 *
 * @par Class:
 * CSC315 Data Structures
 *
 * @date:   Fall 2020
 ******************************************************************************/
#include "heap.h"

/***************************************************************************//**
 * @brief Initialize the size and capacity of the heap
 ******************************************************************************/
MinHeap::MinHeap(int cap) : capacity(cap), Size(1)
{
    items = new Node[capacity];
//  memset(items, 0, capacity*sizeof(Node));
}

/***************************************************************************//**
 * @brief Cleans up dynamic memory on the way out
 ******************************************************************************/
MinHeap::~MinHeap()
{
    delete []items;
}

/***************************************************************************//**
 * @brief Special swap that deals with the heap array.  Swap items a
 * index1 and index2.
 *
 * @param [in] index1 - The first heap value to be swapped.
 * @param [in] index2 - The second heap value to be swapped.
 ******************************************************************************/
void MinHeap::swap(int index1, int index2)
{
    Node tmp = items[index1];
    items[index1] = items[index2];
    items[index2] = tmp;
}

/***************************************************************************//**
 * @brief Increase the size of the heap by 2x once the heap is full.
 ******************************************************************************/
void MinHeap::growCapacity()
{
    if (Size == capacity)
    {
        Node *newItems = new Node[capacity * 2];
        memcpy(newItems, items, capacity * sizeof(Node));
        capacity *= 2;
        delete []items;
        items = newItems;
    }
    return;
} 

/***************************************************************************//**
 * @brief Check the value at the top of the heap (minimum value).
 ******************************************************************************/
Node* MinHeap::top()
{
    if (Size == 1) throw new std::exception();
    return &items[1];
}

/***************************************************************************//**
 * @brief Remove the minimum value and re-establish the heap order.
 ******************************************************************************/
Node MinHeap::removeMin()
{
    if (Size == 1) throw new std::exception();
    Node item = items[1];

    items[1] = items[Size-1];
    Size--; 
    heapifyDown();
    return item;
}

/***************************************************************************//**
 * @brief Add an item to the heap at the bottom and percolate it to its correct
 * position in the heap.
 *
 * @param [in] item - the number/count of the char to establish the heap order.
 * @param [in] key - The character to be stored in node for the heap.
 ******************************************************************************/
void MinHeap::add(int item, char key)
{
    growCapacity();
    items[Size].count = item;
    items[Size].key = key;
    Size++;
    heapifyUp();
}

/***************************************************************************//**
 * @brief Add an item to the heap at the bottom and percolate it to its correct
 * position in the heap.
 *
 * @param [in] l - The left node to be merged into a singular node.
 * @param [in] r - The right node to be merged into a singular node.
 ******************************************************************************/
void MinHeap::add(Node *l, Node *r)
{
    growCapacity();
    items[Size].LeftChild = l;
    items[Size].RightChild = r;
    items[Size].count = l->count + r->count;
    Size++;
    heapifyUp();
}

/***************************************************************************//**
 * @brief Return the Size of the heap.
 ******************************************************************************/
int MinHeap::size() const
{
    return Size-1;
}

/***************************************************************************//**
 * @brief Start at the last item in the heap and percolate it up until it finds
 * its correct place in the heap.
 ******************************************************************************/
void MinHeap::heapifyUp()
{
    int index = Size - 1;
    while (hasParent(index) && parent(index) > items[index].count)
    {
        swap(getParentIndex(index), index);
        index = getParentIndex(index);
    }
}

/***************************************************************************//**
 * @brief Start at the root of the heap and percolate that item down until it is
 * in its correct position based on min heap order.
 ******************************************************************************/
void MinHeap::heapifyDown()
{
    int index = 1;
    bool notDone = true;

    while (hasLeftChild(index) && notDone)
    {
        notDone = false;
        int smallerChildIndex = getLeftChildIndex(index);
        if (hasRightChild(index) && rightChild(index) < leftChild(index))
            smallerChildIndex = getRightChildIndex(index);

        if (items[index].count > items[smallerChildIndex].count)
        {
            swap(index, smallerChildIndex);
            index = smallerChildIndex;
            notDone = true;
        }
    }
}

/***************************************************************************//**
 * @brief Sorts the heap into least to most.
 ******************************************************************************/
Node *MinHeap::sort()
{
    int count = Size;
    int i = 0;
    while(i < count- 1)
    {
        items[0] = removeMin();
        items[Size] = items[0];
        i++;
    }
    Size = count;

    return items;
}
