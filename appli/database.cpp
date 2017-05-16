#include "database.hpp"
#include <QDebug>

QT_USE_NAMESPACE

// [constructor]
Database::Database() {
  db = QSqlDatabase::addDatabase("QMYSQL");

  db.setHostName("localhost");
  db.setUserName("livinglab");
  db.setPassword("livinglab");
  db.setDatabaseName("livinglab");

  if(db.open()) {
    qDebug() << "Vous êtes maintenant connecté à " << db.hostName();
  } else {
    qDebug() << "La connexion a échouée, désolé";
  }
}
//! [constructor]

// [fonction public requete]
int Database::requete(QString requete) {
  if (db.isOpen()) {
    /* code */
  if(query.exec(requete)) {
    record = query.record();
    qDebug() << "Selection réussi :)";
    //int nameCol = record.indexOf("ip_chambre"); // index of the field "name"
    while(query.next()) {
      qDebug() << "Nouvelle entrée";
      for(int x=0; x < record.count(); x++) {
        //qDebug() << query.value(nameCol).toString(); // output all names
        qDebug() << record.fieldName(x) << " = " << query.value(x);
      }
    }
  } else {
    qDebug() << "Une erreur s'est produite. :(";
  }
} else {
  qDebug() << "base de données par ouverte dans la requete";
}
}
//! [fonction public requete]
