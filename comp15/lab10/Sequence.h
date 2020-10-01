#ifndef SEQUENCE_H
#define SEQUENCE_H
/*
 * A generic sequence/dynamic array/vector
 *
 * This code uses the C++11 function to_string() to convert
 * integers to strings.  MUST be compiled with C++11.
 *
 * Mark A. Sheldon, Tufts University
 * Spring 2015
 *
 * Change Log
 *      2016-03-19 [MAS] Used to_string() to throw an exception to
 *                       throw exception with helpful message
 *      2016-11-04 [MAS] Adapted for template lab:  
 *                       Renamed class to Sequence
 *                       Removed separate destroy()
 *                       Moved ensure_in_range() into class
 *                       Used STL max() algorithm
 *
 */

template<typename ElemType>
class Sequence {
public:
        Sequence(int initialCapacity);
        Sequence();
        ~Sequence();
        Sequence(const Sequence &old);
        Sequence(Sequence &&old);
        Sequence &operator=(const Sequence &rhs);
        Sequence &operator=(Sequence &&rhs);

        void         addAtBack(ElemType new_val);
        ElemType     get(int index);
        void         set(int index, ElemType new_val);
        ElemType    &operator[] (const int index);
        void         removeFromBack();
        int          size();

private:
        int       current_capacity, current_size;
        ElemType *data;

        void ensure_capacity(int desired_capacity);
        void ensure_in_range(int i, int lo, int hi);
        void copy_array(ElemType from[], ElemType to[], int length);
};

#include <stdexcept>
#include <string>
#include <algorithm>

using namespace std;
/*
 * Initialize an empty sequence of given initial capacity.
 */
template<typename ElemType>
Sequence<ElemType>::Sequence(int initialCapacity)
{
	current_size = 0;
	current_capacity = initialCapacity;
	data = new ElemType[current_capacity];
}

/*
 * Initialize an empty sequence of 0 capacity.
 */
template<typename ElemType>
Sequence<ElemType>::Sequence()
{
        current_capacity = 0;
        current_size     = 0;
        data             = NULL;
}

/*
 * Sets size and capacity to -1 to identify deleted sequences 
 * when debugging.
 */ 
template<typename ElemType>
Sequence<ElemType>::~Sequence()
{
        current_size = current_capacity = -1;
        delete [] data;
        data = NULL;
}

/*
 * Copy constructor
 */
template<typename ElemType>
Sequence<ElemType>::Sequence(const Sequence &old)
{
        current_capacity = old.current_capacity;
        current_size     = old.current_size;
        data             = new ElemType[current_capacity];

        copy_array(old.data, data, current_size);
}

/*
 * Copy move constructor
 */
template<typename ElemType>
Sequence<ElemType>::Sequence(Sequence &&old)
{
        current_capacity = old.current_capacity;
        current_size     = old.current_capacity;
        data             = old.data;

        old.current_capacity = old.current_size = 0;
        old.data = NULL;
}

/*
 * Assignment operator
 */
template<typename ElemType>
Sequence<ElemType> &Sequence<ElemType>::operator=(const Sequence &rhs)
{
        if (this == &rhs)
                return *this;          /* Ignore self assignment */

        current_capacity = rhs.current_capacity;
        current_size     = rhs.current_size;

        delete [] data;
        data = new ElemType[current_capacity];
        copy_array(rhs.data, data, current_size);

        return *this;
}

/*
 * Assignment move operator
 */
template<typename ElemType>
Sequence<ElemType> &Sequence<ElemType>::operator=(Sequence &&rhs)
{
        if (this == &rhs)
                return *this;          /* Ignore self assignment */

        delete [] data;

        current_capacity = rhs.current_capacity;
        current_size     = rhs.current_size;
        data             = rhs.data;

        rhs.current_capacity = rhs.current_size = 0;
        rhs.data = NULL;

        return *this;
}


template<typename ElemType>
int Sequence<ElemType>::size()
{
        return current_size;
}

/*
 * Subscript operator overload.
 * Returns reference to index-th slot in sequenceso client can 
 * update entry. 
 *
 * Note:
 *      Client should not save pointer or reference, because it will
 *      become stale when array changes capacity.
 */
template<typename ElemType>
ElemType &Sequence<ElemType>::operator[] (const int index)
{
        ensure_in_range(index, 0, current_size);
        return data[index];
}

/*
 * Return the index-th value in the vector.
 * Precondition:  There must be an index-th position.
 * Notes:  requires a copy constructor.
 */
template<typename ElemType>
ElemType Sequence<ElemType>::get(int index)
{
        return (*this)[index];
}

/*
 * Sets the index-th position of the vector to contain the new value.
 * Precondition:  There must be an index-th position.
 *
 * Notes:       * The sequence will not be grown to accommodate out of
 *                bounds indices.
 *              * If ElemType is a struct or class, it must have an
 *                assignment operator.
 */
template<typename ElemType>
void Sequence<ElemType>::set(int index, ElemType new_val)
{
        (*this)[index] = new_val;
}

/*
 * Add the new value as the last element of the sequence.
 * The vector's size increases by one.
 */
template<typename ElemType>
void Sequence<ElemType>::addAtBack(ElemType new_val)
{
	ensure_capacity(current_size+1);
	current_size++;
	set(current_size-1, new_val);

}

/*
 * Remove the last element of the sequence.
 */
template<typename ElemType>
void Sequence<ElemType>::removeFromBack()
{
	current_size--;
}

/*
 * Guarantees there are at least desired_capacity slots in the sequence
 */
template<typename ElemType>
void Sequence<ElemType>::ensure_capacity(int desired_capacity)
{
	if (desired_capacity < current_capacity)
	{
		current_capacity = 2*current_capacity + 2;
		ElemType *temp = new ElemType[current_capacity];
		copy_array(data, temp, current_size);
		data = temp;
	}
}

template<typename ElemType>
void Sequence<ElemType>::copy_array(ElemType from[], ElemType to[], int length)
{
        for (int i = 0; i < length; ++i)
                to[i] = from[i];
}

/* 
 * Guarantees that i is in [0, ..., hi)
 * Throws range_error exceiption if i is out of range
 */
template<typename ElemType>
void Sequence<ElemType>::ensure_in_range(int i, int lo, int hi)
{
        if ((i < lo) || (i >= hi)) {
                throw std::range_error(std::to_string(i) + " not in ["
                                       + std::to_string(lo) + ", "
                                       + std::to_string(hi) + ")");
        }
}

#endif
