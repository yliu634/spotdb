// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_SPOTKV_DB_BUILDER_H_
#define STORAGE_SPOTKV_DB_BUILDER_H_

#include "spotkv/status.h"
#include "ludo/ludo_cp_dp.h"
#include "ludo/cuckoo_ht.h"

namespace spotkv {

struct Options;
struct FileMetaData;

class Env;
class Iterator;
class TableCache;
class VersionEdit;

// Build a Table file from the contents of *iter.  The generated file
// will be named according to meta->number.  On success, the rest of
// *meta will be filled with metadata about the generated table.
// If no data is present in *iter, meta->file_size will be set to
// zero, and no Table file will be produced.
extern Status BuildTable(const std::string& dbname,
                         Env* env,
                         const Options& options,
                         TableCache* table_cache,
                         Iterator* iter,
                         FileMetaData* meta);

extern Status BuildLudoTable(const std::string& dbname,
                         Env* env,
                         const Options& options,
                         TableCache* table_cache,
                         Iterator* iter,
                         FileMetaData* meta,
                         ControlPlaneLudo<uint64_t, uint64_t>* cp);             

}  // namespace spotkv

#endif  // STORAGE_LEVELDB_DB_BUILDER_H_
