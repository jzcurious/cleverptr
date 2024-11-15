#ifndef _WPTR_HPP_
#define _WPTR_HPP_

#include "block.hpp"
#include "shptr.hpp"

namespace cleverptr {

template <class T>
struct WPtr final {
 private:
  const ShPtr<T>* _sptr;
  detail::Block<T>* _block;

  void _release_block() const {
    if (_block == nullptr) return;
    _block->weak_counter--;
    if (not expired()) return;
    if (_block->weak_counter == 0) delete _block;
  }

 public:
  WPtr(const ShPtr<T>& sptr)
      : _sptr(&sptr)
      , _block(detail::get_block(sptr)) {
    _block->weak_counter++;
  }

  WPtr(const WPtr& ptr)
      : _sptr(ptr._sptr)
      , _block(ptr._block) {
    _block->weak_counter++;
  }

  WPtr(WPtr&& ptr)
      : _sptr(ptr._sptr)
      , _block(ptr._block) {
    ptr._sptr = nullptr;
    ptr._block = nullptr;
  }

  WPtr& operator=(const WPtr& ptr) {
    if (this == &ptr) return *this;
    _sptr = ptr._sptr;
    _block = ptr._block;
    _block->weak_counter++;
    return *this;
  }

  WPtr& operator=(WPtr&& ptr) {
    if (this == &ptr) return *this;
    _sptr = ptr._sptr;
    _block = ptr._block;
    ptr._sptr = nullptr;
    ptr._block = nullptr;
    return *this;
  }

  WPtr& operator=(const ShPtr<T>& sptr) {
    _sptr = &sptr;
    _block = detail::get_block(sptr);
    _block->weak_counter++;
    return *this;
  }

  bool expired() const {
    return _block->shared_counter == 0;
  }

  const ShPtr<T> lock() const {
    if (expired()) return *_sptr;
    return ShPtr<T>(_block);
  }

  ~WPtr() {
    _release_block();
  }
};

}  // namespace cleverptr

#endif  // _WPTR_HPP_
