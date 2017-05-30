#ifndef DATABASE_H
#define DATABASE_H

/*!
 * \file Database.hpp
 * \brief Connexion avec la base de données
 * \author {Jeremy B. & Théo D.}
 * \version 1
 */

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QByteArray>
#include <QFile>

/*! \class Database
 * \brief classe representant une connexion avec la base de donnée de type MySQL.
 *
 * Utilisation de QtSQL pour permettre cette connexion.
 *
 *  La classe ouvre une connexion avec la base de données puis permettra de faire des requetes.
 */
class Database : public QObject {
    Q_OBJECT
public:
    /**
     *  \brief Constructeur
     *
     *  Constructeur de la classe Database
     *
     *  \param parent(QObject*) : Possibilité de donner le QObject parent
     */
    explicit Database(QObject *parent = Q_NULLPTR);
    /**
     *  \brief Requete
     *
     *  Méthode requete : permet de faire des requetes de type SELECT
     *
     *  \param sqlquery(QString &) : requete de type select
     */
    QByteArray requete(const QString & sqlquery);
    /**
     *  \brief insertCapteurs
     *
     *  Méthode insertCapteurs : permet de faire des requetes de type INSERT INTO
     *
     *  \param requete(QString) : requete de type insert into
     */
    void insertCapteurs(QString requete);

Q_SIGNALS:

private Q_SLOTS:

private:
  QSqlDatabase db;
  QSqlQuery query;
  QSqlRecord record;
};

#endif // DATABASE_H
