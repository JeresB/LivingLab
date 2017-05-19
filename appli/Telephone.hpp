#ifndef TELEPHONE_H
#define TELEPHONE_H

#include <QObject>
#include <QWebSocket>

class Telephone : public QObject {
    Q_OBJECT
public:
    explicit Telephone(const QUrl &url, QString numero, QObject *parent = Q_NULLPTR);

    // GETTERS
    QString getID();
    // SETTERS
    void setAllSeuil(QString pas);

Q_SIGNALS:
    void sendTextToProcess(QString, int, QString, QString);

private Q_SLOTS:
    void closed(){};
    void onConnected();

public Q_SLOTS:
  void onTextMessageReceived(QString message);

private:
    QWebSocket m_Telephone;
    QUrl m_url;
    QString m_numero;
    QString t_pas;
};

#endif // Chambre_H
