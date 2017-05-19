#include <QCoreApplication>
#include "Traitement.hpp"

int main(int argc, char *argv[]) {
  QCoreApplication appli(argc, argv);

  Traitement IT_processing;

  return appli.exec();
}
