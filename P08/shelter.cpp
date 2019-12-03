#include "shelter.h"
#include "dog.h"
#include "cat.h"
#include "rabbit.h"
#include <sstream>

Shelter::Shelter(std::string name) : _filename{"untitled.mass"}, _name{name} {
    _dirty = false;
}

Shelter::Shelter(std::istream& ist){
    std::string name_check;
    if(!(getline (ist, name_check))){
        throw -1;
    }
    _name = name_check;
    std::string animal_count;
    std::getline(ist, animal_count);
    bool good = valid(ist, animal_count);
    ist.clear();
    ist.seekg(0, ist.beg);
    std::string trash;          //used to skip lines
    std::getline(ist, trash);   //skip line where name is
    std::getline(ist, trash);   //skip line where animal count is
    if(!good){
        throw -1;
    } else {
        for(int i = 0; i < std::stoi(animal_count); i++){
            std::string type;
            std::getline(ist, type);
            if(type == "dog"){
                Dog* dog = new Dog(ist);
                add_animal(*dog);
            } else if(type == "cat"){
                Cat* cat = new Cat(ist);
                add_animal(*cat);
            } else if(type == "rabbit"){
                Rabbit* rabbit = new Rabbit(ist);
                add_animal(*rabbit);
            }
        }
        _dirty = true;
    }
}


bool Shelter::valid(std::istream& ist, std::string animal_count){
    int num_lines = 0;
    std::string temp;
    while(std::getline(ist, temp)){
        num_lines++;
    }
    try{
        int count = std::stoi(animal_count);
        return (num_lines == count*5);
    } catch(std::invalid_argument e){
        return false;
    }
}

std::string Shelter::name(){
    return _name;
}

void Shelter::add_animal(Animal& animal){
    _available.push_back(&animal);
    _dirty = true;
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
    _dirty = true;
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
    _dirty = false;
}

bool Shelter::saved(){
    return !_dirty;
}