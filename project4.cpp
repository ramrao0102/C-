#include <iostream>
#include <list>
#include <iterator>
#include<exception>
 
/* This is Ramkishore Rao's DSA5005 Project 4 code*/

using namespace std;

class Exception {}; // exception class to handle array out of bounds exception

class Exceptionoutofbounds : public Exception {};  //extension created to handle out of bounds for array index

template <class DT>
class setArrayClass
{
	protected:
		list<DT>* arrOfSets; // array of sets/lists
		int lengthOfArray; // length of the array / number of sets

	public: 
		setArrayClass(); // default constructor
		setArrayClass(int n); // non default constructor
		~setArrayClass(); //destructor
		int getLength(); // get the number of sets / array length
		void setLength(int l); // set the length field with the l value
		list<DT> getSet(int i); // return A[i]
		void setValue(int setIndex, DT val); // set the value val in the setIndex position's set
		void display(); // display in the given format the array of sets
		list<DT> setUnion(list<DT> l1, int l); // find the union between set l1 and A[l] and return result
		list<DT> setIntersection(list<DT> l1, int l); // find the intersection between set l1 and A[l] and return result
		list<DT> setComplement(int l); // find the compliment of A[l] and return that list

		// other methods necessary

};

template<class DT>
setArrayClass<DT>::setArrayClass()// setting the parameter values for the default constructor
{
	arrOfSets = NULL;
	lengthOfArray = 0;

}

template<class DT>
setArrayClass<DT>::setArrayClass(int n)  // setting the parameter values for the non default constructor
{
	lengthOfArray =n;//setting length of array to total array index
	arrOfSets = new list<DT>[n];//creating an array of sets of length equal to length of Array

}

template<class DT>  //destructor for setArrayClass
setArrayClass<DT>::~setArrayClass()
{
	delete[]arrOfSets;
	arrOfSets = NULL;

}


template<class DT>  // method to return length of the array of sets
int setArrayClass<DT>::getLength()
{
	int length = lengthOfArray;
	return length;
}

template<class DT>  // this method is not being used
void setArrayClass<DT>::setLength(int l)
{
	//return 0;
}

template<class DT> //returns the set of integers based on called index value
list<DT> setArrayClass<DT>::getSet(int i)
{
	return arrOfSets[i];
}

template<class DT> // sets the index and the integer value for the set for the array of Sets
void setArrayClass<DT>::setValue(int setIndex, DT val)
 {
	int i = setIndex;
	int j = val;

	arrOfSets[i].push_back(j);  
 }

template<class DT>  // this prints the array of sets, looped through 0 to lengthofarray-1
void setArrayClass<DT>::display()
{
	for (int l = 0; l < this->getLength(); l++) {
		cout << "A[" << l << "]: ";
		for (list<int>::iterator m = arrOfSets[l].begin(); m != arrOfSets[l].end(); m++) {
			cout << *m << " ";
		}
		cout << endl;
	}
}


template<class DT>  // this is a method that computes the union of two sets
list<DT> setArrayClass<DT>::setUnion(list<DT> l1, int l)
{
	std::list<int> list1; //list created to get the set for integer l
	std::list<int> result;  //list created to store the result list
	
	//gets the set value if index is greater than or equal to zero
	if (l >= 0) {
		list1 = getSet(l);
	  }
	
	//if index is less than zero then the complement method is called
	    else{ 
		  list1 = setComplement(l);
	  }
	
	// the value from list l1 is passed from main function into the result set
	for (list<int> ::iterator i = l1.begin(); i != l1.end(); i++)
	{
		result.push_back(*i);
	}
	
	// if the list l1 and thus the result set have zero elements
	// then all of list 1 is pushed into the result set.

	if (result.size() == 0) {
		for (list<int> ::iterator j = list1.begin(); j != list1.end(); j++) {
			result.push_back(*j);
		}
	}

	// if list1 and thus the result set have more than zero elements
	// then this portion of the code is executed
	// the code iterates through two for loops:  list 1 outer loop and result set
	// inner loop and if the elements in two sets are identical, code breaks out of 
	// the inner loop but if they are not identical at the end of the result list
	// then the element from list 1 is copied onto the result list.

		if (result.size() > 0) {
			for (list<int> ::iterator j = list1.begin(); j != list1.end(); j++) {
				int ll = 0;
				for (list<int> ::iterator k = result.begin(); k != result.end(); k++) {


					ll = ll + 1;
					if (*j == *k)
					{
						break;
					}

					else if (ll == result.size()) {

						result.push_back(*j);

					}
				}
			}
		}
	return result; // result list is returned to main
}

template<class DT>  // this is a method that computes the intersection of two sets
list<DT> setArrayClass<DT>::setIntersection(list<DT> l1, int l)
{
	
	// this is list 1 created to make a list from array index l sent
	// from main function

	std::list<int> list1;
	
	// this is result list created to store the result of the intersection
	//operation

	std::list<int> result;
	
	// list 1 is created for array index l if l>0
	// otherwise the setComplement method is called to create list1

	if (l >= 0) {
		list1 = getSet(l);
	}

	else {
		list1 = setComplement(l);
	}

	// the below loop loops through l1 and list 1 and pushes the element
	//from l1 into the result list if the elements from the two lists are
	//identical

	for (list<int> ::iterator j = l1.begin(); j != l1.end(); j++) {
		for (list <int> ::iterator k = list1.begin(); k != list1.end(); k++) {
			if (*j == *k) {
				result.push_back(*j);
		   }
		}
	}
	
	return result;  // result of this method is sent back to main  
}

