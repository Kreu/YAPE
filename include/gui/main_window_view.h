#ifndef MAIN_WINDOW_VIEW_H 
#define MAIN_WINDOW_VIEW_H 

#include <QMainWindow>

class QToolBar;
class QStatusBar;
class QWidget;
class SequenceViewModel;
class TranslateViewModel;

class MainWindowView : public QMainWindow {
Q_OBJECT
public:
  explicit MainWindowView(QWidget* parent = 0);
private:
  //Variables
  SequenceViewModel* sequence_view_model_;
  TranslateViewModel* translate_view_model_;
  //ToolBarViewModel;
  //StatusBarViewModel;
  //NewFeatureViewModel;
  QToolBar* toolbar_;
  QStatusBar* status_bar_;
  QWidget* new_feature_view_;
  QWidget* restriction_digest_view_;

  //Menus
  QMenu* file_menu_;
  QMenu* edit_menu_;
  QMenu* tools_menu_;
  QMenu* tools_features_submenu_;
  QMenu* help_menu_;
  //Actions
  //File menu actions
  QAction* new_file_act_;
  QAction* open_file_act_;
  QAction* save_file_act_;
  QAction* print_act_;
  QAction* preferences_act_;

  //Methods
  //UI initialisers
  void CreateMenuBar();
  void CreateToolBar();
  void CreateStatusBar();
  void CreateActions();

  void CreateSequenceViewModel();
  //void CreateNewFeatureViewModel();
  void CreateTranslateViewModel();
  void CreateRestrictionDigestView();
};

#endif
