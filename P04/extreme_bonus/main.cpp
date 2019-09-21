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
        std::cout << "\n-----------------------------------------------------------------|\n";
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
        std::cout << "\n\n1 - Add a standard locomotive    11 - Add a custom locomotive\n";
        std::cout << "2 - Add an empty coach           12 - Add a custom coach\n";
        std::cout << "3 - Add a standard autocoach     13 - Add a custom autocar\n";
        std::cout << "4 - Add a standard cattlecar     14 - Add a custom cattlecar\n";
        std::cout << "5 - Add a standard boxcar        15 - Add a custom boxcar\n";
        std::cout << "9 - Clear the train\n";
        std::cout << "0 - Exit\n\n" << prompt << "\n";
        prompt = "Command?";
        std::cin >> command;
        if(command == 1){
            Locomotive* temp = new Locomotive();
            train += *temp;
        } else if(command == 2){
            Coach* temp = new Coach();
            train += *temp;
        } else if(command == 3){
            Autocoach* temp = new Autocoach();
            train += *temp;
        } else if(command == 4){
            Cattlecar* temp = new Cattlecar();
            train += *temp;
        } else if(command == 5){
            Boxcar* temp = new Boxcar();
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
        } else if(command == 13){
            bool valid = false;
            int weight;
            int power;
            while(!valid){
                std::cout << "Enter weight (default 70000 kg): ";
                std::cin >> weight;
                if(weight < 0 || std::cin.fail()){
                    std::cout << "Please enter a valid weight\n";
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                } else {
                    while(!valid){
                        std::cout << "Enter power (default 9500 kW): ";
                        std::cin >> power;
                        if(power < 0 || std::cin.fail()){
                            std::cout << "Please enter a valid power\n";
                            std::cin.clear();
                            std::cin.ignore(256, '\n');
                        } else {
                            Autocoach* temp = new Autocoach(weight, power);
                            train += *temp;
                            valid = true;
                        }
                    }
                }
            }
        } else if(command == 14){
            bool valid = false;
            int weight;
            int cattle;
            while(!valid){
                std::cout << "Enter weight (default 16500 kg): ";
                std::cin >> weight;
                if(weight < 0 || std::cin.fail()){
                    std::cout << "Please enter a valid weight\n";
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                } else {
                    while(!valid){
                        std::cout << "Enter number of cattle (0-20): ";
                        std::cin >> cattle;
                        if(cattle < 0 || cattle > 20 || std::cin.fail()){
                            std::cin.clear();
                            std::cin.ignore(256, '\n');
                            std::cout << "Please enter a valid number of cattle\n";
                        } else {
                            Cattlecar* temp = new Cattlecar(weight);
                            (*temp).add_cattle(cattle);
                            train += *temp;
                            valid = true;
                        }
                    }
                }
            }
        } else if(command == 15){
            bool valid = false;
            int weight;
            int cargo;
            while(!valid){
                std::cout << "Enter weight (default 14000 kg): ";
                std::cin >> weight;
                if(weight < 0 || std::cin.fail()){
                    std::cout << "Please enter a valid weight\n";
                    std::cin.clear();
                    std::cin.ignore(256, '\n');
                } else {
                    while(!valid){
                        std::cout << "Enter cargo (0-20000 kg): ";
                        std::cin >> cargo;
                        if(cargo < 0 || cargo > 20 || std::cin.fail()){
                            std::cin.clear();
                            std::cin.ignore(256, '\n');
                            std::cout << "Please enter a valid amount of cargo\n";
                        } else {
                            Boxcar* temp = new Boxcar(cargo);
                            (*temp).add_cargo(cargo);
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