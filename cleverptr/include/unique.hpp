#ifndef _CLEVERPTR_UNIQUE_PTR_HPP_
#define _CLEVERPTR_UNIQUE_PTR_HPP_

#include "block.hpp"

namespace cleverptr {

template <class T>
struct unique_ptr final {
 private:
  detail::Block<T>* _block;

  unique_ptr(detail::Block<T>* block)
      : _block(block) {
    _block->shared_counter = 1;
  }

 public:
  unique_ptr(const unique_ptr&) = delete;

  unique_ptr(unique_ptr&& ptr)
      : _block(ptr._block) {
    ptr._block = nullptr;
  }

  unique_ptr& operator=(const unique_ptr&) = delete;

  unique_ptr& operator=(unique_ptr&& ptr) {
    if (this == &ptr) return *this;
    if (_block) delete _block;
    _block = ptr._block;
    ptr._block = nullptr;
    return *this;
  }

  T* operator->() {
    return &_block->object;
  }

  T& operator*() {
    return _block->object;
  }

  operator T*() {
    if (_block == nullptr) return nullptr;
    return &_block->object;
  }

  constexpr bool operator==(const unique_ptr&) {
    return false;
  }

  constexpr bool operator!=(const unique_ptr&) {
    return true;
  }

  ~unique_ptr() {
    if (_block) delete _block;
  }

  template <class... Ts>
  static unique_ptr make(Ts&&... args) {
    return unique_ptr(new detail::Block<T>(std::forward<Ts>(args)...));
  }
};

template <class T, class... Ts>
auto make_unique(Ts&&... args) {
  return unique_ptr<T>::make(std::forward<Ts>(args)...);
}

}  // namespace cleverptr

#endif  // _CLEVERPTR_UNIQUE_PTR_HPP_