#ifndef MAINWIN_H
#define MAINWIN_H

#include <gtkmm.h>
#include "store.h"

class Mainwin : public Gtk::Window {
    public:
        Mainwin();
        Mainwin(Store& store);
        virtual ~Mainwin();

    private:
        Store *_store;
        void reset_sensitivity();
        Gtk::MenuBar* main_menu;
        Gtk::Menu* submenu_file;
        Gtk::Menu* submenu_sweets;
        Gtk::MenuItem* menu_file;
        Gtk::MenuItem* menu_sweets;
        Gtk::MenuItem* menuitem_file_quit;
        Gtk::MenuItem* menuitem_file_new;
        Gtk::MenuItem* menuitem_sweets_add;
        Gtk::MenuItem* menuitem_sweets_list;
        Gtk::MenuItem* menuitem_place_order;
        Gtk::MenuItem* menuitem_list_orders;
        Gtk::ToolButton* add_sweet_button;
        Gtk::ToolButton* list_sweets_button;
        Gtk::ToolButton* place_order_button;
        Gtk::ToolButton* list_orders_button;
        Gtk::Dialog* add_sweet_dialog;
        Gtk::Entry* name;
        Gtk::Entry* price;
        Gtk::Label* data;
        Gtk::Label* msg;

    protected:
        void on_new_store_click();
        void on_add_sweet_click();
        void on_list_sweets_click();
        void on_place_order_click();
        void on_list_orders_click();
        void on_about_click();
        void on_quit_click();
        void on_add_sweet_helper();
    // Lots more Mainwin members are needed!
    // (You ARE permitted to change the above as well if you like.)
};
#endif 
