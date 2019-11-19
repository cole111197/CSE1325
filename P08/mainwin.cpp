#include "mainwin.h"
#include "client.h"
#include "dog.h"
#include "cat.h"
#include "rabbit.h"
#include <sstream>

Mainwin::Mainwin() : shelter{new Shelter{"Mavs Animal Shelter"}} {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(800, 600);
    set_title(APP_TITLE);

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    // ///////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar);
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->on_quit_click();});
    filemenu->append(*menuitem_quit);

    //     A N I M A L
    // Create an Animal menu and add to the menu bar
    Gtk::MenuItem *menuitem_animal = Gtk::manage(new Gtk::MenuItem("_Animal", true));
    menubar->append(*menuitem_animal);
    Gtk::Menu *animalmenu = Gtk::manage(new Gtk::Menu());
    menuitem_animal->set_submenu(*animalmenu);

    //           N E W
    // Append New to the Animal menu
    Gtk::MenuItem *menuitem_newanimal = Gtk::manage(new Gtk::MenuItem("_New", true));
    menuitem_newanimal->signal_activate().connect([this] {this->on_new_animal_click();});
    animalmenu->append(*menuitem_newanimal);

    //           L I S T
    // Append List to the Animal menu
    Gtk::MenuItem *menuitem_listanimal = Gtk::manage(new Gtk::MenuItem("_List", true));
    menuitem_listanimal->signal_activate().connect([this] {this->on_list_animals_click();});
    animalmenu->append(*menuitem_listanimal);

    //           L I S T  A D O P T E D
    Gtk::MenuItem *menuitem_listadopted = Gtk::manage(new Gtk::MenuItem("_List Adopted", true));
    menuitem_listadopted->signal_activate().connect([this] {this->on_list_adopted_click();});
    animalmenu->append(*menuitem_listadopted);

    //     C L I E N T
    // Create a Client menu and add to the menu bar
    Gtk::MenuItem* menuitem_client = Gtk::manage(new Gtk::MenuItem("_Client", true));
    menubar->append(*menuitem_client);
    Gtk::Menu* clientmenu = Gtk::manage(new Gtk::Menu());
    menuitem_client->set_submenu(*clientmenu);

    //           N E W
    Gtk::MenuItem *menuitem_newclient = Gtk::manage(new Gtk::MenuItem("_New", true));
    menuitem_newclient->signal_activate().connect([this] {this->on_new_client_click();});
    clientmenu->append(*menuitem_newclient);

    //           L I S T
    Gtk::MenuItem *menuitem_listclients = Gtk::manage(new Gtk::MenuItem("_List", true));
    menuitem_listclients->signal_activate().connect([this] {this->on_list_clients_click();});
    clientmenu->append(*menuitem_listclients);

    //           A D O P T
    Gtk::MenuItem *menuitem_adoptanimal = Gtk::manage(new Gtk::MenuItem("_Adopt Animal", true));
    menuitem_adoptanimal->signal_activate().connect([this] {this->on_adopt_animal_click();});
    clientmenu->append(*menuitem_adoptanimal);

    //           L I S T  A D O P T E D
    Gtk::MenuItem *menuitem_listadopted2 = Gtk::manage(new Gtk::MenuItem("_List Adopted", true));
    menuitem_listadopted2->signal_activate().connect([this] {this->on_list_adopted_click();});
    clientmenu->append(*menuitem_listadopted2);


    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    toolbar->override_background_color(Gdk::RGBA{"gray"});
    vbox->pack_start(*toolbar, Gtk::PACK_SHRINK, 0);

    // ///////////////////////
    // D A T A   D I S P L A Y
    // Provide a text entry box to show the remaining data
    data = Gtk::manage(new Gtk::Label());
    data->set_hexpand(true);
    data->set_vexpand(true);
    Gtk::ScrolledWindow* scroller = Gtk::manage(new Gtk::ScrolledWindow);
    scroller->add(*data);
    vbox->pack_start(*scroller, Gtk::PACK_EXPAND_WIDGET, 0); // instead of packing *data directly

    // ///////////////////////////////////
    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for program messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    msg->override_background_color(Gdk::RGBA{"gray"});
    vbox->pack_start(*msg, Gtk::PACK_SHRINK, 0);

    // Make the box and everything in it visible
    vbox->show_all();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Mainwin::on_quit_click() {
    close();
}

