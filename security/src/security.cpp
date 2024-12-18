#include "cleverptr/shared.hpp"
#include "cleverptr/unique.hpp"
#include "cleverptr/weak.hpp"

#include <vector>

using namespace cleverptr;

void shared_copy_ctor() {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = ptr1;
  auto ptr3 = ptr2;
  auto ptr4 = ptr1;
  auto ptr5 = ptr3;
  auto ptr6 = ptr1;
}

void shared_move_ctor() {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = std::move(ptr1);
  auto ptr3 = std::move(ptr2);
}

void shared_assign() {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = make_shared<std::vector<int>>(10);
  auto ptr3 = ptr1;
  auto ptr4 = ptr1;
  auto ptr5 = ptr1;
  auto ptr6 = ptr1;
  ptr3 = ptr2;
  ptr4 = ptr2;
  ptr5 = ptr2;
  ptr6 = ptr2;
}

void unique_move_ctor() {
  auto ptr1 = make_unique<std::vector<int>>(10);
  auto ptr2 = std::move(ptr1);
  auto ptr3 = std::move(ptr2);
}

void unique_move() {
  auto ptr1 = make_unique<std::vector<int>>(10);
  auto ptr2 = make_unique<std::vector<int>>(10);
  ptr1 = std::move(ptr2);
}

void wptr_copy_ctor() {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = weak_ptr(ptr1);
  auto ptr3 = weak_ptr(ptr2);
}

void wptr_move_ctor() {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = weak_ptr(ptr1);
  auto ptr3 = weak_ptr(std::move(ptr2));
}

void wptr_ctor_from_shared() {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = weak_ptr(ptr1);
}

int main() {
  shared_copy_ctor();
  shared_move_ctor();
  shared_assign();

  unique_move_ctor();
  unique_move();

  wptr_copy_ctor();
  wptr_move_ctor();
  wptr_ctor_from_shared();
}
