#include <QKeyEvent>
#include <QDebug>

#include "sequence_view.h"

SequenceView::SequenceView(QWidget* parent) : QTextEdit(parent) {
  setLineWrapMode(QTextEdit::LineWrapMode::WidgetWidth);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QFont sequence_font = font();
  sequence_font.setFamily("Courier");
  sequence_font.setPointSize(12);
  setFont(sequence_font);
}

bool SequenceView::event(QEvent* event) {
  //Only allow actual nucleic acid base characters, and control characters
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent* key = static_cast<QKeyEvent*>(event);
    
    //Detect whether the input is modified with control or shift
    if ((key->modifiers() & (Qt::CTRL | Qt::ALT | Qt::SHIFT)) &&
         (key->key() == Qt::Key_C ||
         key->key() == Qt::Key_V)) {
      QTextEdit::event(event);
      emit ViewTextUpdated(this->toPlainText());
      return true;
    }

    if (key->key() == Qt::Key_A || 
        key->key() == Qt::Key_T || 
        key->key() == Qt::Key_C ||
        key->key() == Qt::Key_G ||
        key->key() == Qt::Key_Backspace ||
        key->key() == Qt::Key_Delete ||
        key->key() == Qt::Key_Insert ||
        key->key() == Qt::Key_Left ||
        key->key() == Qt::Key_Right ||
        key->key() == Qt::Key_Up ||
        key->key() == Qt::Key_Down) { 
      QTextEdit::event(event);
      emit ViewTextUpdated(this->toPlainText());
      return true;
    }
    else {
      //Have to return true to make sure only the aforementioned KeyPress events
      //are processed
      return true;
    }
  }
  //If it wasn't a keypress, we still need to process it
  else {
    QTextEdit::event(event);
    emit ViewTextUpdated(this->toPlainText());
    return true;
  }
}

void SequenceView::UpdateCursorPosition(int position) {
  qDebug() << "Setting cursor to position" << position;
  QTextCursor cursor = textCursor();
  cursor.setPosition(position);
  setTextCursor(cursor);
}

