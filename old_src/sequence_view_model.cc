#include <QDebug>
#include <algorithm>
#include <QPlainTextEdit>
#include <QBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QFont>
#include <map>

//For Translate View
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

#include "sequence_view_model.h"
#include "sequence_model.h"
#include "sequence_view.h"

SequenceViewModel::SequenceViewModel(QObject* parent, SequenceView* sequence_view, SequenceModel* sequence_model_) :
    QObject(parent), sequence_view_(sequence_view), sequence_model_(sequence_model_) {

    connect(sequence_view_,
            &SequenceView::NotifyTextUpdated,
            this,
            &SequenceViewModel::ViewTextUpdated);

    //If text has been selected or de-selected, update the variable
    connect(sequence_view_,
            &SequenceView::copyAvailable,
            this,
            &SequenceViewModel::IsTextSelectedUpdated);

    connect(this,
            &SequenceViewModel::CursorPositionChanged,
            sequence_view_,
            &SequenceView::UpdateCursorPosition);
}

QWidget* SequenceViewModel::GetView() {
  return sequence_view_;
}

//Need to rewrite CallComplement and CallReverseComplement, they both should call a generic
//function that takes a function pointer and calls that function on the selection, then 
//updates the sequence and emits the right signals
void SequenceViewModel::CallComplement() {
  ProcessViewSelection(&SequenceViewModel::Complement);
}

void SequenceViewModel::CallReverseComplement() {
  ProcessViewSelection(&SequenceViewModel::ReverseComplement);
}

void SequenceViewModel::CallTranslate() {
  qDebug() << "In SequenceViewModel::CallTranslate()";
  if (is_text_selected) {
    auto [current_selection, start_pos, end_pos] = GetCurrentViewSelection();
    Translate(current_selection);
    return;
 }
 else if (!is_text_selected) {
    std::string current_sequence = GetCurrentViewText();
    Translate(current_sequence);
    return;
 } 
}

void SequenceViewModel::ProcessViewSelection(Function processing_function) {
  qDebug() << "In SequenceViewModel::ProcessViewSelection(Function)";
  if (is_text_selected) {
    auto [current_selection, start_pos, end_pos] = GetCurrentViewSelection();
    (this->*processing_function)(current_selection);  

    std::string current_sequence = GetCurrentViewText();
    current_sequence.replace(start_pos, end_pos-start_pos, current_selection);

    //After updating  
    sequence_model_->sequence = current_sequence;
    UpdateViewText(sequence_model_->sequence);
    emit CursorPositionChanged(end_pos);
    qDebug() << "Sequence was updated to" << QString::fromStdString(current_sequence);
    return;
  }
  else if (!is_text_selected) {
    std::string current_sequence = GetCurrentViewText();
    (this->*processing_function)(current_sequence);  

    sequence_model_->sequence = current_sequence;
    UpdateViewText(sequence_model_->sequence);
    qDebug() << "Sequence was updated to" << QString::fromStdString(current_sequence);
    return;
  }
}

void SequenceViewModel::IsTextSelectedUpdated(bool b) {
  is_text_selected = b;
  qDebug() << "is_text_selected was updated to" << is_text_selected;
}

void SequenceViewModel::ViewTextUpdated(QString str) {
  //qDebug() << "In SequenceViewModel::ViewTextUpdated";
  std::string str_to_write = str.toStdString();
  //qDebug() << "Setting SequenceModel::sequence to" << str;
  sequence_model_->sequence = str.toStdString();
}

