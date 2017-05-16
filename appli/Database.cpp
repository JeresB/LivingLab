#include "Database.hpp"
#include <QDebug>

QT_USE_NAMESPACE

// [constructor]
Database::Database(QObject *parent) : QObject(parent) {
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
  QVector<QVariant> valeur;
  if (db.isOpen()) {
    query = db.exec(requete);
    record = query.record();
    qDebug() << "Selection réussi :)";

    while(query.next()) {
      for(int i=0; i < record.count(); i++) {
        QString colonne = record.fieldName(i);
        QVariant value = query.value(i);

        qDebug() << colonne << " = " << value << " type : " << value.typeName();



        //valeur.insert(record.fieldName(i), query.value(i).toJsonValue());
      }
    }
  } else {
    qDebug() << "La requete n'a pas abouti, la base de données est fermée !";
  }
}
//! [fonction public requete]
