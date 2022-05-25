//Computing Structures
//Fall 2021
//Project BONUS
//Author: Ramkishore Rao

// This is Ramkishore Rao's Bonus Project

#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for math functions 
#include<unordered_set> // used for generating unique elements

using namespace std;

// this below code for bubble sort and shell sort is from Aditya Narsimhan

// bubble sort algorithm with D number of comparisons allowed
int* bubbleSort(int* arr, int numElements, int D)
{
    int numComp = 0; // used to count the number of comparisons and to check with D

    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
                                        // we want to retain the ordering of arr for shell sort 
    for(int i = 0; i < numElements; i++)
        arrCopy[i] = arr[i];

    // bubble sort starts
    for (int i = 0; i < numElements; i++)
    {
        for (int j = 0; j < numElements - 1; j++)
        {
            numComp++; // incrementing the number of comparisons done right before 
                        // the if condition where the comparison happens each time
            if(numComp >= D) // checking for number of comparisons
                return arrCopy; // return the not necessarily sorted array = approximately sorted array

            if (arrCopy[j] > arrCopy[j + 1])
            {
                // swap
                int temp = arrCopy[j];
                arrCopy[j] = arrCopy[j + 1];
                arrCopy[j + 1] = temp;
            }
        }
    }
    // return the completely sorted array
    return arrCopy;
}

