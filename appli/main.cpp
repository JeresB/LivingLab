#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include "websocket.hpp"

void connexion() {
  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
  db.setHostName("localhost");
  db.setUserName("livinglab");
  db.setPassword("livinglab");
  db.setDatabaseName("livinglab");
  if(db.open()) {
    qDebug() << "Vous êtes maintenant connecté à " << db.hostName();

  } else {
    qDebug() << "La connexion a échouée, désolé";
  }

  QSqlQuery query;
  if(query.exec("SELECT * FROM chambre")) {
    QSqlRecord rec = query.record();
    qDebug() << "Selection réussi :)";
    int nameCol = rec.indexOf("ip_chambre"); // index of the field "name"
    while(query.next()) {
      qDebug() << "Nouvelle entrée";
      for(int x=0; x < rec.count(); ++x) {
        qDebug() << query.value(nameCol).toString(); // output all names
      }
    }
  } else {
    qDebug() << "Une erreur s'est produite. :(";
  }
}

int main(int argc, char *argv[]) {
  QCoreApplication appli(argc, argv);

  WebSocket chambre1(QUrl(QStringLiteral("ws://192.168.199.30:1000")));

  connexion();

  return appli.exec();
}
