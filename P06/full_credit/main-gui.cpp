#include "mainwin.h"

// Build Options (mostly the same as the Feature IDs)
//
// BONUS
// -----
//    __SENSITIVITY1 - Manage menu sensitivity for first sprint
//    __TOOLBAR - Add a toolbar (FileNewBtn, FileQuitBtn, SweetsAddBtn, and SweetsListBtn)
//    __RICHTEXT - Use Pango for the About dialog
//
// EXTREME BONUS
// -------------
//    __SWEETSADDDLG - Use a single dialog box for Add Sweets (EXTREME BONUS)
//    __STATUSBAR - Add a status bar (EXTREME BONUS)

int main (int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, APP_NAME);
    Mainwin win;
    return app->run(win);
}

