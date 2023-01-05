/* Circular doubly-linked list */
/* the header file ring.hpp */

#include <iostream>
#include <string>

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

    public:
        Ring() : start(nullptr) {};
        ~Ring();

        class Iterator {
            friend class Ring;

            protected:
                Iterator(Node* ptr) : m_itr(ptr) {}
                Node* m_itr = new Node();
                Node& operator*() { return *m_itr; }
                Node& operator*() const { return *m_itr; }
                Node* operator->() { return m_itr; }

            public:
                using iterator_category = bidirectional_iterator_tag;
                using value_type = Node;
                using difference_type = ptrdiff_t;
                //using pointer = Node*;
                //using reference = Node&;

                Iterator() : m_itr(nullptr) {}
                ~Iterator() {}
                

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

                bool operator==(const Iterator& a) const {
                    return (m_itr == a.getConstPtr());
                }

                bool operator!=(const Iterator& a) const {
                    return (m_itr != a.getConstPtr());
                }

                Node* getPtr() const {
                    return m_itr;
                }

                const Node* getConstPtr() const {
                    return m_itr;
                }
        }; // End of inner class Iterator

        Iterator begin() const{
            return Iterator(start);
        }
        Iterator end() {
            return Iterator((start==nullptr ? start : start->prev));
        }

        Iterator insert(Iterator position, const Key& key, const Info& info) {
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
                cout << "Cannot remove, the ring is empty!" << endl;
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

        void remove(Key key, Info info);    // void remove(Node*& start, Key key, Info info);

        friend ostream& operator<<(ostream &out, Ring& r) {
            auto itr = r.begin(), end = r.end();

            if (!itr.getPtr()) {
                out << "The ring is empty!" << endl;
                return out;
            }

            out << "Traversal in forward direction: " << endl;
            do {
                auto i = *itr.getPtr();
                out << i.key << "-" << i.info << " ";
                itr++;
            } while (itr != end);

            if (r.begin() != r.end()) {     // if the ring has more than one node
                auto i = *itr.getPtr();
                out << i.key << "-" << i.info << " ";
            } out << endl;

            out << "Traversal in reverse direction: " << endl;
            do {
                auto i = *itr.getPtr();
                out << i.key << "-" << i.info << " ";
                itr--;
            } while (itr != end);
            out << endl;
            
            return out;
        }
};

#endif