#ifndef _CLEVERPTR_WEAK_PTR_HPP_
#define _CLEVERPTR_WEAK_PTR_HPP_

#include "block.hpp"
#include "shared.hpp"

namespace cleverptr {

template <class T>
struct weak_ptr final {
 private:
  const shared_ptr<T>* _sptr;
  detail::Block<T>* _block;

  void _release_block() const {
    if (_block == nullptr) return;
    _block->weak_counter--;
    if (not expired()) return;
    if (_block->weak_counter == 0) delete _block;
  }

 public:
  weak_ptr(const shared_ptr<T>& sptr)
      : _sptr(&sptr)
      , _block(detail::get_block(sptr)) {
    _block->weak_counter++;
  }

  weak_ptr(const weak_ptr& ptr)
      : _sptr(ptr._sptr)
      , _block(ptr._block) {
    _block->weak_counter++;
  }

  weak_ptr(weak_ptr&& ptr)
      : _sptr(ptr._sptr)
      , _block(ptr._block) {
    ptr._sptr = nullptr;
    ptr._block = nullptr;
  }

  weak_ptr& operator=(const weak_ptr& ptr) {
    if (this == &ptr) return *this;
    _sptr = ptr._sptr;
    _block = ptr._block;
    _block->weak_counter++;
    return *this;
  }

  weak_ptr& operator=(weak_ptr&& ptr) {
    if (this == &ptr) return *this;
    _sptr = ptr._sptr;
    _block = ptr._block;
    ptr._sptr = nullptr;
    ptr._block = nullptr;
    return *this;
  }

  weak_ptr& operator=(const shared_ptr<T>& sptr) {
    _sptr = &sptr;
    _block = detail::get_block(sptr);
    _block->weak_counter++;
    return *this;
  }

  bool expired() const {
    return _block->shared_counter == 0;
  }

  const shared_ptr<T> lock() const {
    if (not expired()) return *_sptr;
    return shared_ptr<T>(_block);
  }

  ~weak_ptr() {
    _release_block();
  }
};

}  // namespace cleverptr

#endif  // _CLEVERPTR_WEAK_PTR_HPP_
