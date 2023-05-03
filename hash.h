#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
HASH_INDEX_T operator()(const std::string& k) const
{
    // Initialize index to last position in string
    int index = k.size() - 1;

    // Initialize hash result to 0
    HASH_INDEX_T hashResult = 0;

    // Traverse the string backwards in blocks of 6, up to 5 blocks
    for(int blockIndex = 4; blockIndex >= 0; blockIndex--) {
        // Initialize block value to 0
        HASH_INDEX_T blockValue = 0;

        // Compute value for each block (up to 6 characters long)
        for(int j = index; j >= 0 && j >= index - 5; j--)
            blockValue += pow(36, index - j) * letterDigitToNumber(k[j]);
        

        // Add the block value to the hash result
        hashResult = hashResult + ( blockValue * rValues[blockIndex] );

        // Move index to the start of the next block
        index = index - 6;

        // If there are no more blocks, end the process
        if (index < 0)
            break;
    }

    // Return the computed hash
    return hashResult;
}


    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter <= 57) return letter-'0'+26;

        if (letter <= 90) return letter-'A';

        return letter-'a';

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
