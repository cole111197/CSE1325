#include "mainwin.h"
#include <vector>

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
    main_menu = Gtk::manage(new Gtk::MenuBar());
    menu_file = Gtk::manage(new Gtk::MenuItem());
    submenu_file = Gtk::manage(new Gtk::Menu());
    menu_sweets = Gtk::manage(new Gtk::MenuItem());
    submenu_sweets = Gtk::manage(new Gtk::Menu());
    menu_help = Gtk::manage(new Gtk::MenuItem());
    submenu_help = Gtk::manage(new Gtk::Menu());
    menuitem_file_quit = Gtk::manage(new Gtk::MenuItem());
    menuitem_file_new = Gtk::manage(new Gtk::MenuItem());
    menuitem_sweets_add = Gtk::manage(new Gtk::MenuItem());
    menuitem_sweets_list = Gtk::manage(new Gtk::MenuItem());
    menuitem_help_about = Gtk::manage(new Gtk::MenuItem());

    main_box->pack_start(*main_menu, Gtk::PACK_SHRINK);
    main_menu->append(*menu_file);
    main_menu->append(*menu_sweets);
    main_menu->append(*menu_help);

    menu_file->set_label("File");
    menu_file->set_submenu(*submenu_file);
    menuitem_file_quit->set_label("Quit");
    menuitem_file_quit->signal_activate().connect(
            [this] {this->on_quit_click();}
        );
    menuitem_file_new->set_label("New");
    menuitem_file_new->signal_activate().connect(
            [this] {this->on_new_store_click();}
        );
    submenu_file->append(*menuitem_file_quit);
    submenu_file->append(*menuitem_file_new);

    menu_sweets->set_label("Sweets");
    menu_sweets->set_submenu(*submenu_sweets);
    menuitem_sweets_add->set_label("Add");
    menuitem_sweets_add->signal_activate().connect(
            [this] {this->on_add_sweet_click();}
        );
    menuitem_sweets_list->set_label("List");
    menuitem_sweets_list->signal_activate().connect(
            [this] {this->on_list_sweets_click();}
        );
    submenu_sweets->append(*menuitem_sweets_add);
    submenu_sweets->append(*menuitem_sweets_list);

    menu_help->set_label("Help");
    menu_help->set_submenu(*submenu_help);
    menuitem_help_about->set_label("About");
    menuitem_help_about->signal_activate().connect(
            [this] {this->on_about_click();}
        );
    submenu_help->append(*menuitem_help_about);

    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box just below the menu (bonus level)



    // ///////////////////////
    // D A T A   D I S P L A Y
    // Provide a text entry box to show the sweets and orders
    data = Gtk::manage(new Gtk::Label());
    data->set_label("Data");
    main_box->pack_start(*data, Gtk::PACK_SHRINK);

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

void Mainwin::on_add_sweet_click(){
    add_sweet_dialog = Gtk::manage(new Gtk::Dialog());
    add_sweet_dialog->set_title("Add sweet to store");

    name = Gtk::manage(new Gtk::Entry());
    price = Gtk::manage(new Gtk::Entry());
    Gtk::Label* name_label = Gtk::manage(new Gtk::Label());
    Gtk::Label* price_label = Gtk::manage(new Gtk::Label());
    Gtk::Button* close = Gtk::manage(new Gtk::Button());

    close->set_label("Submit");
    close->signal_clicked().connect(
            [this] {this->on_add_sweet_helper();}
        );

    name_label->set_label("Name");
    price_label->set_label("Price");
    add_sweet_dialog->get_vbox()->pack_start(*name_label, Gtk::PACK_SHRINK);
    add_sweet_dialog->get_vbox()->pack_start(*name, Gtk::PACK_SHRINK);
    add_sweet_dialog->get_vbox()->pack_start(*price_label, Gtk::PACK_SHRINK);
    add_sweet_dialog->get_vbox()->pack_start(*price, Gtk::PACK_SHRINK);
    add_sweet_dialog->get_vbox()->pack_start(*close, Gtk::PACK_SHRINK);

    add_sweet_dialog->show_all_children();
    add_sweet_dialog->run();
}

void Mainwin::on_add_sweet_helper(){
    Sweet sweet(name->get_text(),std::atof(price->get_text().data()));
    _store->add(sweet);
    add_sweet_dialog->hide();
}

void Mainwin::on_list_sweets_click(){
    std::string label = "Sweets:\n";
    for(int i = 0; i < _store->num_sweets(); i++){
        label += _store->sweet(i).name() + " : " + std::to_string(_store->sweet(i).price()) + "\n";
    }
    data->set_label(label);
}

void Mainwin::on_about_click(){
    help_dialog = Gtk::manage(new Gtk::AboutDialog());

    std::vector<Glib::ustring> authors;
    authors.push_back("Cole Montgomery");
    help_dialog->set_program_name("Mav's Ultimate Sweet Shop");
    help_dialog->set_authors(authors);
    help_dialog->set_license("LICENSE");

    int response = help_dialog->run();

    if(response == Gtk::RESPONSE_DELETE_EVENT){
        help_dialog->hide();
    }
}

void Mainwin::on_about_click_helper(){
    help_dialog->hide();
}