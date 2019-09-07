#include "average.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(){
  Average avg;
  srand(time(NULL));
  int input;

  do{
    std::cout << " =========================" << std::endl;
    std::cout << " Merely Average Calculator" << std::endl;
    std::cout << " =========================" << std::endl;
    std::cout << "The current average is " << avg << std::endl << std::endl;
    std::cout << "1 - Enter a new value" << std::endl;
    std::cout << "2 - Auto enter a random value" << std::endl;
    std::cout << "9 - Clear the calculator" << std::endl;
    std::cout << "0 - Exit" << std::endl << std::endl;
    std::cout << "Command?" << std::endl;  
    std::cin >> input;

    if(input == 1){
      std::cout << "Value?" << std::endl;
      std::cin >> avg;
      std::cout << avg << std::endl;
    } else if(input == 2){
      avg += (100*((double)rand() / (double)RAND_MAX));
    } else if(input == 9){
      avg = Average();
    } else if(input != 0){
      std::cout << "Invalid input" << std::endl;
    }
  } while(input != 0);

    return 0;
}
