#include <QObject>
#include <QString>
#include <QDebug>
#include <QChar>
#include <QTextCursor>
#include <QWidget>
#include <QMap>
#include <QChar>
#include "sequence_view_model.h"
#include "sequence_view.h"
#include "sequence_model.h"

//////////////
//  PUBLIC  //
//////////////
SequenceViewModel::SequenceViewModel(QObject* parent, SequenceView* sequence_view, SequenceModel* sequence_model) 
  : QObject(parent), sequence_view_(sequence_view), sequence_model_(sequence_model), start_pos_{0}, end_pos_{0} {

  //Load the sequence from the model
  sequence_ = sequence_model_->GetSequence();
  //Update the SequenceView text
  emit NotifySequenceChanged(sequence_);

  //This needs to be set to false to make sure that when the user first opens
  //the app and uses an action, it knows that no text has been selected yet
  text_selected_ = false;  

  //Self-signals
  //Detect whether we have changed the sequence within this ViewModel
  connect(this,
          &SequenceViewModel::NotifySequenceChanged,
          this,
          &SequenceViewModel::ProcessSequenceChanged);

  //Signals FROM here (SequenceViewModel)
  connect(this,
          &SequenceViewModel::NotifySequenceChanged,
          sequence_view_,
          &SequenceView::ProcessSequenceChanged);

  connect(this,
          &SequenceViewModel::NotifyCursorPositionChanged,
          sequence_view_,
          &SequenceView::ProcessCursorPositionChanged);

  connect(this,
          &SequenceViewModel::NotifySequenceChanged,
          sequence_model_,
          &SequenceModel::ProcessSequenceChanged);

  //Signals TO here (SequenceViewModel)
  connect(sequence_view_,
          &SequenceView::NotifySelectionChanged,
          this,
          &SequenceViewModel::ProcessSelectionChanged);

  connect(sequence_view_,
          &SequenceView::copyAvailable, //Emitted if text is (de)selected
          this,
          &SequenceViewModel::ProcessIsTextSelected);

  connect(sequence_view_,
          &SequenceView::NotifySequenceChanged,
          this,
          &SequenceViewModel::ProcessSequenceChanged);

  connect(sequence_model_,
          &SequenceModel::NotifySequenceChanged,
          this,
          &SequenceViewModel::ProcessSequenceChanged);
  
  //FeatureModel signals
  //connect(feature_model_,
  //        FeatureModel::NotifyFeatureChanged,
  //        this,
  //        SequenceViewModel::ProcessFeatureChanged);
}

SequenceView* SequenceViewModel::GetView() {
  return sequence_view_;
}

SequenceModel* SequenceViewModel::GetModel() {
  return sequence_model_;
}

QString SequenceViewModel::GetSequence() {
  if (text_selected_) {
    return sequence_.mid(start_pos_, end_pos_-start_pos_);
  }
  
  if (!text_selected_) {
    return sequence_;
  }
}

/////////////
//  SLOTS  //
/////////////
void SequenceViewModel::ProcessSequenceChanged(QString sequence) {
  if (sequence_ != sequence) {
    qDebug() << "Updated SequenceViewModel";
    qDebug() << "New sequence:" << sequence;
    sequence_ = sequence;
    emit NotifySequenceChanged(sequence_);
    return;
  }
  return;
}

void SequenceViewModel::ProcessSelectionChanged(int start_pos, int end_pos) {
  if(start_pos_ != start_pos || end_pos_ != end_pos) {
    qDebug() << "Updated SequenceViewModel";
    qDebug() << "New start position:" << start_pos << "New end position:" << end_pos;
    start_pos_ = start_pos;
    end_pos_ = end_pos;
    return;
  }
  return;
}

void SequenceViewModel::ProcessIsTextSelected(bool b) {
  text_selected_ = b;
  qDebug() << "Updated SequenceViewModel";
  qDebug() << "Text selected:" << text_selected_;
  return;
}

//void SequenceViewModel::ProcessFeatureAdded(FeatureModel feature) {
//
//}
//
//void SequenceViewModel::ProcessFeatureEdited(FeatureModel feature) {
//
//}
//
//void SequenceViewModel::ProcessFeatureChanged(FeatureModel feature) {
//
//}

///////////////
//  PRIVATE  //
///////////////

//This function takes a pointer to a function and calls it on the current
//SequenceView selection. 

void SequenceViewModel::CallComplement() {
  ProcessSelection(&SequenceViewModel::Complement);
  return;
}

void SequenceViewModel::CallReverseComplement() {
  ProcessSelection(&SequenceViewModel::ReverseComplement);
  return;
}
void SequenceViewModel::CallTranslate() {

}

void SequenceViewModel::ProcessSelection(Function processing_function) {
  //We need a local copy here because setting the text de-selects it, which 
  //in turn emits a NotifyCursorPositionChanged signal to SequenceViewModel that
 //sets the end position to -1
  auto save_end_pos = end_pos_;

  if (text_selected_) {
    QString current_selection = sequence_.mid(start_pos_, end_pos_ - start_pos_);
    QString processed_sequence = (this->*processing_function)(current_selection);    
   
    //Don't update the sequence_ directly
    QString new_sequence = sequence_; 
    new_sequence.replace(start_pos_, processed_sequence.length(), processed_sequence);
    
    emit NotifySequenceChanged(new_sequence);
    emit NotifyCursorPositionChanged(save_end_pos);
    return;
  }
  else if (!text_selected_) {
    QString processed_sequence = (this->*processing_function)(sequence_);    
    emit NotifySequenceChanged(processed_sequence); 
    emit NotifyCursorPositionChanged(save_end_pos);
    return;
  }
}

QString SequenceViewModel::Complement(QString sequence) {
  for (QChar& c : sequence) {
    switch(c.unicode()) {
      case('A') : c = 'T'; break;
      case('a') : c = 't'; break;             
      case('T') : c = 'A'; break;
      case('t') : c = 'a'; break;
      case('G') : c = 'C'; break;
      case('g') : c = 'c'; break;
      case('C') : c = 'G'; break;
      case('c') : c = 'g'; break;

      /* Maybe one day the support for degenerate codons will be added...
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
      */
    }
  }
  return sequence;
}

QString SequenceViewModel::ReverseComplement(QString sequence) {
  QString reverse_complement = Complement(sequence);
  //No STL-type reverse function in QT
  std::string temp = reverse_complement.toStdString();
  std::reverse(temp.begin(), temp.end());
  reverse_complement = QString::fromStdString(temp);
  return reverse_complement;
}
