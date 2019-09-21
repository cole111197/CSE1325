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
        std::cout << "==================\n====CS Express====\n==================\n\n";
        std::cout << train;
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
        std::cout << "\n\n1 - Add a standard locomotive    11 - Add a custom locomotive\n2 - Add an empty coach           12 - Add a custom coach\n9 - Clear the train\n0 - Exit\n\n" << prompt << "\n";
        prompt = "Command?";
        std::cin >> command;
        if(command == 1){
            Locomotive* temp = new Locomotive();
            train += *temp;
        } else if(command == 2){
            Coach* temp = new Coach();
            train += *temp;
        } else if(command == 9){
            train = Train();
        } else if(command == 11){
            bool valid = false;
            int weight;
            int power;
            while(!valid){
                std::cout << "Enter weight (default 80000 kg): ";
                std::cin >> weight;
                if(weight < 0 || std::cin.fail()){
                    std::cout << "Please enter a valid weight\n";
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                } else {
                    while(!valid){
                        std::cout << "Enter power (default 13500 kW): ";
                        std::cin >> power;
                        if(power < 0 || std::cin.fail()){
                            std::cout << "Please enter a valid power\n";
                            std::cin.clear();
                            std::cin.ignore(256, '\n');
                        } else {
                            Locomotive* temp = new Locomotive(weight, power);
                            train += *temp;
                            valid = true;
                        }
                    }
                }
            }
        } else if(command == 12){
            bool valid = false;
            int weight;
            int passengers;
            while(!valid){
                std::cout << "Enter weight (default 28000 kg): ";
                std::cin >> weight;
                if(weight < 0 || std::cin.fail()){
                    std::cout << "Please enter a valid weight\n";
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                } else {
                    while(!valid){
                        std::cout << "Enter number of passengers (0-120): ";
                        std::cin >> passengers;
                        if(passengers < 0 || passengers > 120 || std::cin.fail()){
                            std::cin.clear();
                            std::cin.ignore(256, '\n');
                            std::cout << "Please enter a valid number of passengers\n";
                        } else {
                            Coach* temp = new Coach(weight);
                            (*temp).add_passengers(passengers);
                            train += *temp;
                            valid = true;
                        }
                    }
                }
            }
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