#include<iostream>
#include<exception>

//Note that this is Ramkishore Rao's Project 3 for DSA5005.   


using namespace std; 

class Exception {};

//exception class created to handle exceptions

class ExceptionRowBouce : public Exception {};  //extension created to handle RowBounce Exception
class ExceptionColBounce : public Exception {};  //extension created to handle ColBounce Exception
class ExceptionAdditionMismatch : public Exception {};  //extension created to handle Adddition dimension mismatch
class ExceptionMultiplicationMismatch : public Exception {};  //extension created to handle Multiplication dimension mismatch


class SparseRow {
	
protected:
	int row; // Row#
	int col; // Column#
	int value; // We will assume that all our values will be integers
	// you are restricted to add or modify the fields in the class
public:
	SparseRow(); // default constructor; row=-1;col=-1;value=0 
	SparseRow(int r, int c, int v); // non default constructor
	virtual ~SparseRow(); // Destructor
	void display(); // print Row#, Column#, value for each SparseRow Object
	void setRow(int r); // setter for row value in each SparseRow Object
	void setCol(int c); //setter for col value in each SparseRow Object
	void setValue(int v); //setter for cell value in each SparseRow Object
	int getRow(); // getter for row value in each SparseRow Object
	int getCol(); //getter for col value in each SparseRow Object
	int getValue(); //getter for cell value in each SparseRow Object

	
};


class matrixClass {
	friend ostream& operator <<(ostream& s, matrixClass& p);
	
	//overload ostream operator to be used for display of Matrix

protected:
	int numRows; // number of rows 
	int numCols; // number of columns
	int numNonZero; // number of non zero elements
	int commonValue; // read from input - assume 0
	SparseRow* mat; // an array of SparseRow objects of length numNonZero
	int** mat1;


public:
	
