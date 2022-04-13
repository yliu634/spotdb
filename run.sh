#
mkdir -p temp
rm -rf ./temp/*

# ulimit -n 100000
# 下面这些参数都是按照rocksdb的默认参数定的, open_files = 1000, rocksdb是默认不用;

./out-static/db_bench --benchmarks=fillrandom,overwrite,readrandom,readseq --num=2000000 --reads=1000 --value_size=1024 --bloom_bits=10 --open_files=1000 --write_buffer_size=67108864 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=0 --db=temp > result.txt

#./out-static/db_bench --benchmarks=fillrandom,stats,readrandom,stats,readseq,stats --num=10000000 --reads=1000 --value_size=1024 --bloom_bits=10 --open_files=1000 --write_buffer_size=67108864 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=0 --db=temp > result.txt
#./out-static/db_bench --benchmarks=fillrandom,stats,readrandom,stats,readseq,stats --num=100000000 --reads=1000 --value_size=1024 --bloom_bits=10 --open_files=1000 --write_buffer_size=67108864 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=0 --db=temp > result.txt

#./db_bench --benchmarks=fillrandom,stats,readrandom,scanrandom,sstables,stats --num=53200000 --reads=1000000 --value_size=1000 --bloom_bits=10 --open_files=50000 --write_buffer_size=67108864 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=0 --db=/home/zq/SSD-e/temp1 > partitionResult.txt
#./db_bench --benchmarks=stats,readrandom,sstables,stats --num=53200000 --reads=10000000 --value_size=1000 --bloom_bits=10 --open_files=50000 --write_buffer_size=67108864 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=1 --db=/home/zq/SSD-e/temp1 > partitionResult-read-scan.txt
#./db_bench --benchmarks=stats,readrandom,scanrandom,sstables,stats --num=83200000 --reads=1000000 --value_size=1000 --bloom_bits=10 --open_files=50000 --write_buffer_size=67108864 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=1 --db=/home/zq/SSD-e/temp1 > partitionResult-read-scan-1.txt
#./db_bench --benchmarks=readrandom,sstables,scanrandom,stats --num=2032000 --reads=2000000 --value_size=1000 --bloom_bits=10 --open_files=50000 --write_buffer_size=67108864 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=1 > partitionResult-1.txt
#./db_bench --benchmarks=overwrite,readrandom,sstables,stats,scanrandom --num=10200000 --reads=100000 --value_size=1000 --bloom_bits=10 --open_files=50000 --write_buffer_size=67108864 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=1 > partitionread-100GB.txt
#./db_bench --benchmarks=fillrandom,stats,scanrandom,sstables,stats --num=22000000 --reads=1000000 --value_size=1000 --bloom_bits=10 --open_files=50000 --write_buffer_size=67108864 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=0 --db=/home/zq/SSD-e/temp > ../resultNewDir/partitionResult100G-load-update-0.txt
#./db_bench --benchmarks=fillrandom,stats,overwrite,stats,readrandom,scanrandom,sstables,stats --num=52000000 --reads=1000000 --value_size=1000 --bloom_bits=10 --open_files=50000 --write_buffer_size=67108864 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=0 --db=/home/zq/SSD-e/temp > ../resultNewDir/partitionResult100G-load-update-1.txt
#./db_bench --benchmarks=ycsb,sstables --ycsbTrace=../YCSB_Trace/operateRecord.txt --first_load=1 --ycsbLoadTrace=../YCSB_Trace/loadRecord.txt --num=10000 --value_size=1000 --bloom_bits=10 --open_files=50000 --write_buffer_size=67108864 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=0 --db=/home/zq/SSD-e/temp > partitionResult.txt
#./db_bench --benchmarks=fillrandom,readrandom,scanrandom,sstables,stats --num=1020000 --reads=1000 --value_size=1000 --bloom_bits=10 --open_files=50000 --write_buffer_size=67108864 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=0 --db=/mnt/leveldb/tmp > ../resultDir/partitionResultn.txt
#./db_bench --benchmarks=ycsb,sstables --ycsbTrace=../YCSB_Trace/operateRecord.txt --first_load=1 --ycsbLoadTrace=../YCSB_Trace/loadRecord.txt --num=1000 --value_size=1000 --bloom_bits=10 --open_files=50000 --write_buffer_size=67108864 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=0 --db=/mnt/expdb/levelYCSB > ../resultDir/partitionResult50G1KBYCSBzipfwrite.txt

#./db_bench --benchmarks=rebuildHashIndex --use_existing_db=1    YCSB_insert.txt  YCSB_Load operateRecord.txt
#./db_bench --benchmarks=fillrandom --num=20000000 --value_size=1000 --bloom_bits=10 --open_files=50000 --write_buffer_size=4194304 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=0 > loadResult.txt
#./db_bench --benchmarks=fillrandom,readwhilewriting --num=10000000 --reads=20000000 --value_size=1000 --bloom_bits=10 --open_files=50000 --write_buffer_size=4194304 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=0 > readwhilewriteResult.txt
#./db_bench --benchmarks=readrandom --num=10000000 --reads=500000 --value_size=1000 --bloom_bits=10 --open_files=50000 --write_buffer_size=4194304 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=1 > partitionRead.txt
#./db_bench --benchmarks=fillrandom,readrandom,scanrandom --num=2000000 --reads=200000 --value_size=1000 --bloom_bits=10 --open_files=20000 --write_buffer_size=4194304 --max_file_size=2097152 --block_size=4096 --cache_size=8388608 --threads=1 --compression_ratio=1 --use_existing_db=0 > partitionResult.txt
