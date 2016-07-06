#include "Database.h"

Database::Database(string command)
{
    conn = PQconnectdb(command.c_str());

    if (PQstatus(conn) == CONNECTION_BAD)
    {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1); //throw aquí? //mejora tu interface, debes limpiar y arrojar una excepción
    }
}

Database::~Database()
{
    PQclear(res);
    PQfinish(conn);
}

void Database::foo()
{
    res = PQexec(conn, "SELECT * from Lenguajes;");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {

        printf("No data retrieved\n");
        PQclear(res);
        exit(1);
    }

    int rows = PQntuples(res);
    int cols = PQnfields(res);
    int cols2 = PQnparams(res);

    printf("cols: %d, cols2: %d\n\n", cols, cols2);

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
            printf("%s ", PQgetvalue(res, i, j));
        printf("\n");
    }
}
