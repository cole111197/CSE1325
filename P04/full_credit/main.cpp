#include "coach.h"
#include "locomotive.h"
#include "stock.h"
#include "train.h"
#include <iostream>
#include <iomanip>

void printSpeed(double speed);

int main(){
    Train train;
    int command;
    std::string prompt = "Command?";
    while(command != 0){
        std::cout << "=================\nTITLE HERE\n=================\n\n";
        std::cout << train.to_art();
        std::cout << "#########################################################################\n";
        std::cout << "Minutes   |    1     |    5     |    15    |    30    |    60    |\n";
        std::cout << "----------|----------|----------|----------|----------|----------|\n";
        std::cout << " m/s      |";
        printSpeed(train.speed(1));
        printSpeed(train.speed(5));
        printSpeed(train.speed(15));
        printSpeed(train.speed(30));
        printSpeed(train.speed(60));
        std::cout << "\n km/h     |";
        printSpeed(3.6*train.speed(1));
        printSpeed(3.6*train.speed(5));
        printSpeed(3.6*train.speed(15));
        printSpeed(3.6*train.speed(30));
        printSpeed(3.6*train.speed(60));
        std::cout << "\n mp/h     |";
        printSpeed(2.237*train.speed(1));
        printSpeed(2.237*train.speed(5));
        printSpeed(2.237*train.speed(15));
        printSpeed(2.237*train.speed(30));
        printSpeed(2.237*train.speed(60));
        std::cout << "\n\n1 - Add a locomotive\n2 - Add an empty coach\n9 - Clear the train\n0 - Exit\n\n" << prompt << "\n";
        prompt = "Command?";
        std::cin >> command;
        if(command == 1){
            Locomotive* temp = new Locomotive();
            train.add_locomotive(*temp);
        } else if(command == 2){
            Coach* temp = new Coach();
            train.add_coach(*temp);
        } else if(command == 9){
            train = Train();
        } else if(std::cin.fail()){
            command = -1;
            prompt = "Please enter an integer";
            std::cin.clear();
            std::cin.ignore(256, '\n');
        } else if(command == 0){
            std::cout << "Exiting" << std::endl;
        } else {
            prompt = "Please enter a valid command";
        }
    }
}

void printSpeed(double speed){
    std::cout << std::left << std::setw(10) << std::setfill(' ') << std::to_string(speed);
    std::cout << "|";
}