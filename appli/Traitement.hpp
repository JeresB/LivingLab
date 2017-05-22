#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include <QObject>
#include <QByteArray>
#include <cmath>
#include "Database.hpp"
#include "Chambre.hpp"
#include "Telephone.hpp"
#include "smtp.hpp"

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
  void saveDataRoomToProcess(QDateTime, int, bool, float, float, bool, QString, int);
  void saveDataUserToProcess(QDateTime, int, QString, QString);

private:
  Database *livinglab;
  QVector<Chambre *> vect_chambre;
  QVector<Telephone *> vect_user;

  QVector<int> temperature_save;

  QVector<QTime> vect_four_allume;
  QVector<QTime> vect_deplacement;

  QTime matin;
  QTime soir;

  int diff_temp = 3;
};

#endif // TRAITEMENT_H
