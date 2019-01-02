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
  QLineEdit* start_pos_box;

  QLabel* end_pos_label;
  QLineEdit* end_pos_box;

  QLabel* colour_label;
  QPushButton* display_picked_color;
  QPalette colour_label_palette;
  QColor current_colour;

  QGridLayout* layout;

  QPushButton* confirm_button;
  QPushButton* cancel_button;
 
  QColorDialog* colour_picker_dialog;
 
  void CreateUIElements();
  void CreateUILayout();
  void AddElementsToUI();

  void ShowNewColor(const QColor& color);
};