void Mainwin::on_new_animal_click() {

    // /////////////
    // S P E C I E S   S E L E C T I O N

    std::string species;

    Gtk::Dialog dialog_species{"Select type of animal", *this};
    
    Gtk::Grid grid_species;

    Gtk::Label l_species{"Species"};
    Gtk::ComboBoxText c_species;
    c_species.append("Dog");
    c_species.append("Cat");
    c_species.append("Rabbit");
    c_species.set_active(0);

    grid_species.attach(l_species, 0, 0, 1, 1);
    l_species.set_hexpand(true);
    grid_species.attach(c_species, 1, 0, 2, 1);
    c_species.set_hexpand(true);

    dialog_species.get_content_area()->add(grid_species);
    dialog_species.add_button("OK", 1);
    dialog_species.add_button("Cancel", 0);

    dialog_species.show_all();

    int ret = dialog_species.run();
    if(ret == 1){
        dialog_species.close();
        // /////////////
        // A N I M A L   D E T A I L S
        species = c_species.get_active_text();

        Gtk::Dialog dialog{species+" Information", *this};

        Gtk::Grid grid;

        Gtk::Label l_name{"Name"};
        Gtk::Entry e_name;
        grid.attach(l_name, 0, 0, 1, 1);
        grid.attach(e_name, 1, 0, 2, 1);

        Gtk::Label l_breed{"Breed"};
        Gtk::ComboBoxText c_breed;
        if(species == "Dog"){
            for( auto& [ breed_enum, breed_string] : Dog::dog_breeds) c_breed.append(breed_string);
        } else if(species == "Cat"){
            for( auto& [ breed_enum, breed_string] : Cat::cat_breeds) c_breed.append(breed_string);
        } else if(species == "Rabbit"){
            for( auto& [ breed_enum, breed_string] : Rabbit::rabbit_breeds) c_breed.append(breed_string);
        }
        c_breed.set_active(0);
        grid.attach(l_breed, 0, 1, 1, 1);
        grid.attach(c_breed, 1, 1, 2, 1);

        Gtk::Label l_gender{"Gender"};
        Gtk::ComboBoxText c_gender;
        c_gender.append("Female");
        c_gender.append("Male");
        c_gender.set_active(0);
        grid.attach(l_gender, 0, 2, 1, 1);
        grid.attach(c_gender, 1, 2, 2, 1);

        Gtk::Label l_age{"Age"};
        Gtk::SpinButton s_age;
        s_age.set_range(0,99);
        s_age.set_increments(1,5);
        s_age.set_value(5);
        grid.attach(l_age, 0, 3, 1, 1);
        grid.attach(s_age, 1, 3, 2, 1);

        dialog.get_content_area()->add(grid);

        dialog.add_button("Add "+species, 1);
        dialog.add_button("Cancel", 0);

        dialog.show_all();

        while(dialog.run()) {
            if(e_name.get_text().size() == 0) {e_name.set_text("*required*"); continue;}
            Animal* animal;
            if(species == "Dog"){
                Dog_breed temp_breed;
                for(auto& [ breed_enum, breed_string ] : Dog::dog_breeds) {
                    if(breed_string == c_breed.get_active_text()) temp_breed = breed_enum;
                }
                animal = new Dog{temp_breed,
                    e_name.get_text(),
                    (c_gender.get_active_row_number() ? Gender::MALE : Gender::FEMALE),
                    static_cast<int>(s_age.get_value())};
            } else if(species == "Cat"){
                Cat_breed temp_breed;
                for(auto& [ breed_enum, breed_string ] : Cat::cat_breeds) {
                    if(breed_string == c_breed.get_active_text()) temp_breed = breed_enum;
                }
                animal = new Cat{temp_breed,
                    e_name.get_text(),
                    (c_gender.get_active_row_number() ? Gender::MALE : Gender::FEMALE),
                    static_cast<int>(s_age.get_value())};
            } else if(species == "Rabbit"){
                Rabbit_breed temp_breed;
                for(auto& [ breed_enum, breed_string ] : Rabbit::rabbit_breeds) {
                    if(breed_string == c_breed.get_active_text()) temp_breed = breed_enum;
                }
                animal = new Rabbit{temp_breed,
                    e_name.get_text(),
                    (c_gender.get_active_row_number() ? Gender::MALE : Gender::FEMALE),
                    static_cast<int>(s_age.get_value())};
            }
            shelter->add_animal(*animal);
            std::ostringstream oss;
            oss << "Added " << *animal;
            status(oss.str());
            break;
        }
    } else {
        dialog_species.close();
    }
}

