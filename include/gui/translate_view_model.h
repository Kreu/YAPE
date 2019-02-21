#ifndef TRANSLATE_VIEW_MODEL_H
#define TRANSLATE_VIEW_MODEL_H

#include <QObject>
#include <QWidget>
#include <QString>

#include "translate_view.h"
#include "sequence_view_model.h"

class TranslateViewModel : public QWidget {
Q_OBJECT
public:
  TranslateViewModel(SequenceViewModel* sequence_view_model, QWidget* parent = nullptr);
signals:
  void NotifyTranslatedSequence(QString str);
  void NotifyMolecularWeight(double mw);
  void NotifyLength(int sequence_length);
public slots:
  void CallTranslate();
private:
  //Variables
  SequenceViewModel* sequence_view_model_;
  TranslateView* translate_view_;
  //Methods
  void Translate(QString sequence);
  void CalculateMW(QString sequence);
};

#endif
