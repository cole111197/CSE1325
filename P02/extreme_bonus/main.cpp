#include "average.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <string>
#include <iterator>

int main(){
  std::map<std::string, Average> students;
  students.insert(std::pair<std::string, Average>("John", Average()));
  srand(time(NULL));
  int input;
  std::string name{"John"};

  do{
    std::cout << " =========================" << std::endl;
    std::cout << " Merely Average Calculator" << std::endl;
    std::cout << " =========================" << std::endl;
    std::cout << "The current student is " << name << std::endl;
    std::cout << name << "'s average is " << students[name] << std::endl << std::endl;
    std::cout << "1 - Enter a new value" << std::endl;
    std::cout << "2 - Auto enter a random value" << std::endl;
    std::cout << "5 - Create a new student" << std::endl;
    std::cout << "6 - Select an existing student" << std::endl;
    std::cout << "0 - Exit" << std::endl << std::endl;
    std::cout << "Command?" << std::endl;  
    std::cin >> input;

    if(input == 1){
      std::cout << "Value?" << std::endl;
      std::cin >> students[name];
    } else if(input == 2){
      students[name] += (100*((double)rand() / (double)RAND_MAX));
    } else if(input == 5){
      std::string temp;
      std::cout << "Name?" << std::endl;
      std::cin >> temp;
      students.insert(std::pair<std::string, Average>(temp, Average()));
      name = temp;
    } else if(input == 6){
      std::cout << "Current students:" << std::endl;
      
      std::map<std::string, Average>::iterator it;
      for ( it = students.begin(); it != students.end(); it++ )
      {
        std::cout << it->first << std::endl;
      }
      std::string tname;
      std::cout << "Name?" << std::endl;
      std::cin >> tname;
      if (students.find(tname) == students.end()){
        std::cout << "Invalid input" << std::endl;
      } else {
        name = tname;
      }
    } else if(input != 0){
      std::cout << "Invalid input" << std::endl;
    }
  } while(input != 0);
  return 0;
}
