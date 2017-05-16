#include <QCoreApplication>
#include "Websocket.hpp"
#include "Traitement.hpp"

int main(int argc, char *argv[]) {
  QCoreApplication appli(argc, argv);

  WebSocket chambre1(QUrl(QStringLiteral("ws://192.168.199.30:1000")));

  Traitement IT_processing;

  return appli.exec();
}
