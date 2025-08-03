#include<iostream>
#include<stdio.h>
#include<cstring>

int main()
{
  // char
  char mess1[10] = {'H', 'E', 'R','O', ' '};
  char mess2[] = "Hello World!";
  
  std::cout << mess1 << mess2 << std::endl;
  std::cout << strcat(mess2, mess1) << std::endl;
  
  // std string class
  std::string name = "JACK";
  std::cout << "My name is " << name + " (length: " << name.length() << ")" << std::endl;
  
  return 0;
}