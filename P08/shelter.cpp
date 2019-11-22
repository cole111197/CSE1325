#include "shelter.h"
#include <iostream>

Shelter::Shelter(std::string name) : _name{name} {}

std::string Shelter::name(){
    return _name;
}

void Shelter::add_animal(Animal& animal){
    _available.push_back(&animal);
}

int Shelter::num_animals(){
    return _available.size();
}

Animal& Shelter::animal(int index){
    //return *(_available[index]);
    int i = 0;
    for(std::list<Animal*>::iterator p = _available.begin(); p != _available.end(); p++){
        if(i == index){
            return **p;
        } else {
            i++;
        }
    }
}

void Shelter::add_client(Client& client){
    _clients.push_back(&client);
}

int Shelter::num_clients(){
    return _clients.size();
}

Client& Shelter::client(int index){
    int i = 0;
    for(std::list<Client*>::iterator p = _clients.begin(); p != _clients.end(); p++){
        if(i == index){
            return **p;
        } else {
            i++;
        }
    }
}

void Shelter::adopt(Client& client, Animal& animal){
    _available.remove(&animal);
    client.adopt(animal);
}

void Shelter::set_filename(std::string filename){
    _filename = filename;
}

std::string Shelter::filename(){
    return _filename;
}

void Shelter::save(std::ostream& ost){
    ost << _name << std::endl;
    ost << std::to_string(_available.size()) << std::endl;
    for(std::list<Animal*>::iterator it = _available.begin(); it != _available.end(); it++){
        (*it)->save(ost);
    }
}