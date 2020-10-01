#include <cstdlib>
#include <cstdio>
#include <libpq-fe.h>
#include <cstring>
#include "msg.h"
#include "db.h"
#include <iostream>
static const char* INSERT_MEMBER =
    "insert into member(name, birth_date) values($1, $2)";

static const char* INSERT_MESSAGE =
    "insert into message(message_date, message_text) values($1, $2)";

static const char* INSERT_ROUTING =
    "select store_routing($1, $2, $3)";

static const char* PK_VALUE =
    "select lastval()";

static const char* BIRTH_DATE_QUERY =
    "select birth_date from member where name = $1";

static const char* SENDER_AND_RECEIVER_QUERY = ""
    "select distinct f.name, t.name\n"
    "from member f join routing r on f.member_id = r.from_member_id\n"
    "              join member t on r.to_member_id = t.member_id\n"
    "              join message m on r.message_id = m.message_id\n"
    "where m.message_date = $1\n"
    "order by f.name, t.name";


// API

int add_member(PGconn* connection, const char* name, const char* birth_date)
{
    // Run INSERT_MEMBER
    // Run PK_VALUE
    // Return PK_VALUE output (the member_id just inserted)
    	const char* params[] = {name, birth_date};
	update(connection, INSERT_MEMBER, 2, params);
	PGresult* result = query(connection, PK_VALUE, 0, NULL);
	int ret = atoi(field(result, 0, 0));
	end_query(result);
	return ret;
}

int add_message(PGconn* connection, const char* message_date, const char* message_text)
{
    // Run INSERT_MESSAGE
    // Run PK_VALUE
    // Return PK_VALUE output (the message_id just inserted)
    	const char* params[] = {message_date, message_text};
        update(connection, INSERT_MESSAGE, 2, params);
        PGresult* result = query(connection, PK_VALUE, 0, NULL);
	int ret =  atoi(field(result, 0, 0));
	end_query(result);
	return ret;
}

int add_routing(PGconn* connection, const char* from_member_id, const char* to_member_id, const char* message_ids)
{
    // Run INSERT_ROUTING
    // Return the value returned by the insert_routing stored procedure
    	const char* params[] = {from_member_id, to_member_id, message_ids};
        PGresult* result = query(connection, INSERT_ROUTING, 3, params);
	int ret = PQntuples(result);
	end_query(result);
	return ret;
}

int birth_date(PGconn* connection, const char* name, char* buffer)
{
    // Run BIRTH_DATE_QUERY
	const char* params[] = {name};
    	PGresult* result = query(connection, BIRTH_DATE_QUERY, 1, params);
	if (PQntuples(result) != 0){
		sprintf(buffer, "%s", field(result, 0, 0));
		end_query(result);
		return 1;
	} else {
		end_query(result);
		return 0;
	}
}

int senders_and_receivers(PGconn* connection, const char* date, int max_results, char* buffer[])
{
    // Run SENDER_AND_RECEIVER_QUERY
	const char* params[] = {date};
        PGresult* result = query(connection, SENDER_AND_RECEIVER_QUERY, 1, params);
	int num = PQntuples(result);
	if (num > max_results){
		std::cerr << "Too many results";
		end_query(result);
		exit(1);
	} else {
		for (int i = 0; i < num; i++) {
			sprintf(buffer[i], "%s,%s", field(result, i, 0), field(result, i, 1));
		}
		end_query(result);
	}
	return num;
}
