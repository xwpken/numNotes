/*

Exercise 3 of archer2-cpp course

See https://github.com/EPCCed/archer2-cpp

Last modified: 10/03/2025 by weipeng

*/

#include <iostream>
#include <typeinfo>

#include <vector>
#include <array>
#include <list>
#include <set>
#include <map>

bool is_prime(unsigned x)
{
    return true;
}

std::vector<unsigned> get_first_n_primes(unsigned n)
{   
    std::vector<unsigned> primes;

    unsigned number = 2;

    // while loop
    while (primes.size() < n)
    {
        if (is_prime(number))
        {
            primes.push_back(number); // add to the last
        }

        number += 1;

    }

    return primes;
}


int main()
{
    // ======================= Vector (best)  ======================= 

    std::vector<int> data (5);
    // std::vector<int> data; 
    // data.resize(5);

    data = {1,2,3,4,5};

    // std::vector<int> data (5,10); 

    // std::vector<int> data  = {10,10,10,10,10};

    data.pop_back(); // remove the last

    std::cout << "Vector size: " << data.size() << std::endl;   // how many now
    std::cout << "Vector capacity: " << data.capacity() << std::endl; // how many can

    // range-based for loop
    for (auto x: data)
    {
        std::cout << x << typeid(x).name() << std::endl;
    }

    std::vector<unsigned> primes = get_first_n_primes(10);

    for (int i=0; i<=primes.size() + 4; i+=4)
    {
        try
        {
            // visit element
            std::cout << primes[i] << " "; // no error if exceed
            std::cout << primes.at(i) << std::endl; // error if exceed
        }
        catch(const std::exception& e)
        {
            std::cerr << "Catched Error:" << e.what() << '\n';
        }
        
    }

    std::cout << std::endl;

     // ======================= Array  ======================= 

     // cannot change size
     using fixed_array = std::array<int, 3>; // alias

     fixed_array array;

     array.fill(5);

     std::cout << array.front() << std::endl; // first
     std::cout << array.at(1) << std::endl;  // safe visit
     std::cout << array.back() << std::endl; // back

     std::cout << std::endl;

     // ======================= List  ======================= 

    std::list<int> myList(10);

    for (int i = 0; i<=10; i++)
    {   
        myList.push_back(i+1);
        std::cout << myList.back() << " ";
    }
    
    std::cout << std::endl << std::endl;

    // ======================= Set & Map  =======================

    // Set
    std::set<int> numSet;
    numSet.insert(3);
    numSet.insert(5);
    numSet.insert(7);

    // iterators
    for (auto it = numSet.begin(); it != numSet.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    std::cout << std::endl;

    // Map
    std::map<std::string, std::string> dict;

    dict["David"] = "20";
    dict.insert({"Amy","22"});
    dict.insert(std::make_pair("Kevin","18"));
    dict.emplace("Zark","33");

    for (auto [name, age]:dict)
    {
        std::cout << name << " " << age << std::endl;
    }

    // vector to map
    std::vector<std::pair<int,char>> num2char = {{2,'1'}};
    num2char.push_back({1,'2'});

    std::map<int,char> map_num2char(num2char.begin(), num2char.end());

    for (auto [num, str]: map_num2char)
    {
        std::cout << num << " " << str << std::endl;
    }

    std::cout << "\nAlways use vector if possible!" << std::endl;

}