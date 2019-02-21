#ifndef SEQUENCE_VIEW_MODEL_H
#define SEQUENCE_VIEW_MODEL_H

#include <QObject>
#include <QString>
#include <vector>
#include <QTextCursor>

#include "sequence_view.h"
#include "sequence_model.h"


class SequenceViewModel : public QObject {
Q_OBJECT
typedef QString (SequenceViewModel::*Function)(QString);
public:
  SequenceViewModel(QObject* parent = nullptr, 
                    SequenceView* sequence_view = new SequenceView(),
                    SequenceModel* sequence_model = new SequenceModel());
  SequenceView* GetView();
  SequenceModel* GetModel();
  //Returns the current user-selected sequence. If no sequence is selected, 
  //return the whole sequence.
  QString GetSequence();
signals:
  //This signal is emitted whenever the local sequence copy of SequenceViewModel
  //is updated.
  void NotifySequenceChanged(QString sequence);
  //This signal is emitted whenever the user changed the cursor position
  void NotifyCursorPositionChanged(int position);
public slots:
  //Sets the local sequence copy of SequnceViewModel to sequence. 
  void ProcessSequenceChanged(QString sequence);
  //Sets the start and end positions of the text the user has selected 
  //in SequenceView
  void ProcessSelectionChanged(int start_pos, int end_pos);
  //Sets whether text in SequenceView is selected (true) or not (false)
  void ProcessIsTextSelected(bool b);

//  void ProcessFeatureAdded(FeatureModel* feature);
//  void ProcessFeatureEdited(FeatureModel* feature);
//  void ProcessFeatureChanged(FeatureModel* feature);
  void CallComplement();
  void CallReverseComplement();
  void CallTranslate();

private:
//Q_DISABLE_COPY(SequenceViewModel)
  //Variables
  QString sequence_; //Local copy of the sequence string on the screen
  SequenceView* sequence_view_;
  SequenceModel* sequence_model_;
  int start_pos_;
  int end_pos_;
  bool text_selected_;
  //Methods
  void ProcessSelection(Function function);
  QString Complement(QString sequence);
  QString ReverseComplement(QString sequence);
};

#endif
