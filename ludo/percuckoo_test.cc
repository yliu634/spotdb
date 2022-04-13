#include "ludo/hash2.h"
#include "ludo/hashutil.h"
#include "ludo/farmhash.h"
#include "ludo/common.h"
#include "ludo/disjointset.h"
#include "ludo/ludo_cp_dp.h"
#include "ludo/cuckoo_ht.h"
#include "ludo/count_min.h"
#include "util/testharness.h"

namespace spotkv {

class PerCuckooTest { };

TEST(PerCuckooTest, CM) {
    CountMinSketch<uint16_t> c(0.1, 0.1);
    c.Update("hello", 1, 1);
    c.Update("world", 1, 2);
    uint32_t h = c.Estimate("world", 1);
    ASSERT_EQ(h,2);
}

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
    CuckooHashTable<const char*, uint64_t> cp(1024);
    cp.insert("000245", 5);
    cp.insert("000345", 6);
    uint64_t value;
    cp.lookUp("000245", value);
    ASSERT_EQ(value, 5);
    bool tmp = cp.lookUp("000545", value);
    ASSERT_EQ(tmp, false);
    uint32_t before_size = cp.EntryCount();
    cp.remove("000245");
    uint32_t after_size = cp.EntryCount();
    tmp = cp.lookUp("000245", value);
    ASSERT_EQ(tmp, false);
    ASSERT_EQ(before_size - 1, after_size);
    cp.remove("000145");
    uint32_t afterafter_size = cp.EntryCount();
    ASSERT_EQ(before_size - 1, afterafter_size);

    uint64_t a = 1000;
    int64_t b = 3000;
    cp.insert("bb", (a<<32) + (b&0xffffffff));
    cp.lookUp("bb", value);
    // printf("this one : %ld", value);
    ASSERT_EQ(a, value>>32);
    ASSERT_EQ(b, value&0xffffffff);
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


}  // namespace spotkv

int main(int argc, char** argv) {
  return spotkv::test::RunAllTests();
}