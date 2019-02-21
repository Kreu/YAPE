#include <QGridLayout>
#include <QPlainTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>

#include "translate_view.h"

//////////////
//  PUBLIC  //
//////////////
TranslateView::TranslateView(QWidget* parent) : QWidget(parent) {
  qDebug() << "In TranslateView constructor";

  setWindowTitle("Translation ");
  QGridLayout* layout_ = new QGridLayout();
  setLayout(layout_);

  display_translation_ = new QPlainTextEdit(this);
  display_translation_->setReadOnly(true);
  layout_->addWidget(display_translation_, 2, 0, 2, 4);

  translation_start_ = new QLabel("Start position", this);
  layout_->addWidget(translation_start_, 0, 0);
  translation_start_box_ = new QLineEdit(this);
  translation_start_box_->setMinimumWidth(50);
  translation_start_box_->setMaximumWidth(80);
  layout_->addWidget(translation_start_box_, 0, 1, Qt::AlignLeft);

  translation_end_ = new QLabel("End position", this);
  layout_->addWidget(translation_end_, 0, 2);
  translation_end_box_ = new QLineEdit(this);
  translation_end_box_->setMinimumWidth(120);
  translation_end_box_->setMaximumWidth(160);
  layout_->addWidget(translation_end_box_, 0, 3, Qt::AlignRight);

  length_ = new QLabel("Length", this);
  layout_->addWidget(length_, 1, 0);
  length_box_ = new QLineEdit(this);
  length_box_->setReadOnly(true); 
  length_box_->setMinimumWidth(50);
  length_box_->setMaximumWidth(80);
  layout_->addWidget(length_box_, 1, 1);
  
  mol_weight_ = new QLabel("Molecular weight", this);
  layout_->addWidget(mol_weight_, 1, 2);
  mol_weight_box_ = new QLineEdit(this);
  mol_weight_box_->setReadOnly(true);
  mol_weight_box_->setMinimumWidth(120);
  mol_weight_box_->setMaximumWidth(160);
  layout_->addWidget(mol_weight_box_, 1, 3);

  QFont sequence_font = display_translation_->font();
  sequence_font.setFamily("Courier");
  sequence_font.setPointSize(12);
  display_translation_->setFont(sequence_font);

  setWindowFlags(Qt::Window);
}

/////////////
//  SLOTS  //
/////////////
void TranslateView::ProcessTranslatedSequence(QString sequence) {
  qDebug() << "In TranslateView::ProcessTranslatedSequence()";
  if (display_translation_->toPlainText() != sequence) {
    qDebug() << "Updated sequence to:" << sequence;
    display_translation_->setPlainText(sequence);
    return;
  }
  return;
}

void TranslateView::ProcessMolecularWeight(double mw) {
  mol_weight_box_->setText(QString::number(mw, 'f'));
}

void TranslateView::ProcessLength(int sequence_length) {
  length_box_->setText(QString::number(sequence_length)); 
}


