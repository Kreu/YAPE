#include <iostream>
#include <QEvent>
#include <QKeyEvent>
#include <QString>
#include <QObject>
#include <QClipboard>
#include <QGuiApplication>
#include <QTextCursor>
#include <QDebug>

#include "sequence_textbox.h"

SequenceTextBox::SequenceTextBox(QWidget* parent) : QTextEdit(parent) {
  
  setLineWrapMode(QTextEdit::LineWrapMode::WidgetWidth);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QFont sequence_font = font();
  sequence_font.setFamily("Courier");
  sequence_font.setPointSize(12);
  setFont(sequence_font);

  /////////////////////////////////
  //  CONNECTION IMPLEMENTATION  //
  /////////////////////////////////

  connect(this,
          &SequenceTextBox::textChanged,
          this,
          &SequenceTextBox::UpdateSequence);

  connect(this,
          &SequenceTextBox::copyAvailable,
          this,
          &SequenceTextBox::UpdateIsTextSelected);
}

//////////////////////////////
//  SIGNAL IMPLEMENTATIONS  //
//////////////////////////////

////////////////////////////
//  SLOT IMPLEMENTATIONS  //
////////////////////////////

/* UpdateIsCopyable() responds to QTextEdit::copyAvailable(bool) signal. This is 
 * called only when an initial selection is made, or when selection is 
 * abandoned, so it is necessary to keep track of whether any text is currently
 * selected.
 */
void SequenceTextBox::UpdateIsTextSelected(bool b) {
  is_text_selected = b;
  qDebug() << "Updated is_text_selected to" << is_text_selected;
} 

/* GetSelectedSequence() returns the user-selected sequence from SequenceTextBox.
 * If no sequence is selected, returns an empty string.
 */
//TODO: Don't check for is_text selected? Just return the clipboard, it will be
//empty if nothing is selected? Double check it.
QString SequenceTextBox::GetSelection() {
  if (is_text_selected) {
    QClipboard* clipboard = QGuiApplication::clipboard(); 
    QString selected_content = clipboard->text(QClipboard::Selection);
    return selected_content;
  }
  else {
    return "";
  }
}

std::pair<int, int> SequenceTextBox::GetSelectionLimits() {
  QTextCursor cursor = this->textCursor();
  auto start_pos = cursor.selectionStart();
  auto end_pos = cursor.selectionEnd();
  return std::make_pair(start_pos, end_pos);
}

void SequenceTextBox::UpdateText() {
  //this->setPlainText(this->current_content);
}


void SequenceTextBox::UpdateSequence() {}



bool SequenceTextBox::event(QEvent* event) {
  //Only allow actual nucleic acid base characters, and control characters
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent* key = static_cast<QKeyEvent*>(event);
    
    //Detect whether the input is modified with control or shift
    if ((key->modifiers() & (Qt::CTRL | Qt::ALT | Qt::SHIFT)) &&
         (key->key() == Qt::Key_C ||
         key->key() == Qt::Key_V)) {
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

void SequenceTextBox::Complement() {
  std::string textbox_contents = toPlainText().toStdString();
  
  //If text is selected, slice out the selected area and modify it, and slice 
  //it back in after.
  if (is_text_selected) {
    auto [begin, modify, end] = SpliceSelectedSequence();
    ComplementString(modify);
    std::string composite = begin + modify + end;
    
    //Make sure to move the cursor back to the beggining of the selection after
    //the sequence is modified.
    QTextCursor cursor = textCursor();
    auto anchor = cursor.selectionStart();
    //std::cout << cursor.selectionStart() << " : " << anchor << "\n";
    setText(QString::fromStdString(composite));
    cursor.setPosition(anchor);
    setTextCursor(cursor);
    return;
  }
  
  if (!is_text_selected) {
    ComplementString(textbox_contents);
    setText(QString::fromStdString(textbox_contents));
    return;
  }
}

void SequenceTextBox::ComplementString(std::string& str) {
  for (auto& c : str) {
    switch(c) {
      case('A') : c = 'T'; break;
      case('a') : c = 't'; break;             
      case('T') : c = 'A'; break;
      case('t') : c = 'a'; break;
      case('G') : c = 'C'; break;
      case('g') : c = 'c'; break;
      case('C') : c = 'G'; break;
      case('c') : c = 'g'; break;
      case('W') : c = 'W'; break;
      case('w') : c = 'w'; break;
      case('S') : c = 'S'; break;
      case('s') : c = 's'; break;
      case('M') : c = 'K'; break;
      case('m') : c = 'k'; break;
      case('K') : c = 'M'; break;
      case('k') : c = 'm'; break;
      case('R') : c = 'Y'; break;
      case('r') : c = 'y'; break;
      case('Y') : c = 'R'; break;
      case('y') : c = 'r'; break;
      case('B') : c = 'V'; break;
      case('b') : c = 'v'; break;
      case('D') : c = 'H'; break;
      case('d') : c = 'h'; break;
      case('H') : c = 'D'; break;
      case('h') : c = 'd'; break;
      case('V') : c = 'B'; break;
      case('v') : c = 'b'; break;
      case('N') : c = 'G'; break;
      case('n') : c = 'g'; break;
    }
  }
}

void SequenceTextBox::ReverseComplement() {
  //std::string reverse_complement{Complement(sequence_)};
  
  //std::reverse(reverse_complement.begin(), reverse_complement.end());
}

std::tuple<std::string, std::string, std::string> SequenceTextBox::SpliceSelectedSequence() {
  std::string textbox_contents = toPlainText().toStdString();
  
  QTextCursor cursor = textCursor();
  auto start_pos = cursor.selectionStart();
  auto end_pos = cursor.selectionEnd();

  //std::cout << "Start: " << start_pos << " End: " << end_pos << "\n";
  std::string unmodified_begin = textbox_contents.substr(0, start_pos);
  std::string unmodified_end = textbox_contents.substr(end_pos);
  std::string substring_to_process = textbox_contents.substr(start_pos, end_pos-start_pos);
  //std::cout << "Full: " << textbox_contents << "\nBegin: " << unmodified_begin << "\nSpliced: " << substring_to_process << "\nEnd: " << unmodified_end<< "\n";
  std::tuple contents = std::make_tuple(unmodified_begin, substring_to_process, unmodified_end);
  return contents;
}


