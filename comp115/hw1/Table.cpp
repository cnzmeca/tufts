#include <cstring>
#include "Database.h"
#include <iostream>

using namespace std;

const string &Table::name() const
{
    return _name;
}

const ColumnNames &Table::columns() const
{
    return _columns;
}

const RowSet& Table::rows()
{
    return _rows; 
}

bool Table::add(Row* row)
{
    if (!has(row)){
	_rows.insert(row);
	return true;
    }
    return false;
}

bool Table::remove(Row* row)
{
    if (has(row)){
        RowSet::iterator i = _rows.find(row);
        delete *i;
        _rows.erase(i);
        return true;
    }
    return false;
}

bool Table::has(Row* row)
{
    if (_columns.size() != row->_row.size())
        throw TableException("Wrong number of elements");
    if (_rows.find(row) != _rows.end()){
        return true;
    }
    return false;
}

Table::Table(const string &name, const ColumnNames &columns)
    : _name(name),
      _columns(columns)
{
    if (_columns.empty())
	throw TableException("No columns");
    
    bool cond = false;
    for (unsigned i = 0; i < columns.size(); i++) {
        for (unsigned j = i + 1; j < columns.size(); j++) {
	    if (columns[i] == columns[j]) {
		cond = true;
            }
        }
    }

    if (cond)
	throw TableException("Duplicate columns");
}

Table::~Table()
{
    for (RowSet::iterator i = _rows.begin(); i != _rows.end(); i++) {
	delete *i;
    }
}
