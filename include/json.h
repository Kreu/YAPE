#include <QString>
#include <QJsonArray>

class JSON {
public:
  static QJsonArray LoadJSONArray(QString filename);
private:
  JSON() = delete;
};