	matrixClass(); // default constructor
	matrixClass(int r, int c, int nz); // non default constructor
	matrixClass(int r, int c);
	~matrixClass(); // destructor
	matrixClass(matrixClass& copyThis); // copy constructor only a copy created
	//not used in program
	void display(); // display in sparse row format
	void displayMatrix(); // display in matrix format
	void setValue(int pos, int i, int j, int val); 
	// to set the value at location i, j; pos is to keep track of the position in mat
	int getValue(int i, int j); // return val at i, j
	int getNumRows(); // getter for numRows
	int getNumCols(); // getter for numCols
	int getValWithRowandCol(int row, int col); // given row and col number, return the value at that spot
	int length(); // this is a getter method for number of Non Zero elements in the array of SparseRow objects
	/*matrixClass* multiply(matrixClass* multiplier);*/ // multiply method
	/*matrixClass* add(matrixClass* addend);*/ // add method
	matrixClass* floydWarshall();//all pairs shortest path method
	int cV();//method to get commonValue in matrixClass
		
};



	SparseRow::SparseRow() //default constructor
	{
		row = -1;
		col = -1;
		value = 0;
	}

	SparseRow::SparseRow(int r, int c, int val) {//non default constructor
	row = r;
	col = c;
	value = val;

	//this constructor does not get called.
}

	SparseRow::~SparseRow() {//destructor for non default constructor
		
	}


	void SparseRow::setRow(int r) {

		//setter method for setting row number in each SparseRow object

		row = r;
			
	}

	void SparseRow::setCol(int c) {

		//setter method for setting column number in each SparseRow object

		col = c;
	}

	void SparseRow::setValue(int v) {

		//setter method for setting value in each SparseRow object

		value = v;
			}

	int SparseRow::getRow() {

		//getter method for getting row number in each SparseRow object

		return row;
	}

	int SparseRow::getCol() {

		//getter method for getting column number in each SparseRow object

		return col;
	}

	int SparseRow::getValue() {

		//getter method for getting cell value in each SparseRow object

		return value;
	}

	void SparseRow::display() {

		//display method for sparserow elements in each SparseRow object

		cout << getRow() << getCol() << getValue() << endl;
	
	}

	matrixClass::matrixClass() {//default constructor
		numRows = 0;
		numCols = 0;
		numNonZero = 0;
		commonValue = 999;
		mat = NULL;

	}

	matrixClass::matrixClass(int r, int c, int nz) {

		//non default constructor 
		//each time a new matrix class object is created it sends the values
		//of the number of rows, number of columns, number of non zero elements
		//to create an array of SparseRow objects

		numRows = r;  
		numCols = c;
		numNonZero = nz;
		commonValue = 999;
		mat = new SparseRow[numNonZero];
		//the mat is an array of SparseRow objects of length numNonZero
		}
	
	//constructor for the adjacency matrix called from the shortest path method
    matrixClass::matrixClass(int r, int c) {
		numRows = r;
		numCols = c;
		mat1 = new int* [r];
		int i, j;
		for (i = 0; i < r; i++) {
			mat1[i] = new int[c];
		}
		for (i = 0; i < r; i++) {
			for (j = 0; j < c; j++) {
				mat1[i][j] = 999;
			}
		}

	}


	matrixClass::matrixClass(matrixClass& copyThis) {

		//this is the copy constructor method; only a method created and not used in program

		numRows = copyThis.numRows;  
		numCols = copyThis.numCols;
		numNonZero = copyThis.numNonZero;
		commonValue = copyThis.commonValue;
		mat = copyThis.mat;
	 }

	matrixClass::~matrixClass() {//matrixClass object destructor
		
	delete []mat;
	mat = NULL;

	int i;
	for (int i = 0; i < numRows; i++)
	{
		delete[] mat1[i];
	}
	delete[] mat1;
	
	}

	int matrixClass::getNumRows()//method to get number of rows in the matrixClass object
	{
		return numRows;
	}

	//method getter for number of columns
	int matrixClass::getNumCols()
	{
		return numCols;
	}

	int matrixClass::cV()
	{
		int comm = commonValue;
		return comm;
	}

	void matrixClass::setValue(int pos, int i, int j, int val) {

		//this method accepts the values passed in from input file for
		//the row number, column number and cell value in each SpraseRow.
		//the pos parameter is the index of the SparseRow objects in the array

		mat[pos].setRow(i);//this calls the setRow method of the SparseRow class to set the row number
		mat[pos].setCol(j);//this calls the setCol method of the SparseRow class to set the column number
		mat[pos].setValue(val);//this calls the setvalue method of the SparseRow class to set the cell value
	
	}

	int matrixClass :: length() {
		//this is a getter method for getting the length of the array in each matrixclass object
		return numNonZero;
	   
	}

	int matrixClass::getValue(int i, int j) {

		//this method returns the cell value in the matrix based on its row number and
		//column number, i is row number and j is col number
		//the value is obtained from the SparseRow getValue method

		int l =0;//initializing the index for the dynamic array
		int value1;
		
					for (l = 0; l < this->length(); l++) {//Sparse Row Array Loop
					if (i == mat[l].getRow() && j == mat[l].getCol()) {
						value1 = mat[l].getValue();
						break;
					}
				
				else 
						value1 = commonValue;
			}
			
			return value1;
	}

	int matrixClass::getValWithRowandCol(int row, int col) {

		//this method returns the cell value based on its row number and column number
		//the value is obtained from the SparseRow getValue method

		int value;
		int i = row;
		for (int l = 0; l < length(); l++) {
		value = this->mat[l].getValue();
	}
		return 0;
	}


	void matrixClass::display() {

		//this method prints the SparseRow elements by line within each MatrixClass Object

		int length = this->length();//this statement is used to get the length of the SparseRow array 
		cout  << "Row" << "|" << "Col" << "|" << "Value" << endl;
		for (int l = 0; l < length; l++) {
			if (this->mat[l].getRow() <= this->getNumRows() && this->mat[l].getCol() <=this->getNumCols()&&this->mat[l].getRow()>=0 && this->mat[l].getCol() >=0 )
			cout << this->mat[l].getRow() << " " << this->mat[l].getCol() << " " << this->mat[l].getValue() << endl;
		}
	}

	void matrixClass::displayMatrix() {

		//this method displays the matrix in the matrix format
		//it obtains the value if a corresponding value is available in the SparseRow array,
		//otherwise, commonvalue of 999 is returned.

		int val1;
		int i, j;// these variables are being used to track the row and column numbers in the matrix
		int length = this->length();//this statement is used to get the length of the SparseRow array

		for (int i = 0; i < getNumRows(); i++) {
			for (int j = 0; j < getNumCols(); j++) {
				for (int l = 0; l < length; l++) {
					if (i == mat[l].getRow() && j == mat[l].getCol()||
						i == mat[l].getCol() && j == mat[l].getRow()) {
						val1 = mat[l].getValue();
						break;
					}
					else {
						val1 = commonValue;
					}
				}

				cout << val1 <<" ";
			}
			cout << endl;
		}
	}
	
	ostream& operator <<(ostream& s, matrixClass& p) {

		//this is an overload ostream operator method that has been developed
		//that is similar to the displayMatrix method
		//it obtains the value if a corresponding value is available in the SparseRow array,
		//otherwise, commonvalue of 999 is returned.

		int val1;
		int i, j;
		int length = p.length();

		for (int i = 0; i < p.getNumRows(); i++) {
			for (int j = 0; j < p.getNumCols(); j++) {
				for (int l = 0; l < length; l++) {
					if (i == p.mat[l].getRow() && j == p.mat[l].getCol()|| 
						i == p.mat[l].getCol() && j == p.mat[l].getRow()) {
						val1 = p.mat[l].getValue();
						break;
					}
					else {
						val1= p.cV();
					}
				}

				s << val1<<" ";
			}
			s << endl;
		}
		return s;
	}
	
				matrixClass* matrixClass::floydWarshall()
				{
					int s = 0;//index for position in array of SparseRow Objects in the matrixClass object
					int sp1 = 0;//index for position in array of SparseRow Objects in the matrixClass object
					int val1;//vals for each cell in the adjacency matrix, initial values
					int length = this->length();//length of the Sparse Row Array in the matrixClass object
					
					//new matrixClass object created to store the result of the shortest path of the matrix
					matrixClass* floyd = new matrixClass(this->getNumRows(), this->getNumCols(), this->getNumRows() * this->getNumCols());

					
					int rf = this->getNumRows();
					int cf = this->getNumCols();
	               
					//creates an object for the adjacency matrx
					matrixClass* adjacencymatrix = new matrixClass(rf, cf);
				    
					
				//assigns initial values to the adjacency matrix, when available from sparserow input, otherwise common Value
					for (int i = 0; i < rf; i++) {
						for (int j = 0; j < cf; j++) {
							for (int l = 0; l < length; l++) {
								if (i == mat[l].getRow() && j == mat[l].getCol() ||
									i == mat[l].getCol() && j == mat[l].getRow()) {
									val1 = mat[l].getValue();
									break;
								}
								else {
									val1 = commonValue;
								}
							}
							adjacencymatrix->mat1[i][j] = val1;
						}
					}

						
					//this is the computation for the all pairs shortest path on the adjacency matrix.
							for (int l = 0; l < getNumRows(); l++) {
								for (int i = 0; i < getNumRows(); i++) {
									for (int j = 0; j < getNumCols(); j++) {
										if (adjacencymatrix->mat1[i][l] + adjacencymatrix->mat1[l][j] < adjacencymatrix->mat1[i][j] && i != j)
											adjacencymatrix->mat1[i][j] = adjacencymatrix->mat1[i][l] + adjacencymatrix->mat1[l][j];
									}
								}

							}

							// this is the conversion from the final adjacency matrix to the undirected graph
							// this only does the conversion when row index is less then col index and 
							// for non diagonal elements as it is to result in an undirected graph
								for (int i =0; i<getNumRows(); i++){
									for (int j = 0; j < getNumCols(); j++) {
										if (i<j) {
											floyd->mat[sp1].setRow(i);
											floyd->mat[sp1].setCol(j);
											floyd->mat[sp1].setValue(adjacencymatrix->mat1[i][j]);


											sp1++;
										}
						
								}
							}
																					
				 return floyd;
                 
				}

