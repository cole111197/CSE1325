#include "mainwin.h"
#include <iostream>

Mainwin::Mainwin() : Mainwin{*(new Store)} { }
Mainwin::Mainwin(Store& store) : _store{&store} {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(400, 200);
    set_title("Ultimate Sweet Shop");

    // Set up a vertical box to hold the main window elements
    Gtk::VBox* main_box = Gtk::manage(new Gtk::VBox());
    add(*main_box);
    
    // ///////
    // M E N U
    // Add and configure a menu bar as the top item in the vertical box
    Gtk::MenuBar* menu = Gtk::manage(new Gtk::MenuBar());
    Gtk::MenuItem* menu_file = Gtk::manage(new Gtk::MenuItem());
    Gtk::Menu* submenu_file = Gtk::manage(new Gtk::Menu());
    Gtk::MenuItem* menu_quit = Gtk::manage(new Gtk::MenuItem());
    Gtk::MenuItem* menu_new = Gtk::manage(new Gtk::MenuItem());

    menu_file->set_label("File");
    menu_file->set_submenu(*submenu_file);
    menu_quit->set_label("Quit");
    menu_quit->signal_activate().connect(
            [this] {this->on_quit_click();}
        );
    menu_new->set_label("New");
    menu_new->signal_activate().connect(
            [this] {this->on_new_store_click();}
        );
    submenu_file->append(*menu_quit);
    submenu_file->append(*menu_new);
    menu->append(*menu_file);
    main_box->add(*menu);

    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box just below the menu (bonus level)



    // ///////////////////////
    // D A T A   D I S P L A Y
    // Provide a text entry box to show the sweets and orders
    data = Gtk::manage(new Gtk::Label());
    data->set_label("Data");
    main_box->add(*data);

    // ///////////////////////////////////    
    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for transient messages


    // Make the vertical box and everything in it visible
    main_box->show_all();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////


// /////////////////
// U T I L I T I E S
// /////////////////

void Mainwin::on_quit_click(){
    close();
}

void Mainwin::on_new_store_click(){
    _store = new Store();
}