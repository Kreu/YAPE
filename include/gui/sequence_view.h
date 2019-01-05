#ifndef SEQUENCE_VIEW_H
#define SEQUENCE_VIEW_H

#include <QTextEdit>
#include <QString>

class QWidget;
class QEvent;

class SequenceView : public QTextEdit {
Q_OBJECT
public:
  SequenceView(QWidget* parent = nullptr);
  bool virtual event(QEvent* event) override; //every time a key is inserted, ViewTextUpdated() is emitted

signals:
  void ViewTextUpdated(QString str);
public slots:
  void UpdateCursorPosition(int position);
private:
};

#endif
