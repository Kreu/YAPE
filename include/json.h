#ifndef JSON_H
#define JSON_H

#include <QString>
#include <QJsonArray>

class JSON {
public:
  static QJsonArray LoadJSONArray(QString filename);
private:
  JSON() = delete;
};

#endif