// main function
int main()
{
	int numRows, numCols, numNonZero, t,u, val;  // initialzing variables to be read from the redirected input file

	// read in all the numRows, numCols and numNonZero values from redirected input for matrix A
	cin >> numRows >> numCols >> numNonZero;

	// declare object for matrix A
matrixClass* a = new matrixClass(numRows, numCols, numNonZero);

// read in the values and use setValue to set the values read in for A
//exception handling has been added to ensure that the entered value for
//both the row and the col index does not exceed its corresponding numRows
//and num Cols

for (int r = 0; r < numNonZero; r++) {
	cin >> t >> u >> val;
	
	try {
		if (t > numRows-1) {
			
			throw  ExceptionRowBouce();
		}
		if
			(u > numCols-1) {
			throw ExceptionColBounce();
		}

		(*a).setValue(r, t, u, val);
	}
	
	//catch statement below to catch the Row out of Bounce exception and abort the program

	catch (ExceptionRowBouce myException3) {
		cout << "Row Out of Bounce exception thrown – stopping execution";
		return 0;
	}

	//catch statement below to catch the Column out of Bounce exception and abort the program

	catch (ExceptionColBounce myException4) {
		cout << "Column Out of Bounce exception thrown – stopping execution";
		return 0;
	}
}

// display matrix A
cout << "A in SparseRow format: " << endl;
(*a).display();

cout << "A in Matrix format: " << endl;
cout << *a;
matrixClass b(a);

matrixClass* floyd1 = a->floydWarshall();

// display resultant matrix, all pairs shortest path
cout << "Result in SparseRow format: " << endl;
floyd1->display();

cout << "Result in Matrix format: " << endl;
cout <<*floyd1;

	return 0;
}

