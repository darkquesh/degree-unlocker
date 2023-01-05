/* Circular doubly-linked list */
/* ring_test.cpp test driver file for Ring */

#include "ring.hpp"
#include "ring.cpp"

int main()
{
    Ring<int, string> ring;     // int Key, string Info

    cout << ring;               // Print empty ring

    ring.insert(ring.end(), 1, "Hello");
    ring.insert(ring.end(), 5, "world");
    ring.insert(ring.end(), 7, "heyy");
    ring.insert(ring.end(), 9, "Lorem ipsum");

    cout << ring;

    ring.remove(7, "heyy");     // Remove with key and info

    auto itr = ring.begin();                // Point iterator to the beginning of the ring
    itr = ring.insert(itr, 2, "lab");       // Insert it after the first element
    itr++;                                  // Points to 2
    ring.insert(itr, 3, "eads");            // Insert it after the second element

    cout << endl << ring;

    itr = ring.end();           // Again, point the iterator to the beginning of the ring
    ring.remove(itr);           // Remove with iterator (1st element)

    cout << endl << "Final ring: " << endl << ring << endl;

    ////////////

    Ring<int, string> ring1;
    Ring<int, string> ring2;

    split_by_pos(ring, 1, true, 4, ring1, true, 2, ring2, false, 1);
    split_by_key(ring, 3, 1, true, 2, ring1, true, 2, ring2, true, 1);
}