/* File: LongestCommonSubsequence.cpp
 *
 * This file contains an algorithm for finding the longest common subsequence
 * of two vectors containing the same type of objects. A subsequence of a
 * vector of objects of the same type is a new vector containing some of the
 * objects in the original vector, all in the same order as the original
 * vector. The same order meaning if A and B are two objects in the original
 * vector, and indexA and indexB are the indices where A and B are located in
 * the original object, then newIndexA and newIndexB be will satisfy the same
 * inequality as indexA and indexB do (e.g. if indexA < indexB then newIndexA <
 * newIndexB), where newIndexA and newIndexB are the indices where A and B are
 * located in the new vector.
 *
 * The algorithm uses recursion and memoization to take advantage of subproblem
 * overlap and optimal substructure.
 *
 * A template function is used so that the algorithm works for any types that
 * have a constructor, a copier, a check for equality, and printing of the type
 * to stdout.
 *
 * Compile with -std=c++11 for initializing a vector from an array used in
 * main (not essential to the algorithm).
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


// Function mapTwoIntegersToOneInteger
//
// Inputs: num1 - One of the numbers to be combined into a single number.
//         num2 - The other number to be combined into a single number.
// 
// Output: Returns Szudzik's function of num1 and num2. This provides a unique
//         integer which is within the bounds of twice the size of the maximum
//         value between num1 and num2. I.e. if num1 and num2 are less than or
//         equal to the maximum 32-bit integer than this function will return a
//         number less than or equal to the maximum 64-bit integer. 
//
// This function is useful for turning two integers into a unique integer to be
// used as the key for a map.
int mapTwoIntegersToOneInteger(int num1, int num2)
{
    return (num1 >= num2 ? num1*num1 + num1 + num2 : num1 + num2*num2);
}

// Function findLongestCommonSubsequence
//
// Inputs: sequence1 - The first of two sequences used in searching for the
//                     longest common subsequence between them.
//         currentIndex1 - The index of the element of sequence1 that will be
//                         compared against sequence2.
//         sequence2 - The second of two sequences used in searching for the
//                     longest common subsequence between them.
//         currentIndex2 - The index of the element of sequence2 that will be
//                         compared against sequence1.
//         currentCommonSubsequence
//             - The longest common subsequence of sequence1 and sequence2 that
//               has been found so far.
//         memoizer - A map whose keys are integers formed from combining the
//                    two current indices of both sequences, and whose values
//                    are the longest common subsequence starting at those
//                    indices. 
//
// Output: A vector containing the longest common subsequence of the two input
//          sequences.
//
// This function uses a recursive algorithm with memoization. We compare the
// elements at the current indices, and if they are equal then we append them
// to the longest common subsequence and recursively call the function at the
// next higher indices. If they are not equal then we have to find the two
// remaining possible subsequence extensions by:
// (1) Incrementing currentIndex1 and leaving currentIndex2 unchanged, or
// (2) Leaving currentIndex1 unchanged and incrementing currentIndex2,
// The longest common subsequence is then the longest out of these two options.
//
// The case of incrementing both indices will occur inside the recursive calls
// of both (1) and (2), leading to double checking the same solution, hence
// this algorithm is improved by storing solutions as we compute them and
// looking for an already computed solution before we compute one.
//
// If multiple longest commone subsequences with the same length are found we
// return only the one that was found first.
//
// A template argument, T, is used. The requirements for a type to be used are:
// (a) The type has a constructor,
// (b) Two instances of the type can be checked for equality,
// (c) The type has a function for copying into another instance of the same
// type (used in the vector push_back() call).
template <class T>
vector<T> findLongestCommonSubsequence(vector<T> &sequence1, int currentIndex1,
                                       vector<T> &sequence2, int currentIndex2,
                                       vector<T> &currentCommonSubsequence,
                                       unordered_map<int, vector<T> > &memoizer)
{
    // Makre sure the indices are within the bounds of the vectors:
    if (currentIndex1 < 0 || currentIndex2 < 0 ||
        currentIndex1 >= sequence1.size() || currentIndex2 >= sequence2.size())
    {
        return currentCommonSubsequence;
    }

    // If the elements at the current indices are equal then we can extend the
    // longest known sequence by this element:
    if (sequence1[currentIndex1] == sequence2[currentIndex2])
    {
        vector<T> newCommonSubsequence, resultCommonSubsequence;
        int key = mapTwoIntegersToOneInteger(currentIndex1+1, currentIndex2+1);
        auto got = memoizer.find(key);

        newCommonSubsequence.push_back(sequence1[currentIndex1]);

        // Check if the longest common subsequence starting at indices
        // (currentIndex1 + 1) and (currentIndex2 + 1) has already been found:
        if (got != memoizer.end())
        {
            // Prepend the current element to the known longest common sequence
            // starting at (currentIndex1+1) and (currentIndex2+1):
            newCommonSubsequence.insert(newCommonSubsequence.end(),
                                        got->second.begin(), got->second.end());

            // Store the longest common subsequence for indices currentIndex1
            // and currentIndex2:
            memoizer.emplace(key, newCommonSubsequence);

            return newCommonSubsequence;
        }
        // If the solution wasn't already calculated then calculate and store
        // it:
        else
        {
            vector<T> temp = findLongestCommonSubsequence(sequence1,
                                 currentIndex1+1, sequence2, currentIndex2+1,
                                 newCommonSubsequence, memoizer);
            memoizer.emplace(key, temp);
            return temp;
        }
    }
    // If the elements a the current indices are not equal then check the two
    // ways we can extend the sequence:
    else
    {
        vector<T> longestCandidate1, longestCandidate2;
        int key1 = mapTwoIntegersToOneInteger(currentIndex1+1, currentIndex2);
        int key2 = mapTwoIntegersToOneInteger(currentIndex1, currentIndex2+1);
        auto got1 = memoizer.find(key1);
        auto got2 = memoizer.find(key2);

        // Check if the longest common subsequence starting at indices
        // (currentIndex1 + 1) and currentIndex2 has already been found:
        if (got1 != memoizer.end())
        {
            longestCandidate1 = got1->second;
        }
        // If not then calculate and store it:
        else
        {
            longestCandidate1 = findLongestCommonSubsequence(sequence1,
                                    currentIndex1+1, sequence2, currentIndex2,
                                    currentCommonSubsequence, memoizer);

            memoizer.emplace(key1, longestCandidate1);
        }

        // Check if the longest common subsequence starting at indices
        // currentIndex1 and (currentIndex2 + 1) has already been found:
        if (got2 != memoizer.end())
        {
            longestCandidate2 = got2->second;
        }
        // If not then calculate and store it:
        else
        {
            longestCandidate2 = findLongestCommonSubsequence(sequence1,
                                    currentIndex1, sequence2, currentIndex2+1,
                                    currentCommonSubsequence, memoizer);

            memoizer.emplace(key2, longestCandidate2);
        }

        // Now compare the sizes of the candidates and return the larger one:
        int size1 = longestCandidate1.size(), size2 = longestCandidate2.size();

        if (size1 >= size2)
        {
            return longestCandidate1;
        }
        else
        {
            return longestCandidate2;
        }
    }
}

// Function PrintSequence
//
// Input: sequence - A sequence of elements of arbitary type T.
// Output: None.
//
// This function uses a template type, T, which must have a function for
// printing to stdout.
template<class T>
void printSequence(vector<T> sequence)
{
    for (int i = 0; i < sequence.size(); ++i)
    {
        cout << sequence[i] << " ";
    }
}


// Driver code:
int main()
{
    vector<int> sequence1{1, 2, 5, 7, 9, 11, 13};
    vector<int> sequence2{-1, 2, -5, 7, -9, 11, -13};
    vector<int> sequence3{-99, -99, -99, -99, 7, 9, 11, 13};
    int startIndex1 = 0, startIndex2 = 0, startIndex3 = 0;
    unordered_map<int, vector<int> > memoizer;

    vector<int> currentCommonSubsequence; // Initially empty
    vector<int> longestCommonSubsequence12 = 
        findLongestCommonSubsequence(sequence1, startIndex1,
                                     sequence2, startIndex2,
                                     currentCommonSubsequence, memoizer);

    currentCommonSubsequence.clear();
    memoizer.clear();
    vector<int> longestCommonSubsequence13 =
        findLongestCommonSubsequence(sequence1, startIndex1,
                                     sequence3, startIndex3,
                                     currentCommonSubsequence, memoizer);

    currentCommonSubsequence.clear();
    memoizer.clear();
    vector<int> longestCommonSubsequence23 =
        findLongestCommonSubsequence(sequence2, startIndex2,
                                     sequence3, startIndex3,
                                     currentCommonSubsequence, memoizer);


    cout << "Sequence 1: { ";
    printSequence(sequence1);
    cout << "}" << endl;

    cout << "Sequence 2: { ";
    printSequence(sequence2);
    cout << "}" << endl;

    cout << "Sequence 3: { ";
    printSequence(sequence3);
    cout << "}" << endl;

    cout << "Longest common subsequence of Sequences 1 and 2: { ";
    printSequence(longestCommonSubsequence12);
    cout << "}" << endl;

    cout << "Longest common subsequence of Sequences 1 and 3: { ";
    printSequence(longestCommonSubsequence13);
    cout << "}" << endl;

    cout << "Longest common subsequence of Sequences 2 and 3: { ";
    printSequence(longestCommonSubsequence23);
    cout << "}" << endl;

    return 0;
}
