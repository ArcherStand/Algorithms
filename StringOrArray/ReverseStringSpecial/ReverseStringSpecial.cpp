/*  A C++ program which reverses strings, ignoring any non-alphabetic
 *  characters within the string. I.e., the non-alphabetic characters maintain
 *  their same position before and after the reversal.
 */

#include<iostream>
#include<string>

using namespace std;

// Retruns true if the input is an upper or lower case alphabetic character
//  and false otherwise.
bool isAlphabeticChar(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

// Returns a string which is a reversal of the input string except ignoring 
// any non-alphabetic characters during the reversal.
// The strategy is to iterate inwards from the endpoints of the string
// (beginning and end), swapping characters at the current left and right
// points. Any non-alphabetic character is just skipped.
string reverseString(string str)
{
    string reversedStr(str);
    int left = 0, right = reversedStr.length() - 1;

    while (left < right)
    {
        // Skip non-alphabetic characters:
        if (!isAlphabeticChar(reversedStr[left]))
        {
            ++left;
        }
        else if (!isAlphabeticChar(reversedStr[right]))
        {
            --right;
        }
        // Since both reversedStr[left] and reversedStr[right] are
        // alphabetic we can swap them:
        else
        {
            char temp = reversedStr[left];
            reversedStr[left] = reversedStr[right];
            reversedStr[right] = temp;
            ++left;
            --right;
        }
    }

    return reversedStr;
}

int main()
{
    string str1("t!e@s#t$i%n^g");
    string str2("ida51ad$-i"); // This should look the same reversed;
    string str3("more$$%^&&CHECKS{[]}");

    cout << "First string is: " << str1 << endl;
    cout << "First string reversed is: " << reverseString(str1) << endl;

    cout << "Second string is: " << str2 << endl;
    cout << "Second string reversed string is: " << reverseString(str2) << endl;

    cout << "Third string is: " << str3 << endl;
    cout << "Third string reversed string is: " << reverseString(str3) << endl;

    return 0;
}
