#include <QEvent>
#include <QKeyEvent>
#include <QString>
#include <QObject>

#include "sequence_textbox.h"

SequenceTextBox::SequenceTextBox(QWidget* parent) : QTextEdit(parent) {
  setLineWrapMode(QTextEdit::LineWrapMode::WidgetWidth);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  
  setStyleSheet("padding: 10px;");  

  QFont sequence_font = font();
  sequence_font.setFamily("Courier");
  sequence_font.setPointSize(12);
  setFont(sequence_font);
}

bool SequenceTextBox::event(QEvent* event) {
  //Only allow actual nucleic acid base characters, and control characters
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent* key = static_cast<QKeyEvent*>(event);
    
    //Detect whether the input is modified with control or shift
    if ((key->key() == Qt::Key_C ||
         key->key() == Qt::Key_V) && 
         (key->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier))) {
      return QTextEdit::event(event);
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
      return QTextEdit::event(event);
    }
    else {
      return true;
    }
  }
  else {
    return QTextEdit::event(event);
  }
}
