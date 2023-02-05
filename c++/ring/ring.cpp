/* the source file ring.cpp */
// 02/2023

#include "ring.hpp"

int main()
{
    Ring<int, string> ring;     // int Key, string Info

    cout << "**Empty ring:**" << endl;
    cout << ring << endl;               // Print empty ring

/*--------------------------------------------------*/

    // Node insertion
    cout << "**Node insertion:**" << endl;
    ring.insert(ring.end(), 1, "Hello");
    ring.insert(ring.end(), 5, "world");
    ring.insert(ring.end(), 7, "heyy");
    ring.insert(ring.end(), 9, "Lorem ipsum");

    cout << ring << endl;

/*--------------------------------------------------*/

/*--------------------------------------------------*/

    // Node removal
    cout << "**Node removal with key '7'**" << endl;
    ring.remove(7, "heyy");     // Remove with key and info
    cout << ring << endl;

/*--------------------------------------------------*/

/*--------------------------------------------------*/

    // Insert node at a specific location
    auto itr = ring.begin();                // Point iterator to the beginning of the ring
    
    cout << "**Insert a node after the first element**" << endl;
    itr = ring.insert(itr, 2, "lab");       // Insert it after the first element
    cout << ring << endl;

    itr++;                                  // Points to 2

    cout << "**Insert a node after the second element**" << endl;
    ring.insert(itr, 3, "eads");            // Insert it after the second element
    cout << ring << endl;

/*--------------------------------------------------*/

/*--------------------------------------------------*/

    // Node removal with iterator
    cout << "**Node removal with iterator (last element):**" << endl;
    itr = ring.end();           // Again, point the iterator to the end of the ring
    ring.remove(itr);           // Remove with iterator (last element)

    cout << ring << endl;

    // Add a fifth element before the last node
    ring.insert(--ring.end(), 4, "test");

/*--------------------------------------------------*/

/*--------------------------------------------------*/

    // Ring with string Key and string Info

    Ring<string, string> ring3;

    cout << endl << "**Ring with string Key and string Info:**" << endl;
    ring3.insert(ring3.end(), "hello", "world!");
    ring3.insert(ring3.end(), "nO", "PrOBLEm");
    ring3.insert(ring3.end(), "134", "this is a string");
    cout << ring3 << endl;

    ring3.remove("hello", "WORLD");
    cout << ring3 << endl;

/*--------------------------------------------------*/


/*--------------------------------------------------*/

    cout << endl << "Final ring: " << endl << ring << endl;

    cout << endl << "*** External functions: ***" << endl;
    Ring<int, string> ring1;
    Ring<int, string> ring2;

    split_by_pos(ring, 1, true, 4, ring1, true, 2, ring2, false, 1);
    split_by_key(ring, 3, 1, true, 2, ring1, true, 2, ring2, true, 1);
}