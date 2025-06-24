#include "vector_ex.hpp"

// std::vector documentation:
// https://en.cppreference.com/w/cpp/container/vector

std::vector<int> GetEven(std::vector<int> const& source) 
{
    // Given a vector of integers, return a new vector with only the even
    // elements from our input

    std::vector<int> evens;

    for (auto num: source)
    {
        if (num % 2 == 0)
        {
            evens.push_back(num);
        }

    }

    return evens;

}


void PrintVectorOfInt(std::ostream& output, std::vector<int> const& data)
{
    // Given a vector of ints, print the data to the stream
    // [0, 1]

    output << "[ ";

    for (int i = 0; i < data.size(); ++i)
    {
        output << data[i];

        if (i < data.size()-1)
        {
           output << ", ";
        }

    }
    output << "]";
}
