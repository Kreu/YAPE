#ifndef SEQUENCE_TEXT_BOX_H
#define SEQUENCE_TEXT_BOX_H

#include <QTextEdit>
#include <QString>
#include <utility>

class QEvent;

class SequenceTextBox : public QTextEdit {
Q_OBJECT
public:
  SequenceTextBox(QWidget* parent = nullptr);
  bool virtual event(QEvent* event) override;
  //Signals
  
  
  //Slots
  void slotDoNothing();
  void Complement();
  void ReverseComplement();
private:
  //Variables
  bool is_text_selected;

  //Signals
  
  //Slots
  void UpdateSequence();
  void UpdateIsTextSelected(bool b);
  void UpdateText();
  
  //Member functions
  std::pair<int, int> GetSelectionLimits();
  QString GetSelection();
  void ComplementString(std::string& str);
  std::tuple<std::string, std::string, std::string> SpliceSelectedSequence();
  void SetIsTextSelected(bool b);


};

#endif
