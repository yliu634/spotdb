#!/bin/bash
function __runGLSM(){

#rm -rf ../persitentIndexDir/B_TreeStore.txt
#rm -rf ../persitentIndexDir/hashTableStore.txt
rm -rf $dbfilename/*

./ycsbc -db leveldb -threads 1 -P $workload_name -dbfilename "$dbfilename" -configpath "$configpath" -skipLoad false > reslevel.txt
./ycsbc -db spotkv -threads 1 -P $workload_name -dbfilename "$dbfilename" -configpath "$configpath" -skipLoad false > respotkv.txt

#./ycsbc -db leveldb -threads 1 -P $workload_name -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad false > leveldb-load-100G-read-10M.txt
#./ycsbc -db leveldb -threads 1 -P $workload_name1 -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad true > leveldb-load-100G-scan-1M.txt

#./ycsbc -db hyperleveldb -threads 1 -P $workload_name -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad false > hyperleveldb-load-100G-read-10M.txt
#./ycsbc -db hyperleveldb -threads 1 -P $workload_name1 -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad true > hyperleveldb-load-100G-scan-1M.txt

#./ycsbc -db pebblesdb -threads 1 -P $workload_name -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad false > pebblesdb-load-100G-read-10M.txt
#./ycsbc -db pebblesdb -threads 1 -P $workload_name1 -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad true > pebblesdb-load-100G-scan-1M.txt

#./ycsbc -db rocksdb -threads 1 -P $workload_name -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad false > pebblesdb-load-100G-read-10M.txt
#./ycsbc -db rocksdb -threads 1 -P $workload_name1 -dbfilename "/home/zq/SSD-e/temp1" -configpath "$configpath" -skipLoad true > pebblesdb-load-100G-scan-1M.txt

}

workload_name=./workloads/workloadd.spec
workload_name1=./workloads/workloadb.spec
workload_name2=./workloads/workloadc-1.spec
workload_name3=./workloads/workloadd.spec
workload_name4=./workloads/workloade.spec
workload_name5=./workloads/workloadf.spec
workload_name6=./workloads/workloade.spec

configpath=./configDir/leveldb_config.ini
dbfilename=../temp
#section=basic
#key=hierarchicalBoomflag
#value=true
#./modifyConfig.py "$configpath" "$section" "$key" "$value"
#echo "123"|sudo -S echo 3 > /proc/sys/vm/drop_caches

__runGLSM
