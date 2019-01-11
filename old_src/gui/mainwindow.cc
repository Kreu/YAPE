#include <iostream>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QToolBar>
#include <QTextEdit>
#include <QSizePolicy>
#include <QString>
#include <QKeySequence>
#include <QGuiApplication>
#include <QClipboard>
#include <QTimer>
#include <QCursor>
#include <QObject>
#include "mainwindow.h"
#include "sequence_textbox.h"
#include "newfeature_window.h"
#include "sequence_view.h"
#include "sequence_view_model.h"


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
 
  setWindowTitle("Yet Another Plasmid Editor");
  setBaseSize(800, 550);
  CreateSequenceBox();
  //Create actions
  //DO NOT REORDER -> Actions need to be created before menus
  //because menus require actions to exist.
  CreateActions();

  //Create menus
  CreateMenuBar();
  CreateToolBar();
  CreateStatusBar();

  //Create central textbox
}

void MainWindow::CreateSequenceBox() {
  //sequence_textbox = new SequenceTextBox(this);
  //this->setCentralWidget(sequence_textbox);
  sequence_view = new SequenceView(this);
  sequence_viewmodel = new SequenceViewModel(sequence_view);
  this->setCentralWidget(sequence_view);
}

void MainWindow::CreateMenuBar() {

  //File submenu
  file_menu = this->menuBar()->addMenu(tr("&File"));
  //file_menu->addAction(new_file_act);
  file_menu->addAction(open_file_act);
  file_menu->addAction(save_file_act);
  file_menu->addAction(print_act);
  file_menu->addAction(preferences_act);
  file_menu->addAction(quit_app_act);
  
  //Edit submenu
  //edit_menu->addAction(undo_act);
  //edit_menu->addAction(redo_act);
  //edit_menu->addAction(copy_act);
  //edit_menu->addAction(cut_act);
  //edit_menu->addAction(paste_act);
  edit_menu = this->menuBar()->addMenu(tr("&Edit"));
  edit_menu->addAction(complement_act);
  //edit_menu->addAction(reverse_complement_act);
  
  //Tools submenu
  tools_menu = this->menuBar()->addMenu(tr("&Selection"));
  tools_menu->addAction(tr("&Reverse Complement"));
  tools_menu->addAction(tr("Complement"));
  tools_menu->addAction(tr("&Translate"));
  tools_features_submenu = new QMenu(tr("&Features"));
  tools_menu->addMenu(tools_features_submenu);
  tools_features_submenu->addAction("&New feature");
  tools_features_submenu->addAction("&Edit feature");
  tools_features_submenu->addAction("&Delete feature");
  //tools_menu->addAction(tr("&Features");
  //tools_menu->addAction();
  //tools_menu->addAction();
  //tools_menu->addAction();
  //tools_menu->addAction();
  //tools_menu->addAction();
  //tools_menu->addAction();
  //tools_menu->addAction();
  //tools_menu->addAction();
  //tools_menu->addAction();
      
      
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

  QTimer* timer = new QTimer(this);
  //timer->callOnTimeout(status_bar, this->UpdateStatusBar);
  //connect(timer, 
  //        &QTimer::timeout, 
  //        status_bar, 
  //        &MainWindow::UpdateStatusBar);
  timer->start(10);
}

void MainWindow::slotDoAll() {
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
          sequence_viewmodel,
          &SequenceViewModel::CallComplement);

  //reverse_complement_act= new QAction(tr("&Reverse complement"));
  //connect(reverse_complement_act,
  //       &QAction::triggered,
  //        sequence_textbox,
  //        &SequenceTextBox::ReverseComplement);
  
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


