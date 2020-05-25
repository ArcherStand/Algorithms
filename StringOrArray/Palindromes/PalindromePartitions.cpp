/*  PalindromePartitions.cpp
 *  This program contains and shows example usage of an algorithm which,
 *  given an input string, finds all the substrings which are palindromes,
 *  i.e. all the substrings which are the same after being reversed. E.g.,
 *  for the word 'Originally', the substring palindromes are (in order of
 *  length from smallest to largest): 
 *   O r i g i n a l l y
 *   ll
 *   igi
 */

#include<iostream>
#include<string>
#include<vector>
#include<list>

using namespace std;

// Function isPalindrome
// input: str - the string whose substrings we are checking for palindromes
//        start - the starting index of the substring
//        end - the ending index of the substring
// The strategy is to start from the ends of the string moving inward, checking
// at each step if the endpoints are equal. If the endpoints are ever not
// equal we return false. If the whole string is traveresed from endpoints to
// the center then we return true. 
bool isPalindrome(const string &str, int start, int end)
{
    // Make sure start and end are within the bounds set by the length of str:
    if (start < 0 || end < 0 || start >= str.length() || end >= str.length())
    {
        return false;
    }

    // Since checking for a palindrome is a symmetric process, we can check
    // even when start is actually the end and end is the start:
    if (start > end)
    {
        int temp = start;
        start = end;
        end = temp;
    }

    while (start < end)
    {
        if (str[start] == str[end])
        {
            ++start;
            --end;
        }
        else
        {
            return false;
        }
    }
    // If the while loop didn't return false then we do have a palindrome:
    return true;
}

// Function: findPalindromePartitions
// Inputs: palindromePartitions - a vector of lists of strings which holds the
//          substrings of str that are palindromes. These substrings are stored
//          in order of length, where the ith index of the vector stores a list
//          of all palindrome substrings of length i.
//         str - the main string which contains the substrings to search
//         start - the starting index of the substring to search
//         end - the ending index of the substring to search
void findPalindromePartitions(vector<list<string> >& palindromePartitions,
                              string str, int start, int end)
{
    // Make sure start and end are within the bounds set by the length of str:
    // This also terminates the recursion.
    if (start < 0 || end < 0 || start >= str.length() || end >= str.length())
    {
        return;
    }

    // Since checking for a palindrome is a symmetric process, we can check
    // even when start is actually the end and end is the start:
    if (start > end)
    {
        int temp = start;
        start = end;
        end = temp;
    }

    // Check all substrings of all lengths starting at start:
    for (int i = start; i <= end; ++i)
    {
        if (isPalindrome(str, start, i))
        {
            int length = i-start+1;
            palindromePartitions[length].push_back(str.substr(start, length));
        }
    }
    // Now check all substrings of all lengths starting at the next character,
    // at index start+1:
    findPalindromePartitions(palindromePartitions, str, start+1, end);
}

// Function printPalindromePartitions
// Inputs: palindromePartitions - a vector of lists of strings which holds the
//          substrings of str that are palindromes. These substrings are stored
//          in order of length, where the ith index of the vector stores a list
//          of all palindrome substrings of length i.
void printPalindromePartitions(vector<list<string> > palindromePartitions)
{
    for (int i = 0; i < palindromePartitions.size(); ++i)
    {
        if (palindromePartitions[i].size() != 0)
        {
            for (list<string>::iterator it=palindromePartitions[i].begin();
                    it != palindromePartitions[i].end(); ++it)
            {
                cout << *it << " ";
            }
            cout << endl;
        }
    }
}

int main()
{
    string str1("a"), str2("Originally"), str3("palindromeemordnilap");

    vector<list<string> > pp1(str1.length()+1), pp2(str2.length()+1),
                          pp3(str3.length()+1);

    cout << "Palindrome Partitions of '" << str1 << "':" << endl;
    findPalindromePartitions(pp1, str1, 0, str1.length()-1);
    printPalindromePartitions(pp1);
    cout << endl;

    cout << "Palindrome Partitions of '" << str2 << "':" << endl;
    findPalindromePartitions(pp2, str2, 0, str2.length()-1);
    printPalindromePartitions(pp2);
    cout << endl;

    cout << "Palindrome Partitions of '" << str3 << "':" << endl;
    findPalindromePartitions(pp3, str3, 0, str3.length()-1);
    printPalindromePartitions(pp3);

    return 0;
}
