#ifndef _SHPTR_HPP_
#define _SHPTR_HPP_

#include "block.hpp"

namespace cleverptr {

template <class T>
struct ShPtr;

namespace detail {
template <class U>
Block<U>* get_block(const ShPtr<U>& ptr);
}

template <class T>
struct ShPtr final {
 private:
  detail::Block<T>* _block;

  void _release_block() const {
    if (_block == nullptr) return;
    if (_block->shared_counter > 1) {
      _block->shared_counter--;
      return;
    }
    if (_block->weak_counter == 0) {
      delete _block;
      return;
    }
  }

 public:
  ShPtr(detail::Block<T>* block)
      : _block(block) {
    _block->shared_counter++;
  }

  ShPtr(const ShPtr& ptr)
      : _block(ptr._block) {
    _block->shared_counter++;
  }

  ShPtr(ShPtr&& ptr)
      : _block(ptr._block) {
    ptr._block = nullptr;
  }

  ShPtr& operator=(const ShPtr& ptr) {
    if (this == &ptr) return *this;
    ptr._block->shared_counter++;
    _release_block();
    _block = ptr._block;
    return *this;
  }

  ShPtr& operator=(ShPtr&& ptr) {
    if (this == &ptr) return *this;
    _release_block();
    _block = ptr._block;
    ptr._block = nullptr;
    return *this;
  }

  T* operator->() const {
    return &_block->object;
  }

  T& operator*() const {
    return _block->object;
  }

  operator T*() const {
    if (_block == nullptr) return nullptr;
    return &_block->object;
  }

  bool operator==(const ShPtr& ptr) const {
    if (ptr._block == _block) return true;
    return false;
  }

  bool operator!=(const ShPtr& ptr) const {
    return not(*this == ptr);
  }

  ~ShPtr() {
    _release_block();
  }

  template <class... Ts>
  static ShPtr make(Ts&&... args) {
    return ShPtr(new detail::Block<T>(std::forward<Ts>(args)...));
  }

  friend detail::Block<T>* detail::get_block<T>(const ShPtr&);
};

template <class T, class... Ts>
auto make_shared(Ts&&... args) {
  return ShPtr<T>::make(std::forward<Ts>(args)...);
}

template <class T>
detail::Block<T>* detail::get_block(const ShPtr<T>& ptr) {
  return ptr._block;
}

}  // namespace cleverptr

#endif  // _SHPTR_HPP_