void SequenceViewModel::Complement(std::string& str) {
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

void SequenceViewModel::ReverseComplement(std::string& current_selection) {
  Complement(current_selection);
  std::reverse(current_selection.begin(), current_selection.end());
}

void SequenceViewModel::Translate(std::string& current_selection) {
  qDebug() << "In SequenceViewModel::Translate()"; 
  auto sequence_length = current_selection.length();
  //If sequence length does not encompass full codons, emit a warning and trim
  //the incomplete codon
  if (sequence_length % 3 != 0) {
    qDebug() << "Partial codon selected, ignoring";
    //Creates the longest substring that has modulo 3 equal 0 and update the string length
    current_selection = current_selection.substr(0, sequence_length - (sequence_length % 3));
    sequence_length = current_selection.length();
    //TODO
    //emit PartialCodonSelected();
  }

  std::map<std::string, char> codon_to_protein
      { {"AAA", 'K'}, {"AAT", 'N'}, {"AAG", 'K'}, {"AAC", 'N'},
        {"ATA", 'I'}, {"ATT", 'I'}, {"ATG", 'M'}, {"ATC", 'I'},
        {"AGA", 'R'}, {"AGT", 'S'}, {"AGG", 'R'}, {"AGC", 'S'},
        {"ACA", 'T'}, {"ACT", 'T'}, {"ACG", 'T'}, {"ACC", 'T'},
        {"TAA", '*'}, {"TAT", 'Y'}, {"TAG", '*'}, {"TAC", 'Y'},
        {"TTA", 'L'}, {"TTT", 'F'}, {"TTG", 'L'}, {"TTC", 'F'},
        {"TGA", '*'}, {"TGT", 'C'}, {"TGG", 'W'}, {"TGC", 'C'},
        {"TCA", 'S'}, {"TCT", 'S'}, {"TCG", 'S'}, {"TCC", 'S'},
        {"GAA", 'E'}, {"GAT", 'D'}, {"GAG", 'E'}, {"GAC", 'D'},
        {"GTA", 'V'}, {"GTT", 'V'}, {"GTG", 'V'}, {"GTC", 'V'},
        {"GGA", 'G'}, {"GGT", 'G'}, {"GGG", 'G'}, {"GGC", 'G'},
        {"GCA", 'A'}, {"GCT", 'A'}, {"GCG", 'A'}, {"GCC", 'A'},
        {"CAA", 'Q'}, {"CAT", 'H'}, {"CAG", 'Q'}, {"CAC", 'H'},
        {"CTA", 'L'}, {"CTT", 'L'}, {"CTG", 'L'}, {"CTC", 'L'},
        {"CGA", 'R'}, {"CGT", 'R'}, {"CGG", 'R'}, {"CGC", 'R'},
        {"CCA", 'P'}, {"CCT", 'P'}, {"CCG", 'P'}, {"CCC", 'P'} };

  std::string translated_string;
  std::size_t current_position = 0;
  while(current_position <= sequence_length - 3) {
    std::string codon_to_translate = current_selection.substr(current_position, 3);
    for (auto& c : codon_to_translate) {
      c = toupper(c);
    }
    translated_string += codon_to_protein[codon_to_translate];
    current_position += 3;
  }

  //At some point this will move into a class of its own so it is not hardcoded in this class
  //Create the widget to display Translated sequence
  QWidget* parent = static_cast<QWidget*>(this->parent());
  
  QWidget* translate_widget = new QWidget(parent);
  translate_widget->setWindowTitle("Translate");
  QGridLayout* layout = new QGridLayout();
  translate_widget->setLayout(layout);
  
  QPlainTextEdit* translate_view = new QPlainTextEdit(parent);
  translate_view->setReadOnly(true);
  translate_view->setPlainText(QString::fromStdString(translated_string));
  layout->addWidget(translate_view, 1, 0, 1, 4);

  QLabel* length = new QLabel("Length");
  layout->addWidget(length, 0, 0);
  QLineEdit* length_box = new QLineEdit();
  length_box->setReadOnly(true); 
  length_box->setText(QString::number(translated_string.length()));
  length_box->setMinimumWidth(50);
  length_box->setMaximumWidth(80);
  layout->addWidget(length_box, 0, 1);
  
  QLabel* mol_weight = new QLabel("Molecular weight");
  layout->addWidget(mol_weight, 0, 2);
  QLineEdit* mol_weight_box = new QLineEdit();
  mol_weight_box->setReadOnly(true);
  mol_weight_box->setText(QString::number(CalculateMw(translated_string), 'f'));
  mol_weight_box->setMinimumWidth(120);
  mol_weight_box->setMaximumWidth(160);
  layout->addWidget(mol_weight_box, 0, 3);


  QFont sequence_font = translate_view->font();
  sequence_font.setFamily("Courier");
  sequence_font.setPointSize(12);
  translate_view->setFont(sequence_font);

  translate_widget->setWindowFlags(Qt::Window);
  translate_widget->show();
}

std::tuple<std::string, int, int> SequenceViewModel::GetCurrentViewSelection() {
  QTextCursor cursor = sequence_view_->textCursor();
  auto start_pos = cursor.selectionStart();
  auto end_pos = cursor.selectionEnd();
  qDebug() << "Sequence start pos" << start_pos << ", end pos" << end_pos;

  std::string current_selection = GetCurrentViewText().substr(start_pos, end_pos-start_pos);
  return std::tuple<std::string, int, int>(current_selection, start_pos, end_pos);
}

std::string SequenceViewModel::GetCurrentViewText() {
  return (sequence_view_->toPlainText()).toStdString();
}

void SequenceViewModel::UpdateViewText(const std::string& str) {
  sequence_view_->setPlainText(QString::fromStdString(str));
  return;
}

double SequenceViewModel::CalculateMw(std::string& protein) {
  //Both of these molecular weight mass variables contain the weight of each
  //amino acid MINUS the H2O
  std::map<char, double> monoisotopic_molecular_weights { {'A', 71.03711 },
                                             {'V', 99.06841},
                                             {'I', 113.08406},
                                             {'L', 113.08406},
                                             {'F', 147.06841},
                                             {'Y', 163.06333},
                                             {'W', 186.07931},
                                             {'G', 57.02146},
                                             {'H', 137.05891},
                                             {'N', 114.04293},
                                             {'D', 115.02694},
                                             {'Q', 128.05858},
                                             {'E', 129.04259},
                                             {'K', 128.09496},
                                             {'R', 156.10111},
                                             {'S', 87.03203},
                                             {'T', 101.04768},
                                             {'P', 97.05276},
                                             {'M', 131.04049},
                                             {'C', 103.00919} };

  std::map<char, double> average_molecular_weights { {'A', 71.0788 },
                                             {'V', 99.1326},
                                             {'I', 113.1594},
                                             {'L', 113.1594},
                                             {'F', 147.1766},
                                             {'Y', 163.1760},
                                             {'W', 186.2132},
                                             {'G', 57.0519},
                                             {'H', 137.1411},
                                             {'N', 114.1038},
                                             {'D', 115.0886},
                                             {'Q', 128.1307},
                                             {'E', 129.1155},
                                             {'K', 128.1741},
                                             {'R', 156.1875},
                                             {'S', 87.0782},
                                             {'T', 101.1051},
                                             {'P', 97.1167},
                                             {'M', 131.1926},
                                             {'C', 103.1388} };

  double molecular_weight;

  for (const auto& amino_acid : protein) {
    molecular_weight += average_molecular_weights[amino_acid];
  }
  molecular_weight += 18.01528; //Add the -OH and -H to the ends of the peptide chain
  return molecular_weight;
};





























