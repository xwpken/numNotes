#ifndef LEC6_HPP
#define LEC6_HPP

#include<iostream>

#include<vector>
#include<map>

template<typename T>
T sum(T& a, T&b)
{
    return a + b;
}

template<typename MAT>
class EleStiffnessMatrix
{
    private:
        size_t num_ele = 0;
        std::map<size_t, MAT>* emats = nullptr;

    public:
        EleStiffnessMatrix() = default;
        // EleStiffnessMatrix(size_t num_ele, MAT& mats);

};


#endif