// Author: Trinity Lundgren
// Date: 2019-08-21
// Description: Implementation of "third grade multiplication" algorithm
// example from Algorithms Illuminated: Part I (Roughgarden)

#include <iostream>
#include <string>

// Accepts two strings, adds leading zeros to the shorter one to make it equal
// in length to the longer one.
void leadingPad(std::string &str1, std::string &str2) {
    int numLeadingZeros = 0;
    if (str2.size() < str1.size()) {
        leadingPad(str2, str1);
    }
    numLeadingZeros = str2.size() - str1.size();
    for (int i = 0; i < numLeadingZeros; i++) {
        str1.insert(0, "0");
    }
}


// Goes through the array of strings, determines which string is longest, returns
// its index
int longestStr(std::string stringArray[], int size) {
    int maxLength = 0;
    int maxIndex;
    for (int i = 0; i < size; i++) {
        if (stringArray[i].size() > maxLength) {
            maxLength = stringArray[i].size();
            maxIndex = i;
        }
    }
    return maxIndex;
}


// Accepts a string as an argument, returns string with leading zeros removed
std::string removeLeadingZeros(std::string paddedString) {
    if (paddedString.size() == 0) {
        return "";
    }
    else if (paddedString == std::string(" ")) {
        return "";
    }
    else {
        while(paddedString.at(0) == '0') {
            paddedString.erase(0,1);
        }
        return paddedString;
    }
}

// Accepts a string and a number, removes num lagging zeros
std::string removeLaggingZeros(std::string str, int num) {
    std::string spaces;
    for (int i = 0; i < num; i++) {
        str.pop_back();
    }
    return str;
}

// Accepts a string, returns string with leading zeros replaced with spaces
std::string prettyIndent(std::string str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (str.at(i) == '0') {
            str.replace (i, 1, " ");
        }
        else {
            break;
        }
    }
    return str;
}

// Accepts two numbers as strings, returns a string representing the product
// of the two arguments
std::string thirdGradeMultiply(std::string x, std::string y) {

    // Make x and y the same length with leading zeros
    if (x.size() != y.size()) {
            leadingPad(x, y);
    }

    // Store length of "bottom" multiplication factor, which will be the number
    // of strings in an array of strings that will be added together
    int n = x.size();
    std::string* strPtr = NULL;
    strPtr = new std::string[n];

    // Beginning with the last digit of bottom factor, multiply it by each digit
    // of the top factor (y), beginning with the last. Insert ones digit of the
    // resulting product into a result string, "carrying" the tens digit to be
    // added to the next sub-product
    for (int i = 0; i < n; i++) {
        int xDigit = x[n - 1 - i] - '0';
        int carry = 0;
        int result = 0;
        std::string resultStr = "";
        for (int j = 0; j < n; j++) {
            int yDigit = y[n - 1 - j] -'0';
            result = xDigit * yDigit + carry;
            carry = result / 10;
            result = result % 10;
            std::string resultPiece = std::to_string(result);
            resultStr.insert(0, resultPiece);
        }
        resultStr.insert(0, std::to_string(carry));

        // Add a number of lagging zeros corresponding to the index of the
        // result string in the array - this is equivalent to the "indenting"
        // of intermediate results in third grade multiplication on paper
        int numLaggingZeros = i;
        for (int j = 0; j < numLaggingZeros; j++) {
            resultStr.append("0");
        }

        // Add intemediate result strings to the array
        strPtr[i] = resultStr;
    }

    // Get index of longest string in array
    int longestStrIndex = longestStr(strPtr, n);

    //Add leading zeros to make all strings that length
    //Add one additional leading zero to all strings to make carries work
    for (int i = 0; i < n; i++) {
        leadingPad(strPtr[i], strPtr[longestStrIndex]);
        strPtr[i].insert(0, "0");
    }

    // Initialize the final product string to return. For each digit of the
    // result string in the array, and for each string, add together the
    // corresponding digits of each string, beginning with the last. Carry
    // tens digit to next addition.
    std::string finalString = "";
    int carry = 0;
    for (int i = strPtr[longestStr(strPtr, n)].size() - 1; i >=0; i--) {
        int result = 0;
        for (int j = 0; j < n; j++) {
            result += strPtr[j][i] - '0';
        }
        result += carry;
        carry = result / 10;
        result = result % 10;
        std::string resultString = std::to_string(result);
        finalString.insert(0, resultString);
    }
    finalString.insert(0, std::to_string(carry));

    // Print the visual representation of third grade multiplication of x and
    // y to the console (factors, multiplication symbol and line)
    std::cout << std::endl;
    std::cout << " ";
    for (int i = 0; i <= n; i++) {
        y.insert(0, " ");
    }
    std::cout << prettyIndent(y) << std::endl;
    for (int i = 0; i <= n - 1; i++) {
        std::cout << " ";
    }
    std::cout << "\u2715" << " " << prettyIndent(x) << std::endl;
    std::cout << " ";
    for (int i = 0; i <= x.size() * 2; i++) {
        std::cout << "\u2500";
    }
    std::cout << std::endl;

    // Print intermediate results to the console, trimming leading zeros and
    // replace lagging zeros with " " to indent
    for (int i = 0; i < n; i++) {
        std::cout << " ";
        std::cout << prettyIndent(removeLaggingZeros(strPtr[i], i));
        std::cout << std::endl;
    }
    std::cout << " ";
    for (int i = 0; i <= x.size() * 2; i++) {
        std::cout << "\u2500";
    }
    std::cout << std::endl;

    // Print final product
    std::cout << prettyIndent(finalString) << std::endl << std:: endl;

    // Free intermediate result array
    delete [] strPtr;
    strPtr = NULL;

    // Return final product with leading zeros trimmed
    return removeLeadingZeros(finalString);
}
