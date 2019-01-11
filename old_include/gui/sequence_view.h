#ifndef SEQUENCE_VIEW_H
#define SEQUENCE_VIEW_H

#include <QTextEdit>
#include <QString>
#include <QPlainTextEdit> 

class QWidget;
class QEvent;
class QKeyEvent;

class SequenceView : public QPlainTextEdit {
Q_OBJECT
public:
  SequenceView(QWidget* parent = nullptr);
  //bool virtual event(QEvent* event) override; //every time a key is inserted, ViewTextUpdated() is emitted
  //void insertFromMimeData(const QMimeData* source) override;
  void virtual keyPressEvent(QKeyEvent* event) override;
signals:
  void NotifyTextUpdated(QString str);
  //void NotifyCursorPositionUpdated();
  //void NotifySelectionChanged();
  //void NotifyTextSelected();
public slots:
  void UpdateCursorPosition(int position);
private:
  QString filterClipboardInput();
};

#endif
