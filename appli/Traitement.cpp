#include "Traitement.hpp"
#include <QDebug>

QT_USE_NAMESPACE

// [constructor]
Traitement::Traitement(QObject *parent) : QObject(parent) {
  bool success = false;
  // Création de la connexion à la base de données
  livinglab = new Database;

  // Fonction de récupération des adresses IP des pièces
  success = roomList();
  livinglab->requete("SELECT * FROM chambre");
}
//! [constructor]

int Traitement::roomList() {

}
