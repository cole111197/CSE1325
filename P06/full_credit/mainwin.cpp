#include "mainwin.h"
#include <sstream>

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

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

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

    //     S W E E T S
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

    //     H E L P
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

#ifdef __TOOLBAR
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

    //     Q U I T
    // Add a icon for quitting
    Gtk::ToolButton *quit_button = Gtk::manage(new Gtk::ToolButton(Gtk::Stock::QUIT));
    quit_button->set_tooltip_markup("Exit Sweets");
    quit_button->signal_clicked().connect([this] {this->on_quit_click();});
    Gtk::SeparatorToolItem *sep = Gtk::manage(new Gtk::SeparatorToolItem());
    sep->set_expand(true);  // The expanding sep forces the Quit button to the right
    toolbar->append(*sep);
    toolbar->append(*quit_button);
#endif

    // D A T A   D I S P L A Y
    // Provide a text entry box to show the remaining sticks
    data = Gtk::manage(new Gtk::Label());
    data->set_hexpand(true);
    data->set_vexpand(true);
    vbox->add(*data);

#ifdef __STATUSBAR
    // S T A T U S   B A R   D I S P L A Y
    // Provide a status bar for transient messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->add(*msg);
#endif
#ifdef __SENSITIVITY1
    // Set the sensitivity of menu and tool bar items to match what data is available
    reset_sensitivity();
#endif
    // Make the box and everything in it visible
    vbox->show_all();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Mainwin::on_new_store_click() {
    _store = new Store;

#ifdef __SENSITIVITY1
    reset_sensitivity();
#endif
    data->set_text("");
#ifdef __STATUSBAR
    msg->set_text("New Mav's Ultimate Sweet Shop created");
#endif
}

void Mainwin::on_quit_click() {
    close();
}

void Mainwin::on_add_sweet_click() {
    std::string name = "";
    double price = -1;

#ifndef __SWEETSADDDLG
    EntryDialog dialog{*this, "Name of new sweet?"};
    dialog.run();
    name = dialog.get_text();
    if(name.size() == 0) {
#ifdef __STATUSBAR
        msg->set_text("New sweet cancelled");
#endif
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
#ifdef __STATUSBAR
            msg->set_text("New sweet cancelled");
#endif
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
#ifdef __STATUSBAR
    msg->set_text("Added " + sweet.name());
#endif

#ifdef __SENSITIVITY1
    reset_sensitivity();
#endif
}

void Mainwin::on_list_sweets_click() {
    if (_store->num_sweets() == 0) {
        data->set_markup("<span size='large' weight='bold'>No sweets have been defined yet</span>");
#ifdef __STATUSBAR
        msg->set_text("");
#endif
        return;
    }

    // The string manipulation way
    std::string s = "<span size='large' weight='bold'>";
    for(int i=0; i<_store->num_sweets(); ++i) 
        s += _store->sweet(i).name() + "  $" + std::to_string(_store->sweet(i).price()) + "\n";
    s += "</span>";
    data->set_markup(s);
#ifdef __STATUSBAR
    msg->set_text("");
#endif
}

void Mainwin::on_about_click() {
#ifdef __RICHTEXT
    Glib::ustring s = "<span size='36000' weight='bold'>Mav's Ultimate Sweet Shop " + VERSION + "</span>\n"
        + "<span size='large'>Copyright 2019 by George F. Rice</span>\n\n"
        + "<span size='small'>Licensed under the Gnu General Public License 3.0\n    https://www.gnu.org/licenses/gpl-3.0.en.html\n\n</span>"
        + "<span size='small'>Candy photo created by Biscanski and donated to the public domain\n    https://pixnio.com/food-and-drink/desserts-cakes/sweet-color-sugar-gelatin-confectionery-delicious-food-candy\n\n</span>"
        + "<span size='small'>Lollipop icon derived from http://pngimg.com/download/13817, used under Creative Commons 4.0 BY-NC\n\n</span>"
        + "<span size='small'>Lollipops in Jar icon derived from https://www.pngfind.com/mpng/hxbTbow_jar-clipart-lollipop-lollipops-in-a-jar-hd/ under Personal Use Only license\n\n</span>";
#else
    Glib::ustring s = "Mav's Ultimate Sweet Shop " + VERSION
        + "\nCopyright 2019 by George F. Rice\n\n"
        + "Licensed under the Gnu General Public License 3.0\n    https://www.gnu.org/licenses/gpl-3.0.en.html\n\n"
        + "Candy photo created by Biscanski and donated to the public domain\n    https://pixnio.com/food-and-drink/desserts-cakes/sweet-color-sugar-gelatin-confectionery-delicious-food-candy\n\n"
        + "Lollipop icon derived from http://pngimg.com/download/13817, used under Creative Commons 4.0 BY-NC\n\n"
        + "Lollipops in Jar icon derived from https://www.pngfind.com/mpng/hxbTbow_jar-clipart-lollipop-lollipops-in-a-jar-hd/ under Personal Use Only license";
#endif
    Gtk::MessageDialog dlg(*this, s, true);
    dlg.run();
}

#ifdef __SENSITIVITY1
// /////////////////
// Utilities
// /////////////////

void Mainwin::reset_sensitivity() {
    menuitem_list_sweets->set_sensitive(_store->num_sweets() > 0);
#ifdef __TOOLBAR
    list_sweets_button->set_sensitive(_store->num_sweets() > 0);
#endif
}
#endif

