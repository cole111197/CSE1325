#ifndef __MAINWIN_H
#define __MAINWIN_H

#include <gtkmm.h>

class Mainwin : public Gtk::Window {
	public:
		Mainwin();
		virtual ~Mainwin();
	protected:
		void on_quit_click();
		void on_new_animal_click();
		void on_list_animals_click();
	private:
		Shelter* shelter;
		Gtk::Label* data;
		Gtk::Label* msg;
};

#endif