template<class DT>  // this is a method that computes the complement of a set
 list<DT> setArrayClass<DT>::setComplement(int l)
{

	 std::list<int> list2;  // this is a list that is created to store elements of interger l passed from main function
	 std::list<int> result; // this is a temp result that is created to help create the final result1 list
	 std::list<int> result1; // this is the final result 1 list created to store the elements of the complement of the set

	 // if l<0; then the sign is reversed before get set method is called
	 // if >0, then the get set method is called directly 

	 if (l < 0) {
		 int l2 = -l;
		 list2 = getSet(l2);
	 }
	 else
	 {
		 list2 = getSet(l);
	 }
	
	 // this is temp result created to store the elements from 0 to 20 inclusive

	for (int j = 0; j <= 20; j++) {
		result.push_back(j);
	}
	
	// if list 2 is empty then all elements from result are transferred to result1 list

	if (list2.size() == 0){
	for (list<int>::iterator i = result.begin(); i != result.end(); i++) {
			result1.push_back(*i);
		}
	}

	// if list2 is not empty, then the following code is executed
	// outer loop is for the result list and inner loop has list 2
	// if elements from both lists are equal, code breaks out of the inner loop
	// however if the elements are not equal then, element from the result list
	//is pushed into result1 list, which basically is the difference between a list
	// that contains all elements 0 to 20 inclusive and list 2

		if (list2.size() > 0) {
			for (list<int>::iterator i = result.begin(); i != result.end(); i++){
			int ll = 0;
			for (list<int>::iterator it1 = list2.begin(); it1 != list2.end(); it1++) {

				ll = ll + 1;
				if (*i == *it1) {

					break;
				}

				if (ll == list2.size()) {

					result1.push_back(*i);
					

				}
			}
		}
	}
	return result1;  // this returns the resulf of this method
}

int main()
{
	int numLists, numElements; // input for number of sets and total number of elements
	char oper;  // this is the character for the operator input via an expression
    int val1, val2; // this is the first operand and the second operand separated by the operator

	// read in the number of lists/array length and the number of total elements
	cin >> numLists >> numElements;  

	// arr1 is the array of lists
	setArrayClass<int>* arr1 = new setArrayClass<int>(numLists);

	// read in the number pairs and insert the element to the specific set index
	for(int i = 0; i < numElements; i++)
	{
		
		cin >> val1 >> val2;
		
		try {// this is an exception block for not allowing element values that are less than 0 and greater
			// than the max array index
		
			if (val1<0 || val1 >= arr1->getLength())
				throw Exceptionoutofbounds();
		

			arr1->setValue(val1, val2); //setter method called for setting values in the arrayClass
		}
		// this is the catch block for the exception thrown
		catch (Exceptionoutofbounds myexception1) {
		
		}
		
		}
	
		
	
	
  
	// display the array of sets
	cout << "Input array of sets: " << endl;

	 arr1->display();
	 		 
	 // this is a list that is created to store the result of the operation

	 std::list<int> result;
	 
	 // this is an iterator to store the Expression Number

	 int i = 0;  

	//read all the expressions to evaluate them and display the answer
 while (!cin.eof())
	 {
		 cin >> val1;  // reads the value of the expression
		 i = i + 1;  // keeps a count of the expression number
		 
		 // if val1 is less than 0; then get complement of arrOfSets with index position of val1

		 if (val1 < 0) {
			 result = arr1->setComplement(val1); // gets the complement set
		 }

		 // if val1 is greater than or equal to 0, then get set with index position val1

		 else {
			
			 result = arr1->getSet(val1);  // gets the set for the first value in the expression
		 }

         // this is a while loop that is used once the first operator token is encountered

		 while (cin >> oper)
		 {
			 if (oper == ';')  // if semi colon is reached, the while loop is terminated and result of the list is displayed
			 {
				 cout << endl;
				 cout << "Expression " << i<<":"<< endl;
				 
				 for (list <int> ::iterator m = result.begin(); m != result.end(); m++) {
					 cout << *m << " ";
					 
				 }
				 cout << endl;
				 break;
			 }
			 cin >> val2;
			 
			 // this is a switch case loop based on what type of operator is encountered
			 // the first case is for +, which reflects the need for an union operation
			 // the second case is for *, which reflects the need for an intersection operation

			 switch (oper) {
			 case '+':

				 result = arr1->setUnion(result, val2); // result is created when union operation is called

				 break;
			 case '*':
				  
				 result = arr1->setIntersection(result, val2);  // result is created when intersection operation is called

                 break;
		  }
		 }
	 }
	
    // this deletes the arra1 object that is created
        delete arr1;  

	return 0;
}

