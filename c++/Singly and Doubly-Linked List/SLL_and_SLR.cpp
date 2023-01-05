// Singly-linked list and circular SLL members implemented using recursion

#include <iostream>

using namespace std;

class SLL {
    private:
        struct Node {
            Node* next;
            int data;
        };

    Node* head = nullptr;
    
    void removenLast(Node*& cur, int n);

    public:
        void insert(int what);
        void insertBefore(int chosen, int what);
        void removenLast(int n);
        void print() const;
};

void SLL::print() const {
    Node* tmp = head;

    while (tmp) {
        cout << tmp->data << " ";
        tmp = tmp->next;
    } cout << endl;
}

void SLL::insert(int what) {
    if (!head) {
        Node* tmp = new Node();
        tmp->data = what;
        tmp->next = head;
        head = tmp;
        return;
    }

    Node* cur = head;

    while (cur->next) {
        cur = cur->next;
    }

    Node* tmp = new Node();

    tmp->data = what;
    cur->next = tmp;
    tmp->next = nullptr;
}

void SLL::insertBefore(int chosen, int what) {
    if (!head) {
        Node* tmp = new Node();
        tmp->data = what;
        tmp->next = head;
        head = tmp;
    }

    Node* cur = head;
    Node* prev = cur;

    while (cur) {
        if (cur->data == chosen) {
            Node* temp = new Node();
            if (cur == head) {
                temp->data = what;
                temp->next = head;
                head = temp;
                return;
            }
            temp->data = what;
            temp->next = cur;
            prev->next = temp;
            cur = temp;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void SLL::removenLast(Node*& cur, int n) {
    if (!cur) return;

    removenLast(cur->next, n);

    static int occ = 0;

    if (occ < n) {
        Node* toDel = cur;
        cur = cur->next;
        occ++;
        delete toDel;
    }
}

void SLL::removenLast(int n) {
    return removenLast(head, n);
}

/****************************************/
/*******************************/

class SLR {
    private:
        struct Node {
            Node* next;
            int data;
        };

    Node* head = nullptr;
    
    void remove(Node*& cur, int what);

    public:
        void insert(int what);
        void remove(int what);
        void print() const;
};

void SLR::insert(int what) {
    if (!head) {
        Node* tmp = new Node();
        tmp->data = what;
        tmp->next = head;
        head = tmp;
        head->next = head;  //ring
        return;
    }

    Node* cur = head;

    while (cur->next != head)
        cur = cur->next;
    
    Node* tmp = new Node();
    tmp->data = what;
    cur->next = tmp;
    tmp->next = head;
}

void SLR::print() const {
    Node* tmp = head;

    do {
        cout << tmp->data << " ";
        tmp = tmp->next;
    } while (tmp != head);

    cout << endl;
}

void SLR::remove(Node*& cur, int what) {
    static Node* tail = new Node();
    if (cur->next == head)
        tail = cur;
    if (!cur || cur->next == head) return;
    
    remove(cur->next, what);

    if (cur->next->data == what) {     
        Node* toDel = cur->next;
        if (cur->next->next == head) {      // last node to be removed
            delete toDel;
            cur->next = head;
            return;
        }
        cur->next = cur->next->next;
        delete toDel;
        return;
    }
    if (cur == head && cur->data == what) { // first node to be removed
        Node* toDel = cur;
        tail->next = cur->next;
        delete toDel;
        head = tail->next;
        return;
    }
}

void SLR::remove(int what) {
    return remove(head, what);
}

int main()
{
    SLL list;

    list.insert(1);
    list.insert(2);
    list.insert(18);
    list.insert(7);
    list.print();

    list.insertBefore(2, 5);
    list.print();

    list.insertBefore(1, 16);
    list.print();
    
    list.removenLast(2);
    list.print();

    /****/ cout << endl << "Ring: " << endl; /*****/

    SLR ring;

    ring.insert(3);
    ring.insert(16);
    ring.insert(4);
    ring.insert(99);
    ring.print();

    ring.remove(3);
    ring.print();
}
