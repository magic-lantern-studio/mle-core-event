/** @defgroup MleEventMgr Magic Lantern Event Manager Library API */

/**
 * @file MlePq.h
 * @ingroup MleEventMgr
 *
 * @author Mark S. Millard
 * @created November 15, 2018
 */

// COPYRIGHT_BEGIN
//
// The MIT License (MIT)
//
// Copyright (c) 2015-2019 Wizzer Works
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  For information concerning this header file, contact Mark S. Millard,
//  of Wizzer Works at msm@wizzerworks.com.
//
//  More information concerning Wizzer Works may be found at
//
//      http://www.wizzerworks.com
//
// COPYRIGHT_END

#ifndef __MLE_PQ_H_
#define __MLE_PQ_H_


// Include system header files.
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include <pthread.h>
#endif

// Include Magic Lantern header files.
#include "mle/mlTypes.h"

#include "mle/MleEventMgr.h"


typedef struct MLE_EVENTMGR_API mlePQItem
{
    int m_key;              // priority key
    void *m_data;           // associated data
} MlePQItem;

typedef MlBoolean (*MlePQCallback)(MlePQItem &item,void *clientData);


/**
 * MlePQ is a priority queue.
 */
class MLE_EVENTMGR_API MlePQ
{
  // Declare member variables.

  private:

    MlePQItem *m_fpqQueue;       // array of items in queue
    unsigned int m_fpqSize;      // size of queue
    unsigned int m_fpqNumItems;  // number of items in queue

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
    pthread_mutex_t m_mutex;
#endif

  public:

    /**
     * Default constructor.
     */
    MlePQ(void);

    /**
     * Constructor that takes an initial size.
     *
     * @param size The initial size to set the queue to.
     */
    MlePQ(unsigned int size);

    /**
     * The destructor.
     */
    virtual ~MlePQ(void);

    /**
     * @brief Insert a new item.
     *
     * This method will grow the queue if necessary.
     * Once extended, the queue will never shrink back to its original size
     * (it remains extended).
     *
     * @param item The item to insert into the queue.
     */
    virtual void insert(MlePQItem &item);

    /**
     * @brief Remove the highest priority item.
     *
     * If the action is successful,
     * "item" will contain the data referenced by the removed entry.
     *
     * @param item The output parameter containing the item
     * removed from the queue.
     *
     * @return If an item is successfully removed, then TRUE will be
     * returned. Otherwise, FALSE will be returned.
     */
    virtual MlBoolean remove(MlePQItem &item);

    /**
     * @brief Remove all items for specified priority.
     *
     * If the action is successful,
     * "items" will point to an array containing all data matching the
     * requested priority. It is the responsibility of the caller to
     * delete the returned array.
     *
     * @param priority The priority of the items which are to be removed.
     * @param items A pointer to an array of items that were removed, matching the
     * requested priority.
     * @param numItems A pointer to the number of items in the returned
     * array.
     *
     * @return If the items are successfully removed, then TRUE will be
     * returned. Otherwise, FALSE will be returned.
     */
    virtual MlBoolean remove(int priority, MlePQItem **items,
                             unsigned int *numItems);

    /**
     * @brief Replace the specified item.
     *
     * Replace the highest priority item with a new one (unless the new
     * item is of higher priority).
     *
     * @param item The new item to replace.
     *
     * @return If the item is successfully replaced, then TRUE will be
     * returned. Otherwise, FALSE will be returned.
     */
    virtual MlBoolean replace(MlePQItem &item);

    /**
     * @brief Delete the highest priority item.
     *
     * @return If the item is successfully deleted, then TRUE will be
     * returned. Otherwise, FALSE will be returned.
     */
    virtual void destroy(void);

    /**
     * @brief Delete all items with matching "priority".
     *
     * @param priority The matching priority to use to delete
     * an item from the queue.
     */
    virtual void destroy(int priority);

    /**
     * @brief Create a copy of the specified queue.
     *
     * @param queue A reference to the queue to copy. This queue
     * will be a replica of the copied queue.
     *
     * @return The number of items in the queue will be returned.
     */
    unsigned int copyQueue(MlePQItem **queue);

    /**
     * @brief Determine if an item with the specified "priority" is in
     * the queue.
     *
     * @param priority The priority it match.
     *
     * @return If an item exists in the queue with the matching priority,
     * then TRUE will be returned. Otherwise, FALSE will be returned.
     */
    virtual MlBoolean inQueue(int priority);

    /**
     * @brief Determine if a specified "item" is in the  queue.
     *
     * @param item A reference to the item to match.
     *
     * @return If the item exists in the queue, then TRUE will be
     * returned. Otherwise, FALSE will be returned.
     */
    virtual MlBoolean inQueue(MlePQItem &item);

#if defined(MLE_DEBUG)
    /**
     * @brief Print the queue.
     */
    void print(void);

