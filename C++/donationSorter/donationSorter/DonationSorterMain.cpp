/******************************
   William Morgan
   8/29/2018
   donationSorter.cpp
   Program asks user for number of donations, get the donations,
   and then sorts in ascending order
********************************/

// Headers
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

// Function declarations
void arrSelectionSort(int** ptrToElems, int size);
void displayDonations(int* donations, int size);
void displaySortedDonations(int** ptrToElems, int size);
int** createPtrArray(int* donations, int size);
int* getDonations(int size);

int main()
{
	int numDonations;	// number of donations to enter

	// Get the number of donations from user
	cout << "How many donations do you want to record: ";
	cin >> numDonations;

	// Create an array to hold the donations and get the donations
	int* donations = getDonations(numDonations);

	// Create an array of pointers to ints
	int** ptrDonations = createPtrArray(donations, numDonations);

	// Sort the donations
	arrSelectionSort(ptrDonations, numDonations);

	// Display the donations in original order
	cout << endl;
	cout << "Donations before being sorted:\n";
	displayDonations(donations, numDonations);

	// Display the donations in sorted order
	cout << endl;
	cout << "Donations sorted:\n";
	displaySortedDonations(ptrDonations, numDonations);

    
    
	//	Make sure we place the end message on a new line
    cout << endl;

	//	The following is system dependent.  It will only work on Windows
    system("PAUSE");

	/* 
	// A non-system dependent method is below
	cout << "Press any key to continue";
	cin.get();
	*/
    return 0;
}

// Sort the pointer values in ptrToElems
void arrSelectionSort(int ** ptrToElems, int size)
{
	int startScan,		// where we start searching from
		minIndex;		// which index contains the smallest that we've seen so far
	int* ptrMinElem;	// point to the elem with the smallest value

	for (startScan = 0; startScan < size -1; startScan++)
	{
		minIndex = startScan;
		ptrMinElem = *(ptrToElems + startScan);
		for (int index = startScan + 1; index < size; index++)
		{
			if (*(*(ptrToElems + index)) < *ptrMinElem)
			{
				ptrMinElem = *(ptrToElems + index);
				minIndex = index;
			}
		}
		*(ptrToElems + minIndex) = *(ptrToElems + startScan);
		*(ptrToElems + startScan) = ptrMinElem;
	}
}

// display the donations
void displayDonations(int * donations, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << *(donations + i) << endl;
	}
}

// display the donations in sorted order
void displaySortedDonations(int ** ptrToElems, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << *(*(ptrToElems + i)) << endl;
	}
}

// Create an array of pointers to ints
// Each element in an array will point to an element in donations
int ** createPtrArray(int * donations, int size)
{
	int** ptrDonations = new int*[size];

	for (int i = 0; i < size; i++)
	{
		*(ptrDonations + i) = (donations + i);
	}
	return ptrDonations;
}

// gets the donations from the user, saves them to a dynamic array
// returns the address of the dynamic array
int * getDonations(int size)
{
	int* arr = new int[size];

	for (int i = 0; i < size; i++)
	{
		cout << "Enter amount for donation " << i + 1 << ": ";
		cin >> *(arr + i); // arr[i]
	}
	
	return arr;
}
