#ifndef SEQUENCE_VIEW_MODEL_H
#define SEQUENCE_VIEW_MODEL_H

#include <QObject>
#include <string>

#include "sequence_model.h"
#include "sequence_view.h"

class QWidget;

class SequenceViewModel : public QObject {
Q_OBJECT
public:
  SequenceViewModel(QObject* parent = nullptr, SequenceView* sequence_view = new SequenceView(), SequenceModel* sequence_model_ = new SequenceModel());

  QWidget* GetView();
signals:
  void CursorPositionChanged(int position);

public slots:
  void CallComplement();
  void IsTextSelectedUpdated(bool b);
  void ViewTextUpdated(QString str);

private:
  //Variables
  SequenceView* sequence_view_;
  SequenceModel* sequence_model_;
  bool is_text_selected;

  //Methods
  void Complement(std::string& str);
  
  void UpdateViewText(const std::string& str);
  std::string GetCurrentViewText();
};

#endif