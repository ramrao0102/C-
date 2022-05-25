#include<iostream>

using namespace std;

class matrixClass {
protected:
    int** mat; //2 D dynamic array to store matrix
    int numRows, numCols; //number of rows and number of columns
 
 public:
    matrixClass(); //default constructor
    matrixClass(int r, int c); //non default constructor
    ~matrixClass();// destructor for matrixClass
    void setValue(int i, int j, int val ); // to set value at location i, j
    int getValue(int i, int j);//return val at i,j
    int getRows(); //getter for numRows
    int getCols(); // getter for numCols
    void display(); //display
    matrixClass* multiply(matrixClass *multiplier); //multiply method

};
//default constructor method
matrixClass::matrixClass() {
    mat[3][3] = NULL;
}

//non default constructor method
matrixClass::matrixClass(int r, int c) {
    numRows = r;
    numCols = c;
    mat = new int* [r];
        int i, j;
    for (i = 0; i < r; i++) {
        mat[i] = new int[c];
    }
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            mat[i][j] = 0;
        }
    }
}
//destruct for matrixClass constructor
 matrixClass:: ~matrixClass() {
    int i;
    for (int i = 0; i < numRows; i++)
    {
        delete[] mat[i];
    }
    delete[] mat;
}

 //method to set values
void matrixClass::setValue(int i, int j, int val) {
     
    mat[i][j] = val;
          
  }

//method to return values
int matrixClass::getValue(int i, int j) {
        
    return mat[i][j];
}

//method getter for number of rows
int matrixClass::getRows()
{
    int i;
    i = numRows;
    return numRows;
}

//method getter for number of columns
int matrixClass::getCols()
{
    int j;
    j = numCols;
    return numCols;
}

 //method for multiplication of matrices
 matrixClass* matrixClass::multiply(matrixClass *multiplier) {
     matrixClass* result = new matrixClass(this ->getRows(), multiplier->getCols());
     int i, j, k;

     for (i = 0; i < this -> getRows(); i++) {
         for (j = 0; j < multiplier->getCols(); j++) {
             (*result).mat[i][j] = 0;
             for (k = 0; k < this->getCols(); k++) {
                 (*result).mat[i][j] += this ->mat[i][k] * multiplier->mat[k][j];
                 
             }

         }
         
     }
    
 
     
     return result;//return pointer to result matrix
 }

 //method for displaying matrix
void matrixClass::display() {
    int i, j;
    int k;
    
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            k = getValue(i, j);
            cout << k << " ";
            
        }
        cout << endl;
    }
}

int main() {
    int p, q, x, y, t, u, tot1, tot2, val;
    
    //input for number of non zero rows, columns, and non zero values for matrix A
    cin >> x >> y >> tot1;
    
    //declare object for matrix A

    matrixClass* a = new matrixClass(x,y);
      
    //call set non zero values for matrix A
    for (int r = 0; r < tot1; r++) {
    cin >> t >> u >> val;
    (*a).setValue(t, u, val);
}
    //display matrix A
    cout << "A:" << endl;
    (*a).display();

    //input for number of non zero rows, columns, and non zero values for matrix B
    cin >> p >> q >> tot2;

    //declare object for matrix B

     matrixClass * b = new matrixClass(p, q);
     
    //call set non zero values for matrix B

     for (int r = 0; r < tot2; r++) {
         cin >> t >> u >> val;
         (*b).setValue(t, u, val);
     }
    
     //display matrix B

    cout << "B:" << endl;
    (*b).display();
    
   
    cout << "RESULT:" << endl;

    //call method for result of matrix multiplication

    matrixClass* result = a->multiply(b);

    //display result matrix of multiplication

    result->display();
    

    return 0;
    
}
