#ifndef _CLEVERPTR_SHARED_PTR_HPP_
#define _CLEVERPTR_SHARED_PTR_HPP_

#include "block.hpp"

namespace cleverptr {

template <class T>
struct shared_ptr;

namespace detail {
template <class T>
Block<T>* get_block(const shared_ptr<T>& ptr);
}

template <class T>
struct shared_ptr final {
 private:
  detail::Block<T>* _block;

  void _release_block() const {
    if (not _block) return;
    _block->shared_counter--;
    if (_block->shared_counter) return;
    if (not _block->weak_counter) delete _block;
  }

 public:
  shared_ptr(detail::Block<T>* block)
      : _block(block) {
    _block->shared_counter++;
  }

  shared_ptr(const shared_ptr& ptr)
      : _block(ptr._block) {
    _block->shared_counter++;
  }

  shared_ptr(shared_ptr&& ptr)
      : _block(ptr._block) {
    ptr._block = nullptr;
  }

  shared_ptr& operator=(const shared_ptr& ptr) {
    if (this == &ptr) return *this;
    ptr._block->shared_counter++;
    _release_block();
    _block = ptr._block;
    return *this;
  }

  shared_ptr& operator=(shared_ptr&& ptr) {
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
    if (not _block) return nullptr;
    return &_block->object;
  }

  bool operator==(const shared_ptr& ptr) const {
    return ptr._block == _block;
  }

  bool operator!=(const shared_ptr& ptr) const {
    return ptr._block != _block;
  }

  ~shared_ptr() {
    _release_block();
  }

  template <class... Ts>
  static shared_ptr make(Ts&&... args) {
    return shared_ptr(new detail::Block<T>(std::forward<Ts>(args)...));
  }

  friend detail::Block<T>* detail::get_block<T>(const shared_ptr&);
};

template <class T, class... Ts>
auto make_shared(Ts&&... args) {
  return shared_ptr<T>::make(std::forward<Ts>(args)...);
}

template <class T>
detail::Block<T>* detail::get_block(const shared_ptr<T>& ptr) {
  return ptr._block;
}

}  // namespace cleverptr

#endif  // _CLEVERPTR_SHARED_PTR_HPP_
