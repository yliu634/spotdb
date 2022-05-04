#!/bin/bash
function __runGLSM() {

#rm -r $dbfilename3/persitentIndexDir/B_TreeStore.txt
#rm -r $dbfilename3/persitentIndexDir/hashTableStore.txt
#rm -r $dbfilename/*

echo "" > result.txt

echo "************* LevelDB *************" >> result.txt
#rm -r $dbfilename1/*
#./ycsbc -db leveldb -threads $thread -P $workload_name -dbfilename "$dbfilename1" -configpath "$configpath" -skipLoad false >> result.txt
#./ycsbc -db leveldb -threads $thread -P $workload_name -dbfilename "$dbfilename1" -configpath "$configpath" -skipLoad true >> result.txt
#./ycsbc -db leveldb -threads $thread -P $workload_name -dbfilename "$dbfilename1" -configpath "$configpath" -skipLoad true >> result.txt
#rm -r $dbfilename1/*
echo "************* RocksDB *************" >> result.txt
#rm -r $dbfilename2/*
#./ycsbc -db rocksdb -threads $thread -P $workload_name -dbfilename "$dbfilename2" -configpath "$configpath" -skipLoad false >> result.txt
#./ycsbc -db rocksdb -threads $thread -P $workload_name -dbfilename "$dbfilename2" -configpath "$configpath" -skipLoad false >> result.txt
#rm -r $dbfilename2/*
echo "************** UniKV **************" >> result.txt
#rm -r $dbfilename3/*
#./ycsbc -db unikv -threads $thread -P $workload_name -dbfilename "$dbfilename3" -configpath "$configpath" -skipLoad false >> result.txt
#./ycsbc -db unikv -threads $thread -P $workload_name -dbfilename "$dbfilename3" -configpath "$configpath" -skipLoad false >> result.txt
#rm -r $dbfilename3/*
echo "************* SpotKV **************" >> result.txt
rm -r $dbfilename4/*
./ycsbc -db spotkv -threads $thread -P $workload_name -dbfilename "$dbfilename4" -configpath "$configpath" -skipLoad false >> result.txt
./ycsbc -db spotkv -threads $thread -P $workload_name -dbfilename "$dbfilename4" -configpath "$configpath" -skipLoad true >> result.txt
#rm -r $dbfilename4/*

#./ycsbc -db leveldb -threads 1 -P $workload_name -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad false > leveldb-load-100G-read-10M.txt
#./ycsbc -db leveldb -threads 1 -P $workload_name1 -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad true > leveldb-load-100G-scan-1M.txt

#./ycsbc -db hyperleveldb -threads 1 -P $workload_name -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad false > hyperleveldb-load-100G-read-10M.txt
#./ycsbc -db hyperleveldb -threads 1 -P $workload_name1 -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad true > hyperleveldb-load-100G-scan-1M.txt

#./ycsbc -db pebblesdb -threads 1 -P $workload_name -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad false > pebblesdb-load-100G-read-10M.txt
#./ycsbc -db pebblesdb -threads 1 -P $workload_name1 -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad true > pebblesdb-load-100G-scan-1M.txt

#./ycsbc -db rocksdb -threads 1 -P $workload_name -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad false > pebblesdb-load-100G-read-10M.txt
#./ycsbc -db rocksdb -threads 1 -P $workload_name1 -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad true > pebblesdb-load-100G-scan-1M.txt

}

workload_name=./workloads/workloadb.spec
workload_name1=./workloads/workloadb.spec
workload_name2=./workloads/workloadc.spec
workload_name3=./workloads/workloadd.spec
workload_name4=./workloads/workloade.spec
workload_name5=./workloads/workloadf.spec
workload_name6=./workloads/workloade.spec

configpath=./configDir/leveldb_config.ini

dbfilename=../temp
dbfilename1=../temp/leveldb
dbfilename2=../temp/rocksdb
dbfilename3=../temp/unikv
dbfilename4=../temp/spotkv

thread=1


__runGLSM
