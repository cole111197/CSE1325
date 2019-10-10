#include "mainwin.h"
#include <string>
#include <cmath>

Mainwin::Mainwin() :
  num_entry{Gtk::manage(new Gtk::Entry)},
  operation_sqrt{Gtk::manage(new Gtk::RadioButton("Square root"))},
  operation_log{Gtk::manage(new Gtk::RadioButton("Natural logarithm"))},
  operation_cos{Gtk::manage(new Gtk::RadioButton("Cosine"))},
  output{Gtk::manage(new Gtk::Label("0"))},
  error_negative{Gtk::manage(new Gtk::MessageDialog(*this, "Error: Input less than 0"))},
  error_invalid{Gtk::manage(new Gtk::MessageDialog(*this, "Error: Input invalid. Please enter a number"))}
  {

  set_title("Cole Montgomery - 27");

  Gtk::VBox* vbox = Gtk::manage(new Gtk::VBox);
  add(*vbox);

  vbox->pack_start(*num_entry);
  num_entry->set_text("0");

  Gtk::Frame* radio_frame = Gtk::manage(new Gtk::Frame);
  vbox->pack_start(*radio_frame);
  Gtk::VBox *vbox_frame = Gtk::manage(new Gtk::VBox);
  radio_frame->add(*vbox_frame);
  vbox_frame->pack_start(*operation_sqrt);
  vbox_frame->pack_start(*operation_log);
  vbox_frame->pack_start(*operation_cos);
  operation_log->join_group(*operation_sqrt);
  operation_cos->join_group(*operation_sqrt);

  operation_sqrt->signal_clicked().connect([this] {this->on_operation_click(1);});
  operation_log->signal_clicked().connect([this] {this->on_operation_click(2);});
  operation_cos->signal_clicked().connect([this] {this->on_operation_click(3);});

  vbox->pack_start(*output);

  vbox->show_all();
}

Mainwin::~Mainwin() { }

void Mainwin::on_operation_click(int operation) {
  double entry_data = std::atof(num_entry->get_text().data());
  if(num_entry->get_text() != "0" && entry_data == 0){
    error_invalid->run();
  } else if(entry_data < 0){
    error_negative->run();
  }
  if(operation == 1){
    output->set_text(std::to_string(sqrt(entry_data)));
  } else if(operation == 2){
    output->set_text(std::to_string(log(entry_data)));
  } else if(operation == 3){
    output->set_text(std::to_string(cos(entry_data)));
  }
}
