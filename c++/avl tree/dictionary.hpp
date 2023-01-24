/* the header file dictionary.hpp */
// darkquesh - 24/01/23

#ifndef DICTIONARY
#define DICTIONARY

#include <iostream>
#include <fstream>      // for processing files (i/o)
//#include "ring.hpp"     // custom library for the external function Ring<int, string> Listing(const Dictionary<string, int>&)
//#include <type_traits>  // for comparing template types, used in checkKey()

using namespace std;

static bool found = false;
static bool didCounterExec = false;     // for insertNode function so that it does not print an error
                                        // when inserting duplicate nodes in the external function Counter

template <typename Key, typename Info>
class Dictionary {      // AVL Tree
    private:
        struct Node {
            Node* left;
            Node* right;
            Key key;
            Info info;
            short int height;

            Node() {};
            Node(const Key& k, const Info& i) : key(k), info(i), left(nullptr), right(nullptr), height(1) {};
        };
        Node* root;

        short int max(const short int x, const short int y) { return (x > y) ? x : y; }
        short int height (Node*& r);
        unsigned int nodeCount = 0;
        //bool checkKey() const;
        void removeAll(Node*& r);
        short int getBalanceFactor(Node*& r);
        void updateNodeByKey(Node*& r, const Key& k, Info i);
        void increaseOcc(Node*& r, Key& k, unsigned int& infoVal);
        void getCount(Node*& r);

        // insertNode
        Node* insertNode(Node*& r, const Key& k, const Info& i) {
            if (!r) {
                r = new Node(k, i);
                return r;
            }

            if (k < r->key)
                r->left = insertNode(r->left, k, i);
            else if (k > r->key)
                r->right = insertNode(r->right, k, i);
            else {
                if (!didCounterExec)    // if the external function Counter is not executed, print error prompt
                    cerr << "Specified node with key: " << k << " and info: " << i << " already exists! Please enter another item." << endl;
                return r;
            }

            r = balanceTree(r);
            return r;
        } // insertNode ends

        // print
        void print(Node*& r, string tr) const {
            if (!root) {
                cerr << "Tree is empty!" << endl;
                return;
            }

            if (tr == "in" || tr == "IN") {             // in-order traversal
                if (!r) return;

                print(r->left, tr);
                cout << r->key << "-" << r->info << endl;
                print(r->right, tr);
            }

            else if (tr == "pre" || tr == "PRE") {      // pre-order traversal
                if (!r) return;

                cout << r->key << "-" << r->info << endl;
                print(r->left, tr);
                print(r->right, tr);
            }

            else if (tr == "post" || tr == "POST") {    // post-order traversal
                if (!r) return;
                
                print(r->left, tr);
                print(r->right, tr);
                cout << r->key << "-" << r->info << endl;
            }
            else
                cerr << "Please specify a valid traversal: 'in', 'pre' or 'post'" << endl;
        } // print ends

        // spacing
        void spacing(const unsigned short int size) {
            for (int i = 1; i < size; i++)
                cout << "\t";
        } // spacing ends

        // sketch
        void sketch(Node*& r) {
            if (!root) {
                cerr << "The tree is empty!" << endl;
                return;
            }

            static int size = 0;

            if (!r) return;
            size++;

            sketch(r->right);
            spacing(size);
            cout << r->key << "-" << r->info << endl;
            sketch(r->left);
            size--;
        } // sketch ends

        // removeNode
        Node* removeNode(Node*& r, const Key& k) {
            if (!r) {
                //cerr << "The tree is empty!" << endl;
                return r;
            }
            
            static Node* parent = new Node();
            found = false;            
            
            if (k < r->key) {
                parent = r;
                r->left = removeNode(r->left, k);
            }
            else if (k > r->key) {
                parent = r;
                r->right = removeNode(r->right, k);
            }

            else if (k == r->key) {
                if (!r->left || !r->right) {        // Leaf node or node with only 1 child
                    Node* subtree = r->left ? r->left : r->right;       

                    if (!subtree) r = nullptr;      // Node is a leaf 
                    else if (parent->left == r) parent->left = subtree;     // Left child
                    else parent->right = subtree;                           // Right child
                    
                    found = true;
                    r = nullptr;
                    delete r;
                    
                    return subtree;
                }
                else {     //else if (r->left && r->right)
                    // Parent node with 2 child nodes
                    Node* r_min = r->right;
                    parent = r;

                    while (r_min->left) {      // Descend left to find the min valued key
                        parent = r_min;
                        r_min = r_min->left;
                    }

                    r->key = r_min->key;
                    r->info = r_min->info;
                    r->right = removeNode(r->right, r->key);
                }
            }

            if (!found && (r == root)) 
                cerr << "Specified node with key: '" << k << "' does not exist! Please change the key." << endl;
            
            r = balanceTree(r);
            return r;
        } // removeNode ends
        
