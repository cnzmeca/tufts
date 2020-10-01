#include <sstream>
#include <cstring>
#include "RelationalAlgebra.h"
#include "Database.h"
#include "unittest.h"

static void check_union_compatible(Table *r, Table *s)
{
    if (r->columns().size() != s->columns().size()) {
        throw UnionIncompatibilityException("Incompatible tables");
    }
}

static Row* copy_for(const Row *row, Table *table)
{
    unsigned long n_columns = row->table()->columns().size();
    if (n_columns != table->columns().size()) {
        throw UnionIncompatibilityException("Incompatible row and table");
    }
    Row* copy = new Row(table);
    for (unsigned i = 0; i < n_columns; i++) {
        copy->append(row->at(i));
    }
    return copy;
}

static bool match(Row *r_row, const vector<unsigned int> &join_r_column_positions,
                  Row *s_row, const vector<unsigned int> &join_s_column_positions)
{
    unsigned long n = join_r_column_positions.size();
    for (unsigned long i = 0; i < n; i++) {
        int c = strcmp(r_row->at(join_r_column_positions[i]).c_str(),
                       s_row->at(join_s_column_positions[i]).c_str());
        if (c != 0) {
            return false;
        }
    }
    return true;
}

Table *onion(Table *r, Table *s)
{
    check_union_compatible(r, s);
    Table* new_table = Database::new_table(Database::new_table_name(), r->columns());
    for (const Row* row : r->rows()) {
        bool added = new_table->add(copy_for(row, new_table));
        assert(added);
    }
    for (const Row* row : s->rows()) {
        Row *copy = copy_for(row, new_table);
        bool added = new_table->add(copy);
        if (!added) {
            delete copy;
        }
    }
    return new_table;
}

Table *intersect(Table *r, Table *s)
{
    check_union_compatible(r, s);
    Table *new_table = Database::new_table(Database::new_table_name(), r->columns());
    for (Row* row : r->rows()) {
        if (s->has(row)) {
            bool added = new_table->add(copy_for(row, new_table));
            assert(added);
        }
    }
    return new_table;
}

Table *diff(Table *r, Table *s)
{
    check_union_compatible(r, s);
    Table* new_table = Database::new_table(Database::new_table_name(), r->columns());
    for (const Row* row : r->rows()) {
        bool added = new_table->add(copy_for(row, new_table));
        assert(added);
    }
    for (Row* row : s->rows()) {
        new_table->remove(row);
    }
    return new_table;
}

Table *product(Table *r, Table *s)
{
    ColumnNames rxs_columns(r->columns());
    for (const string& column : s->columns()) {
        rxs_columns.emplace_back(column);
    }
    Table* new_table = Database::new_table(Database::new_table_name(), rxs_columns);
    unsigned long nr = r->columns().size();
    unsigned long ns = s->columns().size();
    for (const Row* r_row : r->rows()) {
        for (const Row* s_row : s->rows()) {
            Row *rxs_row = new Row(new_table);
            for (unsigned i = 0; i < nr; i++) {
                rxs_row->append(r_row->at(i));
            }
            for (unsigned i = 0; i < ns; i++) {
                rxs_row->append(s_row->at(i));
            }
            bool added = new_table->add(rxs_row);
            assert(added);
        }
    }
    return new_table;
}

Table *rename(Table *r, const NameMap &name_map)
{
    // Get the columns being renamed in the name_map
    set<string> old_names;
    for (pair<string, string> kv : name_map) {
        old_names.insert(kv.first);
    }
    // Get the current column names as a set
    set<string> current_names;
    for (const string &name : r->columns()) {
        current_names.insert(name);
    }
    // Check names
    if (old_names != current_names) {
        throw TableException("Each column of the table, and no others, must be renamed.");
    }
    ColumnNames renamedColumns;
    for (const string& column : r->columns()) {
        auto i = name_map.find(column);
        if (i == name_map.end()) {
            renamedColumns.emplace_back(column);
        } else {
            renamedColumns.emplace_back(i->second);
        }
    }
    Table* new_table = Database::new_table(Database::new_table_name(), renamedColumns);
    for (const Row* row : r->rows()) {
        bool added = new_table->add(copy_for(row, new_table));
        assert(added);
    }
    return new_table;
}

Table *select(Table *r, RowPredicate predicate)
{
    Table *new_table = Database::new_table(Database::new_table_name(), r->columns());
    for (Row* row : r->rows()) {
        if (predicate(row)) {
            bool added = new_table->add(copy_for(row, new_table));
            assert(added);
        }
    }
    return new_table;
}

Table *project(Table *r, const ColumnNames &columns)
{
    vector<unsigned> r_column_positions;
    for (const string& column : columns) {
        int r_position = r->columns().position(column);
        if (r_position < 0) {
            throw TableException("Unknown column");
        }
        r_column_positions.emplace_back(r_position);
    }
    unsigned long n = columns.size();
    Table* new_table = Database::new_table(Database::new_table_name(), columns);
    for (Row *row : r->rows()) {
        Row *projected = new Row(new_table);
        for (unsigned i = 0; i < n; i++) {
            projected->append(row->at(r_column_positions[i]));
        }
        bool added = new_table->add(projected);
        if (!added) {
            delete projected;
        }
    }
    return new_table;
}

Table *join(Table *r, Table *s)
{
    unsigned long nr = r->columns().size();
    unsigned long ns = s->columns().size();
    vector<unsigned int> join_r_column_positions;
    vector<unsigned int> join_s_column_positions;
    vector<unsigned int> s_only_column_positions;
    ColumnNames rs_columns(r->columns());
    for (unsigned long is = 0; is < ns; is++) {
        const string& s_column = s->columns().at(is);
        bool duplicate = false;
        for (unsigned long ir = 0; !duplicate && ir < nr; ir++) {
            if (r->columns().at(ir) == s_column) {
                join_r_column_positions.emplace_back(ir);
                join_s_column_positions.emplace_back(is);
                duplicate = true;
            }
        }
        if (!duplicate) {
            s_only_column_positions.emplace_back(is);
            rs_columns.emplace_back(s_column);
        }
    }
    if (join_r_column_positions.empty()) {
        throw JoinException("No join columns");
    }
    unsigned long nso = s_only_column_positions.size();
    Table* new_table = Database::new_table(Database::new_table_name(), rs_columns);
    for (Row *r_row : r->rows()) {
        for (Row *s_row : s->rows()) {
            if (match(r_row, join_r_column_positions, s_row, join_s_column_positions)) {
                Row *join_row = new Row(new_table);
                for (unsigned i = 0; i < nr; i++) {
                    join_row->append(r_row->at(i));
                }
                for (unsigned long i = 0; i < nso; i++) {
                    join_row->append(s_row->at(s_only_column_positions[i]));
                }
                bool added = new_table->add(join_row);
                assert(added);
            }
        }
    }
    return new_table;
}
