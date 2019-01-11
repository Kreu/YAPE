#include <QObject>
#include <tuple>

#include "feature_model.h"

//////////////
//  PUBLIC  //
//////////////
FeatureModel::FeatureModel(QString name, int start_pos, int end_pos, QObject* parent) : QObject(parent) {};

QString FeatureModel::GetName() {
  return name_;
}

int FeatureModel::GetStartPos() {
  return start_pos_;
}

int FeatureModel::GetEndPos() {
  return end_pos_;
}

std::tuple<QString, int, int> FeatureModel::GetAllData() {
  return std::tuple(name_, start_pos_, end_pos_);
}

/////////////
//  SLOTS  //
/////////////

void FeatureModel::ProcessFeatureChanged(QString name, 
                                         int start_pos,
                                         int end_pos) {
  //If the data is new, process it.
  if(name != name_ || start_pos != start_pos_ || end_pos != end_pos_) {
    name_ = name;
    start_pos_ = start_pos;
    end_pos_ = end_pos;
    emit NotifyFeatureChanged(name_, start_pos_, end_pos_);
    return;
  }
  return;
}


