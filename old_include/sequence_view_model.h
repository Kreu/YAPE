#ifndef SEQUENCE_VIEW_MODEL_H
#define SEQUENCE_VIEW_MODEL_H

#include <QObject>
#include <string>
#include <tuple>

#include "sequence_model.h"
#include "sequence_view.h"

class SequenceViewModel;
class QWidget;
typedef void (SequenceViewModel::*Function)(std::string&);

class SequenceViewModel : public QObject {
Q_OBJECT
public:
  SequenceViewModel(QObject* parent = nullptr, SequenceView* sequence_view = new SequenceView(), SequenceModel* sequence_model_ = new SequenceModel());

  QWidget* GetView();
signals:
  void CursorPositionChanged(int position);

  //TODO
  //void PartialCodonSelected();
public slots:
  void CallComplement();
  void CallReverseComplement();
  void CallTranslate();

  void IsTextSelectedUpdated(bool b);
  void ViewTextUpdated(QString str);

private:
  //Variables
  SequenceView* sequence_view_;
  SequenceModel* sequence_model_;
  bool is_text_selected = false;
  //Methods
  void Complement(std::string& str);
  void ReverseComplement(std::string& str);
  void Translate(std::string& str);

  void ProcessViewSelection(Function processing_function);
  std::tuple<std::string, int, int> GetCurrentViewSelection();  
  void UpdateViewText(const std::string& str);
  std::string GetCurrentViewText();
  double CalculateMw(std::string& protein);

};

#endif
