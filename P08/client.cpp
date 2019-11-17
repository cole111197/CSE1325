#include "client.h"

Client::Client(std::string name, std::string phone, std::string email) : _name{name}, _phone{phone}, _email{email} {}

void Client::adopt(Animal& animal){
    _adopted.push_back(&animal);
}

int Client::num_adopted(){
    return _adopted.size();
}

const Animal& Client::animal(int index){
    int i = 0;
    for(std::list<Animal*>::iterator p = _adopted.begin(); p != _adopted.end(); p++){
        if(i == index){
            return **p;
        } else {
            i++;
        }
    }
}

std::ostream& operator<<(std::ostream& ost, const Client& ct){
    ost << ct._name << " (" << ct._phone << ") (" << ct._email << ")";
    return ost;
}