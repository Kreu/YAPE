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

#include "main_window_view.h"
#include "sequence_view_model.h"

MainWindowView::MainWindowView(QWidget* parent) : QMainWindow(parent) {
  setWindowTitle("Yet Another Plasmid Editor");
  //Create the UI element controllers
  CreateSequenceViewModel();
  //CreateNewFeatureViewModel(this);
  
  //Create actions
  //DO NOT REORDER -> Actions need to be created before menus
  //because menus require actions to exist.
  CreateActions();

  //Create menus
  CreateMenuBar();
  CreateToolBar();
  CreateStatusBar();
  this->resize(500, 400);
}

void MainWindowView::CreateSequenceViewModel() {
  sequence_view_model_ = new SequenceViewModel(this);
  this->setCentralWidget(sequence_view_model_->GetView());
}

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
                         sequence_view_model_,
                         &SequenceViewModel::CallTranslate);

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

void MainWindowView::CreateRestrictionDigestView() {
  QWidget* restriction_digest_view = new QWidget(this);
  restriction_digest_view->setWindowFlags(Qt::Window);
  restriction_digest_view->setWindowTitle("Restriction digest");


  QListWidget* all_enymes_view = new QListWidget(restriction_digest_view);
  QListWidget* selected_enzymes_view = new QListWidget(restriction_digest_view);
  all_enymes_view->setFlow(QListWidget::TopToBottom);
  selected_enzymes_view->setFlow(QListWidget::TopToBottom);

  QGridLayout* layout = new QGridLayout();
  QLabel* all_enymes_label = new QLabel("All enzymes");
  QLabel* selected_enzymes_label = new QLabel("Selected enzymes");
  layout->addWidget(all_enymes_label, 0, 0);
  layout->addWidget(selected_enzymes_label, 0, 2);

  layout->addWidget(all_enymes_view, 1, 0);
  layout->addWidget(selected_enzymes_view, 1, 2);
  restriction_digest_view->setLayout(layout);
  restriction_digest_view->show();
 
  //Placeholder data
  QListWidgetItem* ecori = new QListWidgetItem(tr("EcoRI"));
  all_enymes_view->insertItem(0, ecori);
  QListWidgetItem* ecorv = new QListWidgetItem(tr("EcoRV"));
  all_enymes_view->insertItem(0, ecorv);
  QListWidgetItem* bamhi= new QListWidgetItem(tr("BamHI"));
  all_enymes_view->insertItem(0, bamhi);
  QListWidgetItem* xbai = new QListWidgetItem(tr("XbaI"));
  all_enymes_view->insertItem(0, xbai);
}
