/* the header file ring.hpp */
// 02/2023

#include <iostream>

using namespace std;

#ifndef RING
#define RING

template<typename Key, typename Info>
class Ring {
    private:
        struct Node {
            Key key;
            Info info;
            Node* prev;
            Node* next;
        };
    Node* start;
    
    void removeAll();

    public:
        Ring() { start = nullptr; }
        ~Ring() { removeAll(); }

        void remove(const Key& key, const Info& info);    // void remove(Node*& start, Key key, Info info);
        bool isEmpty(const Ring& r) const;

        class Iterator {
            friend class Ring;

            private:
                Node* m_itr;
                Node& operator*() { return *m_itr; }
                Node& operator*() const { return *m_itr; }
                Node* operator->() { return m_itr; }

                const Key& getKey(Node*& n) const { return n->key; }
                const Info& getInfo(Node*& n) const { return n->info; }

            public:
                Iterator() : m_itr(nullptr) {}
                Iterator(Node* ptr) : m_itr(ptr) {}
                //~Iterator() {}

                Iterator& operator++() {        // prefix
                    m_itr = m_itr->next;
                    return (*this);
                }
                
                Iterator operator++(int) {      // postfix
                    //Iterator tmp = *this;       // auto tmp = *this;
                    Iterator tmp = m_itr;
                    m_itr = m_itr->next;
                    return m_itr;
                }

                Iterator& operator--() {
                    m_itr = m_itr->prev;;
                    return *this;
                }
                
                Iterator operator--(int) {
                    /*Iterator tmp = *this;
                    (*this)--;*/
                    Iterator tmp = m_itr;
                    m_itr = m_itr->prev;
                    return tmp;
                }

                bool operator==(const Iterator& a) const { return (m_itr == a.m_itr); }

                bool operator!=(const Iterator& a) const { return (m_itr != a.m_itr); }

                const Key& getKey() { return getKey(m_itr); }

                const Info& getInfo() { return getInfo(m_itr); }

                void removeAll() { removeAll(m_itr); }
        }; // End of inner class Iterator

        Iterator begin() const {
            return Iterator(start);
        }
        Iterator end() const {
            return Iterator((start==nullptr ? start : start->prev));
        }

        Iterator insert(const Iterator& position, const Key& key, const Info& info) {
            if (position == nullptr) {         // empty ring
                Node* tmp = new Node();
                tmp->info = info;
                tmp->key = key;
                tmp->next = tmp->prev = tmp;
                start = tmp;
            }
            else {
                Node* tmp = new Node();
                tmp->key = key;
                tmp->info = info;

                position.m_itr->next->prev = tmp;
                tmp->next = position.m_itr->next;
                position.m_itr->next = tmp;
                tmp->prev = position.m_itr;
                //start = tmp;
            }
            return position;   
        }

        Iterator remove(Iterator position) {        // Node removal with iterators
            if (!position.m_itr) {                      // empty ring
                cerr << "Cannot remove, the ring is empty!" << endl;
            }
            else if (position.m_itr->prev == position.m_itr->next) {      // There is only one node in the ring
                Node* toDel = position.m_itr;
                position.m_itr = nullptr;
                delete toDel;
            }
            else if (position == this->begin()) {       // the node to be removed is the first node
                Node* tmp = position.m_itr;             
                Node* toDel = tmp;

                tmp = start->prev;
                start = start->next;
                tmp->next = start;
                start->prev = tmp;
                delete toDel;
            }
            else {
                Node* toDel = new Node();
                toDel = position.m_itr;
                position.m_itr->prev->next = position.m_itr->next;
                position.m_itr->next->prev = position.m_itr->prev;
                position.m_itr = position.m_itr->next;

                delete toDel;
            }

            return position;
        }

        friend ostream& operator<<(ostream &out, const Ring& r) {
            auto itr = r.begin(), end = r.end();

            if (!r.isEmpty(r)) {
                out << "The ring is empty!" << endl;
                return out;
            }

            out << "Traversal in forward direction: " << endl;
            do {
                out << itr.getKey() << "-" << itr.getInfo() << "  ";
                itr++;
            } while (itr != end);

            if (r.begin() != r.end()) {     // if the ring has more than one node
                out << itr.getKey() << "-" << itr.getInfo() << "  ";
            } out << endl;

            out << "Traversal in reverse direction: " << endl;
            do {
                out << itr.getKey() << "-" << itr.getInfo() << "  ";
                itr--;
            } while (itr != end);
            out << endl;
            
            return out;
        }
};

template<typename Key, typename Info>
bool Ring<Key, Info>::isEmpty(const Ring& r) const {
    if (!r.start)
        return false;
    return true;
}

template<typename Key, typename Info>
void Ring<Key, Info>::removeAll() {
    if (!start) {
        cerr << "Cannot removeAll, the ring is already empty!" << endl;
        return;
    }

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
void Ring<Key, Info>::remove(const Key& key, const Info& info) {  // Node removal by key and info
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
            cout << "Cannot remove, the specified key = '" << key << "' and info = '" << info << "' do not exist!" << endl;
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
void split_by_pos (const Ring <Key, Info>& ring, unsigned int start_pos, bool direct, unsigned int repetitions, 
Ring <Key, Info>& ring1, bool direct1, unsigned int len1, 
Ring <Key, Info>& ring2, bool direct2, unsigned int len2)
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
            ring1.insert(itr1, itr.getKey(), itr.getInfo());
            itr1 = (direct1 ? ring1.end() : ring1.begin());
            itr++;
        }
        for (int k = 0; k < len2; k++) {
            ring2.insert(itr2, itr.getKey(), itr.getInfo());
            itr2 = (direct2 ? ring2.end() : ring2.begin());
            itr++;
        }
    }
    cout << endl << "******" << endl << "split_by_pos (start_pos=" << start_pos << "): " << endl;
    cout << endl << "ring1: " << endl << ring1;
    cout << endl << "ring2: " << endl << ring2;
}

template<typename Key, typename Info>
void split_by_key (const Ring <Key, Info>& ring, const Key& start_key, unsigned int start_occurrence, bool direct, unsigned int repetitions, 
Ring <Key, Info>& ring1, bool direct1, unsigned int len1, 
Ring <Key, Info>& ring2, bool direct2, unsigned int len2)
{
    auto itr = ring.begin();
    auto itr1 = (direct1 ? ring1.end() : ring1.begin());
    auto itr2 = (direct2 ? ring2.end() : ring2.begin());
    //ring1.insert(itr, ring.begin().m_itr->key, ring.begin().m_itr->info);

    for (int k = 0; k < start_occurrence; k++) {
        if (itr.getKey() == start_key)
            break;
        itr++;
    }

    for (int i = 0; i < repetitions; i++) {
        for (int j = 0; j < len1; j++) {
            ring1.insert(itr1, itr.getKey(), itr.getInfo());
            itr1 = (direct1 ? ring1.end() : ring1.begin());
            itr++;
        }
        for (int k = 0; k < len2; k++) {
            ring2.insert(itr2, itr.getKey(), itr.getInfo());
            itr2 = (direct2 ? ring2.end() : ring2.begin());
            itr++;
        }
    }
    cout << endl << "******" << endl << "split_by_key (key=" << start_key << "): " << endl;
    cout << endl << "ring1: " << endl << ring1;
    cout << endl << "ring2: " << endl << ring2;
}

#endif