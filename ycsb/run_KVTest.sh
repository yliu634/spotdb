#!/bin/bash
function __runGLSM(){

rm -rf ../persitentIndexDir/B_TreeStore.txt
rm -rf ../persitentIndexDir/hashTableStore.txt
rm -rf $dbfilename/*

./ycsbc -db leveldb -threads 1 -P $workload_name -dbfilename "$dbfilename" -configpath "$configpath" -skipLoad false > unikv-load-100G-read-10M-threads=test.txt
#./ycsbc -db unikv -threads 1 -P $workload_name1 -dbfilename "/home/yiliu/projs/unikv/temp" -configpath "$configpath" -skipLoad true > unikv-load-100G-scan-1M-threads=test.txt

#./ycsbc -db leveldb -threads 1 -P $workload_name -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad false > leveldb-load-100G-read-10M.txt
#./ycsbc -db leveldb -threads 1 -P $workload_name1 -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad true > leveldb-load-100G-scan-1M.txt

#./ycsbc -db hyperleveldb -threads 1 -P $workload_name -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad false > hyperleveldb-load-100G-read-10M.txt
#./ycsbc -db hyperleveldb -threads 1 -P $workload_name1 -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad true > hyperleveldb-load-100G-scan-1M.txt

#./ycsbc -db pebblesdb -threads 1 -P $workload_name -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad false > pebblesdb-load-100G-read-10M.txt
#./ycsbc -db pebblesdb -threads 1 -P $workload_name1 -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad true > pebblesdb-load-100G-scan-1M.txt

#./ycsbc -db rocksdb -threads 1 -P $workload_name -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad false > pebblesdb-load-100G-read-10M.txt
#./ycsbc -db rocksdb -threads 1 -P $workload_name1 -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad true > pebblesdb-load-100G-scan-1M.txt

}

workload_name=./workloads/workloadc-1.spec
workload_name1=./workloads/workloadc-2.spec
workload_name2=./workloads/workloadc-3.spec
workload_name3=./workloads/workloadc-4.spec
workload_name4=./workloads/workloadc-5.spec
workload_name5=./workloads/workloadc-6.spec
workload_name6=./workloads/workloadc.spec

configpath=./configDir/leveldb_config.ini
dbfilename=../temp
#section=basic
#key=hierarchicalBoomflag
#value=true
#./modifyConfig.py "$configpath" "$section" "$key" "$value"
#echo "123"|sudo -S echo 3 > /proc/sys/vm/drop_caches

__runGLSM
