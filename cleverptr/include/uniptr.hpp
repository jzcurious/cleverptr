#ifndef _UNIPTR_HPP_
#define _UNIPTR_HPP_

#include "block.hpp"

namespace cleverptr {

template <class T>
struct UniPtr final {
 private:
  detail::Block<T>* _block;

  UniPtr(detail::Block<T>* block)
      : _block(block) {
    _block->shared_counter = 1;
  }

 public:
  UniPtr(const UniPtr&) = delete;

  UniPtr(UniPtr&& ptr)
      : _block(ptr._block) {
    ptr._block = nullptr;
  }

  UniPtr& operator=(const UniPtr&) = delete;

  UniPtr& operator=(UniPtr&& ptr) {
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

  constexpr bool operator==(const UniPtr&) {
    return false;
  }

  constexpr bool operator!=(const UniPtr&) {
    return true;
  }

  ~UniPtr() {
    if (_block) delete _block;
  }

  template <class... Ts>
  static UniPtr make(Ts&&... args) {
    return UniPtr(new detail::Block<T>(std::forward<Ts>(args)...));
  }
};

template <class T, class... Ts>
auto make_unique(Ts&&... args) {
  return UniPtr<T>::make(std::forward<Ts>(args)...);
}

}  // namespace cleverptr

#endif  // _UNIPTR_HPP_
