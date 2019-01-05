#ifndef MAIN_WINDOW_VIEW_H 
#define MAIN_WINDOW_VIEW_H 

#include <QMainWindow>

class QToolBar;
class QStatusBar;
class QWidget;
class SequenceViewModel;

class MainWindowView: public QMainWindow {
Q_OBJECT
public:
  explicit MainWindowView(QWidget* parent = 0);
private:
  //Variables
  SequenceViewModel* sequence_view_model_;

  //ToolBarViewModel;
  //StatusBarViewModel;
  //NewFeatureViewModel;
  QToolBar* toolbar_;
  QStatusBar* status_bar_;
  QWidget* new_feature_view_;

  //UI initialisers
  void CreateMenuBar();
  void CreateToolBar();
  void CreateStatusBar();
  void CreateActions();

  void CreateSequenceViewModel();
  //void CreateNewFeatureViewModel();

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

  //Features menu actions
  QAction* create_feature_act;
  //QAction* edit_feature_act;
  //QAction* delete_feature_act;

  //Action functions
  //File menu functions
  //
  //Edit menu functions
};

#endif
