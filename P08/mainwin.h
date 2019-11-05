#ifndef __MAINWIN_H
#define __MAINWIN_H

#include <gtkmm.h>
#include "shelter.h"
#include "dog.h"

class Mainwin : public Gtk::Window {
	public:
		Mainwin();
		~Mainwin();
	protected:
		void on_quit_click();
		void on_new_animal_click();
		void on_list_animals_click();
	private:
		Shelter* shelter;
		Gtk::Label* data;
		Gtk::Label* msg;
		Gtk::MenuItem* menuitem_animal_new;
		Gtk::MenuItem* menuitem_animal_list;
};

#endif