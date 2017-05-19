#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include <QObject>
#include <QByteArray>
#include "Database.hpp"
#include "Chambre.hpp"
#include "Telephone.hpp"

class Traitement : public QObject {
  Q_OBJECT
public:
    Traitement(QObject *parent = Q_NULLPTR);
    int List(QString);
    int roomSeuil();
    int telephoneSeuil();
    int openConnexionChambre(int id, QString IP, int port);
    int openConnexionUser(QString numero, QString IP, int port);

Q_SIGNALS:

private Q_SLOTS:
  void saveDataRoomToProcess(QString, int, bool, float, float, bool, int);
  void saveDataUserToProcess(QString, int, QString, QString);

private:
  Database *livinglab;
  QVector<Chambre *> vect_chambre;
  QVector<Telephone *> vect_user;
};

#endif // TRAITEMENT_H
