#ifndef _BLOCK_HPP_
#define _BLOCK_HPP_

#include <utility>

namespace cleverptr::detail {

template <class T>
struct Block final {
  std::size_t counter;
  T object;

  template <class... Ts>
  Block(Ts&&... args)
      : counter(1)
      , object(std::forward<Ts>(args)...) {}
};

}  // namespace cleverptr::detail

#endif  //   _BLOCK_HPP_
