#include "Database.h"
#include "util.h"

bool Row::operator==(const Row &that) const
{
    return equal(_row.begin(), _row.end(), that._row.begin());
}

bool Row::operator!=(const Row& row) const
{
    return !operator==(row);
}

const Table *Row::table() const
{
    return _table;
}

const string &Row::value(const string &column) const
{
    int index = _table->columns().position(column);
    if (index >= 0)
    	return _row[_table->columns().position(column)];
    throw RowException("Column not in table");
}

void Row::append(const string &value)
{
    _row.push_back(value);
}

Row::Row(const Table *table)
        : _table(table)
{
    _row = vector<string>(0);
}

Row::~Row()
{
}
