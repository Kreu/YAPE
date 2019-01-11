#include <QString>
#include <QDebug>

#include <QJsonArray>
#include <QListWidgetItem>
#include <QListWidget>
#include <QGridLayout>
#include <QLabel>

#include "restriction_digest_view.h"
#include "json.h"

RestrictionDigestView::RestrictionDigestView(QWidget* parent) : QWidget(parent) {

  QWidget* restriction_digest_view = new QWidget(this);
  restriction_digest_view->setWindowFlags(Qt::Window);
  restriction_digest_view->setWindowTitle("Restriction digest");

  QListWidget* all_enzymes_view = new QListWidget(restriction_digest_view);
  QListWidget* selected_enzymes_view = new QListWidget(restriction_digest_view);
  all_enzymes_view->setFlow(QListWidget::TopToBottom);
  selected_enzymes_view->setFlow(QListWidget::TopToBottom);

  QGridLayout* layout = new QGridLayout();
  QLabel* all_enyzmes_label = new QLabel("All enzymes");
  QLabel* selected_enzymes_label = new QLabel("Selected enzymes");
  layout->addWidget(all_enyzmes_label, 0, 0);
  layout->addWidget(selected_enzymes_label, 0, 2);

  layout->addWidget(all_enzymes_view, 1, 0);
  layout->addWidget(selected_enzymes_view, 1, 2);
  restriction_digest_view->setLayout(layout);
  restriction_digest_view->show();

  QJsonArray data = JSON::LoadJSONArray("./config/restriction_enzymes.json");
  for (const auto& d : data) {
    ReadJSON(d.toObject());

  }

  //Placeholder data
  QListWidgetItem* ecori = new QListWidgetItem(tr("EcoRI"));
  all_enzymes_view->insertItem(0, ecori);
  QListWidgetItem* ecorv = new QListWidgetItem(tr("EcoRV"));
  all_enzymes_view->insertItem(0, ecorv);
  QListWidgetItem* bamhi= new QListWidgetItem(tr("BamHI"));
  all_enzymes_view->insertItem(0, bamhi);
  QListWidgetItem* xbai = new QListWidgetItem(tr("XbaI"));
  all_enzymes_view->insertItem(0, xbai);
}

void RestrictionDigestView::ReadJSON(const QJsonObject& enzyme) {
  QString enzyme_name = enzyme["name"].toString();
  QString restriction_site = enzyme["cut-site"].toString();
  int cut_position = enzyme["cut-position"].toInt();
  qDebug() << enzyme_name << restriction_site << cut_position;
}
