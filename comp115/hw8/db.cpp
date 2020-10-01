#include <cstdlib>
#include "db.h"
#include <iostream>

PGconn* connect_to_database(const char* host, const char* dbname, const char* user, const char* password)
{
	char cnxn_info[100];
	sprintf(cnxn_info, "host = %s dbname = %s user = %s password = %s", host, dbname, user, password);
	PGconn* cnxn = PQconnectdb(cnxn_info);
	if (PQstatus(cnxn) != CONNECTION_OK) {
		std::cerr << "Connection failed.\n";
		PQfinish(cnxn);
		exit(1);
	}
	return cnxn;
}

void disconnect_from_database(PGconn* connection)
{
	PQfinish(connection);
	return;
}

PGresult* query(PGconn* connection, const char* sql, int n_params, const char** params)
{	
	PGresult* result = PQexecParams(connection, sql, n_params, NULL, params, NULL, NULL, 0);
	ExecStatusType status = PQresultStatus(result);
	if (status == PGRES_FATAL_ERROR) {
		PQclear(result);
		return NULL;
	} else if (status == PGRES_TUPLES_OK){
		return result;
	} else{
		std::cerr << "Query Error.\n";
		PQclear(result);
		return NULL;
	}
}

int update(PGconn* connection, const char* sql, int n_params, const char** params)
{
	PGresult* result = PQexecParams(connection, sql, n_params, NULL, params, NULL, NULL, 0);
	ExecStatusType status = PQresultStatus(result);
	
	if (status == PGRES_FATAL_ERROR) {
                PQclear(result);
                return -1;
        } else if (status == PGRES_COMMAND_OK) {
                char *num = PQcmdTuples(result);
		PQclear(result);
                return atoi(num);
        } else {
                std::cerr << "Update Error.\n";
                PQclear(result);
                return -2;
        }
}

const char* field(PGresult* result, int row, int column)
{
	if (PQgetisnull(result, row, column) == 1) {
		return NULL;
	} else {
		return PQgetvalue(result, row, column);
	}
}

void end_query(PGresult* result)
{
	PQclear(result);
}