/*
Is this data structure the most efficient way to store the graph and to find the 
shortest path? Is the algorithm performing the best in this data structure?

Answer:  

The undirected graph, represented in this format is very efficient way of storing
the information.  It contains nodes (or vertices) that are entities and edges that
serve as links between the vertices.  Undirected graph only has to have the 
information or weight of edge between nodes wihtout regard to direction between 
the vertices as the graphs can be traversed in either direction. 
Undirected graphs can be implemented in one of two ways either as a an adjacency
matrix, similar to this problem or as an adjacency list.  The matrix order is
VXV where V is the vertex in a graph.  The values in the matrix determine the 
weight or cost of each edge between the two vertices it connects. 

The adjacency list is an array of linked lists where the array
denotes the total vertices and each linked list denotes the vertices 
connected to a particular node.
If a graph is sparse and we use matrix representation then most of the matrix 
cells remain unused which leads to the waste of memory. Thus we usually don't 
use matrix representation for sparse graphs. We prefer adjacency list.

But if the graph is dense then the number of edges is close to (the complete) 
n(n−1)/2, or to n2 if the graph is directed with self-loops. 
Then there is no advantage of using adjacency list over matrix.

In terms of space complexity
Adjacency matrix: O(n2)
Adjacency list: O(n+m)
where n is the number nodes, m is the number of edges.

When the graph is undirected tree then
Adjacency matrix: O(n2)
Adjacency list: O(n+n) is O(n) (better than n2)

When the graph is directed, complete, with self-loops then
Adjacency matrix: O(n2)
Adjacency list: O(n+n2) is O(n2) (no difference)

And finally, when you implement using matrix, checking if there is an edge 
between two nodes takes O(1) times, while 
with an adjacency list, it may take linear time in n.
In general, an adjacency list may be better than an adjacency matrix for
sparse graphs, i.e., those that have lower number of edges than a complete
graph.

In a linked list, the most important component is the pointer named ‘Head’ 
because this single pointer maintains the whole linked list. For linked 
list representation, we will have total pointers equal to the 
number of nodes in the graph.

The Floyd-Warshall stands out in that unlike the Djkstra's and Bellman Ford
algorithms, this algorithm is not a single-source algorithm. 
Meaning, it calculates the shortest distance 
between every pair of nodes in the graph, rather than only calculating from a 
single node, which the former two algorithms calculate. It works by breaking 
the main problem into smaller ones, then  combines the answers to solve the 
main shortest path issue.
Note that the time complexity of Floyd Warshall is O(V^3).  Time complexity
for Djkstra's algorithm is O(V^2) and that for Bellman Ford is O(V.E) time.
But both of the latter algorithms are single source algorithms unlike Floyd
Warshall, which gives the shortest between any two nodes on a graph.

Floyd-Warshall is extremely useful when it comes to generating 
routes for multi-stop trips as it calculates the shortest path between 
all the relevant nodes.  
Floyd-Warshall will determine the fastest way to get to any other node 
on the graph.

*/
