/* the source file dictionary.cpp */

#include "dictionary.hpp"

int main()
{
    Dictionary<int, string> tree;

    tree.print(); cout << endl;

    /* Inserting nodes */
    tree.insertNode(3, "hello");
    tree.insertNode(5, "hey");
    tree.insertNode(2, "asd");
    tree.insertNode(4, "eads");
    tree.insertNode(1, "try");
    tree.insertNode(7, "test");
    tree.insertNode(15, "mc");

/*-------------------------------------------*/

    /* Traversals */
    // In-Order Traversal
    cout << "In-order Traversal: " << endl;
    tree.print("in"); cout << endl;             // or tree.print();
    
    // Pre-Order Traversal
    cout << "Pre-order Traversal: " << endl;
    tree.print("pre"); cout << endl;

    // Post-Order Traversal
    cout << "Post-order Traversal: " << endl;
    tree.print("post"); cout << endl;

/*-------------------------------------------*/

    /* Drawing tree */
    cout << "**Tree**" << endl;
    tree.sketch(); cout << endl;

    // Node count
    tree.getCount(); cout << endl;

/*-------------------------------------------*/

/*-------------------------------------------*/

    /* Update the Info of a node */
    cout << "-- Updating node with key '7' --" << endl;
    tree.updateNodeByKey(7, "baby");
    tree.sketch(); cout << endl;

/*-------------------------------------------*/   

/*-------------------------------------------*/

    /* Insert a node that would make the tree unbalanced */
    cout << "-- Balancing tree... --" << endl;
    tree.insertNode(8, "os");
    cout << "**Tree**" << endl;
    tree.sketch(); cout << endl;

/*-------------------------------------------*/

    /* Assignment operator */
    Dictionary<int, string> tree2;
    cout << "-- Assignment operator: tree2 = tree --" << endl;
    tree2 = tree;
    cout << "**Tree2**" << endl;
    tree2.sketch(); cout << endl;

/*-------------------------------------------*/

    /* Node removal */
    // Removing a leaf node
    cout << "-- Removing a leaf node: --" << endl;
    tree.removeNode(4, "eads");
    cout << "**Tree**" << endl;
    tree.sketch(); cout << endl;

    // Removing a node with one child
    cout << "-- Removing node with only 1 child: --" << endl; //tree.insertNode(4, "eads");  // re-insert node
    tree.removeNode(2, "asd");
    tree.sketch(); cout << endl;

    // Removing a node with 2 children
    cout << "-- Removing node with 2 children: --" << endl; //tree.insertNode(2, "asd");   // re-insert node
    tree.removeNode(8, "os");
    tree.sketch(); cout << endl;

    // Removing the root node
    cout << "-- Removing the root node: --" << endl; //tree.insertNode(8, "os");   // re-insert node
    tree.removeNode(5, "hey");
    tree.sketch(); cout << endl;

/*-------------------------------------------*/

    /* Remove all nodes */
    cout << "-- Removing all nodes from tree --" << endl;
    tree.removeAll();
    tree.print(); cout << endl;

    // Restore tree
    tree = tree2;

/*-------------------------------------------*/    

    /* Creating a tree object whose key is not a number */
    Dictionary<string, string> tree3;
    cout << "Dictionary<string, string> tree3: " << endl;
    tree3.insertNode("bt", "bb");
    tree3.insertNode("cd", "ae");
    tree3.insertNode("ax", "3");
    tree3.insertNode("ww", "lorem");
    tree3.sketch(); cout << endl;

/*-------------------------------------------*/

    /* External function - Counter */
    Dictionary<string, int> tree4;

    string filename = "words.txt";
    tree4 = Counter(filename); cout << endl;

    cout << "**Tree4**" << endl;
    tree4.sketch(); cout << endl;
    tree4.print(); cout << endl;

    // On the Origin of Species, by Charles Darwin text file
    Dictionary<string, int> tree5;

    string filename2 = "On the Origin of Species, by Charles Darwin.txt";
    tree5 = Counter(filename2); cout << endl;

    cout << "**Tree5**" << endl;
   // tree5.print(); cout << endl;      // --uncomment this line to proceed testing--
   // tree5.sketch(); cout << endl;       // --uncomment this line to proceed testing--
    tree5.getCount(); cout << endl;


    /* External function - Listing */
    //Ring<int, string> ring = Listing(tree4);
    //cout << ring << endl;

}