#include <cassert>
#include <algorithm>
#include "QueryProcessor.h"
#include "Table.h"
#include "Index.h"
#include "Iterator.h"
#include "Row.h"
#include "ColumnSelector.h"
#include "Operators.h"
#include "util.h"
#include "RowCompare.h"
#include <iostream>

//----------------------------------------------------------------------

// TableIterator 

unsigned TableIterator::n_columns() 
{
    return _table->columns().size();
}

void TableIterator::open() 
{
    _input = _table->rows().begin();
    _end = _table->rows().end();
}

Row* TableIterator::next() 
{
    if (_input == _end) {
	return NULL;
    }
    return *_input++;
}

void TableIterator::close() {
}

TableIterator::TableIterator(Table* table)
    : _table(table)
{
}

//----------------------------------------------------------------------

// IndexScan

unsigned IndexScan::n_columns()
{
    return _index->n_columns();
}

void IndexScan::open()
{
    _input = _index->begin();
    _end = _index->end();
}

Row* IndexScan::next()
{
    if (_input == _end) {
        return NULL;
    }
    return NULL;
}

void IndexScan::close()
{
}

IndexScan::IndexScan(Index* index, Row* lo, Row* hi)
    : _index(index),
      _lo(lo),
      _hi(hi == NULL ? lo : hi)
{}

//----------------------------------------------------------------------

// Select

unsigned Select::n_columns()
{
    return _input->n_columns();
}

void Select::open()
{
     _input->open();
}

Row* Select::next()
{
    Row* row = _input->next();
    if (row == NULL) {
	return NULL;
    } else if (_predicate(row)){
	return row;
    } else {
	return NULL; 
    }   
}

void Select::close()
{
    _input->close();
}

Select::Select(Iterator* input, RowPredicate predicate)
    : _input(input),
      _predicate(predicate)
{
}

Select::~Select()
{
    delete _input;
}

//----------------------------------------------------------------------

// Project

unsigned Project::n_columns()
{
    return _column_selector.n_selected();
}

void Project::open()
{
    _input->open();
}

Row* Project::next()
{
    Row* projected = NULL;
    Row* row = _input->next();
    if (row) {
        projected = new Row();
        for (unsigned i = 0; i < _column_selector.n_selected(); i++) {
            projected->append(row->at(_column_selector.selected(i)));
        }
        Row::reclaim(row);
    }
    return projected;
}

void Project::close()
{
    _input->close();
}

Project::Project(Iterator* input, const initializer_list<unsigned>& columns)
    : _input(input),
      _column_selector(input->n_columns(), columns)
{}

Project::~Project()
{
    delete _input;
}

//----------------------------------------------------------------------

// NestedLoopsJoin

unsigned NestedLoopsJoin::n_columns()
{
    return _left->n_columns() + _right->n_columns() - _left_join_columns.n_selected(); 
}

void NestedLoopsJoin::open()
{
    _left->open();
    _right->open();
}

Row* NestedLoopsJoin::next()
{
    _left_row = _left->next();
    Row* _right_row = _right->next(); 
    while (_left_row != NULL && _right_row != NULL) {
        if (_right_row == NULL) {
    	    _left_row = _left->next();
	    if (_left_row != NULL) {
		_right->close();	
		_right->open();	
		_right_row = _right->next();
	    }
        }
	else if (_left_row->at(_left_join_columns.selected(0)) ==
	_right_row->at(_right_join_columns.selected(0))) {
	    return NULL;
	}
    }
    return NULL;
}

void NestedLoopsJoin::close()
{
    _left->close();
    _right->close();
}

NestedLoopsJoin::NestedLoopsJoin(Iterator* left,
                                 const initializer_list<unsigned>& left_join_columns,
                                 Iterator* right,
                                 const initializer_list<unsigned>& right_join_columns)
    : _left(left),
      _right(right),
      _left_join_columns(left->n_columns(), left_join_columns),
      _right_join_columns(right->n_columns(), right_join_columns),
      _left_row(NULL)
{
    assert(_left_join_columns.n_selected() == _right_join_columns.n_selected());
}

NestedLoopsJoin::~NestedLoopsJoin()
{
    delete _left;
    delete _right;
    Row::reclaim(_left_row);
}

//----------------------------------------------------------------------

// Sort

unsigned Sort::n_columns() 
{
    return _input->n_columns();
}

void Sort::open() 
{
    _input->open();
    Row* row = _input->next();
    _sorted = vector<Row*>();

    while(row != NULL) {
	_sorted.emplace_back(row);
	row = _input->next();
    }
    sort(_sorted.begin(), _sorted.end(), RowCompare(_sort_columns));
    _sorted_iterator = _sorted.begin();
}

Row* Sort::next() 
{
    if (_sorted_iterator == _sorted.end()) {
        return NULL;
    }
    return *_sorted_iterator++;
}

void Sort::close() 
{
    _input->close();
}

Sort::Sort(Iterator* input, const initializer_list<unsigned>& sort_columns)
    : _input(input),
      _sort_columns(sort_columns)
{}

Sort::~Sort()
{
    delete _input;
}

//----------------------------------------------------------------------

// Unique

unsigned Unique::n_columns()
{
    return _input->n_columns();
}

void Unique::open() 
{
    _input->open();
}

Row* Unique::next()
{
    _current = _input->next();
    if (_current == NULL)
	return NULL;
    else if (_current == _last_unique) {
        _current = _input->next();
	return NULL;
    } else {
	_last_unique = _current;
	return _current;
    }
}

void Unique::close() 
{
    _input->close();
}

Unique::Unique(Iterator* input)
    : _input(input),
      _last_unique(NULL),
      _current(NULL)
{}

Unique::~Unique()
{
    delete _input;
}
