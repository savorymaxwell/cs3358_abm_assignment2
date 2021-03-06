// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     dynamic array whose size is stored in member variable
//     capacity; the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[capacity - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.
//
// DOCUMENTATION for private member (helper) function:
//   void resize(int new_capacity)
//     Pre:  (none)
//           Note: Recall that one of the things a constructor
//                 has to do is to make sure that the object
//                 created BEGINS to be consistent with the
//                 class invariant. Thus, resize() should not
//                 be used within constructors unless it is at
//                 a point where the class invariant has already
//                 been made to hold true.
//     Post: The capacity (size of the dynamic array) of the
//           invoking IntSet is changed to new_capacity...
//           ...EXCEPT when new_capacity would not allow the
//           invoking IntSet to preserve current contents (i.e.,
//           value for new_capacity is invalid or too low for the
//           IntSet to represent the existing collection),...
//           ...IN WHICH CASE the capacity of the invoking IntSet
//           is set to "the minimum that is needed" (which is the
//           same as "exactly what is needed") to preserve current
//           contents...
//           ...BUT if "exactly what is needed" is 0 (i.e. existing
//           collection is empty) then the capacity should be
//           further adjusted to 1 or DEFAULT_CAPACITY (since we
//           don't want to request dynamic arrays of size 0).
//           The collection represented by the invoking IntSet
//           remains unchanged.
//           If reallocation of dynamic array is unsuccessful, an
//           error message to the effect is displayed and the
//           program unconditionally terminated.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

void IntSet::resize(int new_capacity)
{
    // Confirm new capacity is valid. If it is then proceed to change
    // capacity to user specified value.
    if(new_capacity <=0){capacity = DEFAULT_CAPACITY;}
    else if(new_capacity < used ){capacity = used;}
    else{capacity = new_capacity;}

    // Create new dynamic array with specified capacity
    int* new_data = new int[capacity];

    // Copy current data to new dynamic array.
    for(int index = 0; index < used; ++index){
        new_data[index] = data[index];
    }

    // Deallocate the space used by previous data array.
    delete [] data;

    // Move new dynamic array back to private member data.
    data = new_data;
}

IntSet::IntSet(int initial_capacity) : capacity(initial_capacity), used(0)
{
    // Initialize capacity to user specified capacity, and test it
    // for validity. If it's invalid then set it to DEFAULT_CAPACITY
    // otherwise leave it as is.
    if(initial_capacity <= 0){capacity = DEFAULT_CAPACITY;}

    // Instantiate a new dynamic array of size capacity.
    data = new int[capacity];
}

IntSet::IntSet(const IntSet& src) : capacity(src.capacity), used(src.used)
{
    // Create a new dynamic array.
    data = new int[capacity];

    // Copy each item of the dynamic array.
    for(int index = 0; index < capacity; ++index)
        data[index] = src.data[index];
}

IntSet::~IntSet()
{
    // Deallocate any dynamically created variables.
    delete [] data;
    data = NULL;
}

IntSet& IntSet::operator=(const IntSet& rhs)
{
    // Self-assignment fail-safe. If invoking object
    // is the same as object being passed don't do
    // any work just pass back invoking object.
    if (this == &rhs)
        return *this;

    // Create temporary dynamic array to safely assign contents
    // of array.
    int* temp_data = new int[rhs.capacity];

    // Moved contents of rhs array to temp
    for (int index = 0; index < rhs.used; ++index) {
        temp_data[index] = rhs.data[index];
    }

    // Deallocate old dynamic array.
    delete [] data;

    // Start assigning member variables from rhs.
    data = temp_data;
    capacity = rhs.capacity;
    used = rhs.used;

    return *this;
}

int IntSet::size() const
{
    // Return the value of used which is
    // the number of elements in the array.
    return used;
}

bool IntSet::isEmpty() const
{
    // Empty if size() == 0, has unique int otherwise.
    return used == 0;
}

bool IntSet::contains(int anInt) const
{
    // Only traverse array if there are int's to check, otherwise
    // return false because there's no int's to compare with.
    if (used > 0){
        for(int index = 0; index < used; ++index)
            if(data[index] == anInt){ return true; }
    }
    return false;
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
    if(isEmpty()) {

        // Check to see if the invoking IntSet
        // is empty. If it is then return true.
        return true;

    } else {

        // Check otherIntSet against invoking intSet to
        // determine if it's a subset of otherIntSet. If
        // there's a mismatch abort and return false.
        for(int index = 0; index < used; index++){
            if(!otherIntSet.contains(data[index]))
                return false;
        }
        return true;
    }
}

void IntSet::DumpData(ostream& out) const
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
    IntSet unionIntSet = (*this); //Copy of invoking IntSet.

    int sizeOtherInt = otherIntSet.size(); // Keep size safe.

    // Loop through IntSet to be added to invoking set. If duplicate
    // elements found don't union, otherwise union unique elements.

    for (int index = 0; index < sizeOtherInt; ++index) {
        if(!unionIntSet.contains(otherIntSet.data[index]))
            unionIntSet.add(otherIntSet.data[index]);
    }
    return unionIntSet;
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
    IntSet interSet = (*this); // Create copy of invoking IntSet

    int sizeOtherInt = otherIntSet.size(); // Keep size safe.

    // Compare every item of invoking IntSet to otherIntSet
    // if no match is found then remove it from interSet.
    for (int index = 0; index < sizeOtherInt; index++) {
        if(!otherIntSet.contains(data[index])){
            interSet.remove(data[index]);
        }
    }
    return interSet;
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
    IntSet subSet = (*this); // Create copy of invoking IntSet.

    int sizeOtherInt = otherIntSet.size(); // Keep size safe.

    // If an element in intSet is also in otherSet then remove
    // it, otherwise keep elements in their respective sets.
    for(int index = 0; index < sizeOtherInt; ++index){
        if(subSet.contains(otherIntSet.data[index]))
            subSet.remove(otherIntSet.data[index]);
    }
    return subSet; // Return subtracted IntSet.
}

void IntSet::reset()
{
    // Reset intSet by reinitializing used to "0".
    used = 0;
}

bool IntSet::add(int anInt)
{

    // If anInt is unique then add it as the last element in the
    // data array and return true.
    if(!contains(anInt)){

        // If used == capacity or is above then we can't
        // add another item without resizing first.
        if(used >= capacity) {resize(int(capacity * 1.5) + 1);}

        // Regardless of resize add new item to dynamic
        data[used] = anInt;
        ++used;
        return true;
    }

    // No unique int's added to dynamic array return false.
    return false;
}

bool IntSet::remove(int anInt)
{
    // If the intSet has the requested element in the set then
    // remove it, and shift all elements to the left by one.
    if(contains(anInt)){
        for(int index = 0; index < used; ++index){
            if(data[index] == anInt) {
                for(int index2 = index; index2 < used - 1; ++index2) {
                    data[index2] = data[index2 + 1];
                }
                --used;
                return true; // Int removed successfully.
            }
        }
    }
    return false; // No int removed.
}

bool operator==(const IntSet& is1, const IntSet& is2) {

    // First check to see if both IntSet objects are empty,
    // if they are then is1 is a subset of is2. Otherwise
    // compare every element.
    if (is1.IntSet::isEmpty() && is2.IntSet::isEmpty()){
        return true;
    } else if(is1.IntSet::isSubsetOf(is2) && is2.IntSet::isSubsetOf(is1)){
        return true;
    }
    return false;
}
