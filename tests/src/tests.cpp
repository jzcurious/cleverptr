#include "cleverptr/shared.hpp"
#include "cleverptr/unique.hpp"
#include "cleverptr/weak.hpp"
#include "gtest/gtest.h"
#include <utility>
#include <vector>

using namespace cleverptr;

static int vsum(const std::vector<int>* v) {
  int s = 0;
  for (unsigned i = 0; i < v->size(); ++i) s += (*v)[i];
  return s;
}

TEST(shared_ptr, copy_ctor) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = ptr1;

  EXPECT_EQ(ptr1->size(), ptr2->size());
}

TEST(shared_ptr, move_ctor) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = std::move(ptr1);

  EXPECT_EQ(ptr2->size(), 10);
  EXPECT_EQ(static_cast<std::vector<int>*>(ptr1), nullptr);
}

TEST(shared_ptr, indirection) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = ptr1;
  for (unsigned i = 0; i < ptr1->size(); ++i) EXPECT_EQ((*ptr1)[i], (*ptr1)[i]);
}

TEST(shared_ptr, assign) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = make_shared<std::vector<int>>(5);
  ptr2 = ptr1;

  EXPECT_EQ(vsum(ptr1), vsum(ptr2));
}

TEST(shared_ptr, move) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = make_shared<std::vector<int>>(5);
  ptr2 = std::move(ptr1);

  EXPECT_EQ(vsum(ptr2), vsum(ptr2));
  EXPECT_EQ(static_cast<std::vector<int>*>(ptr1), nullptr);
}

TEST(shared_ptr, comparison) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = make_shared<std::vector<int>>(5);
  auto ptr3 = ptr1;

  EXPECT_EQ((ptr1 == ptr3), true);
  EXPECT_EQ((ptr1 != ptr3), false);

  EXPECT_EQ((ptr1 == ptr2), false);
  EXPECT_EQ((ptr1 != ptr2), true);
}

TEST(unique_ptr, move_ctor) {
  auto ptr1 = make_unique<std::vector<int>>(10);
  auto ptr2 = std::move(ptr1);

  EXPECT_EQ(static_cast<std::vector<int>*>(ptr1), nullptr);
  EXPECT_EQ(ptr2->size(), 10);
}

TEST(unique_ptr, indirection) {
  auto ptr1 = make_unique<std::vector<int>>(10);
  auto ptr2 = std::move(ptr1);

  for (unsigned i = 0; i < ptr2->size(); ++i) EXPECT_EQ((*ptr2)[i], (*ptr2)[i]);
}

TEST(unique_ptr, move) {
  auto ptr1 = make_unique<std::vector<int>>(10);
  auto ptr2 = make_unique<std::vector<int>>(5);
  ptr2 = std::move(ptr1);

  EXPECT_EQ(vsum(ptr2), vsum(ptr2));
  EXPECT_EQ(static_cast<std::vector<int>*>(ptr1), nullptr);
}

TEST(weak_ptr, ctor_shptr) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = weak_ptr(ptr1);

  EXPECT_EQ(ptr1->size(), ptr2.lock()->size());
}

TEST(weak_ptr, expired) {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = weak_ptr(ptr1);

  EXPECT_EQ(ptr2.expired(), false);
}
