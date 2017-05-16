#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include <QObject>
#include "Database.hpp"

class Traitement : public QObject {
  Q_OBJECT
public:
    explicit Traitement(QObject *parent = Q_NULLPTR);

Q_SIGNALS:

private Q_SLOTS:

private:

};

#endif // TRAITEMENT_H
