CC=g++
CFLAGS=-std=c++11  -Wall -pthread -I./ -g -lrt
LDFLAGS= -ltcmalloc -lpthread -ltbb -lhiredis  -lboost_system -lboost_thread -lrt -lleveldb -lrocksdb -lspotkv -lunikv #-lpebblesdb -lboost_thread -lleveldb -lpebblesdb -lhyperleveldb  -lleveldb
SUBDIRS=core db redis
SUBSRCS=$(wildcard core/*.cc) $(wildcard db/*.cc)
OBJECTS=$(SUBSRCS:.cc=.o)
EXEC=ycsbc

all: $(SUBDIRS) $(EXEC)

$(SUBDIRS):
	$(MAKE) -C $@

$(EXEC): $(wildcard *.cc) $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
	$(RM) $(EXEC)

.PHONY: $(SUBDIRS) $(EXEC)

