#include "mainwin.h"
#include <sstream>
#include <iostream>
#include <fstream>

#ifndef __SWEETSADDDLG
#include "entrydialog.h"
#endif

Mainwin::Mainwin() : Mainwin{*(new Store)} { }
Mainwin::Mainwin(Store& store) : _store{&store} {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(640, 480);
    set_title("Mav's Ultimate Sweet Shop");

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    // ///////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

//////     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    // S A V E
    menuitem_file_save = Gtk::manage(new Gtk::MenuItem("_Save", true));
    menuitem_file_save->signal_activate().connect([this] {this->on_save_click();});
    filemenu->append(*menuitem_file_save);

    // L O A D
    menuitem_file_load = Gtk::manage(new Gtk::MenuItem("_Load", true));
    menuitem_file_load->signal_activate().connect([this] {this->on_load_click();});
    filemenu->append(*menuitem_file_load);

    //         N E W   S T O R E
    // Append New to the File menu
    Gtk::MenuItem *menuitem_new = Gtk::manage(new Gtk::MenuItem("_New Store", true));
    menuitem_new->signal_activate().connect([this] {this->on_new_store_click();});
    filemenu->append(*menuitem_new);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->on_quit_click();});
    filemenu->append(*menuitem_quit);

//////     O R D E R S
    // Create an Orders menu and add to the menu bar
    Gtk::MenuItem *menuitem_orders = Gtk::manage(new Gtk::MenuItem("_Orders", true));
    menubar->append(*menuitem_orders);
    Gtk::Menu *ordersmenu = Gtk::manage(new Gtk::Menu());
    menuitem_orders->set_submenu(*ordersmenu);

    //         P L A C E
    menuitem_place_order = Gtk::manage(new Gtk::MenuItem("_Place", true));
    menuitem_place_order->signal_activate().connect([this] {this->on_place_order_click();});
    ordersmenu->append(*menuitem_place_order);

    //         L I S T
    menuitem_list_orders = Gtk::manage(new Gtk::MenuItem("_List", true));
    menuitem_list_orders->signal_activate().connect([this] {this->on_list_orders_click();});
    ordersmenu->append(*menuitem_list_orders);

//////     S W E E T S
    // Create a Sweets menu and add to the menu bar
    Gtk::MenuItem *menuitem_sweets = Gtk::manage(new Gtk::MenuItem("_Sweets", true));
    menubar->append(*menuitem_sweets);
    Gtk::Menu *sweetsmenu = Gtk::manage(new Gtk::Menu());
    menuitem_sweets->set_submenu(*sweetsmenu);

    //         A D D   S W E E T
    // Append Add to the Sweets menu
    menuitem_add_sweet = Gtk::manage(new Gtk::MenuItem("_Add", true));
    menuitem_add_sweet->signal_activate().connect([this] {this->on_add_sweet_click();});
    sweetsmenu->append(*menuitem_add_sweet);

    //         L I S T   S W E E T S
    // Append List to the Sweets menu
    menuitem_list_sweets = Gtk::manage(new Gtk::MenuItem("_List", true));
    menuitem_list_sweets->signal_activate().connect([this] {this->on_list_sweets_click();});
    sweetsmenu->append(*menuitem_list_sweets);