        // rotate
        Node* rotate(Node*& r, const char* rot) {    // rot value should be "l" or "r"
            Node* tmp = new Node();
            
            if (rot == "l") {
                //cout << "\t\t\t\t> Left rotation" << endl;
                tmp = r->right;
                Node* tmp_l = tmp->left;

                tmp->left = r;
                r->right = tmp_l;

                r->height = max(height(r->left), height(r->right)) + 1;
                tmp->height = max(height(tmp->left), height(tmp->right)) + 1;

                return tmp;
            }
            else if (rot == "r") {
                //cout << "\t\t\t\t> Right rotation" << endl;
                tmp = r->left;
                Node* tmp_r = tmp->right;
                
                tmp->right = r;
                r->left = tmp_r;

                r->height = max(height(r->left), height(r->right)) + 1;
                tmp->height = max(height(tmp->left), height(tmp->right)) + 1;

                return tmp;
            }
            else {
                cerr << "Not a valid rotation, please select 'l' or 'r'!" << endl;
                return r;
            }
        } // rotate ends

        // balanceTree
        Node* balanceTree(Node*& r) {
            if (!r) return r;

            r->height = max(height(r->left), height(r->right)) + 1;

            if (getBalanceFactor(r) == 2) {
                if (getBalanceFactor(r->left) >= 0)
                    r = rotate(r, "r");     // Right Rotation
                else {      // Left-Right Rotation
                    r->left = rotate(r->left, "l");
                    return rotate(r, "r");
                }
            }
            else if (getBalanceFactor(r) == -2) {
                if (getBalanceFactor(r->right) <= 0)
                    r = rotate(r, "l");     // Left Rotation
                else {      // Right-Left Rotation
                    r->right = rotate(r->right, "r");
                    return rotate(r, "l");
                }
            }
            return r;
        } // balanceTree ends

        // copyNodes
        Node* copyNodes(Node* r) {
            if (!r) return nullptr;

            Node* copied = new Node(r->key, r->info);
            copied->left = copyNodes(r->left);
            copied->right = copyNodes(r->right);

            return copied;
        } // copyNodes ends

        // search
        Node* search (Node*& r, const Key& k, bool& found, Node*& nodeFound) {
            found = false;
            if (!r) return r;

            if (k < r->key)
                r->left = search(r->left, k, found, nodeFound);
            else if (k > r->key)
                r->right = search(r->right, k, found, nodeFound);
            else if (k == r->key) {
                found = true;
                if (!didCounterExec)
                    cout << "The node with key: '" << r->key << "' and info: '" << r->info << "' has been found!" << endl;
                nodeFound = r;
                return r;
            }
            return r;
        } // search ends

    public:
        Dictionary() { root = nullptr; }
        ~Dictionary() { removeAll(); }
        void insertNode(const Key& k, const Info& i);
        void removeNode(const Key& k);
        void removeAll();
        void print(string tr = "in");       // default: in-order traversal
        void sketch();
        void getCount();
        bool search(const Key& k);
        void updateNodeByKey(const Key& k, Info i);
        unsigned int increaseOcc(Key& k);
        
        Dictionary& operator=(const Dictionary& dict);
};

