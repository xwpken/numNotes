#include <iostream>
#include <cstring>

template<typename T>
T sum(const T& a, const T& b) 
{

  T result = a + b;

  std::cout << a << " + " << b << " = " << result << std::endl;

  return result;

}

const char* sum(const char* a, const char*b)
{
  std::string result = std::string(a) + b;

  std::cout << result << std::endl;

  return result.c_str();
}


int main() {
  // 3 + 4 = 7
  sum(3, 4);

  // 3.2 + 5.1 = 8.3
  sum(3.2, 5.1);

  std::cout << typeid("Hello").name() << std::endl;

  sum(std::string("Hello "), std::string("World!"));

  sum("Hello ", "World!");
}