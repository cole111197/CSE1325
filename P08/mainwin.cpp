#include "mainwin.h"
#include <iostream>

Mainwin::Mainwin(){
    set_default_size(640, 480);
    set_title("Mav's Animal Shelter");

    shelter = new Shelter("Default");

    Gtk::Box* vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    Gtk::MenuBar* menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

//////     F I L E
    // Create File menu
    Gtk::MenuItem* menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu* filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    // Add Quit to File menu
    Gtk::MenuItem* menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->on_quit_click();});
    filemenu->append(*menuitem_quit);

//////     A N I M A L
    // Create Animal menu
    Gtk::MenuItem* menuitem_animal = Gtk::manage(new Gtk::MenuItem("_Animal", true));
    menubar->append(*menuitem_animal);
    Gtk::Menu* animalmenu = Gtk::manage(new Gtk::Menu());
    menuitem_animal->set_submenu(*animalmenu);

    // Add New to Animal menu
    menuitem_animal_new = Gtk::manage(new Gtk::MenuItem("_New", true));
    menuitem_animal_new->signal_activate().connect([this] {this->on_new_animal_click();});
    animalmenu->append(*menuitem_animal_new);

    // Add List Available to Animal menu
    menuitem_animal_list = Gtk::manage(new Gtk::MenuItem("_List Available", true));
    menuitem_animal_list->signal_activate().connect([this] {this->on_list_animals_click();});
    animalmenu->append(*menuitem_animal_list);

    data = Gtk::manage(new Gtk::Label());
    data->set_hexpand(true);
    data->set_vexpand(true);
    vbox->add(*data);

    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->add(*msg);

    vbox->show_all();
}

Mainwin::~Mainwin(){}

void Mainwin::on_quit_click(){
    close();
}

void Mainwin::on_new_animal_click(){
    std::string name;
    Gender gender;
    int age;
    Gtk::Dialog* dialog = new Gtk::Dialog{"Add a new animal", *this};

    Gtk::HBox b_name{true};
    Gtk::Label l_name{"Name:"};
    Gtk::Entry e_name;
    b_name.pack_start(l_name);
    b_name.pack_start(e_name);
    dialog->get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    Gtk::HBox b_gender{true};
    Gtk::Label l_gender{"Gender:"};
    Gtk::ComboBoxText e_gender{false};
    e_gender.append("Male");
    e_gender.append("Female");
    b_gender.pack_start(l_gender);
    b_gender.pack_start(e_gender);
    dialog->get_vbox()->pack_start(b_gender, Gtk::PACK_SHRINK);

    Gtk::HBox b_age{true};
    Gtk::Label l_age{"Age:"};
    Gtk::Entry e_age;
    b_age.pack_start(l_age);
    b_age.pack_start(e_age);
    dialog->get_vbox()->pack_start(b_age, Gtk::PACK_SHRINK);

    dialog->add_button("Cancel", 0);
    dialog->add_button("Add", 1);
    dialog->show_all();

    int result;
    bool fail = true;

    while (fail) {
        fail = false;
        result = dialog->run();
        if (result != 1) {
            msg->set_text("New animal cancelled");
            delete dialog;
            return;
        }
        try {
            age = std::stoi(e_age.get_text());
        } catch(std::exception e) {
            e_age.set_text("### Invalid ###");
            fail = true;
        }
        name = e_name.get_text();
        if (name.size() == 0) {
            e_name.set_text("### Invalid ###");
            fail = true;
        }
        if(e_gender.get_active_text() == "Male"){
            gender = Gender::MALE;
        } else {
            gender = Gender::FEMALE;
        }
    }
    Dog* dog = new Dog(Dog_breed::AUSTRALIAN_SHEPHERD, name, gender, age);
    shelter->add_animal(*dog);
    delete dialog;
    msg->set_text("New animal added");
}

void Mainwin::on_list_animals_click(){
    std::ostringstream text;
    for(int i = 0; i < shelter->num_animals(); i++){
        text << shelter->animal(i) << "\n";
    }

    data->set_text(text.str());
    msg->set_text("Animals listed");
}