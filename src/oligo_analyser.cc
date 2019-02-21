#include <QMap>
#include <QString>
#include <QPair>
#include <QDebug>
#include <cmath>

#include "oligo_analyser.h"

//Map of DNA thermodynamic properties, key is the oligonucleotide pair, first
//element in pair is delta H, second one is delta S.
QMap<QString, QPair<double, double>> dna_thermodynamic_properties
    { {"AA", {-8.4, -0.0236} }, 
      {"TT", {-8.4, -0.0236} },
      {"AT", {-6.5, -0.0188} },
      {"TA", {-6.3, -0.0185} },  
      {"CA", {-7.4, -0.0193} },
      {"TG", {-7.4, -0.0193} },
      {"GT", {-8.6, -0.0230} },
      {"AC", {-8.6, -0.0230} },
      {"CT", {-6.1, -0.0161} },
      {"AG", {-6.1, -0.0161} },
      {"GA", {-7.7, -0.0203} },
      {"TC", {-7.7, -0.0203} },
      {"CG", {-10.1, -0.0255} },
      {"GC", {-11.1, -0.0284} },
      {"GG", {-6.7, -0.0156} },
      {"CC", {-6.7, -0.0156} } };

//QMap<QString, QPair<double, double>> dna_thermodynamic_properties
//    { {"AA", {-9.1, -0.0240} }, 
//      {"TT", {-9.1, -0.0240} },
//      {"AT", {-8.6, -0.0239} },
//      {"TA", {-6.0, -0.0169} },  
//      {"CA", {-5.8, -0.0129} },
//      {"TG", {-5.8, -0.0129} },
//      {"GT", {-6.5, -0.0173} },
//      {"AC", {-6.5, -0.0173} },
//      {"CT", {-7.8, -0.0208} },
//      {"AG", {-7.8, -0.0208} },
//      {"GA", {-5.6, -0.0135} },
//      {"TC", {-5.6, -0.0135} },
//      {"CG", {-11.9, -0.0278} },
//      {"GC", {-11.1, -0.0267} },
//      {"GG", {-11.0, -0.0266} },
//      {"CC", {-11.0, -0.0266} } };

double OligoAnalyser::CalculateTm(QString oligo) {
  /*
  TODO: Need to find another source due to copyright reasons
  //Source 
  
  Tm = (dH / (A + dS + R* ln(C/4))) - 273.15 + 16.6*log[Na+]

  Tm = melting temperature in °C
  ΔH = enthalpy change in kcal mol-1 (accounts for the energy change during annealing / melting)
  A = constant of -0.0108 kcal K-1 ᐧ mol-1 (accounts for helix initiation during annealing / melting)
  ΔS = entropy change in kcal K-1 ᐧ mol-1 (accounts for energy unable to do work, i.e. disorder)
  R = gas constant of 0.00199 kcal K-1 ᐧ mol-1 (constant that scales energy to temperature)
  C = oligonucleotide concentration in M or mol L-1 (we use 0.0000005, i.e. 0.5 µM)
  -273.15 = conversion factor to change the expected temperature in Kelvins to °C
  [Na+] = sodium ion concentration in M or mol L-1 (we use 0.05, i.e. 50 mM)
  */
  constexpr double HELIX_CONSTANT = -0.0108; // kcal/mol
  constexpr double GAS_CONSTANT = 0.001987; // kcal/mol*K
  constexpr double OLIGONUCLEOTIDE_CONC = 0.00000005; //M, 50 nM used
  constexpr double SODIUM_CONC = 0.05; //M, 50 mM used
  constexpr double DINUCLEOTIDE_LENGTH = 2; //Dinucleotide sequence length
 
  double melting_temperature{0};
  double delta_H{0};
  double delta_S{0};
  std::size_t current_position = 0;
  
  qDebug() << "Calculating Tm of" << oligo;
  //Make sure that we not read out of range
  while(current_position <= oligo.length() - DINUCLEOTIDE_LENGTH) {
    //qDebug() << "Current position:" << current_position;
    QString dinucleotide = oligo.mid(current_position, DINUCLEOTIDE_LENGTH);
    //Turn the codon into uppercase so it can be matched to the codon table
    dinucleotide  = dinucleotide.toUpper();
    QPair<double, double> dinucleotide_properties = dna_thermodynamic_properties[dinucleotide];
    delta_H += dinucleotide_properties.first;
    delta_S += dinucleotide_properties.second;
    ++current_position;
  }
  qDebug() << "Delta H" << delta_H;
  qDebug() << "Delta S" << delta_S;
  
  melting_temperature = delta_H / (HELIX_CONSTANT + delta_S + GAS_CONSTANT * log(OLIGONUCLEOTIDE_CONC/4)) \
                        - 273.15 + 12.5*log10(SODIUM_CONC); 
  return melting_temperature;
} 
