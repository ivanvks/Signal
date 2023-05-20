#include "connectdatabase.h"
#include <QSettings>
#include <QtSql/QSqlDatabase>
ConnectDatabase::ConnectDatabase(QObject *parent)
    : QObject{parent}
{

}
void ConnectDatabase::checkDatabaseConnection()
{
    QSettings settings("config.conf", QSettings::IniFormat);

    emit databaseConnected(
                connectToDatabase(
                    settings.value("DataBase/host").toString(),
                    settings.value("DataBase/port").toInt(),
                    settings.value("DataBase/name").toString(),
                    settings.value("DataBase/user").toString(),
                    settings.value("DataBase/pass").toString()
                    ));
}

bool ConnectDatabase::connectToDatabase(const QString &host, int port, const QString &databaseName,
                                       const QString &userName, const QString &password)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(databaseName);
    db.setUserName(userName);
    db.setPassword(password);

    bool connected = db.open();

    return connected;

}
