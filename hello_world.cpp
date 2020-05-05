#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

int
main()
{
  std::string name;                         // initialise name
  std::cin >> name;                         // cin name
  std::cout << "Hello World from " << name; // write hello world @name
  return 0;
}