void Mainwin::on_list_animals_click() {
    std::ostringstream oss;
    for(int i=0; i<shelter->num_animals(); ++i)
        oss << shelter->animal(i) << '\n'; 
    data->set_text(oss.str());
    status("");
}      // List all animals

void Mainwin::on_new_client_click(){
    Gtk::Dialog dialog{"Client Information", *this};

    Gtk::Grid grid;

    Gtk::Label l_name{"Name"};
    Gtk::Entry e_name;
    grid.attach(l_name, 0, 0, 1, 1);
    grid.attach(e_name, 1, 0, 2, 1);

    Gtk::Label l_phone{"Phone"};
    Gtk::Entry e_phone;
    grid.attach(l_phone, 0, 1, 1, 1);
    grid.attach(e_phone, 1, 1, 2, 1);

    Gtk::Label l_email{"Email"};
    Gtk::Entry e_email;
    grid.attach(l_email, 0, 2, 1, 1);
    grid.attach(e_email, 1, 2, 2, 1);

    dialog.get_content_area()->add(grid);

    dialog.add_button("Add Client", 1);
    dialog.add_button("Cancel", 0);

    dialog.show_all();

    while(dialog.run()) {
        if (e_name.get_text().size() == 0) {e_name.set_text("*required*"); continue;}
        if (e_phone.get_text().size() == 0) {e_phone.set_text("*required*"); continue;}
        if (e_email.get_text().size() == 0) {e_email.set_text("*required*"); continue;}

        Client* temp = new Client{e_name.get_text(), e_phone.get_text(), e_email.get_text()};
        shelter->add_client(*temp);
        std::ostringstream oss;
        oss << "Added " << *temp;
        status(oss.str());
        break;
    }
}

void Mainwin::on_list_clients_click(){
    std::ostringstream oss;
    for(int i=0; i<shelter->num_clients(); ++i)
        oss << shelter->client(i) << '\n'; 
    data->set_text(oss.str());
    status("");
}

void Mainwin::on_adopt_animal_click(){
    Gtk::Dialog dialog{"Adopt Animal", *this};

    Gtk::Grid grid;

    Gtk::Label l_client{"Client"};
    Gtk::ComboBoxText e_client;
    grid.attach(l_client, 0, 0, 1, 1);
    grid.attach(e_client, 1, 0, 2, 1);

    for(int i = 0; i < shelter->num_clients(); i++){
        std::ostringstream oss;
        oss << shelter->client(i);
        e_client.append(oss.str());
    }

    Gtk::Label l_animal{"Animal"};
    Gtk::ComboBoxText e_animal;
    grid.attach(l_animal, 0, 1, 1, 1);
    grid.attach(e_animal, 1, 1, 2, 1);

    for(int i = 0; i < shelter->num_animals(); i++){
        std::ostringstream oss;
        oss << shelter->animal(i);
        e_animal.append(oss.str());
    }

    dialog.get_content_area()->add(grid);

    dialog.add_button("Adopt Animal", 1);
    dialog.add_button("Cancel", 0);

    dialog.show_all();

    while(dialog.run()) {
        if(e_client.get_active_row_number() != -1 && e_animal.get_active_row_number() != -1){
            shelter->adopt(shelter->client(e_client.get_active_row_number()), shelter->animal(e_animal.get_active_row_number()));
        }
        break;
    }
}

void Mainwin::on_list_adopted_click(){
    Gtk::Dialog dialog{"List Adopted Animals", *this};

    Gtk::Grid grid;

    Gtk::Label l_client{"Client"};
    Gtk::ComboBoxText e_client;
    grid.attach(l_client, 0, 0, 1, 1);
    grid.attach(e_client, 1, 0, 2, 1);

    for(int i = 0; i < shelter->num_clients(); i++){
        std::ostringstream oss;
        oss << shelter->client(i);
        e_client.append(oss.str());
    }
    
    dialog.get_content_area()->add(grid);

    dialog.add_button("Choose Client", 1);
    dialog.add_button("Cancel", 0);

    dialog.show_all();

    while(dialog.run()) {
        if(e_client.get_active_row_number() != -1){
            std::ostringstream oss;
            for(int i = 0; i < shelter->client(e_client.get_active_row_number()).num_adopted(); i++){
                oss << shelter->client(e_client.get_active_row_number()).animal(i) << std::endl;
            }
            data->set_text(oss.str());
        }
        break;
    }
}

// /////////////////
// U T I L I T I E S
// /////////////////

void Mainwin::status(std::string s) {
    msg->set_text(s);
}
