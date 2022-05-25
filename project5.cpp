// Fall 2021 Computing Structures
// Project 5

#include<iostream>

//This is Ramkishore Rao's DSA5005 Project 5

using namespace std;

class Tree {
	friend ostream& operator<<(ostream& o, Tree& tree);	// ostream operator which prints the parent array
protected:
	int* parentArray;									// The parentArray that stores the parents of not i
	int _size;											// The size of the parentArray
public:
	Tree();												// Default Constructor
	Tree(int size);										// Non - Default constructor
	Tree(Tree& anotherTree);							// Copy Constructor
	~Tree();											// Destructor
	int getSize() ;										// Get the size of the parentArray
	int* getParentArray() ;								// Get the parentArray
	int LCA(int firstNode, int secondNode);				// Returns the least common ancestor given two nodes
	int parent(int i);									// Get the parent of node i
	void children(int i);								// Prints the children of node i	
	void siblings(int i);								// Prints the siblings of node i
	int root();											// Get the root of the tree
	void setParent(int node, int parent);				// Set the parent of the node 
	void nodesAtLevel(int i);							// Give the nodes at level i
	int level(int i);									// Get the level of node i
	int height();										// Get the hight of the tree
	void preorder();									// Give the Preorder traversal of the tree
	bool isLeaf(int k);									// check if it is a leaf node
	void recursivepreorder(int i);                      // recursive preorder method
};
// the below is a default constructor for Class Tree
Tree::Tree()
{
	parentArray = NULL;//pointer to 1D array set to null
	_size = 0;//array is set to size 0
}

// the below is code for non default constructor
Tree::Tree(int size)
{
	_size = size;
	parentArray = new int [_size];//1D array set to size of array passed in from main
	for (int l = 0; l < _size; l++) {
		parentArray[l] = -1;// elements of array initialized to value of -1 
		
	 }
 }

// the below is a copy constructor
Tree::Tree(Tree& anotherTree)
{
	parentArray = new int[anotherTree._size];//set to size equal to size of array
	_size = anotherTree._size;
	for (int i = 0; i < _size; i++)
	{
		parentArray[i] = anotherTree.parentArray[i];  // deep copy of the 1D array created here
	}
}

// the below is a destructor for the 1 d array
Tree::~Tree()
{
	delete [] parentArray;
	parentArray = NULL;

}

// the below method returns the size of the  1D parrentArray
int Tree::getSize()
{
	
	return _size;
}

// the below method gets the elements of the 1D parent Array

int* Tree::getParentArray(){
	// returns the parentArray that can be accessed by main with a 1-D array
	// in main of integer values 

	return parentArray; 

	}

// the below method computes the Least Common Ancestor of 2 Nodes

