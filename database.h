#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

#define DATABASE_NAME "diapo"
#define CONNECT_TYPE "QODBC"

class Database
{
public:
    Database();
    bool OpenDataBase();
    void closeDataBase();

private:
    QSqlDatabase mydb;
};

#endif // DATABASE_H
