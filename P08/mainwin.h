#ifndef __MAINWIN_H
#define __MAINWIN_H

#include <gtkmm.h>
#include "shelter.h"

const std::string APP_TITLE{"Mavs Animal Shelter Software"};
const std::string APP_NAME{"edu.uta.cse1325.mass.v0_1_0"};
const std::string VERSION{"0.1.0"};

class Mainwin : public Gtk::Window {
	public:
		Mainwin();
		virtual ~Mainwin();
	protected:
		void on_quit_click();
		void on_new_animal_click();
		void on_list_animals_click();
		
		void status(std::string s);
	private:
		Shelter* shelter;
		Gtk::Label* data;
		Gtk::Label* msg;
		Gtk::MenuItem* menuitem_animal_new;
		Gtk::MenuItem* menuitem_animal_list;
};

#endif