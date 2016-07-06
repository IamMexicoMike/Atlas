#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <libpq-fe.h>

using namespace std;

class Database
{

    public:
        Database(string command);
        ~Database();
        void foo();
        PGconn* conn;
        PGresult* res;

    protected:

};

#endif // DATABASE_H