//////     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("About", true));
    menuitem_about->signal_activate().connect([this] {this->on_about_click();});
    helpmenu->append(*menuitem_about);

    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////
    // /////////////
    // T O O L B A R
    // Add a toolbar to the vertical box below the menu
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar);
    vbox->add(*toolbar);

    //     N E W   S T O R E
    // Add a new store icon
    Gtk::ToolButton *new_store_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::NEW));
    new_store_button->set_tooltip_markup("Create a new store, discarding any unsaved data");
    new_store_button->signal_clicked().connect([this] {this->on_new_store_click();});
    toolbar->append(*new_store_button);

    //     A D D   S W E E T 
    // Add a icon for adding a new sweet product
    Gtk::Image* add_sweet_image = Gtk::manage(new Gtk::Image{"lollipop+32.png"});
    add_sweet_button = Gtk::manage(new Gtk::ToolButton(*add_sweet_image));
    add_sweet_button->set_tooltip_markup("Add a new sweet");
    add_sweet_button->signal_clicked().connect([this] {this->on_add_sweet_click();});
    toolbar->append(*add_sweet_button);

    //     L I S T   S W E E T S
    // Add a icon for listing sweets
    Gtk::Image* list_sweets_image = Gtk::manage(new Gtk::Image{"lollipop-32.png"});
    list_sweets_button = Gtk::manage(new Gtk::ToolButton(*list_sweets_image));
    list_sweets_button->set_tooltip_markup("List an sweet");
    list_sweets_button->signal_clicked().connect([this] {this->on_list_sweets_click();});
    toolbar->append(*list_sweets_button);

    //     P L A C E   O R D E R
    Gtk::Image* place_order_image = Gtk::manage(new Gtk::Image{"order_place.png"});
    place_order_button = Gtk::manage(new Gtk::ToolButton(*place_order_image));
    place_order_button->set_tooltip_markup("Place a new order");
    place_order_button->signal_clicked().connect([this] {this->on_place_order_click();});
    toolbar->append(*place_order_button);

    //     L I S T   O R D E R
    Gtk::Image* list_orders_image = Gtk::manage(new Gtk::Image{"order_list.png"});
    list_orders_button = Gtk::manage(new Gtk::ToolButton(*list_orders_image));
    list_orders_button->set_tooltip_markup("List an order");
    list_orders_button->signal_clicked().connect([this] {this->on_list_orders_click();});
    toolbar->append(*list_orders_button);

    //     Q U I T
    // Add a icon for quitting
    Gtk::ToolButton *quit_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::QUIT));
    quit_button->set_tooltip_markup("Exit Sweets");
    quit_button->signal_clicked().connect([this] {this->on_quit_click();});
    Gtk::SeparatorToolItem *sep = Gtk::manage(new Gtk::SeparatorToolItem());
    sep->set_expand(true);  // The expanding sep forces the Quit button to the right
    toolbar->append(*sep);
    toolbar->append(*quit_button);
    //////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////

    // D A T A   D I S P L A Y
    // Provide a text entry box to show the remaining sticks
    data = Gtk::manage(new Gtk::Label());
    data->set_hexpand(true);
    data->set_vexpand(true);
    vbox->add(*data);

    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for transient messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->add(*msg);

    // Set the sensitivity of menu and tool bar items to match what data is available
    reset_sensitivity();
    
    // Make the box and everything in it visible
    vbox->show_all();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Mainwin::on_new_store_click() {
    _store = new Store;

    reset_sensitivity();
    data->set_text("");
    msg->set_text("New Mav's Ultimate Sweet Shop created");
}

void Mainwin::on_quit_click() {
    close();
}

