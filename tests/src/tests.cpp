#include "shptr.hpp"
#include "gtest/gtest.h"
#include <vector>

using namespace cleverptr;

static int vsum(const std::vector<int>* v) {
  int s = 0;
  for (unsigned i = 0; i < v->size(); ++i) s += (*v)[i];
  return s;
}

TEST(Shptr, copy_ctor) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = ptr1;
  EXPECT_EQ(ptr1->size(), ptr2->size());
}

TEST(Shptr, indirection) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = ptr1;
  for (unsigned i = 0; i < ptr1->size(); ++i) EXPECT_EQ((*ptr1)[i], (*ptr1)[i]);
}

TEST(Shptr, assign) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = make_shared<std::vector<int>>(5);
  ptr2 = ptr1;
  EXPECT_EQ(vsum(ptr1), vsum(ptr2));
}

TEST(Shptr, comparison) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = make_shared<std::vector<int>>(5);
  auto ptr3 = ptr1;

  EXPECT_EQ((ptr1 == ptr3), true);
  EXPECT_EQ((ptr1 != ptr3), false);

  EXPECT_EQ((ptr1 == ptr2), false);
  EXPECT_EQ((ptr1 != ptr2), true);
}