// shell sort algorithm with D number of comparisons allowed
int* shellSort(int* arr, int numElements, int D)
{
    int j;
    int numComp = 0;

    // need not make a copy of the arr array since shell sort is performed later/last

    // Start with a largest increment, then reduce by factors of 3 
    for (int inc = numElements / 3; inc > 1; inc /= 3)
    {
        // Insertion sort for the increment length
        for (int i = inc; i < numElements; ++i)
        {
            int temp = arr[i];
            j = i - inc;

            while ((j >= 0) && (arr[j] > temp))
            {
                numComp++; // incrementing the number of comparisons done right before 
                            // the if condition where the comparison happens each time
                if (numComp >= D) // checking for number of comparisons
                    return arr; // return the not necessarily sorted array = approximately sorted array
                arr[j + inc] = arr[j];
                j = j - inc;
            }
            arr[j + inc] = temp;
        }
    }
    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
    for (int i = 1; i < numElements; ++i)
    {
        int temp = arr[i];
        j = i - 1;

        numComp++; // incrementing the number of comparisons done right before 
                    // the if condition where the comparison happens each time
        if (numComp >= D) // checking for number of comparisons
            return arr; // return the not necessarily sorted array = approximately sorted array

        while ((j >= 0) && (arr[j] > temp))
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
    return arr;
}

//main function
int main()
{   
	int n; // number of elements to be sorted
    int* arr1;  // array 1 is the array to be used to push unique random numbers into
    int* arrsort; //array  for a completed sorted using bubble sort algorthim, complexity of n * n
    int* arrbubblesort; // array for a partially sorted using bubble sort when comparisons are limited to D 
    int* arrshellsort; // array for a partially sorted using shell sort when comparisons are limited to D

	cin >> n; // read the number of elements
	cout << "Number of elements: " << n << endl;

	int s, l, u, D;// reads in seed value for random number, lower and upper limits 
    // for random number generator and for number of comparisons
     
    cin >> s >> l >> u >> D; // read the seed, lower range, upper range and the number of comparisons
    cout << "Number of comparisons allowed: " << D << endl;
    cout << endl;
    srand(s);
	// generate n random elements with the seed s, within the lower and upper range 
    int size = n; // size of array equal to number of elements in input file

    // initializing the arrays dynamically of size n
    arr1 = new int[n];
    arrsort = new int[n];
    arrbubblesort = new int[n];
    arrshellsort = new int[n];
    
    //using unordered set to generate setofNumbers, random unique numbers

    std::unordered_set<int> setOfNum;

    for (int i = 0; i <= size; i++) {
        setOfNum.insert((rand() % (u - l + 1)) + l);
    }

    int ii = 0;
    
   //setif Numbers are pushed into array1

    for (auto it = setOfNum.begin(); it != setOfNum.end(); ++it) {
        *(arr1+ii) = *it ;
        ii = ii + 1;
    }

       
	cout << "Randomly generated elements: ~~~~~~~~~~" << endl;
	// display the array A
    
    for (int i = 0; i < size; i++) {
        cout << *(arr1 + i);
        cout << " ";
    }
    cout << endl;
    cout << endl;

    // use one of the sorting algorithms with the third argument for D as n*n (for bubble sort) and store the fully sorted result 

    // display the completely sorted array

	cout << "Completely sorted elements: ~~~~~~~~~~" << endl;
    
    // calling bubble sort; time compexity of n*n

        arrsort = bubbleSort(arr1, n, n * n);
    
// printing completely sorted array

    for (int i = 0; i < size; i++) {
        
        cout << *(arrsort + i);
        cout << " ";
    }

    cout << endl;
    cout << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Bubble Sort algorithm and store the output array as bubResult in an array
    // calculate and display the two quality measures for bubResult
    cout << "Bubble Sort Result: ~~~~~~~~~~" << endl;

    // display bubResult
    
        arrbubblesort = bubbleSort(arr1, n, D);
         

    for (int i = 0; i < size; i++) {

        cout << arrbubblesort[i];
        cout << " ";
    }

    cout << endl;
    cout << endl;

    // find both the quality metrics for bubResult
    // code to check total number of inversions
    // code to check total number of inversions
    // algorthm that checks number of values to the right of index positions 0 to n-1
    // are actually lower than the given value.  the sum is returned as total number
    // of inversions in an array


    int invbubble;
    invbubble = 0;
    for (int i = 0; i < size-1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (*(arrbubblesort + i) > *(arrbubblesort + j)) {
                invbubble = invbubble +1;
            }
        }
    }
    cout << "Number of inversions in bubResult: ";
    cout << invbubble << endl;
    cout << endl;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    


    // check Maximum displacement/Chebyshev distance for bubResult
    // code to check max distance or difference in position between correct position in 
   // a completely sorted array and the current position in a partially
   // sorted array
    
    
    int k = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arrsort[i] == arrbubblesort[j] && i != j) {
                if (abs(i - j) > k) {
                    k = abs(i - j);
                }
            }

        }
    }

    cout << "Chebyshev distance in bubResult: ";
    cout << k << endl;
    cout << endl;


    // sort the array A with only given D comparions using the Shell Sort algorithm and store the output array as shellResult in an array
    // calculate and display the two quality measures for shellResult
  
    // display shellResult

    cout << "Shell Sort Result: ~~~~~~~~~~" << endl;
    
    arrshellsort = shellSort(arr1, n, D);
        
    
    
    for (int i = 0; i < size; i++) {

        cout << arrshellsort[i] << " ";
        
    }

    cout << endl;
    cout << endl;

    // find both the quality metrics for shellResult
    // code to check total number of inversions
    // algorthm that checks number of values to the right of index positions 0 to n-1
    // are actually lower than the given value.  the sum is returned as total number
    // of inversions in an array

    int invshell;
    invshell = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (*(arrshellsort + i) > *(arrshellsort + j)) {
                invshell = invshell + 1;
            }
        }
    }

    cout << "Number of inversions in shellResult: ";
    cout << invshell << endl;
    cout << endl;


   // check Maximum displacement/Chebyshev distance for shellResult
   // code to check max distance or difference in position between correct position in 
   // a completely sorted array and the current position in a partially
   // sorted array
    
    int k1 = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arrsort[i] == arrshellsort[j] && i != j) {
                if (abs(i - j) > k1) {
                    k1 = abs(i - j);
                }
            }

        }
    }

    cout << "Chebyshev distance in shellResult: ";
    cout << k1 << endl;
      
    return 0;
}
