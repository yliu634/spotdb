//
//  basic_db.cc
//  YCSB-C
//
//  Created by Jinglei Ren on 12/17/14.
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//
#include <string>

#include "db/basic_db.h"
#include "db/redis_db.h"
#include "db/db_factory.h"
#include "db/lock_stl_db.h"
#include "db/tbb_rand_db.h"
#include "db/tbb_scan_db.h"
#include "db/leveldb_db.h"
#include "db/rocksdb_db.h"
#include "db/spotkv_db.h"
#include "db/unikv_db.h"

using namespace std;

using ycsbc::DB;
using ycsbc::DBFactory;
using ycsbc::LevelDB;
using ycsbc::RocksDB;
using ycsbc::UniKVDB;
using ycsbc::SpotkvDB;

DB* DBFactory::CreateDB(utils::Properties &props) {
  if (props["dbname"] == "basic") {
    return new BasicDB;
  } else if (props["dbname"] == "lock_stl") {
    return new LockStlDB;
  } else if (props["dbname"] == "redis") {
    int port = stoi(props["port"]);
    int slaves = stoi(props["slaves"]);
    return new RedisDB(props["host"].c_str(), port, slaves);
  } else if (props["dbname"] == "tbb_rand") {
    return new TbbRandDB;
  } else if (props["dbname"] == "tbb_scan") {
    return new TbbScanDB;
  } else if (props["dbname"] == "leveldb"){
	  return new LevelDB(props["dbfilename"].c_str(),props["configpath"].c_str());//configpath
  }else if (props["dbname"] == "rocksdb"){
	  return new RocksDB(props["dbfilename"].c_str(),props["configpath"].c_str());//configpath
  }else if (props["dbname"] == "unikv"){
	  return new UniKVDB(props["dbfilename"].c_str(),props["configpath"].c_str());//configpath
  }else if (props["dbname"] == "spotkv"){
	  return new SpotkvDB(props["dbfilename"].c_str(),props["configpath"].c_str());//configpath
  }
  else return NULL;
}

