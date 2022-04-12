#include <iostream>
#include <memory>
#include <vector>
#include <time.h>
#include <cstring>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <spotkv/cache.h>

#include "basic_config.h"
#include "spotkv_db.h"

using namespace std;

namespace ycsbc {
    
SpotkvDB::SpotkvDB(const char* dbfilename,const char* configPath) {
    
    leveldb::Options options;
    LevelDB_ConfigMod::getInstance().setConfigPath(configPath);
    
    int bloom_bits = LevelDB_ConfigMod::getInstance().getBloom_bits();
    int max_File_sizes = LevelDB_ConfigMod::getInstance().getMax_file_size();
    int max_open_files = LevelDB_ConfigMod::getInstance().getMax_open_files();
    size_t memTableSize=LevelDB_ConfigMod::getInstance().getMemTableSize();
    int bloom_type = LevelDB_ConfigMod::getInstance().getBloomType();
    bool seek_compaction_flag = LevelDB_ConfigMod::getInstance().getSeekCompactionFlag();
    size_t block_cache_size = LevelDB_ConfigMod::getInstance().getBlockCacheSize();
    //int size_ratio = LevelDB_ConfigMod::getInstance().getSizeRatio();
    bool compression_Open = LevelDB_ConfigMod::getInstance().getCompression_flag();
    //bool directIO_flag = LevelDB_ConfigMod::getInstance().getDirectIOFlag();
    /****
    if (directIO_flag) {
	   options.opEp_.no_cache_io_ = true;
	   fprintf(stderr,"directIO\n");
	   leveldb::setDirectIOFlag(directIO_flag);
    }
    ****/
    if (bloom_type == 1) {
        } else if (bloom_type == 0){
            options.filter_policy = leveldb::NewBloomFilterPolicy(bloom_bits);
        } else if (bloom_type == 2){
        } else {
            fprintf(stderr,"Wrong filter type!\n");
    }


    options.create_if_missing = true;
    options.compression = compression_Open? leveldb::kSnappyCompression:leveldb::kNoCompression;  //compression is disabled.
    options.write_buffer_size = memTableSize;//67108864;8388608
    options.max_file_size = max_File_sizes;
    options.max_open_files = max_open_files;
    options.block_size = 4096;
    // options.opEp_.seek_compaction_ = seek_compaction_flag;
    options.block_cache = leveldb::NewLRUCache(8388608);
    // options.opEp_.size_ratio = size_ratio;
    fprintf(stderr, "********* SpotKV ********\n");
    // fprintf(stderr,"block_cache_size %lu, max_open_files:%d",options.block_cache, options.max_open_files);
    fprintf(stderr,"bloom_bits:%d,seek_compaction_flag:%d\n",bloom_bits,seek_compaction_flag);
    // if(LevelDB_ConfigMod::getInstance().getStatisticsOpen()){
    //  options.opEp_.stats_ = leveldb::CreateDBStatistics();
    // }
    leveldb::Status status = leveldb::DB::Open(options,dbfilename, &db_);
    if (!status.ok()) {
        fprintf(stderr, "can't open leveldb\n");
        cerr << status.ToString() << endl;
        exit(0);
    }
}

int SpotkvDB::Read(const string& table, const string& key, 
                    const vector<string>* fields, vector<DB::KVPair>& result) {
    std::string value;
    leveldb::Status s = db_->Get(leveldb::ReadOptions(), key, &value);
    if(s.IsNotFound()){
        // fprintf(stderr,"Not Found!\n");
        return DB::kErrorNoData;
    }
    if(!s.ok()){
         cerr<<s.ToString()<<endl;
        fprintf(stderr,"read error\n");
        exit(0);
    }
    return DB::kOK;
}

int SpotkvDB::Insert(const string& table, const string& key, 
                                        vector< DB::KVPair >& values) {
    leveldb::Status s;
    for(KVPair &p : values) {
        // cout<<p.second.length()<<endl;
        // leveldb::WriteOptions write_options_;
        // write_options_=leveldb::WriteOptions();
        // write_options_.sync = true;
        //clock_t start_time=clock();
        s = db_->Put(leveldb::WriteOptions(), key, p.second);
        //s = db_->Put(write_options_, key, p.second);
        //clock_t end_time=clock();
        if(!s.ok()){
            fprintf(stderr,"insert error!\n");
            cout<<s.ToString()<<endl;
            exit(0);
        }
    }
    return DB::kOK;
}

int SpotkvDB::Delete(const string& table, const string& key) {
    vector<DB::KVPair> values;
    return Insert(table,key,values);
}

int SpotkvDB::Scan(const string& table, const string& key, int len, 
                    const vector< string >* fields, vector< vector< DB::KVPair > >& result) {
    vector< DB::KVPair > scanValue;
    std::string value;
    leveldb:: Iterator* iter = db_->NewIterator(leveldb::ReadOptions());
    iter->Seek(key);
    int num_next = len;
    if (iter->Valid() && iter->key() == key) {	   
        //fprintf(stderr,"after iter->Seek(key)!\n"); 
        for (int j = 0; iter->Valid() && j < num_next; j ++) {
            iter->Next();
        // value=iter->value();
        // scanValue.push_back(iter->value());
        // result.push_back(iter->value());
        }
    } else {    	  
        // fprintf(stderr,"not found!\n");
        return DB::kErrorNoData;
    }
    delete iter;
    return DB::kOK;
}

int SpotkvDB::Update(const string& table, const string& key, vector< DB::KVPair >& values) {
    return Insert(table,key,values);
}

void SpotkvDB::analysisTableKey(){
	//db_->AnalysisTableKeys(leveldb::ReadOptions());
}

void SpotkvDB::Close() {};

void SpotkvDB::doSomeThing(const char* thing_str) {
  
  if(strncmp(thing_str,"adjust_filter",strlen("adjust_filter")) == 0){
 
  }else if(strncmp(thing_str,"printFilterCount",strlen("printFilterCount")) == 0){
    //printFilterCount();
  }else if(strncmp(thing_str,"printStats",strlen("printStats")) == 0){
    std::string stat_str;
    db_->GetProperty("leveldb.stats",&stat_str);
    cout<<stat_str<<endl;
     /*if(!db_->GetProperty("leveldb.sstables",&stat_str)){
      stat_str="(failed)";
    }
    cout<<stat_str<<endl;*/
  }

  //////////////////
  /*cout<<"writeDataSize: "<<db_->writeDataSize<<endl;
  cout<<"writeDataSizeActual: "<<db_->writeDataSizeActual<<endl;
  cout<<"readDataSize: "<<db_->readDataSize<<endl;
  cout<<"readDataSizeActual: "<<db_->readDataSizeActual<<endl;
  cout<<"db_->tableCacheNum: "<<db_->tableCacheNum<<endl;
  cout<<"db_->blockCacheNum: "<<db_->blockCacheNum<<endl;
  cout<<"db_->readIn0: "<<db_->readIn0<<endl;
  cout<<"db_->readIn1: "<<db_->readIn1<<endl;
  //cout<<"db_->readHotMem: "<<db_->readHotMem<<endl;
  cout<<"db_->readMem: "<<db_->readMem<<endl;
  cout<<"db_->readImm: "<<db_->readImm<<endl;
  cout<<"db_->LevelRead: "<<db_->cacheRead<<endl;*/
  //cout<<" db_->reduceIOInComp: "<< db_->reduceIOInComp<<endl;
  //cout<<" db_->totalIOInComp: "<< db_->totalIOInComp<<endl;
  //cout<<" db_->totalDropKeyN: "<< db_->totalDropKeyN<<endl;
  //////////////////
}

void SpotkvDB::openStatistics() {
    std::string stat_str;
    db_->GetProperty("leveldb.stats", &stat_str);
    cout << "------------------- Before Do Transaction -------------------" << endl;
    cout<<stat_str<<endl;
    cout << "--------------------- Transaction Output --------------------" << endl;
}

SpotkvDB::~SpotkvDB() {
    delete db_;
}

}
