To build the full_credit version, just type

  make clean ; make

To build the bonus version, type

  make clean ; make bonus

To build the extreme bonus version, type

  make clean ; make xbonus

To make with an arbitrary combination of bonus or extreme bonus features, define the associated variable(s). For example, to build with ONLY the toolbar added, type

  make clean ; make CXXFLAGS='--std=c++17 -D__TOOLBAR'

The preprocessor variables are shown in main-gui.cpp, and replicated here for convenience::

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

Note that I didn't exhaustively try every possible combination of features.  :-)

