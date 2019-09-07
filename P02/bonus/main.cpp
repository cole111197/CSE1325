#include "average.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

int main(){
  std::vector<Average> students;
  students.push_back(Average());
  srand(time(NULL));
  int input;
  int student{0};

  do{
    std::cout << " =========================" << std::endl;
    std::cout << " Merely Average Calculator" << std::endl;
    std::cout << " =========================" << std::endl;
    std::cout << "The current student is " << student << std::endl;
    std::cout << "The current average is " << students.at(student) << std::endl << std::endl;
    std::cout << "1 - Enter a new value" << std::endl;
    std::cout << "2 - Auto enter a random value" << std::endl;
    std::cout << "5 - Create a new student" << std::endl;
    std::cout << "6 - Select an existing student" << std::endl;
    std::cout << "9 - Clear the calculator" << std::endl;
    std::cout << "0 - Exit" << std::endl << std::endl;
    std::cout << "Command?" << std::endl;  
    std::cin >> input;

    if(input == 1){
      std::cout << "Value?" << std::endl;
      std::cin >> students.at(student);
      std::cout << students.at(student) << std::endl;
    } else if(input == 2){
      students.at(student) += (100*((double)rand() / (double)RAND_MAX));
    } else if(input == 5){
      students.push_back(Average());
      student = students.size()-1;
    } else if(input == 6){
      int temp;
      std::cout << "Value?" << std::endl;
      std::cin >> temp;
      if(temp >= 0 && temp < students.size()){
        student = temp;
      } else {
        std::cout << "Invalid input" << std::endl;
      }
    } else if(input == 9){
      students.at(student) = Average();
    } else if(input != 0){
      std::cout << "Invalid input" << std::endl;
    }
  } while(input != 0);

    return 0;
}
