#ifndef YCSB_C_ROCKSDB_H
#define YCSB_C_ROCKSDB_H

#include "db_factory.h"
#include "core/db.h"
#include "core/utils.h"
#include "core/properties.h"
#include "core/core_workload.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <rocksdb/db.h>
#include <rocksdb/env.h>
#include <rocksdb/cache.h>
#include <rocksdb/status.h>
#include <rocksdb/options.h>
#include <rocksdb/write_batch.h>
#include <rocksdb/filter_policy.h>
#include <rocksdb/merge_operator.h>
#include <rocksdb/utilities/options_util.h>


using std::cout;
using std::endl;

namespace ycsbc {
class RocksDB : public DB{
public :
    RocksDB(const char *dbfilename,const char* configPath);
    int Read(const std::string &table, const std::string &key,
           const std::vector<std::string> *fields,
           std::vector<KVPair> &result);

    int Scan(const std::string &table, const std::string &key,
            int len, const std::vector<std::string> *fields,
            std::vector<std::vector<KVPair>> &result) ;

    int Update(const std::string &table, const std::string &key,
                std::vector<KVPair> &values);

    int Insert(const std::string &table, const std::string &key,
                std::vector<KVPair> &values) ;

    int Delete(const std::string &table, const std::string &key);
    //void openStatistics();
    //void printAccessFreq();
    virtual ~RocksDB();
    //virtual void doSomeThing(const char *thing_str="adjust_filter");
    //virtual void analysisTableKey();
    void Close();
private:
    rocksdb::DB *db_;
    std::ofstream outW; 
    static bool hasRead;
    void printFilterCount();
};
}
#endif
