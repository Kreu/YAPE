#include <QWidget>

#include <QJsonObject>

class RestrictionDigestView : public QWidget {
Q_OBJECT
public:
  RestrictionDigestView(QWidget* parent = nullptr);
public slots:

signals:

private:
  void ReadJSON(const QJsonObject& enzyme);
};
