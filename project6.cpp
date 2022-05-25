//Computing Structures
//Fall 2021
//Project 6
// This is Ramkishore Rao's DSA 5005 Project 6 

#include <iostream>
#include <queue> // for BFS

using namespace std;

class CSR {
protected:
	int n; //The number rows of the original matrix
	int nonZeros; //The number of non-zeros in the original matrix
	int *rowPtr; //Array that contains number of non-zero elements in each row of the original matrix
	int *colPos; //Array that contains the column number from the original matrix for the non-zero values.
	int rowIndex; //maybe used for building the CSR data structure
	int colIndex; //maybe used for building the CSR data structure

public:
	CSR(); //default constructor
	CSR(const CSR& csrToCopy); //Copy Constructor
	CSR(int rows, int numNonZeros); //Non-default Constructor
	~CSR(); //destructor
	int getNumRows(); //get n
	int getNonZero(); //get nonZeros
	int getRowPtr(int i); //get rowPtr at index i
	int getColPos(int i); //get colPos at index i
	void addColumn(int col); //add a column in the colPos array
	void addRow(int row); //add a row in the rowPtr array
	void display(); //print the contents of the 2 arrays and the matrix
	int getEdge(int row, int col); //return an edge existent (1 or 0)
	int triangleCount(); //count the number of triangles and return it
	void DFS(int startNode, int* visited); //print the nodes in DFS ordering; visited is an array for recursive implementation
	void BFS(int startNode); //print the nodes in BFS ordering
	int* getrowPtr();// returns the pointer to rowPtr array
	int* getColPos();// returns the pointer to colPos array
	void DFS(int startNode);//recursive method for DFS
	
	//You may have other methods

};

CSR::CSR()  // non default constructor 
{
	n = 0; // number of rows of original matrix
	nonZeros = 0; // number of now zeros in the orginal matrix
	colIndex = 0; // index of the colPos array
	rowIndex = 1;  //index of the rowPtr array
	rowPtr = NULL;  // initializing pointer to rowPtr array as NULL
	colPos = NULL;  // initializing pointer to colPos array as NULL
}

CSR::CSR(const CSR& csrToCopy)  //copy constructor for the CSR class
{
	rowPtr = new int[csrToCopy.n]; //rowPtr array copy constructor
	colPos = new int[csrToCopy.nonZeros]; //colPos array copy constructor

	for (int i = 0; i < n; i++) {
		rowPtr[i] = csrToCopy.rowPtr[i]; //copying rowPtr array elements
	}

	for (int j = 0; j < nonZeros; j++) {
		colPos[j] = csrToCopy.colPos[j]; //copying colPos array elements
	}
}

CSR::CSR(int rows, int numNonZeros) //non default constructor for CSR class
{
	n = rows;  //number of rows in original matrix
	colIndex = 0; // intializing index position of the colPosition array to zero
	rowIndex = 1; // initializing index position of the rowPtr array to zero
	nonZeros = numNonZeros; // number of nonZeros in the original matrix
	rowPtr = new int[rows]; // creating rowPtr array of Size rows
	colPos = new int[numNonZeros]; // creating colPos array of Size numNonZeros

	// initiailzing rowPtr values to zero
	for (int i = 0; i < n; i++) {
		rowPtr[i] = 0;
	}

	// initializing colPos values to -1
	for (int j = 0; j < nonZeros; j++) {
		colPos[j] = -1;
	}

}

CSR::~CSR()//destructor for the CSR class
{
	
	delete [] rowPtr;  //destructor for the rowPtr array
	rowPtr = NULL;
	
	delete[] colPos;  // destructor for the colPos array
	colPos = NULL;

}

int CSR::getNumRows() // getter for number of rows in matrix or number of nodes
{
	return n;
}

int CSR::getNonZero()  // getter for number of nonZeros in original matrix
{
	return nonZeros;
}

int CSR::getRowPtr(int i) //getter for rowPtr value at index position of i
{
	return rowPtr[i];
}

int CSR::getColPos(int i) // getter for colPos value at index position of i
{
	return colPos[i];
}

void CSR::addColumn(int col)  // setting colPos value at index position 
//sent from main program
{
	
	colPos[colIndex] = col;
	colIndex++;
	
}

int* CSR::getrowPtr()  // this returns the rowPtr array
{
	return rowPtr;
}

