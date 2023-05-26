#include "database.h"

Database::Database()
{

}
bool Database::OpenDataBase()
{
    mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    mydb.setDatabaseName(DATABASE_NAME);
    if(mydb.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Database::closeDataBase()
{
    mydb.close();
}
