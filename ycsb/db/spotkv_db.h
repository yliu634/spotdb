#ifndef YCSB_C_SPOTKVDB_H
#define YCSB_C_SPOTKVDB_H

#include "core/db.h"
#include "core/properties.h"

#include <iostream>
#include <string>
#include <fstream>
#include <spotkv/db.h>
#include <spotkv/env.h>
#include <spotkv/filter_policy.h>

using std::cout;
using std::endl;

namespace ycsbc {
class SpotkvDB : public DB{
public :
    SpotkvDB(const char *dbfilename,const char* configPath);
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
    void openStatistics();
    void printAccessFreq();
    virtual ~SpotkvDB();
    virtual void doSomeThing(const char *thing_str="adjust_filter");
    virtual void analysisTableKey();
    void Close();
private:
    SpotkvDB::DB *db_;
    std::ofstream outW; 
    static bool hasRead;
    void printFilterCount();
};
}
#endif
