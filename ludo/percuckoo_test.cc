
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

TEST(PerCuckooTest, Ludo) {
    ControlPlaneLudo<const char*, uint64_t, 16> cp(1024);
    cp.insert("000245", 5);
    cp.insert("000345", 6);
    uint64_t value;
    cp.lookUp("000245", value);
    ASSERT_EQ(value, 5);
    bool tmp = cp.lookUp("000545", value);
    ASSERT_EQ(tmp, false);
    uint32_t before_size = cp.size();
    cp.remove("000245");
    uint32_t after_size = cp.size();
    tmp = cp.lookUp("000245", value);
    ASSERT_EQ(tmp, false);
    ASSERT_EQ(before_size - 1, after_size);
    cp.remove("000145");
    uint32_t afterafter_size = cp.size();
    ASSERT_EQ(before_size - 1, afterafter_size);
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