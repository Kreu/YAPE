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

  connect(sequence_textbox,
          &QTextEdit::copyAvailable, 
          this,
          &MainWindow::IsTextSelected);
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
  edit_menu->addAction(reverse_complement_act);

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

std::tuple<std::string, std::string, std::string> MainWindow::SpliceSelectedSequence() {
  std::string textbox_contents = (sequence_textbox->toPlainText()).toStdString();
  
  QTextCursor cursor = sequence_textbox->textCursor();
  auto start_pos = cursor.selectionStart();
  auto end_pos = cursor.selectionEnd();

  //std::cout << "Start: " << start_pos << " End: " << end_pos << "\n";
  std::string unmodified_begin = textbox_contents.substr(0, start_pos);
  std::string unmodified_end = textbox_contents.substr(end_pos);
  std::string substring_to_process = textbox_contents.substr(start_pos, end_pos-start_pos);
  //std::cout << "Full: " << textbox_contents << "\nBegin: " << unmodified_begin << "\nSpliced: " << substring_to_process << "\nEnd: " << unmodified_end<< "\n";
  std::tuple contents = std::make_tuple(unmodified_begin, substring_to_process, unmodified_end);
  return contents;
}

void MainWindow::Complement() {
  std::string textbox_contents = (sequence_textbox->toPlainText()).toStdString();
  
  //If text is selected, slice out the selected area and modify it, and slice 
  //it back in after.
  if (text_selected) {
    auto [begin, modify, end] = SpliceSelectedSequence();
    ComplementString(modify);
    std::string composite = begin + modify + end;
    
    //Make sure to move the cursor back to the beggining of the selection after
    //the sequence is modified.
    QTextCursor cursor = sequence_textbox->textCursor();
    auto anchor = cursor.selectionStart();
    //std::cout << cursor.selectionStart() << " : " << anchor << "\n";
    sequence_textbox->setText(QString::fromStdString(composite));
    cursor.setPosition(anchor);
    sequence_textbox->setTextCursor(cursor);
    return;
  }
  
  if (!text_selected) {
    ComplementString(textbox_contents);
    sequence_textbox->setText(QString::fromStdString(textbox_contents));
    return;
  }
}

void MainWindow::ComplementString(std::string& str) {
  for (auto& c : str) {
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
}

void MainWindow::ReverseComplement() {
  //std::string reverse_complement{Complement(sequence_)};
  
  //std::reverse(reverse_complement.begin(), reverse_complement.end());
}

void MainWindow::IsTextSelected(bool b) {
  if (b) {
    text_selected = true;
  }
  else if (!b) {
    text_selected = false;
  }
}
