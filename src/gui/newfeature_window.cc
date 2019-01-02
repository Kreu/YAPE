#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QColorDialog>
#include <QColor>
#include <QSize>

#include "newfeature_window.h"

NewFeatureWindow::NewFeatureWindow(QWidget* parent) : QWidget(parent) {
  setWindowTitle("New feature");
  setWindowFlags(Qt::Window);

  CreateUIElements();
  CreateUILayout();

  //Create the pushbuttons
  

  //Create the labels and user input boxes

   AddElementsToUI();
};

void NewFeatureWindow::CreateUIElements() {
  start_pos_label = new QLabel("Start position");
  start_pos_box = new QLineEdit(this);
  
  end_pos_label = new QLabel("End position");
  end_pos_box = new QLineEdit(this);
  

  cancel_button = new QPushButton("Cancel", this);
  confirm_button = new QPushButton("Create", this);

  colour_label = new QLabel("Colour");
  display_picked_color = new QPushButton;
  display_picked_color->setFlat(true);
  display_picked_color->setAutoFillBackground(true);

  current_colour = QColor(Qt::green); 
  colour_label_palette = display_picked_color->palette();
  colour_label_palette.setColor(QPalette::Button, current_colour);
  display_picked_color->setPalette(colour_label_palette);

  colour_picker_dialog  = new QColorDialog(this);

  //Connects selected colour from QColorDialog to the update function
  //ShowNewColor(const Color&)
  connect(colour_picker_dialog,
          &QColorDialog::colorSelected,
          this,
          &NewFeatureWindow::ShowNewColor);

  //Connects pressing the coloured button to opening a QColorDialog
  connect(display_picked_color,
          &QPushButton::clicked,
          colour_picker_dialog,
          &QColorDialog::show);

  //Connects pressing Cancel to closing the window
  connect(cancel_button,
          &QPushButton::clicked,
          this,
          &NewFeatureWindow::close);
}

void NewFeatureWindow::CreateUILayout() {
  layout = new QGridLayout(this); 
}

void NewFeatureWindow::AddElementsToUI() {
  layout->addWidget(start_pos_label, 0, 0);
  layout->addWidget(end_pos_label, 1, 0);
  layout->addWidget(start_pos_box, 0, 1);
  layout->addWidget(end_pos_box, 1, 1);

  layout->addWidget(colour_label, 2, 0);
  layout->addWidget(confirm_button, 3, 1);
  layout->addWidget(cancel_button, 3, 0);
  layout->addWidget(display_picked_color, 2, 1);
}

void NewFeatureWindow::ShowNewColor(const QColor& color) {
  colour_label_palette.setColor(QPalette::Button, color);
  display_picked_color->setPalette(colour_label_palette);
}
