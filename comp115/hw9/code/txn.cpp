#include <stdlib.h>
#include <stdio.h>
#include <libpq-fe.h>
#include <sys/param.h>
#include "txn.h"
#include "db.h"
#include <iostream>

const int BALANCE_FAILED = INT_MIN;
const int AUDIT_FAILED = INT_MIN;

static int update_balance(PGconn* connection, int account_id, int amount)
{
    // Run SQL to increment balance by amount.
	char command[100];
	sprintf(command, "update account set balance = balance + %d where account_id = %d", amount, account_id);
	PGresult* result = PQexec(connection, command);
	if (PQresultStatus(result) == PGRES_COMMAND_OK) {
		PQclear(result);
        	return 1;
	} else {
		PQclear(result);
                return 0;
        }	
}

int read_balance(PGconn* connection, int account_id)
{
    // Run SQL to read balance of account.
    	char command[100];
        sprintf(command, "select balance from account where account_id = %d", account_id);        
        PGresult* result = PQexec(connection, command);
	if (PQresultStatus(result) == PGRES_TUPLES_OK) {
		int ret = atoi(field(result, 0, 0));
		PQclear(result);
		return ret;
	} else {
		PQclear(result);
		return BALANCE_FAILED;
	}
}

int transfer(PGconn* connection, int from_id, int to_id, int amount)
{
    // Update smaller account id first to avoid deadlock.
    int ok = 1;
    if (from_id < to_id) {
        ok = ok && update_balance(connection, from_id, -amount);
        ok = ok && update_balance(connection, to_id, amount);
    } else {
        ok = ok && update_balance(connection, to_id, amount);
        ok = ok && update_balance(connection, from_id, -amount);
    }
    return ok;
}

int audit(PGconn* connection)
{
    	PGresult* result = PQexec(connection, "select sum(balance) from account");
	if (PQresultStatus(result) == PGRES_TUPLES_OK) {
		int ret = atoi(field(result, 0, 0));
		PQclear(result);
        	return ret;
	} else {
		PQclear(result);
                return AUDIT_FAILED;
        }
}
