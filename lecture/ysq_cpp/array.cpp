#include<iostream>
#include<stdio.h>

int array_sum(const int *array, size_t len)
{
  int sum = 0;
  for (int i=0; i<len; i++)
  {
    sum += array[i];
  }
  
  std::cout << sizeof(array) << std::endl;
  std::cout << "The array sum is " << sum << std::endl;
  
  return sum;
}

int main()
{
  int array[5] = {1,2,3,4,5};
  int array2d[][3] = {{6,7,8},{9,10,11}};
  
  for (size_t i=0; i < 5; i++)
  {
    std::cout << array[i] << std::endl;
  }
  
  array_sum(array, 3);
  
  for (int i=0; i<2; i++)
  {
    for (int j=0; j<3; j++)
    {
      std::cout << array2d[i][j] << " ";
    }
    
    std::cout << std::endl;
  }
  
  
  return 0;
}