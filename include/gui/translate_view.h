#ifndef TRANSLATE_VIEW_H
#define TRANSLATE_VIEW_H

#include <QString>
#include <QPlainTextEdit>

class QWidget;
class QGridLayout;
class QLabel;
class QLineEdit;

class TranslateView : public QWidget {
Q_OBJECT
public:
  TranslateView(QWidget* parent = nullptr);
public slots:
  void ProcessTranslatedSequence(QString sequence);
  void ProcessMolecularWeight(double mw);
  void ProcessLength(int sequence_length);
signals:

private:
  //Variables
  QPlainTextEdit* display_translation_;
  QGridLayout* layout_;
  QLabel* length_;
  QLabel* mol_weight_;
  QLabel* translation_start_;
  QLabel* translation_end_;
  QLineEdit* length_box_;
  QLineEdit* mol_weight_box_;
  QLineEdit* translation_start_box_;
  QLineEdit* translation_end_box_;
};

#endif
