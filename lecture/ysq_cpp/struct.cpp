#include<iostream>
#include<stdio.h>

enum gender{MALE, FEMALE};

struct student
{
  std::string name;
  enum gender gen;
  int age;
};


int main()
{
  struct student stu = {.name="Ken", .gen=MALE, .age=25};
  
  std::cout << "My name is " << stu.name << "I am " << stu.age << "years old" << std::endl;
  
  return 0;
}