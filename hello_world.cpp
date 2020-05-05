#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

int
main()
{
  std::string name;                         //объявляем  name
  std::cin >> name;                         //считываем name
  std::cout << "Hello World from " << name; //пишем hello world @name
  return 0;
}
