#include <QFile>
#include <QByteArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QDebug>

#include "json.h"

//Reads a JSON file that contains an array of objects. Returns the array containing
//the objects, or an empty array if either parsing failed or the JSON file contains
//no data.
QJsonArray JSON::LoadJSONArray(QString filename) {
  QFile file(filename);
  qDebug() << "Opening" << filename;

  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Could not open file";
    return QJsonArray();
  }
  QByteArray data = file.readAll();
  file.close();

  QJsonParseError error;
  QJsonDocument doc = QJsonDocument::fromJson(data, &error);
  if (doc.isNull()) {
    qDebug() << "Could not create QJsonDocument";
    qDebug() << error.errorString();
    return QJsonArray();
  }

  QJsonArray data_array = doc.array();
  if (data_array.empty()) {
    qDebug() << "No objects in array";
    return QJsonArray();
  }

  return data_array;
}
