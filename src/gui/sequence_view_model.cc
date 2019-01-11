#include <QObject>
#include <QString>
#include <QDebug>
#include <QChar>
#include <QTextCursor>
#include <QWidget>
#include <QMap>
#include <QChar>
#include "sequence_view_model.h"
#include "sequence_view.h"
#include "sequence_model.h"

namespace {
  const int CODON_LENGTH = 3;
}

//////////////
//  PUBLIC  //
//////////////
SequenceViewModel::SequenceViewModel(QObject* parent, SequenceView* sequence_view, SequenceModel* sequence_model) 
  : QObject(parent), sequence_view_(sequence_view), sequence_model_(sequence_model), start_pos_{0}, end_pos_{0} {

  //Set the local copy of the sequence to whatever the model holds
  //sequence_ = sequence_model_->GetSequence();

  //This needs to be set to false to make sure that when the user first opens
  //the app and uses an action, it knows that no text has been selected yet
  text_selected_ = false;  

  //Self-signals
  
  //Detect whether we have changed the sequence within this ViewModel
  connect(this,
          &SequenceViewModel::NotifySequenceChanged,
          this,
          &SequenceViewModel::ProcessSequenceChanged);

  //Signals FROM here (SequenceViewModel)
  connect(this,
          &SequenceViewModel::NotifySequenceChanged,
          sequence_view_,
          &SequenceView::ProcessSequenceChanged);

  connect(this,
          &SequenceViewModel::NotifyCursorPositionChanged,
          sequence_view_,
          &SequenceView::ProcessCursorPositionChanged);

  //Tell SequenceModel sequence has changed
//  connect(this,
//          &SequenceViewModel::NotifySequenceChanged,
//          sequence_model_,
//          &SequenceModel::ProcessSequenceChanged);

  //Signals TO here (SequenceViewModel)
  connect(sequence_view_,
          &SequenceView::NotifySelectionChanged,
          this,
          &SequenceViewModel::ProcessSelectionChanged);

  connect(sequence_view_,
          &SequenceView::copyAvailable, //Emitted if text is (de)selected
          this,
          &SequenceViewModel::ProcessIsTextSelected);

  connect(sequence_view_,
          &SequenceView::NotifySequenceChanged,
          this,
          &SequenceViewModel::ProcessSequenceChanged);

  connect(sequence_model_,
          &SequenceModel::NotifySequenceChanged,
          this,
          &SequenceViewModel::ProcessSequenceChanged);
  
  //FeatureModel signals
  //connect(feature_model_,
  //        FeatureModel::NotifyFeatureChanged,
  //        this,
  //        SequenceViewModel::ProcessFeatureChanged);
}

QWidget* SequenceViewModel::GetView() {
  return sequence_view_;
}

/////////////
//  SLOTS  //
/////////////
void SequenceViewModel::ProcessSequenceChanged(QString sequence) {
  if (sequence_ != sequence) {
    sequence_ = sequence;
    emit NotifySequenceChanged(sequence_);
    return;
  }
  return;
}

void SequenceViewModel::ProcessSelectionChanged(int start_pos, int end_pos) {
  if(start_pos_ != start_pos || end_pos_ != end_pos) {
    start_pos_ = start_pos;
    end_pos_ = end_pos;
    return;
  }
  return;
}

void SequenceViewModel::ProcessIsTextSelected(bool b) {
  text_selected_ = b;
  qDebug() << "Text selected:" << text_selected_;
  return;
}

//void SequenceViewModel::ProcessFeatureAdded(FeatureModel feature) {
//
//}
//
//void SequenceViewModel::ProcessFeatureEdited(FeatureModel feature) {
//
//}
//
//void SequenceViewModel::ProcessFeatureChanged(FeatureModel feature) {
//
//}

///////////////
//  PRIVATE  //
///////////////

//This function takes a pointer to a function and calls it on the current
//SequenceView selection. 

void SequenceViewModel::CallComplement() {
  ProcessSelection(&SequenceViewModel::Complement);
  return;
}

void SequenceViewModel::CallReverseComplement() {
  ProcessSelection(&SequenceViewModel::ReverseComplement);
  return;
}

