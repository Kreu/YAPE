#include <tuple>
#include <QObject>
#include <QString>
#include <QDebug>
#include "sequence_model.h"

//////////////
//  PUBLIC  //
//////////////
SequenceModel::SequenceModel(QObject* parent) : QObject(parent) {}

QString SequenceModel::GetSequence() {
  return sequence_;
}

/////////////
//  SLOTS  //
/////////////
void SequenceModel::ProcessSequenceChanged(QString sequence) {
  //If the data is new, process it.
  if(sequence != sequence_) {
    qDebug() << "Updated SequenceModel";
    qDebug() << "New sequence:" << sequence;
    sequence_ = sequence;
    emit NotifySequenceChanged(sequence_);
    return;
  }
  return;
}
