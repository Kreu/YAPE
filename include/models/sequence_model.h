#ifndef SEQUENCE_MODEL_H
#define SEQUENCE_MODEL_H

#include <QObject>
#include <vector>
#include <QString>
#include <tuple>

class SequenceModel : public QObject {
Q_OBJECT
public:
  SequenceModel(QObject* parent = nullptr);
  QString GetSequence();
signals:
  void NotifySequenceChanged(QString sequence);
public slots:
  void ProcessSequenceChanged(QString sequence);
private:
  QString sequence_;
};

#endif
