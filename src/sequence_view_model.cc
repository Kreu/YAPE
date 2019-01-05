#include <QDebug>

#include "sequence_view_model.h"
#include "sequence_model.h"
#include "sequence_view.h"

SequenceViewModel::SequenceViewModel(QObject* parent, SequenceView* sequence_view, SequenceModel* sequence_model_) :
    QObject(parent), sequence_view_(sequence_view), sequence_model_(sequence_model_) {

    connect(sequence_view_,
            &SequenceView::ViewTextUpdated,
            this,
            &SequenceViewModel::ViewTextUpdated);

    //If text has been selected or de-selected, update the variable
    connect(sequence_view_,
            &SequenceView::copyAvailable,
            this,
            &SequenceViewModel::IsTextSelectedUpdated);

    connect(this,
            &SequenceViewModel::CursorPositionChanged,
            sequence_view_,
            &SequenceView::UpdateCursorPosition);
}

QWidget* SequenceViewModel::GetView() {
  return sequence_view_;
}

void SequenceViewModel::CallComplement() {
  std::string current_sequence = GetCurrentViewText();
  if (is_text_selected) {
    QTextCursor cursor = sequence_view_->textCursor();
    auto start_pos = cursor.selectionStart();
    auto end_pos = cursor.selectionEnd();

    qDebug() << "Sequence start pos: " << start_pos << "End pos" << end_pos;
    std::string complement_sequence = current_sequence.substr(start_pos, end_pos-start_pos);
    qDebug() << "Called Complement() on" << QString::fromStdString(complement_sequence);
    Complement(complement_sequence);
    current_sequence.replace(start_pos, end_pos-start_pos, complement_sequence);

    //After updating  
    sequence_model_->sequence = current_sequence;
    UpdateViewText(sequence_model_->sequence);
    emit CursorPositionChanged(end_pos);
    return;
  }
  else if (!is_text_selected) {
    Complement(current_sequence);
    sequence_model_->sequence = current_sequence;
    UpdateViewText(sequence_model_->sequence);
    return;
  }
}

void SequenceViewModel::UpdateViewText(const std::string& str) {
  sequence_view_->setText(QString::fromStdString(str));
  return;
}

void SequenceViewModel::ViewTextUpdated(QString str) {
  std::string str_to_write = str.toStdString();
  //qDebug() << "Setting SequenceModel::sequence to" << str;
  sequence_model_->sequence = str.toStdString();
}
void SequenceViewModel::Complement(std::string& str) {
  for (auto& c : str) {
    switch(c) {
      case('A') : c = 'T'; break;
      case('a') : c = 't'; break;             
      case('T') : c = 'A'; break;
      case('t') : c = 'a'; break;
      case('G') : c = 'C'; break;
      case('g') : c = 'c'; break;
      case('C') : c = 'G'; break;
      case('c') : c = 'g'; break;
      case('W') : c = 'W'; break;
      case('w') : c = 'w'; break;
      case('S') : c = 'S'; break;
      case('s') : c = 's'; break;
      case('M') : c = 'K'; break;
      case('m') : c = 'k'; break;
      case('K') : c = 'M'; break;
      case('k') : c = 'm'; break;
      case('R') : c = 'Y'; break;
      case('r') : c = 'y'; break;
      case('Y') : c = 'R'; break;
      case('y') : c = 'r'; break;
      case('B') : c = 'V'; break;
      case('b') : c = 'v'; break;
      case('D') : c = 'H'; break;
      case('d') : c = 'h'; break;
      case('H') : c = 'D'; break;
      case('h') : c = 'd'; break;
      case('V') : c = 'B'; break;
      case('v') : c = 'b'; break;
      case('N') : c = 'G'; break;
      case('n') : c = 'g'; break;
    }
  }
}

void SequenceViewModel::IsTextSelectedUpdated(bool b) {
  is_text_selected = b;
  qDebug() << "Updated is_text_selected to" << is_text_selected;
}

std::string SequenceViewModel::GetCurrentViewText() {
  return (sequence_view_->toPlainText()).toStdString();
}


