#ifndef FEATURE_MODEL_H
#define FEATURE_MODEL_H

#include <QObject>
#include <QString>
#include <tuple>

class FeatureModel : public QObject {
Q_OBJECT
public:
  FeatureModel(QString name, int start_pos, int end_pos, QObject* parent = nullptr);
  QString GetName();
  int GetStartPos();
  int GetEndPos();
  //Convenience function that returns all data in a tuple. Extremely likely to
  //change in the future.
  std::tuple<QString, int, int> GetAllData();
signals:
  void NotifyFeatureChanged(QString name, int start_pos, int end_pos);
public slots:
  void ProcessFeatureChanged(QString name, int start_pos, int end_pos);
private:
Q_DISABLE_COPY(FeatureModel)
  QString name_;
  int start_pos_;
  int end_pos_;
};

#endif