int* CSR::getColPos()  // this returns the colPos array
{
	return colPos;
}

void CSR::addRow(int row) // setting rowPtr vale at inde position of row
{
	
	rowPtr[rowIndex] = row;
	rowIndex++;
	
}

void CSR::display()  // display method for the original matrix
{
	int l1; int l2; // integers used to track number of non zeros for given node
	int k;
	l1 = rowPtr[0];//value at zero index position of rowPtr array
	k = l1; 
	l2 = rowPtr[1]; // this is the upper end of the rowPtr array for node 0
	// we subtract l1 from l2 to determine number of nonZeros for node 0

	cout << "Matrix A: " << endl;
	// the below loope through rows and then columns withi each row of the 
	//original matrix
	for (int i = 0; i < getNumRows(); i++) {
		for (int j = 0; j < getNumRows(); j++) {
	
	// the below is used to find column values for a given node or row
	// we find all non zero column positions for a given node or row
    // print 1 for non Zero position
	// and 0 for Zero position

			if (j == colPos[k] && k <l2){
				k++;
					cout << 1 << " ";
              }
			else { cout << 0 << " "; }
			}
				 
	    cout << endl;

// the below is used to update the counters for next node or row
// use the if condition counter for all nodes except the last node
// or the bottom row
// use the else condition for the bottom node or bottom row


		if (i < getNumRows() - 2) {
			l1 = rowPtr[i+1];
			k = l1;
		    l2 = rowPtr[i + 2];
		}
		else if (i == getNumRows() - 2) {
			l1 = rowPtr[i +1];
			k = l1;
			l2 = getNonZero();
			
		}
	}

	// the below code prints the values from the rowPtr array
	
	cout << "rowPtr: ";

	for (int i = 0; i < getNumRows(); i++) {
		cout << rowPtr[i] << " ";
	}

	cout << endl;

	// the below code prints the values from the colPos array

	cout << "colPos: ";

	for (int j = 0; j < getNonZero(); j++) {
		cout << colPos[j] << " ";
	}

	cout << endl;

}

// method used to see if we have a connected edge between nodes

int CSR::getEdge(int row, int col)
{
	int l1; int l2;
	
// the below if else code sets the counters to be used for a
// particular node or row based on value of node
// all rows except the last but one use if condition
// and else for the last row or node

	if (row < getNumRows() - 1) {
		l2 = rowPtr[row + 1];
		l1 = rowPtr[row];
	}

	else if (row == getNumRows() - 1) {
		l2 = getNonZero();
		l1 = rowPtr[row];
	}

// the below code checks if the column sent to method
// is a column position for a given node or row

	bool stop = false;
	
		for (int k = l1; k <l2; k++)  {
			if (col == colPos[k])
			{
				stop = true;
				
				break;
					}
		
	}
		if (!stop) { return 0;}
		else { return 1; }

	
}

// this method estimates the number of triangles in a graph.
// the below is looking for a connection from node i to node j
// and if a connection exists between i and j, look for a connection
// between j and k, and if a connection exists between j and k;
// look for a connection between k and i; there are total of 6
// such loops for each triangle, so return the traingle as 1/6 for
// each triangle

int CSR::triangleCount()
{
	int triangle = 0;
	for (int i = 0; i < getNumRows(); i++) {
		for (int j = 0; j < getNumRows(); j++) {
			if (i != j && getEdge(i, j) == 1) {
				for (int k = 0; k < getNumRows(); k++) {
					if (j != k && getEdge(j, k) == 1) {
						if (k !=i && getEdge(k, i) == 1) {
							//cout << triangle;
							triangle = triangle + 1;
						}
					}
				}
			}
		}

	}
	int tri= triangle/6;
	
	return tri;
}

// the below is a recursive method for depth first tree
// implementation.  takes the start node
// and then recursively finds it connections by depth 
// until the bottom of the graph and then recursively go
//back up until all nodes are found
// the if condition for if colPos is visited helps complete
// this recursive loop

