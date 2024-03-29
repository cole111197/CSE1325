#include "mainwin.h"
#include "client.h"
#include "dog.h"
#include "cat.h"
#include "rabbit.h"
#include <sstream>
#include <fstream>

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

    //         N E W
    Gtk::MenuItem* menuitem_file_new = Gtk::manage(new Gtk::MenuItem("_New", true));
    menuitem_file_new->signal_activate().connect([this] {this->on_new_shelter_click();});
    filemenu->append(*menuitem_file_new);

    //         S A V E
    Gtk::MenuItem* menuitem_file_save = Gtk::manage(new Gtk::MenuItem("_Save", true));
    menuitem_file_save->signal_activate().connect([this] {this->on_save_click();});
    filemenu->append(*menuitem_file_save);

    //         S A V E  A S
    Gtk::MenuItem* menuitem_file_save_as = Gtk::manage(new Gtk::MenuItem("_Save As", true));
    menuitem_file_save_as->signal_activate().connect([this] {this->on_save_as_click();});
    filemenu->append(*menuitem_file_save_as);

    //         O P E N
    Gtk::MenuItem* menuitem_file_open = Gtk::manage(new Gtk::MenuItem("_Open", true));
    menuitem_file_open->signal_activate().connect([this] {this->on_open_click();});
    filemenu->append(*menuitem_file_open);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->on_quit_click();});
    filemenu->append(*menuitem_quit);

#ifdef __DEBUG
    Gtk::MenuItem *menuitem_test = Gtk::manage(new Gtk::MenuItem("_Test", true));
    menuitem_test->signal_activate().connect([this] {this->on_test_click();});
    filemenu->append(*menuitem_test);
#endif

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

    //     H E L P
    Gtk::MenuItem* menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu* helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    //           A B O U T
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_About", true));
    menuitem_about->signal_activate().connect([this] {this->on_about_click();});
    helpmenu->append(*menuitem_about);


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

void Mainwin::on_save_click(){
    try {
        std::ofstream ofs{shelter->filename()};
        shelter->save(ofs);
        ofs.close();
    } catch(std::exception e) {
        Gtk::MessageDialog{*this, "Unable to save data", false, Gtk::MESSAGE_ERROR}.run();
    }
}

void Mainwin::on_save_as_click(){
    Gtk::FileChooserDialog dialog("Please choose a file",
        Gtk::FileChooserAction::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);

    auto filter_ctp = Gtk::FileFilter::create();
    filter_ctp->set_name("mass");
    filter_ctp->add_pattern("*.mass");
    dialog.add_filter(filter_ctp);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    dialog.set_filename("untitled.mass");

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Save", 1);

    int result = dialog.run();

    if (result == 1) {
        shelter->set_filename(dialog.get_filename());
        on_save_click();
    }
}

void Mainwin::on_open_click() {
    if(!all_data_saved()) return;

    Gtk::FileChooserDialog dialog("Please choose a file",
          Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    auto filter_ctp = Gtk::FileFilter::create();
    filter_ctp->set_name("mass");
    filter_ctp->add_pattern("*.mass");
    dialog.add_filter(filter_ctp);
 
    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    dialog.set_filename("untitled.mass");

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", 0);
    dialog.add_button("_Open", 1);

    int result = dialog.run();

    if (result == 1) {
        try {
            std::ifstream ifs{dialog.get_filename()};
            Shelter* old = shelter;
            shelter = new Shelter(ifs);
            delete old;
        } catch (std::exception& e) {
            Gtk::MessageDialog{*this, "Unable to open shelter", false, Gtk::MESSAGE_ERROR}.run();
        }
    }
    /*
    std::ifstream ifs{"untitled.mass"};
    if(ifs){
        try {
            Shelter* old = shelter;
            shelter = new Shelter(ifs);
            delete old;
            ifs.close();
        } catch(int x){
            if(x == -1){
                Gtk::MessageDialog{*this, "Error: Incorrect line count", false, Gtk::MESSAGE_ERROR}.run();
            }
        }
    } else {
        Gtk::MessageDialog{*this, "Error: Could not open file", false, Gtk::MESSAGE_ERROR}.run();
    }
    */
}

void Mainwin::on_new_shelter_click(){
    delete shelter;
    shelter = new Shelter("Mavs Animal Shelter");
}

void Mainwin::on_about_click() {
    Gtk::AboutDialog* about = Gtk::manage(new Gtk::AboutDialog());
    about->set_deletable(true);

    about->set_program_name("Mav's Animal Shelter Software");
    about->set_version("1");
    about->set_copyright("Copyright 2019 by Cole Montgomery");
    about->set_license("Licensed under the Gnu General Public License 3.0\nhttps://www.gnu.org/licenses/gpl-3.0.en.html");

    int value = about->run();
    if(value == Gtk::RESPONSE_DELETE_EVENT){
        delete about;
    }
}

#ifdef __DEBUG
void Mainwin::on_test_click(){
    //shelter->add_animal()
    Dog* d1 = new Dog{Dog_breed::DACHSHUND, "Izzy", Gender::FEMALE, 7};
    Dog* d2 = new Dog{Dog_breed::MIX, "Reet", Gender::MALE, 3};
    Cat* c1 = new Cat{Cat_breed::RUSSIAN_BLUE, "Maude", Gender::FEMALE, 5};
    Cat* c2 = new Cat{Cat_breed::SIAMESE, "Kitty", Gender::MALE, 16};
    Rabbit* r1 = new Rabbit{Rabbit_breed::AMERICAN, "Rabbi", Gender::FEMALE, 1};
    Rabbit* r2 = new Rabbit{Rabbit_breed::PYGMY, "Goober", Gender::MALE, 2};
    shelter->add_animal(*d1);
    shelter->add_animal(*d2);
    shelter->add_animal(*c1);
    shelter->add_animal(*c2);
    shelter->add_animal(*r1);
    shelter->add_animal(*r2);
    //shelter->add_client()
    Client* cl1 = new Client{"Cole", "9723987873", "cole111197@gmail.com"};
    Client* cl2 = new Client{"David", "2145358098", "davidmontgomery59@yahoo.com"};
    Client* cl3 = new Client{"Patty", "2142363857", "pattymontgomery@verizon.net"};
    Client* cl4 = new Client{"Paige", "2145555555", "paige_martinez@gmail.com"};
    shelter->add_client(*cl1);
    shelter->add_client(*cl2);
    shelter->add_client(*cl3);
    shelter->add_client(*cl4);
    //shelter->adopt(shelter->client(#), shelter->animal(#))

}
#endif

// /////////////////
// U T I L I T I E S
// /////////////////

void Mainwin::status(std::string s) {
    msg->set_text(s);
}

bool Mainwin::all_data_saved() {
  if (shelter->saved()) return true;
  Gtk::MessageDialog dialog{*this, "Unsaved data will be lost", false, 
                            Gtk::MESSAGE_WARNING, Gtk::BUTTONS_NONE};
  dialog.add_button("Save", 1);
  dialog.add_button("Discard", 2);
  dialog.add_button("Cancel", 3);
  int response = dialog.run();
  if (response == 1) {        // Save
    try {
        on_save_as_click();
        return true; // save was successful
    } catch(std::exception& e) {
        Gtk::MessageDialog{*this, "Unable to save data", false, Gtk::MESSAGE_ERROR}.run();
        return false;
    }
  } else if (response == 2) { // Discard
    Shelter* old = shelter;
    shelter = new Shelter{"Mavs Animal Shelter"};
    delete old;

    return true;
  } else {                    // Cancel
    return false;
  }
}