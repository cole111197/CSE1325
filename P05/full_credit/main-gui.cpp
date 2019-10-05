#include "mainwin.h"

int main (int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  Mainwin main_win;
  return app->run(main_win);
}

