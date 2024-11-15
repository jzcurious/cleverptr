#ifndef _BLOCK_HPP_
#define _BLOCK_HPP_

#include <utility>

namespace cleverptr::detail {

template <class T>
struct Block final {
  std::size_t shared_counter;
  std::size_t weak_counter;
  T object;

  template <class... Ts>
  Block(Ts&&... args)
      : shared_counter(0)
      , weak_counter(0)
      , object(std::forward<Ts>(args)...) {}
};

}  // namespace cleverptr::detail

#endif  //   _BLOCK_HPP_
