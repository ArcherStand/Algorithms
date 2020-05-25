/*  File: AlternateArray.cpp
 *
 *  This file contains an algorithm for organizing an array of arbitrary
 *  integers into an order where each element is either greater than or equal
 *  to both its neighbors or less than or equal to both its neighbors and this
 *  alternates with each index. E.g., the input array:
 *  {100, 25, 3, 99, 56, 2, -1, -5} is converted to:
 *  {100, 3, 99, 25, 56, -1, 2, -5}.
 *  The order of the first two elements determines the start of the alternating
 *  pattern (if both elements are equal then we consider the first element to
 *  be larger than the second for purposes of the alternating patter).
 *
 *  Requirements: compile with -std=c++11 for initializing a vector from an
 *  array.
 */

#include<iostream>
#include<vector>

using namespace std;

// Function alternateArray
// 
// Inputs: array - a vector of integers in an arbitrary order
// Outputs: alternateArray - a vector of integers in an alternating order of
//           (greater than or equal to) and (less than or equal to)
//
// The input array is organized so that each element is either larger than or
// equal to both its neighbors or smaller than or equal to both its neighbors,
// and this pattern alternates with each index of the array. E.g. the array
// {100, 25, 3, 99, 56, 2, -1, -5} is converted to the index
// {100, 3, 99, 25, 56, -1, 2, -5}. The order of the firs two elements
// determines the start of the alternating pattern, and if they are equal then
// the starting pattern considers the first element larger than or equal to its
// neighbors.
vector<int> alternateArray(vector<int> array)
{
    vector<int> alternateArray(array);
    bool isMax = true; // Used to track alternation

    // We need at least 3 elements to do anything:
    if (alternateArray.size() > 2)
    {
        // The first two elements determine the start of the alternating
        // pattern:
        if (alternateArray[0] < alternateArray[1])
        {
            isMax = false;
        }

        for (int i = 0; i < array.size(); ++i)
        {
            // Make sure we have two elements to check:
            if (i >= array.size()-1)
            {
                break;
            }

            // If the array order is opposite to the pattern then swap values:
            if ((isMax && alternateArray[i] < alternateArray[i+1]) ||
                (!isMax && alternateArray[i] > alternateArray[i+1]))
            {
                int temp = alternateArray[i];
                alternateArray[i] = alternateArray[i+1];
                alternateArray[i+1] = temp;
            }

            // Negate isMax for alternating the pattern:
            isMax = !isMax;
        }
    }

    return alternateArray;
}

// Function printArray
// 
// Input: array - a vector of integers
// Output: none
//
// This is a helper function for printing a vector of integers.
void printArray(vector<int> array)
{
    cout << "{ ";
    for (int i = 0; i < array.size(); ++i)
    {
        cout << array[i] << " ";
    }
    cout << "}" << endl;
}

// Driver code:
int main()
{
    vector<int> array1{100, 3, 99, 25, 56, -1, 2, -5};
    vector<int> array2{500, -500, -2, 0, 0, 77};
    vector<int> array3{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> array4{9, -1, 9, 9, 9, 9, 9, -1, -1};
    vector<int> alternateArray1, alternateArray2, alternateArray3,
                alternateArray4;

    alternateArray1 = alternateArray(array1);
    alternateArray2 = alternateArray(array2);
    alternateArray3 = alternateArray(array3);
    alternateArray4 = alternateArray(array4);

    cout << "The initial array is: ";
    printArray(array1);
    cout << "The alternated array is: ";
    printArray(alternateArray1);
    cout << endl;

    cout << "The initial array is: ";
    printArray(array2);
    cout << "The alternated array is: ";
    printArray(alternateArray2);
    cout << endl;

    cout << "The initial array is: ";
    printArray(array3);
    cout << "The alternated array is: ";
    printArray(alternateArray3);
    cout << endl;

    cout << "The initial array is: ";
    printArray(array4);
    cout << "The alternated array is: ";
    printArray(alternateArray4);

}
