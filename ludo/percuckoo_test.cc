
#include "ludo/hash2.h"
#include "ludo/hashutil.h"
#include "ludo/farmhash.h"
#include "ludo/common.h"
#include "ludo/disjointset.h"
#include "ludo/ludo_cp_dp.h"
#include "util/testharness.h"

namespace leveldb {

class PerCuckooTest { };

TEST(PerCuckooTest, Farmhash) {
    const char s[3]= "ab";
    size_t b=2;
    uint32_t res = farmhash::Hash32(s, b);
}

TEST(PerCuckooTest, DisjointSet) {
    DisjointSet ds;
}

TEST(PerCuckooTest, Hash2) {
    Hasher32<uint32_t> h32;
}

TEST(PerCuckooTest, ludo) {
    ControlPlaneLudo<int, int, 2> cp(1024);
}
/*
TEST(PerCuckooTest, DisjointSet) {
    DisjointSet ds;
}
/*
TEST(PerCuckooTest, Common) {
    InputBase base;
}
*/


}  // namespace leveldb

int main(int argc, char** argv) {
  return leveldb::test::RunAllTests();
}