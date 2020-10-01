#include "Database.h"

/*
bool Row::operator==(const Row &that) const
{
    unsigned long n = _table->columns().size();
    for (unsigned long i = 0; i < n; i++) {
        if (this->at(i) != that.at(i)) {
            return false;
        }
    }
    return true;
}
bool Row::operator!=(const Row& row) const
{
    return !operator==(row);
}
 */

const Table *Row::table() const
{
    return _table;
}

const string &Row::value(const string &column) const
{
    const ColumnNames &columns = _table->columns();
    unsigned long n = columns.size();
    for (unsigned i = 0; i < n; i++) {
        if (columns.at(i) == column) {
            return _values.at(i);
        }
    }
    throw RowException("Unknown column");
}

const string &Row::at(unsigned i) const
{
    return _values.at(i);
}

void Row::append(const string &value)
{
    _values.emplace_back(value);
}

unsigned long Row::size() const
{
    return _values.size();
}

Row::Row(const Table *table)
        : _table(table)
{}

Row::~Row()
{
    _values.clear();
}
