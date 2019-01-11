#include <QKeyEvent>
#include <QDebug>
#include <QSize>
#include <QMimeData>
#include <QChar>
#include <QClipboard>
#include <QGuiApplication>

#include "sequence_view.h"

SequenceView::SequenceView(QWidget* parent) : QPlainTextEdit(parent) {
  setLineWrapMode(QPlainTextEdit::LineWrapMode::WidgetWidth);

  QFont sequence_font = font();
  sequence_font.setFamily("Courier");
  sequence_font.setPointSize(12);
  setFont(sequence_font);

  QSize defaultSize = this->minimumSizeHint();
}

void SequenceView::keyPressEvent(QKeyEvent* event) {
  //Detects ALL the keyPressEvents that are allowed. Anything that is not
  //explicitly allowed is disallowed.
  
  //Allow pasting
  if ((event->modifiers() & (Qt::CTRL)) &&
       (event->key() == Qt::Key_V)) {
    QPlainTextEdit::insertPlainText(filterClipboardInput());
    emit NotifyTextUpdated(this->toPlainText());
    return;
  }
 
  //Allow copying 
  if ((event->modifiers() & (Qt::CTRL)) &&
        (event->key() == Qt::Key_C)) { 
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
    emit NotifyTextUpdated(this->toPlainText());
    return;
  }
  return;
}

//void SequenceView::insertFromMimeData(const QMimeData* source) {
//  if (source->hasText()) {
//    auto filtered_text = filterClipboardInput(QString("AGTA"));
//    this->insertPlainText(source->text());
//  }
//
//  else {
//    //QTextEdit::insertFromMimeData(source);
//  }
//}

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


void SequenceView::UpdateCursorPosition(int position) {
  qDebug() << "In SequenceView::UpdateCursorPosition, setting cursor to position" << position;
  QTextCursor cursor = textCursor();
  cursor.setPosition(position);
  setTextCursor(cursor);
}
