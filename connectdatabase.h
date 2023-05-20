#ifndef CONNECTDATABASE_H
#define CONNECTDATABASE_H

#include <QObject>

class ConnectDatabase : public QObject
{
    Q_OBJECT
public:
    explicit ConnectDatabase(QObject *parent = nullptr);

signals:

    void databaseConnected(bool connected);

    public slots:
        void checkDatabaseConnection();

    private:
        bool connectToDatabase(const QString &host, int port, const QString &databaseName,
                               const QString &userName, const QString &password);
    };

    #endif // CONNECTDATABASE_H
