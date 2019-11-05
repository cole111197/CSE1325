#include "dog.h"

Dog::Dog(Dog_breed breed, std::string name, Gender gender, int age) : Animal(name, gender, age), _breed{breed} {}

Dog::~Dog() {}

std::string Dog::family(){
    return "dog";
}

std::string Dog::breed(){
    if(_breed == Dog_breed::AUSTRALIAN_SHEPHERD){
        return "Australian Shepherd";
    } else if(_breed == Dog_breed::SHIBA_INU){
        return "Shiba Inu";
    } else if(_breed == Dog_breed::MASTIFF){
        return "Mastiff";
    } else if(_breed == Dog_breed::CORGI){
        return "Corgi";
    } else if(_breed == Dog_breed::BULLDOG){
        return "Bulldog";
    } else if(_breed == Dog_breed::BORDER_COLLIE){
        return "Border Collie";
    } else if(_breed == Dog_breed::HUSKY){
        return "Husky";
    } else if(_breed == Dog_breed::PIT_BILL){
        return "Pit Bull";
    } else {
        return "UNKNOWN";
    }
}

std::string Dog::to_string(){
    return "dog";
}