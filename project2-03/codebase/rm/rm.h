
#ifndef _rm_h_
#define _rm_h_

#include <string>
#include <vector>

#include "../rbf/rbfm.h"

using namespace std;

#define TABLE_FILE_EXTENSION ".tbl"

#define TABLES_TABLE_NAME           "Tables"
#define TABLES_TABLE_ID             1

// Format for Tables table:
// (table-id:int, table-name:varchar(50), file-name:varchar(50), system:int)
// system will be 1 if the table is a system table, 0 otherwise

#define TABLES_COL_TABLE_ID         "table-id"
#define TABLES_COL_TABLE_NAME       "table-name"
#define TABLES_COL_FILE_NAME        "file-name"
//#define TABLES_COL_SYSTEM           "system"
#define TABLES_COL_TABLE_NAME_SIZE  50
#define TABLES_COL_FILE_NAME_SIZE   50

// 1 null byte, 2 integer and 2 varchars
#define TABLES_RECORD_DATA_SIZE 1 + 4 * INT_SIZE + TABLES_COL_TABLE_NAME_SIZE + TABLES_COL_FILE_NAME_SIZE

#define COLUMNS_TABLE_NAME           "Columns"
#define COLUMNS_TABLE_ID             2

#define COLUMNS_COL_TABLE_ID         "table-id"
#define COLUMNS_COL_COLUMN_NAME      "column-name"
#define COLUMNS_COL_COLUMN_TYPE      "column-type"
#define COLUMNS_COL_COLUMN_LENGTH    "column-length"
#define COLUMNS_COL_COLUMN_POSITION  "column-position"
#define COLUMNS_COL_COLUMN_NAME_SIZE 50

// 1 null byte, 4 integer fields and a varchar
#define COLUMNS_RECORD_DATA_SIZE 1 + 5 * INT_SIZE + COLUMNS_COL_COLUMN_NAME_SIZE

# define RM_EOF (-1)  // end of a scan operator

#define RM_CANNOT_MOD_SYS_TBL 1
#define RM_NULL_COLUMN        2

typedef struct IndexedAttr
{
    int32_t pos;
    Attribute attr;
    bool operator < (const IndexedAttr& t) const
    {
        return (pos < t.pos);
    }
} IndexedAttr;

// RM_ScanIterator is an iteratr to go through tuples
class RM_ScanIterator {
public:
    RM_ScanIterator() {};
    ~RM_ScanIterator() {};

    // "data" follows the same format as RelationManager::insertTuple()
    RC getNextTuple(RID &rid, void *data);
    RC close();

    friend class RelationManager;
private:
    RBFM_ScanIterator rbfm_iter;
    FileHandle fileHandle;
};


// Relation Manager
class RelationManager
{
public:
    static RelationManager* instance();

    RC createCatalog();

    RC deleteCatalog();

    RC createTable(const string &tableName, const vector<Attribute> &attrs);

    RC deleteTable(const string &tableName);

    RC getAttributes(const string &tableName, vector<Attribute> &attrs);

    RC insertTuple(const string &tableName, const void *data, RID &rid);

    RC deleteTuple(const string &tableName, const RID &rid);

    RC updateTuple(const string &tableName, const void *data, const RID &rid);

    RC readTuple(const string &tableName, const RID &rid, void *data);

    // Print a tuple that is passed to this utility method.
    // The format is the same as printRecord().
    RC printTuple(const vector<Attribute> &attrs, const void *data);

    RC readAttribute(const string &tableName, const RID &rid, const string &attributeName, void *data);

    // Scan returns an iterator to allow the caller to go through the results one by one.
    // Do not store entire results in the scan iterator.
    RC scan(const string &tableName,
            const string &conditionAttribute,
            const CompOp compOp,                  // comparison type such as "<" and "="
            const void *value,                    // used in the comparison
            const vector<string> &attributeNames, // a list of projected attributes
            RM_ScanIterator &rm_ScanIterator);


protected:
    RelationManager();
    ~RelationManager();

private:
    static RelationManager *_rm;
    vector<Attribute> tableDescriptor;
    vector<Attribute> columnDescriptor;

    // Given a table ID and recordDescriptor, creates entries in Column table
    RC insertColumns(int32_t id, const vector<Attribute> &recordDescriptor);
    // Given table ID, system flag, and table name, creates entry in Table table
    RC insertTable(int32_t id, int32_t system, const string &tableName);

    // Get table ID of table with name tableName
    RC getTableID(const string &tableName, int32_t &tableID);

    RC isSystemTable(bool &system, const string &tableName);

public:
    // Extra credit work (10 points)
    RC addAttribute(const string &tableName, const Attribute &attr);

    RC dropAttribute(const string &tableName, const string &attributeName);
};

#endif