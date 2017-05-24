/**
 * \file main.cpp
 * \brief  Fonction main
 *         Ouvre un objet de type Traitement
 * \version 1
 * \date 24 mai 2017
 * \author {Jeremy B. & Théo D.}
 */

#include <QCoreApplication>
#include "Traitement.hpp"

/**
 * \fn main
 * \brief  Crée une application console QT
 *         Crée un objet Traitement
 *
 * \return appli.exec() permet de boucler le programme
 */
int main(int argc, char *argv[]) {
  QCoreApplication appli(argc, argv);

  Traitement IT_processing;

  return appli.exec();
}
