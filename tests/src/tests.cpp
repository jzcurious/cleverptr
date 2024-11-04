#include "shptr.hpp"
#include "uniptr.hpp"
#include "gtest/gtest.h"
#include <utility>
#include <vector>

using namespace cleverptr;

static int vsum(const std::vector<int>* v) {
  int s = 0;
  for (unsigned i = 0; i < v->size(); ++i) s += (*v)[i];
  return s;
}

TEST(ShPtr, copy_ctor) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = ptr1;

  EXPECT_EQ(ptr1->size(), ptr2->size());
}

TEST(ShPtr, move_ctor) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = std::move(ptr1);

  EXPECT_EQ(ptr2->size(), 10);
  EXPECT_EQ(static_cast<std::vector<int>*>(ptr1), nullptr);
}

TEST(ShPtr, indirection) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = ptr1;
  for (unsigned i = 0; i < ptr1->size(); ++i) EXPECT_EQ((*ptr1)[i], (*ptr1)[i]);
}

TEST(ShPtr, assign) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = make_shared<std::vector<int>>(5);
  ptr2 = ptr1;

  EXPECT_EQ(vsum(ptr1), vsum(ptr2));
}

TEST(ShPtr, move) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = make_shared<std::vector<int>>(5);
  ptr2 = std::move(ptr1);

  EXPECT_EQ(vsum(ptr2), vsum(ptr2));
  EXPECT_EQ(static_cast<std::vector<int>*>(ptr1), nullptr);
}

TEST(ShPtr, comparison) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = make_shared<std::vector<int>>(5);
  auto ptr3 = ptr1;

  EXPECT_EQ((ptr1 == ptr3), true);
  EXPECT_EQ((ptr1 != ptr3), false);

  EXPECT_EQ((ptr1 == ptr2), false);
  EXPECT_EQ((ptr1 != ptr2), true);
}

TEST(UniPtr, move_ctor) {
  auto ptr1 = make_unique<std::vector<int>>(10);
  auto ptr2 = std::move(ptr1);

  EXPECT_EQ(static_cast<std::vector<int>*>(ptr1), nullptr);
  EXPECT_EQ(ptr2->size(), 10);
}

TEST(UniPtr, indirection) {
  auto ptr1 = make_unique<std::vector<int>>(10);
  auto ptr2 = std::move(ptr1);

  for (unsigned i = 0; i < ptr2->size(); ++i) EXPECT_EQ((*ptr2)[i], (*ptr2)[i]);
}

TEST(UniPtr, move) {
  auto ptr1 = make_unique<std::vector<int>>(10);
  auto ptr2 = make_unique<std::vector<int>>(5);
  ptr2 = std::move(ptr1);

  EXPECT_EQ(vsum(ptr2), vsum(ptr2));
  EXPECT_EQ(static_cast<std::vector<int>*>(ptr1), nullptr);
}
