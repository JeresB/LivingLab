#ifndef CHAMBRE_H
#define CHAMBRE_H

#include <QObject>
#include <QWebSocket>

class Chambre : public QObject {
    Q_OBJECT
public:
    explicit Chambre(const QUrl &url, int id_chambre, QObject *parent = Q_NULLPTR);

    // GETTERS
    int getID();
    int getCO2_M();
    int getCO2_H();
    int getTemp_Max();
    int getTemp_Min();
    int getHum_Max();
    int getHum_Min();
    QString getFour();

    // SETTERS
    int setAllSeuil(int hmin, int hmax, int tmax, int tmin, int cm, int ch, QString f);

Q_SIGNALS:
    void closed();
    void sendTextToProcess(QDateTime, int, bool, float, float, bool, int);

private Q_SLOTS:
    void onConnected();

public Q_SLOTS:
  void onTextMessageReceived(QString message);

private:
    QWebSocket m_Chambre;
    QUrl c_url;
    int c_id_chambre;

    int humiditymin     = 0;
    int humiditymax     = 0;
    int temperaturemin  = 0;
    int temperaturemax  = 0;
    int co2moyen        = 0;
    int co2haut         = 0;
    QString four        = "";
};

#endif // CHAMBRE_H