//void SequenceViewModel::CallComplement() {
//  if (text_selected_) {
//    auto selection_length_ = start_pos_ + (end_pos_ - start_pos_);
//    QString current_selection = sequence_.mid(start_pos_, end_pos_ - start_pos_);
//    QString complemented_sequence = Complement(current_selection);    
//   
//    //Don't update the sequence_ directly
//    QString new_sequence = sequence_; 
//    new_sequence.replace(start_pos_, complemented_sequence.length(), complemented_sequence);
//    
//    //We need a local copy here because setting the text de-selects it, which 
//    //in turn emits a NotifyCursorPositionChanged signal to SequenceViewModel that
//    //sets the end position to -1
//    auto save_end_pos = end_pos_;
//    emit NotifySequenceChanged(new_sequence);
//    emit NotifyCursorPositionChanged(save_end_pos);
//    return;
//  }
//  else if (!text_selected_) {
//    QString complemented_sequence = Complement(sequence_);
//    
//    //We need a local copy here because setting the text de-selects it, which 
//    //in turn emits a NotifyCursorPositionChanged signal to SequenceViewModel that
//    //sets the end position to -1
//    auto save_end_pos = end_pos_;
//    emit NotifySequenceChanged(complemented_sequence);; 
//    emit NotifyCursorPositionChanged(save_end_pos);
//    return;
//  }
//}
//
//void SequenceViewModel::CallReverseComplement() {
//  if (text_selected_) {
//    auto selection_length_ = start_pos_ + (end_pos_ - start_pos_);
//    QString current_selection = sequence_.mid(start_pos_, end_pos_ - start_pos_);
//    QString reverse_complement = Complement(current_selection);
//         
//    //Don't update the sequence_ directly
//    QString new_sequence = sequence_; 
//    
//    //No STL-type reverse function in QT
//    std::string temp = reverse_complement.toStdString();
//    std::reverse(temp.begin(), temp.end());
//    reverse_complement = QString::fromStdString(temp);
//    
//    new_sequence.replace(start_pos_, reverse_complement.length(), reverse_complement);
//    
//    //We need a local copy here because setting the text de-selects it, which 
//    //in turn emits a NotifyCursorPositionChanged signal to SequenceViewModel that
//    //sets the end position to -1
//    auto save_end_pos = end_pos_;
//    emit NotifySequenceChanged(new_sequence);
//    emit NotifyCursorPositionChanged(save_end_pos);
//    return;
//  }
//  else if (!text_selected_) {
//    QString new_sequence = sequence_;
//    QString reverse_complement = Complement(new_sequence);
//    //No STL-type reverse function in QT
//    std::string temp = reverse_complement.toStdString();
//    std::reverse(temp.begin(), temp.end());
//    reverse_complement = QString::fromStdString(temp);
//    
//    //We need a local copy here because setting the text de-selects it, which 
//    //in turn emits a NotifyCursorPositionChanged signal to SequenceViewModel that
//    //sets the end position to -1
//    auto save_end_pos = end_pos_;
//    emit NotifySequenceChanged(reverse_complement); 
//    emit NotifyCursorPositionChanged(save_end_pos);
//    return;
//  }
//}

void SequenceViewModel::CallTranslate() {

}

void SequenceViewModel::ProcessSelection(Function processing_function) {
  if (text_selected_) {
    QString current_selection = sequence_.mid(start_pos_, end_pos_ - start_pos_);
    QString processed_sequence = (this->*processing_function)(current_selection);    
   
    //Don't update the sequence_ directly
    QString new_sequence = sequence_; 
    new_sequence.replace(start_pos_, processed_sequence.length(), processed_sequence);
    
    //We need a local copy here because setting the text de-selects it, which 
    //in turn emits a NotifyCursorPositionChanged signal to SequenceViewModel that
    //sets the end position to -1
    auto save_end_pos = end_pos_;
    emit NotifySequenceChanged(new_sequence);
    emit NotifyCursorPositionChanged(save_end_pos);
    return;
  }
  else if (!text_selected_) {
    QString processed_sequence = (this->*processing_function)(sequence_);    
    //We need a local copy here because setting the text de-selects it, which 
    //in turn emits a NotifyCursorPositionChanged signal to SequenceViewModel that
    //sets the end position to -1
    auto save_end_pos = end_pos_;
    emit NotifySequenceChanged(processed_sequence); 
    emit NotifyCursorPositionChanged(save_end_pos);
    return;
  }
}

QString SequenceViewModel::Complement(QString sequence) {
  for (QChar& c : sequence) {
    switch(c.unicode()) {
      case('A') : c = 'T'; break;
      case('a') : c = 't'; break;             
      case('T') : c = 'A'; break;
      case('t') : c = 'a'; break;
      case('G') : c = 'C'; break;
      case('g') : c = 'c'; break;
      case('C') : c = 'G'; break;
      case('c') : c = 'g'; break;

      /* Maybe one day the support for degenerate codons will be added...
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
      */
    }
  }
  return sequence;
}

QString SequenceViewModel::ReverseComplement(QString sequence) {
  QString reverse_complement = Complement(sequence);
  //No STL-type reverse function in QT
  std::string temp = reverse_complement.toStdString();
  std::reverse(temp.begin(), temp.end());
  reverse_complement = QString::fromStdString(temp);
  return reverse_complement;
}

QString SequenceViewModel::Translate(QString sequence) {
  qDebug() << "In SequenceViewModel::Translate()"; 
  std::size_t sequence_length = sequence.length();
  
  if (sequence_length % CODON_LENGTH != 0) {
    qDebug() << "Partial codon selected, ignoring";
    //Creates the longest substring with intact codons
    sequence = sequence.mid(0, sequence_length - (sequence_length % CODON_LENGTH));
    sequence_length = sequence.length();
    //TODO: Emit to the status bar as a warning
    //emit PartialCodonSelected();
  }

  QMap<QString, QChar> codon_to_protein
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

  QString translated_string;
  std::size_t current_position = 0;
  //Make sure that we not read out of range
  while(current_position <= sequence_length - CODON_LENGTH) {
    QString codon_to_translate = sequence.mid(current_position, CODON_LENGTH);
    //Turn the codon into uppercase so it can be matched to the codon table
    for (QChar& c : codon_to_translate) {
      c.toUpper();
    }
    translated_string += codon_to_protein[codon_to_translate];
    current_position += CODON_LENGTH;
  }
  return translated_string;
}

  /* Create a new TranslateWidget class for this. DOES NOT BELONG IN VIEWMODEL
  //At some point this will move into a class of its own so it is not hardcoded
  //in this class
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
  */

double SequenceViewModel::CalculateMw(QString protein_sequence) {
  //Both of these molecular weight mass variables contain the weight of each
  //amino acid MINUS the H2O
  QMap<QChar, double> monoisotopic_molecular_weights 
      { {'A', 71.03712 },
        {'V', 100.06841},
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

  QMap<QChar, double> average_molecular_weights
      { {'A', 71.0788 },
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

  for (const QChar& amino_acid : protein_sequence) {
    molecular_weight += average_molecular_weights[amino_acid];
  }
  molecular_weight += 18.01528; //Add the -OH and -H to the ends of the peptide chain
  return molecular_weight;
}
