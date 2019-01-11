#ifndef SEQUENCE_VIEW_H
#define SEQUENCE_VIEW_H

#include <QPlainTextEdit>

class QString;

class SequenceView : public QPlainTextEdit {
Q_OBJECT
public:
  SequenceView(QWidget* parent = nullptr);
signals:
  //Notifies that the user has changed the sequence in the SequenceView widget
  void NotifySequenceChanged(QString sequence);
  //Notifies that the user has clicked somewhere in the SequenceView widget
  void NotifyCursorPositionChanged(int current_position);
  //Notifies that the user has selected a different text. It is only emitted
  //when there is actually something selected, i.e. deselecting a text does
  //not emit this signal.
  void NotifySelectionChanged(int start_pos, int end_pos);
public slots:
  //Sets the current QPlainTextEdit text to sequence
  void ProcessSequenceChanged(QString sequence);
  //Sets the cursor position to the new position
  void ProcessCursorPositionChanged(int position);
  //Captures textChanged() signal from QPlainTextEdit and re-emits NotifySelectionChanged(int, int);
  void ProcessSelectionChanged();
private:
  //Filters key presses from the keyboard
  virtual void keyPressEvent(QKeyEvent* event) override;
  //Filters text copied from an outside source into the SequenceView widget
  QString filterClipboardInput();
};

#endif