    /**
     * @brief Print the queue - with sorted priorities.
     */
    void printSorted(void);
#endif /* MLE_DEBUG */

    /**
     * @brief Clear the queue.
     */
    virtual void clear(void);

    /**
     * @brief Find an item with specified priority.
     *
     * @param priority The priority to match.
     *
     * @return If an item is not found with a matching priority,
     * 0 will be returned. If an item is found with the matching
     * priority, then the item location within the queue, the index,
     * is returned.
     */
    virtual unsigned int findItem(int priority);

    /**
     * @brief Find an item in the queue matching another item.
     *
     * @param item A reference to the item to match.
     *
     * @return If an item is not found with the matching reference,
     * 0 will be returned. If an item is found with the matching
     * reference, then the item location within the queue, the index,
     * is returned.
     */
    virtual unsigned int findItem(MlePQItem &item);

    /**
     * @brief Find an item in the queue using a callback handler
     * to determine the criteria for selection.
     *
     * @param item A reference to the item to match.
     *
     * @return If an item is not found with the matching criteria,
     * 0 will be returned. If an item is found with the matching
     * criterua, then the item location within the queue, the index,
     * is returned.
     */
    virtual unsigned int findItem(MlePQCallback func,void *clientData);

    /**
     * @brief Delete an item located at the specified index.
     *
     * @param k The index of the item to delete.
     */
    virtual void destroyItem(unsigned int k);

    /**
     * @brief Change the priority of an item.
     *
     * @param k The index of the item in the queue to modify.
     * @param priority The new priority to use.
     *
     * @return If the item's priority is successfully updated,
     * then TRUE will be returned. Otherwise, FALSE will be returned.
     */
    virtual MlBoolean changeItem(unsigned int k,int priority);

    /**
     * @brief Peek into queue for specified item.
     *
     * @param k The index of the item to peek at.
     * @param item A reference to an item that will contain the
     * contents of the found item that is being peeked at.
     *
     * @return TRUE will be returned if an item is found in the
     * queue at the given index, k. If there is no item at index k,
     * then FALSE will be returned.
     */
    virtual MlBoolean peek(unsigned int k,MlePQItem &item);

    /**
     * @brief Get the number of items in the queue.
     *
     * @return The number of items in the queue will be returned.
     */
    inline unsigned int getNumItems(void);

    /**
     * @brief Join two priority queues into one larger one.
     */
    static MlePQ *join(MlePQ &pq1,MlePQ &pq2);

    /**
     * @brief Sort the specified queue.
     *
     * The resulting queue will be sorted from
     * lowest to highest priority (queue[0] = lowest priority item and
     * queue[numItems] = highest priority item).
     *
     * @param queue A pointer to the queue to sort.
     # @param numItems The number if items in the queue.
     */
    static void sort(MlePQItem *queue,int numItems);

    /**
     * @brief Overload assignment operator.
     *
     * @param queue A reference to a queue which will be assigned to this one.
     */
    void operator =(MlePQ &queue);

    /**
     * @brief Override operator new.
     *
     * @param tSize The size, in bytes, to allocate.
     */
    void* operator new(size_t tSize);

    /**
     * @brief Override operator delete.
     *
     * @param p A pointer to the memory to delete.
     */
    void  operator delete(void *p);

  protected:

    /**
     * @brief Extend the queue.
     *
     * The queue will grow by MLE_INC_QSIZE.
     *
     * @return If the successful, TRUE will be returned. Otherwise,
     * FALSE will be returned.
     */
    MlBoolean grow(void);

    /**
     * @brief Extend the queue.
     *
     * @param size The queue will grow by the specified size
     *
     * @return If the successful, TRUE will be returned. Otherwise,
     * FALSE will be returned.
     */
    MlBoolean grow(unsigned int size);

    /**
     * @brief Traverse through the heap from bottom to top,
     * reordering priorities.
     *
     * @param k The index location to begin reordering.
     */
    void upHeap(unsigned int k);

    /*
     * @brief Traverse through the heap from top to bottom,
     * reordering priorities.
     *
     * @param k The index location to beging reordering.
     */
    void downHeap(unsigned int k);

  private:

    MlBoolean _grow(unsigned int size);  // Grow queue by specified size.

};


// Define some useful macros.

#ifdef WIN32
#define MAXINT 32767
#endif /* WIN32 */
#ifdef __linux__
#define MAXINT INT_MAX
#endif /* __linux__ */
#define MLE_MAX_QPRIORITY MAXINT         // maximum priority
#define MLE_MIN_QPRIORITY ~MAXINT        // minimum priority
#define MLE_INC_QSIZE     64             // defualt size queue grows by


// Define inline methods.

inline unsigned int MlePQ::getNumItems(void)
{
    return(m_fpqNumItems);
}


#endif /* __MLE_PQ_H_ */
