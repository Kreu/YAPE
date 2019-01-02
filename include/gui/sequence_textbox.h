#ifndef MAINTEXTBOX_H
#define MAINTEXTBOX_H

#include <QTextEdit>
#include <QString>

class QEvent;

class SequenceTextBox : public QTextEdit {
Q_OBJECT
public:
  SequenceTextBox(QWidget* parent);
  bool virtual event(QEvent* event) override;
private:
};

#endif