int Tree::LCA(int firstNode, int secondNode)
{
	int LCA; int x; int x1; int x2; int x3;
	int x4; int x5;
	x = parent(firstNode);
	x1 = parent(secondNode);
	
	// if firstNode is equal to second Node
	// it returns the LCA as first node
	// or if fist node is root, it returns first node
	// as LCA

	if (firstNode ==secondNode || parent(firstNode) == -1)
	{
		LCA = firstNode;
	}

	// if second node is root, it returns second node as LCA
	if (parent(secondNode) == -1)
	{
		LCA = secondNode;
	}

	// if none of the above conditions are true
	// the below code is executed

	if (firstNode != secondNode && parent(firstNode) != -1 && parent(secondNode) != -1)
	{

	// if the 2 nodes are at the same level, then the below code is executed
	// the below executes as long as the parent of the two nodes are not the same
	// if the parents of the two nodes are the same, then it returns 
	// one of the parents as the LCA

		if (level(firstNode) == level(secondNode)) {
			while (x != x1) {

				x = parent(x);
				x1 = parent(x1);
			}
			LCA = x1;
		}

		// the below code executes when level of first node
		// is less than level of second node

		else if (level(firstNode) < level(secondNode)) {
			x2 = parent(secondNode);
			x3 = parent(firstNode);

			// execute the below until level of first node is equal
			// to parent of second node

			while (level(firstNode) < level(x2)) {
				x2 = parent(x2);
			}

			// once the parent node of second node chain computed iteratively reaches
			// the level of the first node, the below is executed
			// if parent of second node chain computed iteratively is equal to the
			// first node

			if (x2 == firstNode)
			{
				LCA = firstNode;
			}

			// else the below is done, and it continues until
			// parents of the node chains are not equal
			// once they are determined to be equal one of them
			// is returned as the LCA

			else {
				x2 = parent(x2);
				while (x3 != x2) {

					x3 = parent(x3);
					x2 = parent(x2);
				}
				LCA = x2;
			}
		}

		// the below is the same as the above combination
		// except it is reversed in that level of second node 
		// now is less than the level of the first node

		else {
			x4 = parent(secondNode);
			x5 = parent(firstNode);
			while (level(secondNode) < level(x5)) {
				x5 = parent(x5);
			}


			// once the parent node of first node chain computed iteratively reaches
			// the level of the second node, the below is executed
			// if parent of first node chain computed iteratively is equal to the
			// second node


			if (x5 == secondNode)
			{
				LCA = secondNode;
			}

			// else the below is done, and it continues until
			// parents of the node chains are not equal
			// once they are determined to be equal one of them
			// is returned as the LCA


			else {
				x5 = parent(x5);
				while (x4 != x5) {

					x5 = parent(x5);
					x4 = parent(x4);
				}
				LCA = x5;
			}
		}
	}
	return LCA;
}

// the below returns the array value at the 
// the ith index position

int Tree::parent(int i)
{
	return parentArray[i];
}

// the below method finds the child
// of the element at index position i.
// it returns the children at the index position
// whose array value is equal to the index position i

void Tree::children(int i)
{
	for (int l = 0; l < this->getSize(); l++) {
		if (parentArray[l] == i) {
			cout << l << " ";
		}
	}
}

// the below method finds the siblings of
// the index position i
// siblings are returned if their parents are the same!
// so long as when looped through the lth index does 
// not match the ith index

void Tree::siblings(int i)
{
	for (int l = 0; l < this->getSize(); l++) {
		if (parentArray[l] == parentArray[i]) {
			if (l != i) {
				cout << l << " ";
			}
		}
	}
 }

// the below returns the root of the tree
// root is returned when array value for that index
// position is -1.  this is the only index position that
// does not have a parent and so it retains the default
// initialization of 1

int Tree::root()
{
	int val1{};
	    for (int l = 0; l < _size; l++) {
	//	cout << " am i here 1";
		if (parent(l) == -1 ) {
			val1 = l;
		break;
		}
     }
		return val1;
}

// the below method sets the values
// of the array at given index position
// based on node value and parent value
// passed in from main


void Tree::setParent(int node, int parent)
{
	int j = node;
	parentArray[j] = parent;
	//cout << j <<":" << parentArray[j] << " ";
}

// the below method returns the nodes at a given level
// the level method is accessed to determine the level
// of index position as it is looped from 0 to size of
// array and then the value of that index is printed if
// its value matches that of the value passed in from
// main

void Tree::nodesAtLevel(int i)
{
	for (int l = 0; l < this->getSize(); l++) {
		if (level(l) == i) {
			cout << l << " ";
		}
	 }
}

// the below method returns the level of a node
// value is passed in from main.  
// the level is set at 1 corresponding to the level
// of the root and is incremented by 1 via a do while loop
// until the root is reached, and the incremented value is
// returned as level of node

int Tree::level(int i)
{
	int val2 = 1;
	int x;
	x = parentArray[i];
	//cout << x;
	while (x != -1) {
		x = parentArray[x];
	    val2 = val2 + 1;
		//cout << x << val2;
	}
	return val2;
}

// the below method determines the height of the tree
// the array is looped and level of each node is determined
// by accesssing the level method and if level is greater than the
// height as it is looped, value of height is reset.
// at the end of the for loop, the value of height 
// is returned to main

int Tree::height()
{
	int height = 0;
	int val2;
	for (int l = 0; l < this->getSize(); l++) {
		val2 = level(l);
		if (val2 > height)
			height = val2;
	}
	return height;
}

