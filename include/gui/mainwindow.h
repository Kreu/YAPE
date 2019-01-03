#ifndef MAINWINDOW_H 
#define MAINWINDOW_H 

#include <QMainWindow>
#include "sequence_textbox.h"
#include <string>
#include <tuple>
//Forward declarations
class QStatusBar;
class QToolBar;
class QMenu;
class QTextEdit;
class QWidget;

class MainWindow : public QMainWindow {
Q_OBJECT
public:
  explicit MainWindow(QWidget* parent = 0);
private:
  //Variables
  QTextEdit* sequence_textbox; 
  QToolBar* toolbar;
  QStatusBar* status_bar;
  QWidget* new_feature;
  QString current_selection;
  QString original_content;
  bool text_selected;
  void IsTextSelected(bool b);

  //UI initialisers
  void CreateMenuBar();
  void CreateToolBar();
  void CreateStatusBar();
  void CreateActions();

  void CreateSequenceBox();
  void CreateNewFeatureWindow();

  //Menus
  QMenu* file_menu;
  QMenu* edit_menu;
  QMenu* features_menu;
  QMenu* tools_menu;
  QMenu* tools_features_submenu;

  //Actions
  //File menu actions
  QAction* open_file_act;
  QAction* save_file_act;
  QAction* print_act;
  QAction* preferences_act;
  QAction* quit_app_act;

  //Edit menu actions
  QAction* complement_act;
  QAction* reverse_complement_act;

  //Features menu actions
  QAction* create_feature_act;
  QAction* edit_feature_act;
  QAction* delete_feature_act;

  //Action functions
  //File menu functions
  //
  //Edit menu functions
  void Complement();
  void ComplementString(std::string& str);
  void ReverseComplement();
  std::tuple<std::string, std::string, std::string> SpliceSelectedSequence();
};

#endif
