#include<iostream>
#include<exception>

//Note that this is Ramkishore Rao's Project 2 for DSA5005.  Transpose Provided in Separate File
//This File only has documentation for the Base Program
//The Bonus Documentation is provided in the bonus file


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

	// you are restricted to add or modify the fields in the class

public:
	matrixClass(); // default constructor
	matrixClass(int r, int c, int nz); // non default constructor
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
	matrixClass* multiply(matrixClass* multiplier); // multiply method
	matrixClass* add(matrixClass* addend); // add method
 //matrixClass* transpose();	
	
	// BONUS: matrixClass* transpose(); // transpose method
	
	// TODO: Write the overloaded ostream operator - same as displayMatrix() method

	// other methods as you deem fit
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
		commonValue = 0;
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
		commonValue = 0;
		mat = new SparseRow[numNonZero];
		//the mat is an array of SparseRow objects of length numNonZero
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
		cout << "Row" << "|" << "Column" << "|" << "Value" << endl;
		for (int l = 0; l < length; l++) {
			if (this->mat[l].getRow() <= this->getNumRows() && this->mat[l].getCol() <=this->getNumCols()&&this->mat[l].getRow()>=0 && this->mat[l].getCol() >=0 )
			cout << this->mat[l].getRow() << " " << this->mat[l].getCol() << " " << this->mat[l].getValue() << endl;
		}
	}

	void matrixClass::displayMatrix() {

		//this method displays the matrix in the matrix format
		//it obtains the value if a corresponding value is available in the SparseRow array,
		//otherwise, commonvalue of 0 is returned.

		int val1{};
		int i, j;// these variables are being used to track the row and column numbers in the matrix
		int length = this->length();//this statement is used to get the length of the SparseRow array

		for (int i = 0; i < getNumRows(); i++) {
			for (int j = 0; j < getNumCols(); j++) {
				for (int l = 0; l < length; l++) {
					if (i == mat[l].getRow() && j == mat[l].getCol()) {
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
		//otherwise, commonvalue of 0 is returned.

		int val1{};
		int i, j;
		int length = p.length();

		for (int i = 0; i < p.getNumRows(); i++) {
			for (int j = 0; j < p.getNumCols(); j++) {
				for (int l = 0; l < length; l++) {
					if (i == p.mat[l].getRow() && j == p.mat[l].getCol()) {
						val1 = p.mat[l].getValue();
						break;
					}
					else {
						val1= 0;
					}
				}

				s << val1<<" ";
			}
			s << endl;
		}
		return s;
	}
		
		matrixClass* matrixClass::add(matrixClass* addend) { 

          // this method is used to add 2 matrix Class objects
		  // this is essentially the addition of the sparserows of the 2 matrices
		  // the display to sparserow or to the dense matrix is from the display
		  // methods provided above

					int length = this->length();  // this is the length of the SparseRow array in first matrix that is being added
					int length1 = addend->length(); // this is the length of the SparseRow array in second matrix that is being added

					// the below line creates a new SparseRow object to store the sum of the added SparseRow lines
				
					matrixClass* sum = new matrixClass(this->getNumRows(), this->getNumCols(), (length + length1+2));

					int i, j, l, s, s1;
					i = 0;
					l = 0;
					j = 0;
					s = 0;// this is the index position for the array in the addition matrix Class object 
					s1 = 0; // this is the index position for the array in the consolidated matrix Class object

					while ((i <= length) && (j <= length1))// while statement to loop through the 2 arrays being added
					{
						//condition below runs when the row and col numbers of the 2 sparserows are the same
						//note that the index position in the matrices being added are only being incremented when
						//their values are being copied into the addition matrix. Each time the addition matrix
						//sparse row is created, its index position is incremented after the call to the methods
						//setting the values for the elements in the SparseRows is made.

						if (this->mat[i].getRow() == addend->mat[j].getRow() && this->mat[i].getCol() == addend->mat[j].getCol())
						{
							sum->mat[s].setRow(this->mat[i].getRow());
							sum->mat[s].setCol(this->mat[i].getCol());
							sum->mat[s].setValue(this->mat[i].getValue() + addend->mat[j].getValue());
							i++;
							j++;
							s++;
						}
						//condition below runs when the row number is the same but col numbers are different
						
						else if (this->mat[i].getRow() == addend->mat[j].getRow() && this->mat[i].getCol() < addend->mat[j].getCol()) {

							sum->mat[s].setRow(this->mat[i].getRow());
							sum->mat[s].setCol(this->mat[i].getCol());
							sum->mat[s].setValue(this->mat[i].getValue());

							i++;
							s++;
						}

						//condition below runs when the row number is the same but col numbers are different

						else if (this->mat[i].getRow() == addend->mat[j].getRow() && this->mat[i].getCol() > addend->mat[j].getCol()) {

							sum->mat[s].setRow(addend->mat[j].getRow());
							sum->mat[s].setCol(addend->mat[j].getCol());
							sum->mat[s].setValue(addend->mat[j].getValue());
							j++;
							s++;
						}

						//condition below runs when row numbers are disparate

						else if (this->mat[i].getRow() < addend->mat[j].getRow()) {
							sum->mat[s].setRow(this->mat[i].getRow());
							sum->mat[s].setCol(this->mat[i].getCol());
							sum->mat[s].setValue(this->mat[i].getValue());
							i++;
							s++;
						}

						//condition below runs when row numbers are disparate

						else if (this->mat[i].getRow() > addend->mat[j].getRow()) {
							sum->mat[s].setRow(addend->mat[j].getRow());
							sum->mat[s].setCol(addend->mat[j].getCol());
							sum->mat[s].setValue(addend->mat[j].getValue());
							j++;
							s++;
						}
					}

					//loop below run for the elements that are not satisfied by conditions noted above
					//and for remaining elements in the first matrix

					if (i <= length)
					{
						for (int p = i; i < length; p++) {
							sum->mat[s].setRow(this->mat[i].getRow());
							sum->mat[s].setCol(this->mat[i].getCol());
							sum->mat[s].setValue(this->mat[i].getValue());
							s++;
						}
					}

					//loop below run for the elements that are not satisfied by conditions noted above
					//and for remaining elements in the second matrix

					else if (j <= length1)
					{
						for (int p = j; j < length1; p++) {
							sum->mat[s].setRow(addend->mat[j].getRow());
							sum->mat[s].setCol(addend->mat[j].getCol());
							sum->mat[s].setValue(addend->mat[j].getValue());
							s++;
						}
					}

					//this is a consolidated matrix with array size matching number of NonZero rows following addition.


					matrixClass* sum1 = new matrixClass(sum->getNumRows(), sum->getNumCols(), (s+1));
					
					for (l = 0; l < s; l++) {
						sum1->mat[s1].setRow(sum->mat[l].getRow());
						sum1->mat[s1].setCol(sum->mat[l].getCol());
						sum1->mat[s1].setValue(sum->mat[l].getValue());
						s1++ ;
					}
					return sum1;  // matrix Class pointer return when main function calls this method
			
	}

			matrixClass* matrixClass::multiply(matrixClass * multiplier) {

				// this method is used to multiply 2 matrix Class objects
		        // this is essentially the multiplication of the sparserows of the 2 matrices
		       // the display to sparserow or to the dense matrix is from the display
		       // methods provided above 
		
						int length = this->length();  // this is the length of the array of SparseRow Array in the first matrix being multipied
						int length1 = multiplier->length(); // this is the length of the array of the SparseRow Array in the second matrix being multiplied
				
			            int s = 0; // index for the array created after mutiplication; this array has multiple row with the same row/col index
						int s1 = 0; // index for the consolidated multiplication array; this array has each row with a unique row/col index
						int s2 = 0; //index for the consolidated multplication array of size that reflects the # of rows in the result matrix
						int l, m,z;
						int sum;
						int sum1;

						//the below lines create the new matrixClass object to store the multiplication arrays

						matrixClass* result = new matrixClass(this->getNumRows(), multiplier->getNumCols(), length * multiplier->getNumRows());
						
						matrixClass* result2 = new matrixClass(this->getNumRows(), multiplier->getNumCols(), length * multiplier->getNumRows());

						//condition below runs when the column number of matrix 1 matches the row number of 
						// matrix 2 of the 2 sparserows being multiplied
						//Each time the multiplication matrix
						//sparse row is created, its index position is incremented after the call to the methods
						//setting the values for the elements in the SparseRows is made.
						//note in the first for loop, mutiple rows can have the same row/col index

						for (int i = 0; i < length; i++) {
							
							for (int j = 0; j < length1; j++) {
								if (this->mat[i].getCol() == multiplier->mat[j].getRow()) {
									sum = this->mat[i].getValue() * multiplier->mat[j].getValue();
									if (sum != 0)
									result->mat[s].setValue(sum);
									result->mat[s].setRow(this->mat[i].getRow());
									result->mat[s].setCol(multiplier->mat[j].getCol());
																	
									s++;
								}
							}
							
						}
						for (l = 0; l < s; l++) {// this is the loop to consolidate the array elements that have the same row and column index
							sum1 = result->mat[l].getValue();
							
							for (m = 0; m < s; m++) {
								if (result->mat[l].getRow() == result->mat[m].getRow() &&
									result->mat[l].getCol() == result->mat[m].getCol() && l != m)
									sum1 =  sum1+ result->mat[m].getValue();
					                 			
							}
							//the value of the resulting cells are passed into the consolidated matrix
							//using the code in the lines below and the index position is incremented after.

							result2->mat[s1].setRow(result->mat[l].getRow());
							result2->mat[s1].setCol(result->mat[l].getCol());
							result2->mat[s1].setValue(sum1);
							s1++ ;
						}
						
						// this is the final matrix class being created so that the number of rows match
						// the total size of the resultant matrix array

						matrixClass* result3 = new matrixClass(result2->getNumRows(), result2->getNumCols(), (s1+1));
						for (z = 0; z < s1; z++) {
							result3->mat[s2].setRow(result2->mat[z].getRow());
							result3->mat[s2].setCol(result2->mat[z].getCol());
							result3->mat[s2].setValue(result2->mat[z].getValue());
							s2++;
						}

						// the below is a sorting function based on the bubble sort algorithm
						// to sort the row index values of the resultant matrix in ascending order
						

						for (int p = 0; p < s2 - 1; p++) {
							for (int q = 0; q < s2-1; q++) {
								if (result3->mat[q].getRow() > result3->mat[q + 1].getRow()) {
									int temp = result3->mat[q].getRow();
									int temp1 = result3->mat[q].getCol();
									int temp2 = result3->mat[q].getValue();
									result3->mat[q].setRow(result3->mat[q + 1].getRow());
									result3->mat[q].setCol(result3->mat[q + 1].getCol());
									result3->mat[q].setValue(result3->mat[q + 1].getValue());
									result3->mat[q + 1].setRow(temp);
									result3->mat[q + 1].setCol(temp1);
									result3->mat[q + 1].setValue(temp2);
								}
							}
						}

						// the below is a sorting function to sort the column index position 
						//for identical row index
						//col index is sorted in ascending order

						for (int pp = 0; pp < s2 - 1; pp++) {//this is a sorting function
							for (int qq = 0; qq < s2 - 1; qq++) {
								if (result3->mat[qq].getRow() == result3->mat[qq+1].getRow() &&
									result3->mat[qq].getCol() > result3->mat[qq + 1].getCol()) {
									int temp3 = result3->mat[qq].getRow();
									int temp4 = result3->mat[qq].getCol();
									int temp5 = result3->mat[qq].getValue();
									result3->mat[qq].setRow(result3->mat[qq + 1].getRow());
									result3->mat[qq].setCol(result3->mat[qq + 1].getCol());
									result3->mat[qq].setValue(result3->mat[qq + 1].getValue());
									result3->mat[qq + 1].setRow(temp3);
									result3->mat[qq + 1].setCol(temp4);
									result3->mat[qq + 1].setValue(temp5);
							
								}
							}
						}
									
						return result3;  // this returns the  pointer to the result of the multiplication  matrix when it is called from main
					
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

// read in all the numRows, numCols and numNonZero values from redirected input for matrix B
cin >> numRows >> numCols >> numNonZero;

// declare object for matrix B
matrixClass* b = new matrixClass(numRows, numCols, numNonZero);

// read in the values and use setValue to set the values read in for B
for (int r = 0; r < numNonZero; r++) {
	cin >> t >> u >> val;
	try {
		if (t > numRows-1)
			throw  ExceptionRowBouce();
		if (u > numCols-1)
			throw ExceptionColBounce();

		(*b).setValue(r, t, u, val);

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

// display matrix B
cout << "B in SparseRow format: " << endl;
(*b).display();

cout << "B in Matrix format: " << endl;
//cout << b; // use ostream operator 
cout << *b;

// declare resultant matrix to store A * B
matrixClass* result2 = a->multiply(b);

// call to multiplication method being made
// exception handling added to try-catch multiplication dimension mismatch

try {

	if (a->getNumCols() != b->getNumRows())
		throw ExceptionMultiplicationMismatch();

	cout << "RESULT A*B in SparseRow format: " << endl;
	result2->display();

	cout << "RESULT A*B in Matrix format: " << endl;
	//cout << resultMultiply; // use ostream operator method
	cout << *result2;
}

//catch block for exception handling for multiplication dimension mismatch

catch (ExceptionMultiplicationMismatch myException5){
	cout << "Matrix Dimension Mismatch for Multiplication exception thrown " <<endl;
}

delete result2;//deletes the result2 matrixClass object

// this is a call to the add method for addition of matrices
// exception handling added to try-catch multiplication dimension mismatch

matrixClass* result1 = a->add(b);


try {
	if (a->getNumRows() != b->getNumRows() && b->getNumRows() != b->getNumCols())
		throw ExceptionAdditionMismatch();

	// declare resultant matrix to store A + B
	
	// display resultant matrix
	cout << "RESULT A+B in SparseRow format: " << endl;
	result1->display();
	cout << "RESULT A+B in Matrix format: " << endl;
	cout << *result1;

}

//catch block for exception handling for addition dimension mismatch

catch(ExceptionAdditionMismatch myException6) {
	cout << "Matrix Dimension Mismatch for Addition exception thrown";

}

	// BONUS
	// declare resultant matrix to store transpose of A

	// display resultant matrix
	// BONUS cout << "RESULT A^T in SparseRow format: " << endl;

	// BONUS cout << "RESULT A^T in Matrix format: " << endl;
	// cout << resultTranspose; use ostream operator method

delete result1; //deletes the result1 matrixClass object 

	return 0;
}