void Mainwin::on_place_order_click() {
    Gtk::Dialog* dialog = Gtk::manage(new Gtk::Dialog("Place an order", *this));

    Gtk::Separator* sep = Gtk::manage(new Gtk::Separator(Gtk::ORIENTATION_VERTICAL));
    Gtk::Label* total_data = Gtk::manage(new Gtk::Label());
    Gtk::Label* add = Gtk::manage(new Gtk::Label("Add"));
    Gtk::Label* sweet = Gtk::manage(new Gtk::Label("Sweet:"));
    Gtk::Label* quantity_label = Gtk::manage(new Gtk::Label("Quantity:"));

    Gtk::ComboBoxText* sweet_dropdown = Gtk::manage(new Gtk::ComboBoxText(false));
    Gtk::ComboBoxText* quantity_dropdown = Gtk::manage(new Gtk::ComboBoxText(true));
    Gtk::HBox* sweet_hbox = Gtk::manage(new Gtk::HBox(true, 0));
    Gtk::HBox* quantity_hbox = Gtk::manage(new Gtk::HBox(true, 0));

    Gtk::Button* add_order = Gtk::manage(new Gtk::Button("Add"));
    Gtk::Button* finish = Gtk::manage(new Gtk::Button("Finish"));
    Gtk::HBox* button_hbox = Gtk::manage(new Gtk::HBox(true, 5));
    Gtk::Button* cancel = Gtk::manage(new Gtk::Button("Cancel"));

    for(int i = 0; i < _store->num_sweets(); i++){
        sweet_dropdown->append(_store->sweet(i).name());
    }
    sweet_hbox->pack_start(*sweet, Gtk::PACK_SHRINK);
    sweet_hbox->pack_start(*sweet_dropdown);

    for(int i = 1; i <= 10; i++){
        quantity_dropdown->append(std::to_string(i));
    }
    quantity_hbox->pack_start(*quantity_label, Gtk::PACK_SHRINK);
    quantity_hbox->pack_start(*quantity_dropdown);

    button_hbox->pack_start(*add_order);
    button_hbox->pack_start(*finish);

    Sweet temp_sweet{"", 0};
    sweet_dropdown->signal_changed().connect([&] {
        for(int i = 0; i < _store->num_sweets(); i++){
            if(_store->sweet(i).name() == sweet_dropdown->get_active_text()){
                temp_sweet = _store->sweet(i);
            }
        }
    });

    int quantity = -1;
    quantity_dropdown->signal_changed().connect([&] {
        try {
            quantity = std::stoi(quantity_dropdown->get_active_text());
        } catch(std::exception e) {
            quantity = -1;
            total_data->set_text("Invalid quantity");
        }
    });

    cancel->signal_clicked().connect([&dialog] {delete dialog;});

    std::vector<Sweet> added_sweets;
    std::vector<int> added_quantities;
    std::string data = "";
    for(int i = 0; i < added_sweets.size(); i++){
        data += added_sweets.at(i).name() + " x " + std::to_string(added_quantities.at(i)) + "\n";
    }
    total_data->set_text(data);

    add_order->signal_clicked().connect([&] {
        if(quantity != -1){
            bool duplicate = false;
            for(int i = 0; i < added_sweets.size(); i++){
                if(temp_sweet.name() == added_sweets.at(i).name()){
                    added_quantities.at(i) += quantity;
                    duplicate = true;
                }
            }
            if(duplicate == false){
                added_sweets.push_back(temp_sweet);
                added_quantities.push_back(quantity);
            }
            
            std::string data = "";
            for(int i = 0; i < added_sweets.size(); i++){
                data += added_sweets.at(i).name() + " x " + std::to_string(added_quantities.at(i)) + "\n";
            }
            total_data->set_text(data);
        } else {
            total_data->set_text("Error placing order. Check values");
        }
    });

    finish->signal_clicked().connect([&] {
        Order order;
        for(int i = 0; i < added_sweets.size(); i++){
            order.add(added_quantities.at(i), added_sweets.at(i));
        }
        _store->add(order);
        reset_sensitivity();
        delete dialog;
    });

    dialog->get_vbox()->pack_start(*total_data, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(*sep, Gtk::PACK_SHRINK, 10);
    dialog->get_vbox()->pack_start(*add, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(*sweet_hbox, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(*quantity_hbox, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(*button_hbox, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(*cancel);

    dialog->show_all();
    dialog->run();
}

void Mainwin::on_add_sweet_click() {
    std::string name = "";
    double price = -1;

#ifndef __SWEETSADDDLG
    EntryDialog dialog{*this, "Name of new sweet?"};
    dialog.run();
    name = dialog.get_text();
    if(name.size() == 0) {
        msg->set_text("New sweet cancelled");
        return;
    }

    std::string prompt = "Price?";
    while (price < 0) {
        EntryDialog dialog{*this, prompt};
        dialog.run();
        try {
            price = std::stod(dialog.get_text());
        } catch(std::exception e) {
            prompt = "Invalid Price! Price?";
            price = -1;
        }
    }
    
#else
    Gtk::Dialog *dialog = new Gtk::Dialog{"Create a Sweet", *this};

    // Name
    Gtk::HBox b_name;

    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(15);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);

    Gtk::Entry e_name;
    e_name.set_max_length(50);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    // Price
    Gtk::HBox b_price;

    Gtk::Label l_price{"Price:"};
    l_price.set_width_chars(15);
    b_price.pack_start(l_price, Gtk::PACK_SHRINK);

    Gtk::Entry e_price;
    e_price.set_max_length(50);
    b_price.pack_start(e_price, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_price, Gtk::PACK_SHRINK);

    // Show dialog
    dialog->add_button("Cancel", 0);
    dialog->add_button("Create", 1);
    dialog->show_all();

    int result; // of the dialog (1 = OK)
    bool fail = true;  // set to true if any data is invalid

    while (fail) {
        fail = false;  // optimist!
        result = dialog->run();
        if (result != 1) {
            msg->set_text("New sweet cancelled");
            delete dialog;
            return;}
        try {
            price = std::stod(e_price.get_text());
        } catch(std::exception e) {
            e_price.set_text("### Invalid ###");
            fail = true;
        }
        name = e_name.get_text();
        if (name.size() == 0) {
            e_name.set_text("### Invalid ###");
            fail = true;
        }
    }
    delete dialog;
#endif
    Sweet sweet{name, price};
    _store->add(sweet);
    on_list_sweets_click();
    msg->set_text("Added " + sweet.name());

    reset_sensitivity();
}

void Mainwin::on_list_orders_click(){
    if(_store->num_orders() == 0){
        data->set_markup("<span size='large' weight='bold'>No orders have been defined yet</span>");
        msg->set_text("");
        return;
    }

    std::string prompt;
    if(_store->num_orders() == 1){
        prompt = "Enter order number: 0";
    } else {
        prompt = "Enter order number: 0-" + std::to_string(_store->num_orders()-1);
    }
    EntryDialog dialog{*this, prompt};
    try{
        dialog.run();
        int index = std::stoi(dialog.get_text());
        if(index < 0 || index > _store->num_orders()-1){
            throw std::exception();
        }
        std::string s = "<span size='large' weight='bold'>";
        s += "Order #" + std::to_string(index) + ":\n";
        for(int i = 0; i < _store->order(index).size(); i++){
            s += _store->order(index).sweet(i).name() + " x " + std::to_string( _store->order(index).quantity(i)) + "\n";
        }
        s += "\n";
        s += "</span>";
        data->set_markup(s);
        msg->set_text("");
    } catch(std::exception e){
        msg->set_text("Invalid order number!");
        dialog.hide();
    }
}

void Mainwin::on_list_sweets_click() {
    if (_store->num_sweets() == 0) {
        data->set_markup("<span size='large' weight='bold'>No sweets have been defined yet</span>");
        msg->set_text("");
        return;
    }

    std::string s = "<span size='large' weight='bold'>";
    for(int i=0; i<_store->num_sweets(); ++i) 
        s += _store->sweet(i).name() + "  $" + std::to_string(_store->sweet(i).price()) + "\n";
    s += "</span>";
    data->set_markup(s);
    msg->set_text("");
}

void Mainwin::on_about_click() {
    Gtk::AboutDialog* about = Gtk::manage(new Gtk::AboutDialog());
    about->set_deletable(true);
    std::vector<Glib::ustring> artists;
    artists.push_back("Candy photo created by Biscanski and donated to the public domain\nhttps://pixnio.com/food-and-drink/desserts-cakes/sweet-color-sugar-gelatin-confectionery-delicious-food-candy");
    artists.push_back("Lollipop icon derived from http://pngimg.com/download/13817, used under Creative Commons 4.0 BY-NC");
    artists.push_back("Lollipops in Jar icon derived from https://www.pngfind.com/mpng/hxbTbow_jar-clipart-lollipop-lollipops-in-a-jar-hd/ under Personal Use Only license");
    artists.push_back("Clipboard icon derived from https://www.iconfinder.com/icons/314893/list_notebook_icon under Free for commercial use license");

    about->set_program_name("Mav's Ultimate Sweet Shop");
    about->set_version(VERSION);
    about->set_copyright("Copyright 2019 by Cole Montgomery");
    about->set_license("Licensed under the Gnu General Public License 3.0\nhttps://www.gnu.org/licenses/gpl-3.0.en.html");
    about->set_artists(artists);

    about->run();
}

void Mainwin::on_save_click(){
    std::ofstream file;
    file.open("data.muss");
    file << "SWEETS----\n";
    for(int i = 0; i < _store->num_sweets(); i++){
        file << _store->sweet(i).name() << "\n" << std::to_string(_store->sweet(i).price()) << "\n";
    }
    file << "ORDERS----\n";
    for(int i = 0; i < _store->num_orders(); i++){
        file << "NEW\n";
        for(int j = 0; j < _store->order(i).size(); j++){
            file << std::to_string(_store->order(i).quantity(j)) << "\n" << _store->order(i).sweet(j).name() << "\n" << std::to_string(_store->order(i).sweet(j).price()) << "\n";
        }
    }
    file.close();
}

void Mainwin::on_load_click(){
    _store = new Store;
    std::ifstream file("data.muss");
    std::string line;
    std::string temp;
    std::string sweet_name;
    double sweet_price;
    int quantity;
    Sweet* temp_sweet = new Sweet("",0);
    Order temp_order;
    if(file.is_open()){
        getline(file,line);
        while(line != "ORDERS----"){
            if(line != "SWEETS----"){
                getline(file,temp);
                sweet_name = temp;
                getline(file,temp);
                sweet_price = std::stod(temp);
                temp_sweet = new Sweet(sweet_name, sweet_price);
                _store->add(*temp_sweet);
            }
        }
        while(getline(file,line)){
            if(line == "NEW"){
                while(line != "NEW"){
                    getline(file,temp);
                    quantity = std::stoi(temp);
                    getline(file,temp);
                    sweet_name = temp;
                    getline(file,temp);
                    sweet_price = std::stod(temp);
                    temp_sweet = new Sweet(sweet_name, sweet_price);
                    temp_order.add(quantity, *temp_sweet);
                    _store->add(temp_order);
                }
            }
        }
        file.close();
    }
}

// /////////////////
// Utilities
// /////////////////

void Mainwin::reset_sensitivity() {
    menuitem_list_sweets->set_sensitive(_store->num_sweets() > 0);
    menuitem_place_order->set_sensitive(_store->num_sweets() > 0);
    menuitem_list_orders->set_sensitive(_store->num_orders() > 0);

    list_sweets_button->set_sensitive(_store->num_sweets() > 0);
    place_order_button->set_sensitive(_store->num_sweets() > 0);
    list_orders_button->set_sensitive(_store->num_orders() > 0);
}