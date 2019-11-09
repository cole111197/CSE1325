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
    vbox->pack_start(*data, Gtk::PACK_EXPAND_WIDGET, 0);

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
            for(auto b : dog_breeds) c_breed.append(to_string(b));
        } else if(species == "Cat"){
            for(auto b : cat_breeds) c_breed.append(to_string(b));
        } else if(species == "Rabbit"){
            for(auto b : rabbit_breeds) c_breed.append(to_string(b));
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
                animal = new Dog{dog_breeds[c_breed.get_active_row_number()], 
                    e_name.get_text(),
                    (c_gender.get_active_row_number() ? Gender::MALE : Gender::FEMALE),
                    static_cast<int>(s_age.get_value())};
            } else if(species == "Cat"){
                animal = new Cat{cat_breeds[c_breed.get_active_row_number()], 
                    e_name.get_text(),
                    (c_gender.get_active_row_number() ? Gender::MALE : Gender::FEMALE),
                    static_cast<int>(s_age.get_value())};
            } else if(species == "Rabbit"){
                animal = new Rabbit{rabbit_breeds[c_breed.get_active_row_number()],
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
    Gtk::Dialog dialog{"New client", *this};
    //dialog.set_default_size(280, 180);

    Gtk::Grid grid;

    Gtk::Label n_label{"Name"};
    Gtk::Entry n_entry;
    Gtk::Label p_label{"Phone"};
    Gtk::Entry p_entry;
    Gtk::Label e_label{"Email"};
    Gtk::Entry e_entry;
    Gtk::Label errors{""};

    grid.attach(n_label, 0, 0, 1, 1);
    grid.attach(n_entry, 1, 0, 4, 1);
    grid.attach(p_label, 0, 1, 1, 1);
    grid.attach(p_entry, 1, 1, 4, 1);
    grid.attach(e_label, 0, 2, 1, 1);
    grid.attach(e_entry, 1, 2, 4, 1);
    grid.attach(errors, 1, 3, 1, 1);

    dialog.get_content_area()->add(grid);
    //dialog.get_content_area()->add(errors);
    dialog.add_button("OK", 1);
    dialog.add_button("Cancel", 0);

    dialog.show_all();
    
    int run = -1;
    while(dialog.run() != 0){
        std::string name;
        std::string email;
        std::string phone;
        long long int phone_i;
        try {
            phone_i = std::stoll(p_entry.get_text());
            if(n_entry.get_text().length() == 0){
                errors.set_text("Error\nPlease enter name");
            }else if(phone_i >= 10000000000 || phone_i < 1000000000){
                errors.set_text("Error\nPhone format: AAABBBCCCC");
            } else if(e_entry.get_text().length() == 0 || e_entry.get_text().find("@") == std::string::npos || e_entry.get_text().find(".") == std::string::npos){
                errors.set_text("Error\nEmail format: a@b.c");
            } else {
                phone = std::to_string(phone_i);
                name = n_entry.get_text();
                email = e_entry.get_text();
                Client* client = new Client{name, phone, email};
                shelter->add_client(*client);
                dialog.close();
                std::ostringstream oss;
                oss << "Added " << *client;
                status(oss.str());
                return;
            }
        } catch(std::exception e) {
            errors.set_text("Error\nPhone format: AAABBBCCCC");
        }

    }
    dialog.close();
}

// /////////////////
// U T I L I T I E S
// /////////////////

void Mainwin::status(std::string s) {
    msg->set_text(s);
}
