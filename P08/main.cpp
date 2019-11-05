#include "mainwin.h"

int main (int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "shelter.app");
    Mainwin win;
    return app->run(win);
}