#include <gtkmm.h>

class Mainwin : public Gtk::Window {
  public:
    Mainwin();
    virtual ~Mainwin();
  protected:
    void on_operation_click(int operation);
  private:
    Gtk::Entry* num_entry;
    Gtk::RadioButton* operation_sqrt;
    Gtk::RadioButton* operation_log;
    Gtk::RadioButton* operation_cos;
    Gtk::Label* output;
    Gtk::MessageDialog* error_negative;
    Gtk::MessageDialog* error_invalid;
};
