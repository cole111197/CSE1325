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


