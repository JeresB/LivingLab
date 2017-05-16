#include <QCoreApplication>
#include "websocket.hpp"
#include "database.hpp"

int main(int argc, char *argv[]) {
  QCoreApplication appli(argc, argv);

  WebSocket chambre1(QUrl(QStringLiteral("ws://192.168.199.30:1000")));

  Database *livinglab = new Database;

  livinglab::requete("SELECT * FROM chambre");

  return appli.exec();
}
