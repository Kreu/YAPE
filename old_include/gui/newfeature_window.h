#ifndef NEW_FEATURE_WINDOW_H
#define NEW_FEATURE_WINDOW_H

#include <QWidget>
#include <QGridLayout>

class QLabel;
class QGridLayout;
class QPushButton;
class QColorDialog;
class QPalette;
class QColor;
class QLineEdit;

class NewFeatureWindow : public QWidget {
Q_OBJECT
public:
  NewFeatureWindow(QWidget* parent);
private:
  QLabel* start_pos_label;
  QLabel* end_pos_label;
  QLabel* colour_label;
  QLabel* name_label;

  QLineEdit* start_pos_box;
  QLineEdit* end_pos_box;
  QLineEdit* name_box;

  QPalette colour_label_palette;

  QColor current_colour;

  QGridLayout* layout;

  QPushButton* display_picked_color;
  QPushButton* confirm_button;
  QPushButton* cancel_button;
 
  QColorDialog* colour_picker_dialog;
 
  void CreateUIElements();
  void CreateUILayout();
  void AddElementsToUI();

  void CreateFeature();
  void ShowNewColor(const QColor& color);
};

#endif
