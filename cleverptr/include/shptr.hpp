#ifndef _SHPTR_HPP_
#define _SHPTR_HPP_

#include "block.hpp"

namespace cleverptr {

template <class T>
struct ShPtr final {
 private:
  detail::Block<T>* _block;

  ShPtr(detail::Block<T>* block)
      : _block(block) {
    _block->counter++;
  }

 public:
  ShPtr(const ShPtr& ptr)
      : _block(ptr._block) {
    _block->counter++;
  }

  ShPtr(ShPtr&& ptr)
      : _block(ptr._block) {
    ptr._block = nullptr;
  }

  ShPtr& operator=(const ShPtr& ptr) {
    if (this == &ptr) return *this;
    ptr._block->counter++;
    if (_block) {
      if (_block->counter <= 1)
        delete _block;
      else
        _block->counter--;
    }
    _block = ptr._block;
    return *this;
  }

  ShPtr& operator=(ShPtr&& ptr) {
    if (this == &ptr) return *this;
    if (_block) {
      if (_block->counter <= 1)
        delete _block;
      else
        _block->counter--;
    }
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

  bool operator==(const ShPtr& ptr) {
    if (ptr._block == _block) return true;
    return false;
  }

  bool operator!=(const ShPtr& ptr) {
    return not(*this == ptr);
  }

  ~ShPtr() {
    if (_block == nullptr) return;
    if (_block->counter <= 1) {
      delete _block;
    } else {
      _block->counter--;
    }
  }

  template <class... Ts>
  static ShPtr make(Ts&&... args) {
    return ShPtr(new detail::Block<T>(std::forward<Ts>(args)...));
  }
};

template <class T, class... Ts>
auto make_shared(Ts&&... args) {
  return ShPtr<T>::make(std::forward<Ts>(args)...);
}

}  // namespace cleverptr

#endif  // _SHPTR_HPP_
