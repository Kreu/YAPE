#include <QDebug>

#include "translate_view_model.h"
#include "translate_view.h"
#include "sequence_model.h"

namespace {
  const int CODON_LENGTH = 3;
}

//////////////
//  PUBLIC  //
//////////////
TranslateViewModel::TranslateViewModel(SequenceViewModel* sequence_view_model, QWidget* parent) 
                        : QWidget(parent), sequence_view_model_(sequence_view_model) {
  qDebug() << "In TranslateViewModel constructor"; 
 
  //TODO: Connect TranslateView slots to TranslateViewModel signals INSIDE 
  //TranslateView, not here! TranslateViewModel shouldn't be connecting signals
  //on somebody else's behalf.
  translate_view_ = new TranslateView(this);
  //Connections
  connect(this,
          &TranslateViewModel::NotifyTranslatedSequence,
          translate_view_,
          &TranslateView::ProcessTranslatedSequence);

  connect(this,
          &TranslateViewModel::NotifyMolecularWeight,
          translate_view_,
          &TranslateView::ProcessMolecularWeight);

  connect(this,
          &TranslateViewModel::NotifyLength,
          translate_view_,
          &TranslateView::ProcessLength);
}

void TranslateViewModel::CallTranslate() {
  //TODO: Don't use sequence_model directly, get sequence from SequenceViewModel
  Translate(sequence_view_model_->GetSequence());
  translate_view_->show();
}


///////////////
//  PRIVATE  //
///////////////
void TranslateViewModel::Translate(QString sequence) {
  //TODO: Does QString use int or size_t for length?
  qDebug() << "In TranslateViewModel::Translate()";
  std::size_t sequence_length = sequence.length();

  if (sequence_length < 3) {
    qDebug() << "Nothing to translate";
    return;
  }

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
    //qDebug() << "Current position:" << current_position;
    QString codon_to_translate = sequence.mid(current_position, CODON_LENGTH);
   
    //Turn the codon into uppercase so it can be matched to the codon table
    codon_to_translate = codon_to_translate.toUpper();
    
    translated_string += codon_to_protein[codon_to_translate];
    current_position += CODON_LENGTH;
  }
 
  CalculateMW(translated_string);

  qDebug() << "Translated string:" << translated_string;
  emit NotifyTranslatedSequence(translated_string);
  emit NotifyLength(translated_string.length());
}

void TranslateViewModel::CalculateMW(QString protein_sequence) {

  if (protein_sequence.length() == 0) {
    qDebug() << "No sequence provided";
    return;
  }

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

  double molecular_weight{0};
  for (const QChar& amino_acid : protein_sequence) {
    molecular_weight += average_molecular_weights[amino_acid];
  }
  molecular_weight += 18.01528; //Add the -OH and -H to the ends of the peptide chain
  emit NotifyMolecularWeight(molecular_weight);
}
