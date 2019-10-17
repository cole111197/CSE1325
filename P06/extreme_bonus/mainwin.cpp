#include "mainwin.h"
#include <vector>

Mainwin::Mainwin() : Mainwin{*(new Store)} { }
Mainwin::Mainwin(Store& store) : _store{&store},
    menuitem_file_quit{Gtk::manage(new Gtk::MenuItem("Quit"))},
    menuitem_file_new{Gtk::manage(new Gtk::MenuItem("New"))},
    menuitem_sweets_add{Gtk::manage(new Gtk::MenuItem("Add"))},
    menuitem_sweets_list{Gtk::manage(new Gtk::MenuItem("List"))},
    menuitem_help_about{Gtk::manage(new Gtk::MenuItem("About"))},
    new_store_button{Gtk::manage(new Gtk::ToolButton(Gtk::Stock::NEW))},
    quit_button{Gtk::manage(new Gtk::ToolButton(Gtk::Stock::QUIT))},
    data{Gtk::manage(new Gtk::Label("Data"))},
    add_sweet_button{Gtk::manage(new Gtk::ToolButton(*Gtk::manage(new Gtk::Image("Assets/sweet.png"))))},
    list_sweets_button{Gtk::manage(new Gtk::ToolButton(*Gtk::manage(new Gtk::Image("Assets/list.png"))))},
    msg{Gtk::manage(new Gtk::Label())}
{

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
    Gtk::MenuBar* main_menu = Gtk::manage(new Gtk::MenuBar());
    Gtk::MenuItem* menu_file = Gtk::manage(new Gtk::MenuItem("File"));
    Gtk::MenuItem* menu_sweets = Gtk::manage(new Gtk::MenuItem("Sweets"));
    Gtk::MenuItem* menu_help = Gtk::manage(new Gtk::MenuItem("Help"));
    Gtk::Menu* submenu_file = Gtk::manage(new Gtk::Menu());
    Gtk::Menu* submenu_sweets = Gtk::manage(new Gtk::Menu());
    Gtk::Menu* submenu_help = Gtk::manage(new Gtk::Menu());

    main_box->pack_start(*main_menu, Gtk::PACK_SHRINK);
    main_menu->append(*menu_file);
    main_menu->append(*menu_sweets);
    main_menu->append(*menu_help);

    menu_file->set_submenu(*submenu_file);
    menuitem_file_quit->signal_activate().connect(
            [this] {this->on_quit_click();}
        );
    menuitem_file_new->signal_activate().connect(
            [this] {this->on_new_store_click();}
        );
    submenu_file->append(*menuitem_file_quit);
    submenu_file->append(*menuitem_file_new);

    menu_sweets->set_submenu(*submenu_sweets);
    menuitem_sweets_add->signal_activate().connect(
            [this] {this->on_add_sweet_click();}
        );
    menuitem_sweets_list->signal_activate().connect(
            [this] {this->on_list_sweets_click();}
        );
    submenu_sweets->append(*menuitem_sweets_add);
    submenu_sweets->append(*menuitem_sweets_list);

    menu_help->set_submenu(*submenu_help);
    menuitem_help_about->signal_activate().connect(
            [this] {this->on_about_click();}
        );
    submenu_help->add(*menuitem_help_about);

    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box just below the menu (bonus level)
    Gtk::Toolbar* main_toolbar = Gtk::manage(new Gtk::Toolbar());

    main_toolbar->append(*new_store_button);
    main_toolbar->append(*list_sweets_button);
    main_toolbar->append(*add_sweet_button);
    main_toolbar->append(*quit_button);
    main_box->pack_start(*main_toolbar, Gtk::PACK_SHRINK);

    new_store_button->signal_clicked().connect(
        [this] {this->on_new_store_click();}
    );
    list_sweets_button->signal_clicked().connect(
        [this] {this->on_list_sweets_click();}
    );
    add_sweet_button->signal_clicked().connect(
        [this] {this->on_add_sweet_click();}
    );
    quit_button->signal_clicked().connect(
        [this] {this->on_quit_click();}
    );

    // ///////////////////////
    // D A T A   D I S P L A Y
    // Provide a text entry box to show the sweets and orders
    main_box->pack_start(*data, Gtk::PACK_SHRINK);

    // ///////////////////////////////////    
    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for transient messages
    msg->set_hexpand(true);
    main_box->pack_start(*msg);

    // Make the vertical box and everything in it visible
    menuitem_sweets_list->set_sensitive(false);
    main_box->show_all();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Mainwin::on_quit_click(){
    close();
}

void Mainwin::on_new_store_click(){
    _store = new Store();
    menuitem_sweets_list->set_sensitive(false);
    msg->set_text("New shop created");
}

void Mainwin::on_add_sweet_click(){
    add_sweet_dialog = Gtk::manage(new Gtk::Dialog());
    add_name = Gtk::manage(new Gtk::Entry());
    add_price = Gtk::manage(new Gtk::Entry());
    Gtk::Label* name_label = Gtk::manage(new Gtk::Label("Name"));
    Gtk::Label* price_label = Gtk::manage(new Gtk::Label("Price"));
    Gtk::HBox* container_name = Gtk::manage(new Gtk::HBox(true, 0));
    Gtk::HBox* container_price = Gtk::manage(new Gtk::HBox(true, 0));
    Gtk::HBox* container_buttons = Gtk::manage(new Gtk::HBox(true, 0));
    Gtk::Button* create = Gtk::manage(new Gtk::Button("Create"));
    Gtk::Button* cancel = Gtk::manage(new Gtk::Button("Cancel"));

    add_sweet_dialog->set_title("Add sweet to store");

    container_name->pack_start(*name_label);
    container_name->pack_start(*add_name);
    container_price->pack_start(*price_label);
    container_price->pack_start(*add_price);
    container_buttons->pack_start(*create);
    container_buttons->pack_start(*cancel);

    add_sweet_dialog->get_vbox()->pack_start(*container_name);
    add_sweet_dialog->get_vbox()->pack_start(*container_price);
    add_sweet_dialog->get_vbox()->pack_start(*container_buttons);

    create->signal_clicked().connect(
            [this] {this->on_add_sweet_helper(true);}
        );
    cancel->signal_clicked().connect(
            [this] {this->on_add_sweet_helper(false);}
        );

    add_sweet_dialog->show_all_children();
    add_sweet_dialog->run();
}

void Mainwin::on_list_sweets_click(){
    std::string label = "Sweets:\n";
    for(int i = 0; i < _store->num_sweets(); i++){
        label += _store->sweet(i).name() + " : " + std::to_string(_store->sweet(i).price()) + "\n";
    }
    data->set_label(label);
}

void Mainwin::on_about_click(){
    Gtk::AboutDialog* help_dialog = Gtk::manage(new Gtk::AboutDialog());

    std::vector<Glib::ustring> authors;
    std::vector<Glib::ustring> artists;
    authors.push_back("Cole Montgomery");
    artists.push_back("https://www.iconfinder.com/icons/111034/candy_icon");
    artists.push_back("https://www.iconfinder.com/icons/111124/find_search_zoom_icon");
    help_dialog->set_program_name("Mav's Ultimate Sweet Shop");
    help_dialog->set_authors(authors);
    help_dialog->set_artists(artists);
    help_dialog->set_license("GPLv3");

    int response = help_dialog->run();

    if(response == Gtk::RESPONSE_DELETE_EVENT){
        help_dialog->hide();
    }
}

// /////////////////
// U T I L I T I E S
// /////////////////

void Mainwin::reset_sensitivity(){
    menuitem_sweets_list->set_sensitive();
}

void Mainwin::on_add_sweet_helper(bool add){
    if(add == true){
        int num_sweets = _store->num_sweets();
        Sweet sweet(add_name->get_text(),std::atof(add_price->get_text().data()));
        _store->add(sweet);
        if(_store->num_sweets() > num_sweets){
            reset_sensitivity();
            msg->set_text("Added " + add_name->get_text());
        }
    } else if(add == false){
        msg->set_text("New sweet cancelled");
    }
    add_sweet_dialog->hide();
}
