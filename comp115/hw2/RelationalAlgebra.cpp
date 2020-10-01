#include <sstream>
#include <cstring>
#include "RelationalAlgebra.h"
#include "Database.h"
#include "unittest.h"
#include <iostream>

bool compatible(Table *r, Table *s)
{
	ColumnNames rcols = r->columns();
	ColumnNames scols = s->columns();

	return rcols.size() == scols.size();
}

Table *onion(Table *r, Table *s)
{
	if (!compatible(r, s))
		throw UnionIncompatibilityException("Not compatible");	

	RowSet rrows = r->rows();	
	RowSet srows = s->rows();

	Table *ret = new Table(r->name() + " ∪ " + s->name(), r->columns());

	for (RowSet::iterator i = rrows.begin(); i != rrows.end(); i++){
		if(!ret->has(*i))
			ret->add(*i);
	}
	for (RowSet::iterator i = srows.begin(); i != srows.end(); i++){
                if(!ret->has(*i))
                        ret->add(*i);
        }
	return ret;
}

Table *intersect(Table *r, Table *s)
{
	if (!compatible(r, s))
        	throw UnionIncompatibilityException("Not compatible");
	
	RowSet rrows = r->rows();
        RowSet srows = s->rows();

        Table *ret = new Table(r->name() + " ∩ " + s->name(), r->columns());

        for (RowSet::iterator i = rrows.begin(); i != rrows.end(); i++){
                if(s->has(*i))
                        ret->add(*i);
        }

        return ret;

}

Table *diff(Table *r, Table *s)
{
	if (!compatible(r, s))
                throw UnionIncompatibilityException("Not compatible");
	
	RowSet rrows = r->rows();
        RowSet srows = s->rows();

	Table *ret = new Table(r->name() + " ∩ " + s->name(), r->columns());

	for (RowSet::iterator i = rrows.begin(); i != rrows.end(); i++){
                if(!s->has(*i))
                        ret->add(*i);
        }

        return ret;
}

Table *product(Table *r, Table *s)
{
	ColumnNames rcols = r->columns();
        ColumnNames scols = s->columns();
	ColumnNames cols = ColumnNames();	
	
	for(ColumnNames::iterator i = rcols.begin(); i != rcols.end(); ++i) {
		for(ColumnNames::iterator j = scols.begin(); j != scols.end(); ++j) {
			if (*i == *j)
				throw TableException("Duplicate columns");
			cols.push_back(*i + *j);
		}
	}

	Table *ret = new Table(r->name() + " x " + s->name(), cols);
	
	RowSet rrows = r->rows();
	RowSet srows = s->rows();

	for(RowSet::iterator i = rrows.begin(); i != rrows.end(); ++i) {
		for(RowSet::iterator j = srows.begin(); j != srows.end(); ++j) {
			Row *tmp = new Row(ret);
			for(unsigned k = 0; k < (*i)->size(); k++)
				tmp->append((*i)->at(k));
			for(unsigned k = 0; k < (*j)->size(); k++)
				tmp->append((*j)->at(k));
			ret->add(tmp);
		}
        }	
	return ret;
}

Table *rename(Table *r, const NameMap &name_map)
{
	ColumnNames rcols = r->columns();
	ColumnNames cols = ColumnNames();
	
	for(ColumnNames::iterator i = rcols.begin(); i != rcols.end(); ++i) {
		try{
			cols.push_back(name_map.at(*i));
		} catch(out_of_range) {
			throw TableException("Faulty map");
		}			
	}

	Table *ret = new Table(r->name(), cols);

	RowSet rrows = r->rows();
	for(RowSet::iterator i = rrows.begin(); i != rrows.end(); ++i){
		ret->add(*i);
	}

	return ret;
}

Table *select(Table *r, RowPredicate predicate)
{
	Table *ret = new Table(r->name(), r->columns());

	RowSet rrows = r->rows();
        for(RowSet::iterator i = rrows.begin(); i != rrows.end(); ++i){
		if (predicate(*i))
			ret->add(*i); 
	}
	return ret;
}

Table *project(Table *r, const ColumnNames &columns)
{	
	Table *ret = new Table(r->name(), columns);
	ColumnNames rcols = r->columns();
	for(unsigned i = 0; i < columns.size(); i++){
		if (rcols.position(columns[i]) == -1) {
			throw TableException("Unknown Column");
		}
	}
	
	RowSet rrows = r->rows();
	for(RowSet::iterator i = rrows.begin(); i != rrows.end(); ++i){
        	Row *tmp = new Row(ret);
		for(unsigned j = 0; j < columns.size(); j++){
			tmp->append((*i)->value(columns[j]));
		}
		ret->add(tmp);
	}

   	return ret;
}

Table *join(Table *r, Table *s)
{
	ColumnNames rcols = r->columns();
        ColumnNames scols = s->columns();
        ColumnNames cols = ColumnNames();
	ColumnNames joins = ColumnNames();

	for(ColumnNames::iterator i = rcols.begin(); i != rcols.end(); ++i) {
		if (scols.position(*i) != -1 && joins.position(*i) == -1)
			joins.push_back(*i);
		if (cols.position(*i) == -1)
			cols.push_back(*i);
	}

	for(ColumnNames::iterator i = scols.begin(); i != scols.end(); ++i) {
                if (rcols.position(*i) != -1 && joins.position(*i) == -1)
                        joins.push_back(*i);
                if (cols.position(*i) == -1)
                        cols.push_back(*i);
        }


	if (joins.empty())
		throw JoinException("No join column");

	Table *ret = new Table(r->name() + " ⨝ " + s->name(), cols);

	RowSet rrows = r->rows();
        RowSet srows = s->rows();
	
	for(RowSet::iterator i = rrows.begin(); i != rrows.end(); ++i){
		for(RowSet::iterator j = srows.begin(); j != srows.end(); ++j){
			bool joinable = true;
			for(ColumnNames::iterator k = joins.begin(); k != joins.end(); ++k) {
				if ((*i)->value(*k) != (*j)->value(*k))
					joinable = false;
			}
			if (joinable) {
				Row *tmp = new Row(ret);
				for(ColumnNames::iterator k = cols.begin(); k != cols.end(); ++k) {
					try {
						tmp->append((*i)->value(*k));
					} catch (RowException) {
						tmp->append((*j)->value(*k));
					}
				}
                		ret->add(tmp);
			}
		}
	}
	return ret;	
}