template <typename Key, typename Info>
short int Dictionary<Key, Info>::height (Node*& r) {
    if (!r) return 0;
    return r->height;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::insertNode(const Key& k, const Info& i) {
    insertNode(root, k, i);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::print(string tr) {
    print(root, tr);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::sketch() {
    sketch(root);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::removeNode(const Key& k) {
    removeNode(root, k);
    if (found) 
        cout << "The node with key: '" << k << "' is removed" << endl;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::removeAll(Node*& r) {
    if (r) {
        removeAll(r->left);
        removeAll(r->right);
        r = nullptr;
        delete r;
    }
    else return;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::removeAll() {
    if (root)
        removeAll(root);
}

template <typename Key, typename Info>
short int Dictionary<Key, Info>::getBalanceFactor(Node*& r) {      // Left - Right subtree height convention
    if (!r) return 0;
    else {
        short int l_h = height(r->left);
        short int r_h = height(r->right);
        short int b_fac = l_h - r_h;

        return b_fac;
    }
}

template <typename Key, typename Info>
Dictionary<Key, Info>& Dictionary<Key, Info>::operator=(const Dictionary<Key, Info>& dict) {
    removeAll(root);
    root = copyNodes(dict.root);
    return *this;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::getCount(Node*& r) {
    if (!r) return;

    getCount(r->left);
    getCount(r->right);
    nodeCount++;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::getCount() {
    getCount(root);
    cout << "There are " << nodeCount << (didCounterExec ? " words." : " nodes.") << endl; 
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::search(const Key& k) {
    Node* nodeFound = nullptr;
    bool found = false;
    search(root, k, found, nodeFound);
    if (!found && !didCounterExec) cerr << "Specified node with key '" << k << "' was not found! Please change the key." << endl;
    return found;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::updateNodeByKey(Node*& r, const Key& k, Info i) {
    bool found = false;
    didCounterExec = true;      // to not to trigger the error prompt in search()

    Node* nodeFound = nullptr;
    search(r, k, found, nodeFound);

    if (found)                  // if the node is found
        nodeFound->info = i;    // change its info
    else
        cerr << "The node with key '" << k << "' does not exist, please change the value!" << endl;

    didCounterExec = false;     // reset val
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::updateNodeByKey(const Key& k, Info i) {
    updateNodeByKey(root, k, i);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::increaseOcc(Node*& r, Key& k, unsigned int& infoVal) {
    bool found = false;

    Node* nodeFound = nullptr;
    search(r, k, found, nodeFound);

    if (found) {                  // if the node is found
        nodeFound->info++;    // change its info
        infoVal = nodeFound->info;
    }
    else
        cerr << "Cannot increaseOcc, the node with key '" << k << "' does not exist, please change the value!" << endl;
}

template <typename Key, typename Info>
unsigned int Dictionary<Key, Info>::increaseOcc(Key& k) {
    unsigned int infoVal = 0;
    increaseOcc(root, k, infoVal);
    return infoVal;
}


/* External functions */

// Function #1
// This function creates a Dictionary of words read from the text file
// together with the word occurrence count, ordered lexically

Dictionary<string, int> Counter(const string& filename)     // case insensitive as dictionaries are
{   
    ifstream myFile(filename);
    Dictionary<string, int> dict;

    if (!myFile.is_open()) {
        cerr << "Cannot open the file: " << filename << endl;
        return dict;
    }
    
    unsigned int count = 1;     // Number of word occurrence
    string word;                // Whole words
    char c;                     // Single character
    didCounterExec = true;      // for insertNode function so that it does not print an error when inserting duplicate nodes

    while (!myFile.eof()) {     // Read characters from file until EOF
        while (!myFile.eof()) {
            c = myFile.get();
            if ((c>='a' && c<='z') || (c>='A' && c<='Z')) {     // If the character is a letter
                if (c>='A' && c <= 'Z') c += 32;        // ASCII conversion - if the first character is upper case; convert it to lower case
                word = c;                                       // assign the first letter to word
                c = '\0';
                break;      // run this block until the first character of a word is read
            }
        }
        while (!myFile.eof()) {
            c = myFile.get();
            if ((c>='a' && c<='z') || (c>='A' && c<='Z')) {
                word += c;                                      // Append the remaining characters until word is read
                c = '\0';
            }
            else
                break;
        }

        if (c == -1) return dict;       // return dict if a new line is detected at EOF 

        if (dict.search(word))          // if there is a duplicate word
            count = dict.increaseOcc(word);     // Increase the occurrence count 
        dict.insertNode(word, count);           // Insert string word and int count into the tree

        count = 1;      // Reset counter
        word = "";      // reset word in case of a garbage value
    }
    
    return dict;
}


// Function #2 - (optional task)
// The function "listing" creates a Ring of words from a Dictionary
// ordered by the word occurrence count, moreover words with the same counter
// should be ordered lexically within the listing

/*Ring<int, string> Listing(const Dictionary<string, int>& dict)  // !!! NOT complete !!!!
{
    Ring<int, string> ring;


    return ring;
}*/


#endif