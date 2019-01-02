#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QToolBar>
#include <QTextEdit>
#include <QSizePolicy>
#include <QString>
#include <QKeySequence>

#include "mainwindow.h"
#include "sequence_textbox.h"
#include "newfeature_window.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
 
  setWindowTitle("Yet Another Plasmid Editor");
  setBaseSize(800, 550);

  //Create actions
  //DO NOT REORDER -> Actions need to be created before menus
  //because menus require actions to exist.
  CreateActions();

  //Create menus
  CreateMenuBar();
  CreateToolBar();
  CreateStatusBar();

  //Create central textbox
  CreateSequenceBox();
}

void MainWindow::CreateSequenceBox() {
  sequence_textbox = new SequenceTextBox(this);
  this->setCentralWidget(sequence_textbox); 
}

void MainWindow::CreateMenuBar() {

  //File submenu
  file_menu = this->menuBar()->addMenu(tr("&File"));
  file_menu->addAction(open_file_act);
  file_menu->addAction(save_file_act);  
  file_menu->addAction(print_act);
  file_menu->addAction(preferences_act);
  file_menu->addAction(quit_app_act);
  
  //Edit submenu
  edit_menu = this->menuBar()->addMenu(tr("&Edit"));
  edit_menu->addAction(complement_act);
  edit_menu->addAction(reverse_complement_act);

  //Features submenu
  features_menu = this->menuBar()->addMenu(tr("Fea&tures"));
  features_menu->addAction(create_feature_act);
  features_menu->addAction(edit_feature_act);
  features_menu->addAction(delete_feature_act);
}

void MainWindow::CreateToolBar() {
  toolbar = new QToolBar("Toolbar");
  this->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolbar);
}

void MainWindow::CreateStatusBar() {
  status_bar = new QStatusBar(this);
  this->setStatusBar(status_bar);
}

void MainWindow::CreateActions() {
  //File menu actions
  open_file_act = new QAction(tr("&Open file"));
  open_file_act->setShortcut(QKeySequence::Open);

  save_file_act = new QAction(tr("&Save file"));
  save_file_act->setShortcut(QKeySequence::Save);

  print_act = new QAction(tr("&Print"));
  print_act->setShortcut(QKeySequence::Print);

  preferences_act = new  QAction(tr("P&references"));

  quit_app_act = new QAction(tr("E&xit"));
  quit_app_act->setShortcut(QKeySequence(tr("Ctrl+X")));
  connect(quit_app_act,
          &QAction::triggered,
          this,
          &MainWindow::close);

  //Edit menu actions
  complement_act = new QAction(tr("&Complement"));
  connect(complement_act,
          &QAction::triggered,
          this,
          &MainWindow::Complement);

  reverse_complement_act = new QAction(tr("&Reverse complement"));
  //connect(ReverseComplementAct,
  //        &QAction::triggered,
  //        this,
  //        &MainWindow::ReverseComplement);
  //
  create_feature_act = new QAction(tr("&Create feature"));
  connect(create_feature_act,
          &QAction::triggered,
          this,
          &MainWindow::CreateNewFeatureWindow);

  edit_feature_act = new QAction(tr("&Edit feature"));
  delete_feature_act = new QAction(tr("&Delete feature"));
}

void MainWindow::CreateNewFeatureWindow() {
  new_feature = new NewFeatureWindow(this);
  new_feature->show();
}

void MainWindow::Complement() {
  /** Cannot use std::replace because four passes are required to create the 
   *complement string.
   */
  QString qcontents = sequence_textbox->toPlainText();
  std::string contents = qcontents.toStdString();
    for (auto& c : contents) {
      switch(c) {
        case('A') : c = 'T'; break;
        case('a') : c = 't'; break;             
        case('T') : c = 'A'; break;
        case('t') : c = 'a'; break;
        case('G') : c = 'C'; break;
        case('g') : c = 'c'; break;
        case('C') : c = 'G'; break;
        case('c') : c = 'g'; break;
        case('W') : c = 'W'; break;
        case('w') : c = 'w'; break;
        case('S') : c = 'S'; break;
        case('s') : c = 's'; break;
        case('M') : c = 'K'; break;
        case('m') : c = 'k'; break;
        case('K') : c = 'M'; break;
        case('k') : c = 'm'; break;
        case('R') : c = 'Y'; break;
        case('r') : c = 'y'; break;
        case('Y') : c = 'R'; break;
        case('y') : c = 'r'; break;
        case('B') : c = 'V'; break;
        case('b') : c = 'v'; break;
        case('D') : c = 'H'; break;
        case('d') : c = 'h'; break;
        case('H') : c = 'D'; break;
        case('h') : c = 'd'; break;
        case('V') : c = 'B'; break;
        case('v') : c = 'b'; break;
        case('N') : c = 'G'; break;
        case('n') : c = 'g'; break;
    }
  }
  QString new_content = QString::fromStdString(contents);
  sequence_textbox->setPlainText(new_content); 
}


void MainWindow::ReverseComplement() {
  //std::string reverse_complement{Complement(sequence_)};
  
  //std::reverse(reverse_complement.begin(), reverse_complement.end());
}


