#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QKeySequence>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QToolBar>
#include <QTimer>
#include <QListWidget>
#include <QGridLayout>
#include <QLabel>
#include <QDebug>

#include "main_window_view.h"
#include "sequence_view_model.h"
#include "translate_view_model.h"

#include "restriction_digest_view.h"

#include "oligo_analyser.h"
//////////////
//  PUBLIC  //
//////////////
MainWindowView::MainWindowView(QWidget* parent) : QMainWindow(parent) {
  setWindowTitle("Yet Another Plasmid Editor");
  //Create the UI element controllers
  CreateSequenceViewModel();
  CreateTranslateViewModel();
  //CreateNewFeatureViewModel(this);
  //Create actions
  //DO NOT REORDER -> Actions need to be created before menus
  //because menus require actions to exist.
  CreateActions();

  //Create menus
  CreateMenuBar();
  CreateToolBar();
  CreateStatusBar();
  connect(sequence_view_model_->GetView(),
        &SequenceView::NotifySelectionChanged,
        this,
        &MainWindowView::ProcessSelectionChanged);

 this->resize(500, 400);
}

///////////////
//  PRIVATE  //
///////////////
void MainWindowView::CreateMenuBar() {

 //File submenu
  file_menu_ = this->menuBar()->addMenu(tr("&File"));
  //file_menu_->addAction(new_file_act);
  file_menu_->addAction(open_file_act_);
  file_menu_->addAction(save_file_act_);
  file_menu_->addAction(print_act_);
  file_menu_->addAction(preferences_act_);
  file_menu_->addAction(tr("E&xit"),
                       this,
                       &MainWindowView::close,
                       QKeySequence(tr("Ctrl+X")));

  //Edit submenu
  //edit_menu_->addAction(undo_act);
  //edit_menu_->addAction(redo_act);
  //edit_menu_->addAction(copy_act);
  //edit_menu_->addAction(cut_act);
  //edit_menu_->addAction(paste_act);
  edit_menu_ = this->menuBar()->addMenu(tr("&Edit"));
  //edit_menu_->addAction(reverse_complement_act);
  
  //Tools submenu
  tools_menu_ = this->menuBar()->addMenu(tr("&Tools"));

  tools_menu_->addAction((tr("&Complement")),
                         sequence_view_model_,
                         &SequenceViewModel::CallComplement);
  tools_menu_->addAction((tr("&Reverse complement")),
                         sequence_view_model_,
                         &SequenceViewModel::CallReverseComplement);

  tools_menu_->addAction((tr("&Translate")),
                         translate_view_model_,
                         &TranslateViewModel::CallTranslate);

  tools_menu_->addAction((tr("Restriction &digest")),
                         this,
                         &MainWindowView::CreateRestrictionDigestView);

  tools_features_submenu_ = new QMenu(tr("&Features"));
  tools_menu_->addMenu(tools_features_submenu_);
  tools_features_submenu_->addAction("&New feature");
  tools_features_submenu_->addAction("&Edit feature");
  tools_features_submenu_->addAction("&Delete feature");
  //tools_menu_->addAction(tr("&Features");
  //tools_menu_->addAction();
  //tools_menu_->addAction();
  //tools_menu_->addAction();
  //tools_menu_->addAction();
  //tools_menu_->addAction();
  //tools_menu_->addAction();
  //tools_menu_->addAction();
  //tools_menu_->addAction();
  //tools_menu_->addAction();
  help_menu_ = this->menuBar()->addMenu(tr("&About"));
}

void MainWindowView::CreateToolBar() {
  toolbar_ = new QToolBar("Toolbar");
  this->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolbar_);
}

void MainWindowView::CreateStatusBar() {
  status_bar_ = new QStatusBar(this);
  this->setStatusBar(status_bar_);

  //QTimer* timer = new QTimer(this);
  //timer->callOnTimeout(status_bar_, this->UpdateStatusBar);
  //connect(timer, 
  //        &QTimer::timeout, 
  //        status_bar_, 
  //        &MainWindowView::UpdateStatusBar);
  //timer->start(10);
}

void MainWindowView::CreateActions() {
  //File menu actions
  new_file_act_ = new QAction(tr("&New file"));
  open_file_act_ = new QAction(tr("&Open file"));
  open_file_act_->setShortcut(QKeySequence::Open);

  save_file_act_ = new QAction(tr("&Save file"));
  save_file_act_->setShortcut(QKeySequence::Save);

  print_act_ = new QAction(tr("&Print"));
  print_act_->setShortcut(QKeySequence::Print);

  preferences_act_ = new  QAction(tr("P&references"));
}

void MainWindowView::CreateSequenceViewModel() {
  qDebug() << "Created SequenceViewModel";
  sequence_view_model_ = new SequenceViewModel(this);
  this->setCentralWidget(sequence_view_model_->GetView());
}

void MainWindowView::CreateTranslateViewModel() {
  qDebug() << "Created TranslateViewModel";
  translate_view_model_ = new TranslateViewModel(sequence_view_model_, this);
}

void MainWindowView::CreateRestrictionDigestView() {
  RestrictionDigestView* restriction_enzymes = new RestrictionDigestView(this);
}

void MainWindowView::ProcessSelectionChanged() {
  QString sequence = sequence_view_model_->GetSequence();
  double tm = OligoAnalyser::CalculateTm(sequence);
  status_bar_->showMessage(QString::number(tm));
};


