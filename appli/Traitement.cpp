#include "Traitement.hpp"
#include <QDebug>

QT_USE_NAMESPACE

// [constructor]
Traitement::Traitement() {
  Database *livinglab = new Database;

  livinglab->requete("SELECT * FROM chambre");
}
//! [constructor]
