#include<iostream>
#include<exception>

//This is Only the Documentation for then Bonus Part of Project 2.
//Ramkishore Rao's Project DSA 5005
//See Main File for the Rest of the Documentation

using namespace std;

class Exception {};

class ExceptionRowBouce : public Exception {};
class ExceptionColBounce : public Exception {};
class ExceptionAdditionMismatch : public Exception {};
class ExceptionMultiplicationMismatch : public Exception {};

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
	void display(); // print Row#, Column#, value
	void setRow(int r); // setters
	void setCol(int c);
	void setValue(int v);
	int getRow(); // getters
	int getCol();
	int getValue();

	
};


class matrixClass {
	friend ostream& operator <<(ostream& s, matrixClass& p);
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
	matrixClass(matrixClass& copyThis); // copy constructor
	void display(); // display in sparse row format
	void displayMatrix(); // display in matrix format
	void setValue(int pos, int i, int j, int val); // to set the value at location i, j; pos is to keep track of the position in mat
	int getValue(int i, int j); // return val at i, j
	int getNumRows(); // getter for numRows
	int getNumCols(); // getter for numCols
	int getValWithRowandCol(int row, int col); // given row and col number, return the value at that spot
	int length();
	matrixClass* multiply(matrixClass* multiplier); // multiply method
	matrixClass* add(matrixClass* addend); // add method
        matrixClass* transpose();//method for the development of the transpose of a matrix	
	void displayTranspose();//method to display the transpose of the matrix

	
};

	
	SparseRow::SparseRow()
	{
		row = -1;
		col = -1;
		value = 0;
	}

	SparseRow::SparseRow(int r, int c, int val) {
	row = r;
	col = c;
	value = val;
	
}

	SparseRow::~SparseRow() {
	
	}


	void SparseRow::setRow(int r) {
		row = r;
			
	}

	void SparseRow::setCol(int c) {
		col = c;
	}

	void SparseRow::setValue(int v) {
		value = v;
			}

	int SparseRow::getRow() {
		return row;
	}

	int SparseRow::getCol() {
		return col;
	}

	int SparseRow::getValue() {
		return value;
	}

	void SparseRow::display() {

		cout << getRow() << getCol() << getValue() << endl;
	
	}

	matrixClass::matrixClass() {
		numRows = 0;
		numCols = 0;
		numNonZero = 0;
		commonValue = 0;
		mat = NULL;
	}

	matrixClass::matrixClass(int r, int c, int nz) {
		numRows = r; 
		numCols = c;
		numNonZero = nz;
		commonValue = 0;
		mat = new SparseRow[numNonZero];
		
		}

	matrixClass::matrixClass(matrixClass& copyThis) {
		numRows = copyThis.numRows; 
		numCols = copyThis.numCols;
		numNonZero = copyThis.numNonZero;
		commonValue = copyThis.commonValue;
		mat = copyThis.mat;
	}


	matrixClass::~matrixClass() {
	

	delete []mat;
	mat = NULL;
	
	}

	int matrixClass::getNumRows()
	{
		return numRows;
	}

	
	int matrixClass::getNumCols()
	{
		return numCols;
	}

	void matrixClass::setValue(int pos, int i, int j, int val) {
		mat[pos].setRow(i);
		mat[pos].setCol(j);
		mat[pos].setValue(val);
	
	}

	int matrixClass :: length() {
		
		return numNonZero;
	   
	}

	int matrixClass::getValue(int i, int j) {
		
		int l =0;
		int value1;

					for (l = 0; l < this->length(); l++) {
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
		int value;
		int i = row;
		for (int l = 0; l < length(); l++) {
		value = this->mat[l].getValue();
	}
		return 0;
	}


	void matrixClass::display() {
		int length = this->length();
		cout << "Row" << "|" << "Column" << "|" << "Value" << endl;
		for (int l = 0; l < length; l++) {
			if (this->mat[l].getRow() <= this->getNumRows() && this->mat[l].getCol() <=this->getNumCols()&&this->mat[l].getRow()>=0 && this->mat[l].getCol() >=0 )
			cout << this->mat[l].getRow() << " " << this->mat[l].getCol() << " " << this->mat[l].getValue() << endl;
		}
	}

	void matrixClass::displayMatrix() {
		int val1{};
		int i, j;
		int length = this->length();

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

	//Method to Display Transpose of the Matrix
	//The change here is that the numRows and numCols are flipped
	//from the original input as it is a transpose of the matrix
	//returns the cell value if i,j matches the values in the Sparse Row
	//otherwise common value of 0 is returned.

	void matrixClass::displayTranspose() {
		int val1{};
		int i, j;//row and col index
		int length = this->length();//length of the array

		for (int i = 0; i < getNumCols(); i++) {
			for (int j = 0; j < getNumRows(); j++) {
				for (int l = 0; l < length; l++) {
					if (i == mat[l].getRow() && j == mat[l].getCol()) {
						val1 = mat[l].getValue();
						break;
					}
					else {
						val1 = commonValue;
					}
				}

				cout << val1 << " ";
			}
			cout << endl;
		}
	}


	
	ostream& operator <<(ostream& s, matrixClass& p) {
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

					int length = this->length();
					int length1 = addend->length();

					matrixClass* sum = new matrixClass(this->getNumRows(), this->getNumCols(), (length + length1+2));

					int i, j, l, s, s1;
					i = 0;
					l = 0;
					j = 0;
					s = 0;
					s1 = 0;

					while ((i <= length) && (j <= length1))
					{
						if (this->mat[i].getRow() == addend->mat[j].getRow() && this->mat[i].getCol() == addend->mat[j].getCol())
						{
							sum->mat[s].setRow(this->mat[i].getRow());
							sum->mat[s].setCol(this->mat[i].getCol());
							sum->mat[s].setValue(this->mat[i].getValue() + addend->mat[j].getValue());
							i++;
							j++;
							s++;
						}
						else if (this->mat[i].getRow() == addend->mat[j].getRow() && this->mat[i].getCol() < addend->mat[j].getCol()) {

							sum->mat[s].setRow(this->mat[i].getRow());
							sum->mat[s].setCol(this->mat[i].getCol());
							sum->mat[s].setValue(this->mat[i].getValue());

							i++;
							s++;
						}
						else if (this->mat[i].getRow() == addend->mat[j].getRow() && this->mat[i].getCol() > addend->mat[j].getCol()) {

							sum->mat[s].setRow(addend->mat[j].getRow());
							sum->mat[s].setCol(addend->mat[j].getCol());
							sum->mat[s].setValue(addend->mat[j].getValue());
							j++;
							s++;
						}
						else if (this->mat[i].getRow() < addend->mat[j].getRow()) {
							sum->mat[s].setRow(this->mat[i].getRow());
							sum->mat[s].setCol(this->mat[i].getCol());
							sum->mat[s].setValue(this->mat[i].getValue());
							i++;
							s++;
						}

						else if (this->mat[i].getRow() > addend->mat[j].getRow()) {
							sum->mat[s].setRow(addend->mat[j].getRow());
							sum->mat[s].setCol(addend->mat[j].getCol());
							sum->mat[s].setValue(addend->mat[j].getValue());
							j++;
							s++;
						}
					}

					if (i <= length)
					{
						for (int p = i; i < length; p++) {
							sum->mat[s].setRow(this->mat[i].getRow());
							sum->mat[s].setCol(this->mat[i].getCol());
							sum->mat[s].setValue(this->mat[i].getValue());
							s++;
						}
					}
					else if (j <= length1)
					{
						for (int p = j; j < length1; p++) {
							sum->mat[s].setRow(addend->mat[j].getRow());
							sum->mat[s].setCol(addend->mat[j].getCol());
							sum->mat[s].setValue(addend->mat[j].getValue());
							s++;
						}
					}
					matrixClass* sum1 = new matrixClass(sum->getNumRows(), sum->getNumCols(), (s+1));
					
					for (l = 0; l < s; l++) {
						sum1->mat[s1].setRow(sum->mat[l].getRow());
						sum1->mat[s1].setCol(sum->mat[l].getCol());
						sum1->mat[s1].setValue(sum->mat[l].getValue());
						s1++ ;
					}
					return sum1;
			
	}
		//SEE MAIN PROGRAM FOR DOCUMENTATION OF THIS METHOD
			matrixClass* matrixClass::multiply(matrixClass * multiplier) {
		
						int length = this->length();
						int length1 = multiplier->length();
				
			            int s = 0;
						int s1 = 0;
						int s2 = 0;
						int l, m,z;
						int sum;
						int sum1;
						matrixClass* result = new matrixClass(this->getNumRows(), multiplier->getNumCols(), length * multiplier->getNumRows());
						matrixClass* result2 = new matrixClass(this->getNumRows(), multiplier->getNumCols(), length * multiplier->getNumRows());

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
						for (l = 0; l < s; l++) {
							sum1 = result->mat[l].getValue();
							
							for (m = 0; m < s; m++) {
								if (result->mat[l].getRow() == result->mat[m].getRow() &&
									result->mat[l].getCol() == result->mat[m].getCol() && l != m)
									sum1 =  sum1+ result->mat[m].getValue();
					                 			
							}

							result2->mat[s1].setRow(result->mat[l].getRow());
							result2->mat[s1].setCol(result->mat[l].getCol());
							result2->mat[s1].setValue(sum1);
							s1++ ;
						}
						
						matrixClass* result3 = new matrixClass(result2->getNumRows(), result2->getNumCols(), (s1+1));
						for (z = 0; z < s1; z++) {
							result3->mat[s2].setRow(result2->mat[z].getRow());
							result3->mat[s2].setCol(result2->mat[z].getCol());
							result3->mat[s2].setValue(result2->mat[z].getValue());
							s2++;
						}

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

						for (int pp = 0; pp < s2 - 1; pp++) {
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
									
						return result3;
					
				}
	
			// this is the method for the multiplication of 2 matrices

			matrixClass* matrixClass::transpose() {
				
				int s = 0;//index for position in array of SparseRow Objects in the matrixClass object
				int length = this->length();//length of the Sparse Row Array in the matrixClass object

				//new matrixClass object created to store the result of the transpose of the matrix

				matrixClass* transpose = new matrixClass(this->getNumRows(), this->getNumCols(), length);
				
				// this loops through the original matrix and flips the row and col indices and 
				//does not change the cell value from the original matrix

				for (int i = 0; i < length; i++) {
					
					transpose->mat[s].setRow(this->mat[i].getCol());
					transpose->mat[s].setCol(this->mat[i].getRow());
					transpose->mat[s].setValue(this->mat[i].getValue());
					s++;
				}

				// this is a bubble sort alogorithm that sorts the row index of the resultant
				//SparseRow Array in ascending order

				for (int p = 0; p < s - 1; p++) {
					for (int q = 0; q < s-1 - 1; q++) {
						if (transpose->mat[q].getRow() > transpose->mat[q + 1].getRow()) {
							int temp = transpose->mat[q].getRow();
							int temp1 = transpose->mat[q].getCol();
							int temp2 = transpose->mat[q].getValue();
							transpose->mat[q].setRow(transpose->mat[q + 1].getRow());
							transpose->mat[q].setCol(transpose->mat[q + 1].getCol());
							transpose->mat[q].setValue(transpose->mat[q + 1].getValue());
							transpose->mat[q + 1].setRow(temp);
							transpose->mat[q + 1].setCol(temp1);
							transpose->mat[q + 1].setValue(temp2);
						}
					}
				}

				// this is sorting the col index in ascending order when the row index
				//is the same

				for (int pp = 0; pp < s - 1; pp++) {
					for (int qq = 0; qq < s - 1; qq++) {
						if (transpose->mat[qq].getRow() == transpose->mat[qq + 1].getRow() &&
							transpose->mat[qq].getCol() > transpose->mat[qq + 1].getCol()) {
							int temp3 = transpose->mat[qq].getRow();
							int temp4 = transpose->mat[qq].getCol();
							int temp5 = transpose->mat[qq].getValue();
							transpose->mat[qq].setRow(transpose->mat[qq + 1].getRow());
							transpose->mat[qq].setCol(transpose->mat[qq + 1].getCol());
							transpose->mat[qq].setValue(transpose->mat[qq + 1].getValue());
							transpose->mat[qq + 1].setRow(temp3);
							transpose->mat[qq + 1].setCol(temp4);
							transpose->mat[qq + 1].setValue(temp5);

						}
					}
				}
				return transpose;  //returns the pointer to the transpose of the matrix when called from the main function

			}

						

// main function
			int main()
			{
				int numRows, numCols, numNonZero, t, u, val;

				// read in all the numRows, numCols and numNonZero values from redirected input for matrix A
				cin >> numRows >> numCols >> numNonZero;

				// declare object for matrix A
				matrixClass* a = new matrixClass(numRows, numCols, numNonZero);

				// read in the values and use setValue to set the values read in for A
				for (int r = 0; r < numNonZero; r++) {
					cin >> t >> u >> val;

					try {
						if (t > numRows - 1) {

							throw  ExceptionRowBouce();
						}
						if
							(u > numCols - 1) {
							throw ExceptionColBounce();
						}

						(*a).setValue(r, t, u, val);
					}

					catch (ExceptionRowBouce myException3) {
						cout << "Row Out of Bounce exception thrown – stopping execution";
						return 0;
					}
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
						if (t > numRows - 1)
							throw  ExceptionRowBouce();
						if (u > numCols - 1)
							throw ExceptionColBounce();

						(*b).setValue(r, t, u, val);

					}
					catch (ExceptionRowBouce myException3) {
						cout << "Row Out of Bounce exception thrown – stopping execution";
						return 0;
					}
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

		
				try {

					if (a->getNumCols() != b->getNumRows())
						throw ExceptionMultiplicationMismatch();

					cout << "RESULT A*B in SparseRow format: " << endl;
					result2->display();

					cout << "RESULT A*B in Matrix format: " << endl;
					//cout << resultMultiply; // use ostream operator method
					result2->displayMatrix();
				}


				catch (ExceptionMultiplicationMismatch myException5) {
					cout << "Matrix Dimension Mismatch for Multiplication exception thrown " << endl;
				}



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

catch(ExceptionAdditionMismatch myException6) {
	cout << "Matrix Dimension Mismatch for Addition exception thrown";

}


	// BONUS
	// declare resultant matrix to store transpose of A

matrixClass* transpose = a->transpose();

	// display resultant matrix
	cout << "RESULT A^T in SparseRow format: " << endl;
	transpose->display();

	 cout << "RESULT A^T in Matrix format: " << endl;
	transpose->displayTranspose();
	
	//deletes objects after program completes execution

	delete result2;
	delete result1;
	delete transpose;


	return 0;
}


