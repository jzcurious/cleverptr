#include "shptr.hpp"
#include <vector>

using namespace shptr;

void case_copy_ctor() {
  auto ptr1 = make_shared<std::vector<int>>(10);
  auto ptr2 = ptr1;
  auto ptr3 = ptr2;
  auto ptr4 = ptr1;
  auto ptr5 = ptr3;
  auto ptr6 = ptr1;
}

void case_assign() {
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

int main() {
  case_copy_ctor();
  case_assign();
}