// the below method is used to check if leaf node is
// reached.  currently not used in the program

bool Tree::isLeaf(int k)
{
	for (int j = 0; j < this->getSize(); j++) {
		if (k == parentArray[j]) {
			return true;
			break;
		}
		}
	return false;
}

// this is a recursive call for preorder traversal

void Tree::recursivepreorder(int i)
{
	cout <<i<< " ";
	for (int j = 0; j < this->getSize(); j++) {
		if (parentArray[j] == i) {
			recursivepreorder(j);
		}
	}
 }

// this calls the recursive preodrer method from the root

void Tree::preorder()
{
	recursivepreorder(root());
}
	

// the below method is ostream operator for
// the parent array. returns it so it can be accessed from main

ostream& operator<<(ostream& o, Tree& tree)

{
	o << "Parent Array of tree:" << endl;

	for (int j = 0; j < tree.getSize(); j++) {
		o <<j<<": "<<tree.parent(j)<<"  ";
 }
	o << endl;
	return o;
}

// main function

int main()
{

	int numNodes, numChildren, nodeNum, childNum; 
	int level1, node1, node2;

	// read in the number of nodes in the tree
    cin >> numNodes;
	
	// create object of class Tree
	Tree* myTree = new Tree (numNodes);

	// the below for loop loops through the values
	// of child which is set as index position in the array
	// and the parent as the array value for that index position
	// first parent node number is read along with the number of children it has

	for (int i = 1; i <= numNodes; i++) {
		cin >> nodeNum >> numChildren;
		if (numChildren >0){
			for (int j = 1; j <= numChildren; j++) {
				cin >> childNum;
				myTree->setParent(childNum, nodeNum);
		  }
		}
	 }
    	
	char option; // to read in the option
	
	// the below executes until a query or option is available

	while (cin >>option)
	{
		//cin >> option;

	//switch case loop used to process the request based on
	// the type of query to be processed

		switch (option) {
		case 'D':  // print out parent array
			//can use the below but using ostream instead
	/*		cout << "Parent Array of tree :" << endl;
			for (int i = 0; i < numNodes; i++) {
				cout << i << ": "<< myTree->parent(i) << "  ";
			}*/

			//ostream used to display below

			cout << *myTree;

			break;

		case 'O': // print out root of tree
			cout <<"Root of tree: "<< myTree->root()<<endl;
	
			break;

		case 'H':  // print out height of tree
			cout << "Height of tree: "<< myTree->height()<<endl;
			
			break;

		case 'P': // print out parent of node number
			cin >> nodeNum;
			cout <<"Parent of " <<nodeNum <<": " << myTree->parent(nodeNum) << endl;

			break;

		case 'C':  // print out children of nodenumber
			cin >> nodeNum;
			cout << "Children of " << nodeNum << ": "<< endl;

			myTree->children(nodeNum);
			cout << endl;

			break;

		case 'S':  // print out siblings of node number

			cin >> nodeNum;
			cout << "Siblings of " << nodeNum << ": "<< endl;
			
			myTree->siblings(nodeNum);
			cout << endl;

			break;

		case 'L':  // print out level of node number
			cin >> nodeNum;

			cout << "Level of " << nodeNum << ": ";
			cout << myTree->level(nodeNum) <<endl;

			break;

		case 'N':  // print out the values of the nodes at a given level
			cin >> level1;

			cout << "Nodes at level " << level1 << ": " << endl;
			myTree->nodesAtLevel(level1);
			cout << endl;

			break;

		case 'A':  //print out the LCA of 2 nodes
			cin >> node1 >> node2;
			
			cout << "LCA of " << node1 << " and " << node2 << ": ";
			cout << myTree->LCA(node1, node2);
			cout << endl;

			break;

		case 'R':  // print out preorder traversal of tree
			
			cout << "Preorder traversal of tree:" << endl;
			myTree->preorder();
			cout << endl;
			break;
				
		}
	}
	
	// delete the myTree object that is created
	    delete myTree;
	
		return 0;
}