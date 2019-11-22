#ifndef __SHELTER_H
#define __SHELTER_H

#include "animal.h"
#include "client.h"
#include <string>
#include <list>

class Shelter{
    public:
        Shelter(std::string name);

        std::string name();
        void add_animal(Animal& animal);
        int num_animals();
        Animal& animal(int index);
        void add_client(Client& client);
        int num_clients();
        Client& client(int index);
        void adopt(Client& client, Animal& animal);

        void set_filename(std::string filename);
        std::string filename();
        void save(std::ostream& ost);
    private:
        std::string _name;
        std::list<Animal*> _available;
        std::list<Client*> _clients;
        std::string _filename;
};

#endif