void CSR::DFS(int startNode, int* visited)
{
	int l1;
	int l2;
	
	// this happens if startNode has not yet been visited
	// the below are the bottom and top counters for each node or row 
	// if checks all rows except the bottom row
	// else checks for the bottom row


	if (visited[startNode] == 0)
	{
		if (startNode < getNumRows() - 1)
		{
			cout << startNode << " ";
			visited[startNode] = 1;
			l1 = rowPtr[startNode];
			l2 = rowPtr[startNode + 1];
		}
		else if (startNode == getNumRows() - 1)
		{
			cout << startNode << " ";
			visited[startNode] = 1;
			l1 = rowPtr[startNode];
			l2 = getNonZero();

		}
		

	}
			
	for (int k = l1; k < l2; k++) {
		//cout << k << " " << endl;
		if (visited[colPos[k]] == 0) {
			
		DFS(colPos[k], visited);
		}
	}
}

// this is an extra method written below 
// to interact with the call from main
// this method sets the visited array to 0s
// values are changed to 1 when a node is visited in the above method

void CSR::DFS(int startNode)
{
	
	CSR* visited = new CSR(getNumRows(), getNonZero());
	
	for (int i = 0; i < getNumRows(); i++) {
		visited->rowPtr[i] = 0;
	}

			DFS(startNode, visited->rowPtr);
	
}

// below method is used to implement Breadt First Search
// sets visited array to zero first for all positions
// values change to 1 when a bode is visited
// when a node is visited, node value is printed and the 
// corresponding position for that index in the visited array
// changes to 1.  when a node is visited, its printed and put into
// stack.  all its neighbors are printed.
// once all neighbors of a given node are visited then the next
// element in the queue is popped and its neighbors are visited if
// they have not already been visited.  this process continues unti
// all neighbors are visited


void CSR::BFS(int startNode)
{
	// visited array set to zero for all index positions initially	
	CSR* visit = new CSR(getNumRows(), getNonZero());

	for (int i = 0; i < getNumRows(); i++) {
		visit->rowPtr[i] = 0;
	}

	std::queue <int> myqueue;
	int l; int l1; int l2;
	visit->rowPtr[startNode] = 1;

	// the below are the bottom and top counters for each node or row 
	// if checks all rows except the bottom row
	// else checks for the bottom row

	if (startNode < getNumRows() - 1) {
		l1 = rowPtr[startNode];
		l2 = rowPtr[startNode + 1];
		cout << startNode << " ";
		l = 1;
	}

	else if (startNode == getNumRows()-1) {
		l1 = rowPtr[startNode];
		l2 = getNonZero();
		cout << startNode << " ";
		l = 1;
	}

	// the below is implemented until nodes or rows are visited
	// in a breadth first manner

	while (l < getNumRows()) {
		for (int j = 0; j < getNumRows(); j++) {
			for (int k = l1; k < l2; k++) {
				if (visit->rowPtr[colPos[k]] == 0) {
					myqueue.push(colPos[k]);
					l = l + 1;
					cout << colPos[k] << " ";
					visit->rowPtr[colPos[k]] = 1;

				}
			}
		}
			l1 = rowPtr[myqueue.front()];
			l2 = rowPtr[myqueue.front() + 1];
			myqueue.pop();
	}

	}



int main() {

	int numRows, numNonZeros, count = 0; 
	int row, col, value;
	int startNode;
	
	// i am using numRows and numNonZeros
	// to define number of rows in the original matrix
	// and numNonZeros are tthe number of 1s in the original matrix

	//read in the first matrix
	cin >> numRows >> numNonZeros;

	//object A of CSR
	CSR *A; 
	A = new CSR(numRows, numNonZeros);

	// the below is used to send rowPtr and colPos values
	// to the setter methods above

	row = 0;
	int j = numRows;
	for (int i = 0; i < j; i++) {
	
		for (int j = 0; j < numRows; j++) {
	
			cin >> value;
			//cout << value << " ";
			if (value == 1) {
				A->addColumn(j);
				row = row + 1;
			}
		}
		//cout << endl;
		if (i < (j - 1)) {
			A->addRow(row);
		}
	}
	
	// startNode is read from the input file for BFS and DFS 

	cin >> startNode;
	
	
    //TODO: read in the matrix A from the input file and store it in the given format


    //display mat A
	//cout << "Matrix A:" << endl;
	(*A).display();

    //triangle counting
	int numTri = A->triangleCount();
	cout << "Number of Triangles: " << numTri << endl;
		

    //BFS Call
	cout << "BFS ordering: ";
	A->BFS(startNode);
	
	cout << endl;

    //DFS Call
	cout << "DFS ordering: ";
	A->DFS(startNode);
	cout << endl;
  
	//TODO: Call the destructors
	delete A;
	
	return 0;
}
