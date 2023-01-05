/* Circular doubly-linked list */
/* the source file ring.cpp */

#include "ring.hpp"

template<typename Key, typename Info>
Ring<Key, Info>::~Ring() {          // Destructor for class Ring
    Node* tmp = start;
    Node* tail = new Node();

    do {
        tail = tmp;
        tmp = tmp->next;
    } while (tmp->next != start);

    tail = tail->next;

    if (start) {                    // is ring empty?
        Node* temp = tail;

        while (temp != start) {     // delete nodes until reaching the start node
            temp->next = start->next;
            delete start;
            start = temp->next;
        }
        if (temp == start) {        // one node left
            delete start;
            start = nullptr;
        }
    }
}


template<typename Key, typename Info>
void Ring<Key, Info>::remove(Key key, Info info) {  // Node removal by key and info
    if (!start) {
        cout << "Cannot remove, the ring is empty!" << endl;
        return;
    }
    Node* tmp = start;

    if (tmp->prev == tmp->next) {      // There is only one node in the ring
        start = nullptr;
        delete tmp;
        return;
    }

    if (tmp->key == key && tmp->info == info) {     // The ring has more than 1 node and
        Node* toDel = tmp;                          // the node to be removed is the first node
        tmp = start->prev;
        start = start->next;
        tmp->next = start;
        start->prev = tmp;
        delete toDel;
        return;
    }

    Node* last = tmp;

    while ((tmp->key != key) || (tmp->info != info)) {
        if (tmp->next == start) {
            cout << "**Cannot remove, the specified key and info do not exist!**" << endl;
            return;
        }
        last = tmp;
        tmp = tmp->next;
    }

    if (tmp->next == start) {       // If it is the last node
        Node* toDel = tmp;
        last->next = start;
        start->prev = last;
        delete toDel;
    }

    else {
        Node* toDel = tmp;
        tmp->next->prev = last;
        last->next = tmp->next;
        delete toDel;
    }
}

// For instance split_by_pos
//
// ring={1,}{2,}{3,}{4,}{5,}
// start_pos=1, direct=true, repetitions=4,
// direct1=true, len1=2,
// direct2=false, len2=1
//
// ring1={2,}{3,}{5,}{1,}{3,}{4,}{1,}{2,}
// ring2={3,}{5,}{2,}{4,}

template<typename Key, typename Info>
void split_by_pos (const Ring <Key, Info>& ring, int start_pos, bool direct, int repetitions, 
Ring <Key, Info>& ring1, bool direct1, int len1, 
Ring <Key, Info>& ring2, bool direct2, int len2)
{   
    if (start_pos < 1) {
        cout << "split_by_key failed, enter a valid start_pos value!" << endl;
        return;
    }

    auto itr = ring.begin();
    auto itr1 = (direct1 ? ring1.end() : ring1.begin());
    auto itr2 = (direct2 ? ring2.end() : ring2.begin());
    //ring1.insert(itr, ring.begin().m_itr->key, ring.begin().m_itr->info);

    for (int k = 0; k < start_pos; k++) {
        itr++;
    }

    for (int i = 0; i < repetitions; i++) {
        for (int j = 0; j < len1; j++) {
            ring1.insert(itr1, itr.getPtr()->key, itr.getPtr()->info);
            itr1 = (direct1 ? ring1.end() : ring1.begin());
            itr++;
        }
        for (int k = 0; k < len2; k++) {
            ring2.insert(itr2, itr.getPtr()->prev->key, itr.getPtr()->prev->info);
            itr2 = (direct2 ? ring2.end() : ring2.begin());
            itr++;
        }
    }
    cout << endl << "******" << endl << "split_by_pos (start_pos=" << start_pos << "): " << endl;
    cout << endl << "ring1: " << endl << ring1;
    cout << endl << "ring2: " << endl << ring2;
}

template<typename Key, typename Info>
void split_by_key (const Ring <Key, Info>& ring, const Key& start_key, int start_occurrence, bool direct, int repetitions, 
Ring <Key, Info>& ring1, bool direct1, int len1, 
Ring <Key, Info>& ring2, bool direct2, int len2)
{
    auto itr = ring.begin();
    auto itr1 = (direct1 ? ring1.end() : ring1.begin());
    auto itr2 = (direct2 ? ring2.end() : ring2.begin());
    //ring1.insert(itr, ring.begin().m_itr->key, ring.begin().m_itr->info);

    for (int k = 0; k < start_occurrence; k++) {
        if (itr.getPtr()->key == start_key)
            break;
        itr++;
    }

    for (int i = 0; i < repetitions; i++) {
        for (int j = 0; j < len1; j++) {
            ring1.insert(itr1, itr.getPtr()->key, itr.getPtr()->info);
            itr1 = (direct1 ? ring1.end() : ring1.begin());
            itr++;
        }
        for (int k = 0; k < len2; k++) {
            ring2.insert(itr2, itr.getPtr()->key, itr.getPtr()->info);
            itr2 = (direct2 ? ring2.end() : ring2.begin());
            itr++;
        }
    }
    cout << endl << "******" << endl << "split_by_key (key=" << start_key << "): " << endl;
    cout << endl << "ring1: " << endl << ring1;
    cout << endl << "ring2: " << endl << ring2;
}