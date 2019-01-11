#include <QPlainTextEdit>
#include <QString>
#include <QDebug>
#include <QClipboard>
#include <QGuiApplication>

#include "sequence_view.h"

//////////////
//  PUBLIC  //
//////////////
SequenceView::SequenceView(QWidget* parent) : QPlainTextEdit(parent) {
  //Self-connections
  
  //Overrides the QPlainTextEdit::selectionChanged() signal to provide more
  //information to any listeners
  connect(this,
          &SequenceView::selectionChanged,
          this,
          &SequenceView::ProcessSelectionChanged);

  QFont sequence_font = font();
  sequence_font.setFamily("Courier");
  sequence_font.setPointSize(12);
  setFont(sequence_font);

  setLineWrapMode(QPlainTextEdit::LineWrapMode::WidgetWidth);
}

/////////////
//  SLOTS  //
/////////////
void SequenceView::ProcessSequenceChanged(QString sequence) {
  if (this->toPlainText() != sequence) {
    this->setPlainText(sequence);
    emit NotifySequenceChanged(sequence);
    return;
  }
  return;
}

void SequenceView::ProcessCursorPositionChanged(int position) {
  //No need to check whether the previous position was the same because the
  //heavy lifting is done in constructing the QTextCursor anyway.
  QTextCursor cursor = textCursor();
  cursor.setPosition(position);
  qDebug() << "Setting cursor to" << position;
  this->setTextCursor(cursor);
  return;
}

void SequenceView::ProcessSelectionChanged() {
  QTextCursor cursor = this->textCursor();
  qDebug() << cursor.selectionStart() << cursor.selectionEnd();
  emit NotifySelectionChanged(cursor.selectionStart(), cursor.selectionEnd());
  return;
}

///////////////
//  PRIVATE  //
///////////////
void SequenceView::keyPressEvent(QKeyEvent* event) {
  //Detects ALL the keyPressEvents that are allowed. Anything that is not
  //explicitly allowed is disallowed.
  
  //Allow pasting
  if ((event->modifiers() & (Qt::CTRL)) &&
       (event->key() == Qt::Key_V)) {
    QPlainTextEdit::insertPlainText(filterClipboardInput());
    emit NotifySequenceChanged(this->toPlainText());
    return;
  }
 
  //Allow copying
  if ((event->modifiers() & Qt::CTRL) &&
        event->key() == Qt::Key_C) { 
    QPlainTextEdit::keyPressEvent(event);
    return;
  }

  //Allow sequence input and navigating
  if (event->key() == Qt::Key_A || 
      event->key() == Qt::Key_T || 
      event->key() == Qt::Key_C ||
      event->key() == Qt::Key_G ||
      event->key() == Qt::Key_Backspace ||
      event->key() == Qt::Key_Delete ||
      event->key() == Qt::Key_Insert ||
      event->key() == Qt::Key_Left ||
      event->key() == Qt::Key_Right ||
      event->key() == Qt::Key_Up ||
      event->key() == Qt::Key_Down) { 
    QPlainTextEdit::keyPressEvent(event);
    emit NotifySequenceChanged(this->toPlainText());
    return;
  }
  return;
}

QString SequenceView::filterClipboardInput() {
  QClipboard* clipboard = QGuiApplication::clipboard();
  QString clipboard_contents = clipboard->text();
  QString filtered_contents;
  for (QChar& c : clipboard_contents) {
    //Check explicitly whether the character is upper- or lowercase because we
    //want to preserve the formatting
    if (c == 'A' || c == 'a' || c == 'T' || c == 't' || 
        c == 'C' || c == 'c' || c == 'G' || c == 'g') {
      filtered_contents += c; 
    }
  }
  return filtered_contents;
}


