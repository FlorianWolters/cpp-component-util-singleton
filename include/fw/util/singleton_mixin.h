/**
 * Declares the `fw::util::SingletonMixin` template class.
 *
 * @file    fw/util/singleton_mixin.h
 * @author  Florian Wolters <wolters.fl@gmail.com>
 * @section License
 *
 * Copyright Florian Wolters 2014 (http://blog.florianwolters.de).
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef FW_UTIL_SINGLETON_MIXIN_H_
#define FW_UTIL_SINGLETON_MIXIN_H_

#include <functional>

#include "fw/core/uncopyable_mixin.h"

namespace fw {
namespace util {

/**
 * The `SingletonMixin<TDerived>` template class is a generic implementation of
 * the *Singleton* creational design pattern.
 *
 * The class is thread-safe. It uses perfect forwarding to pass the arguments
 * given to the static `GetInstance` function to the corresponding constructor.
 *
 * `SingletonMixin<TDerived>` implements the *Curiously Recurring Template
 * Pattern (CRTP)* (a. k. a. *Mixin-from-above*) idiom.
 *
 * @author Florian Wolters <wolters.fl@gmail.com>
 * @tparam TDerived The type of the derived class.
 */
template <class TDerived>
class SingletonMixin : public core::UncopyableMixin<SingletonMixin<TDerived>> {
 public:
  /**
   * Returns the *Singleton* instance of the class using this
   * *Mixin-from-above*.
   *
   * @tparam TArgs The types of the arguments passed to a constructor of the
   *    derived class.
   *
   * @param args The arguments passed to a constructor of the derived class.
   *
   * @return The *Singleton* instance.
   */
  template <typename ... TArgs>
  static TDerived& GetInstance(TArgs... args) {
    static auto function = std::bind(CreateInstance<TArgs...>, args...);

    return CallCreateInstance(function);
  }

 protected:
  /**
   * Initializes a new instance of the `SingletonMixin<TDerived>` class.
   */
  SingletonMixin() = default;

  /**
   * Finalizes an instance of the `SingletonMixin<TDerived>` class.
   */
  ~SingletonMixin() = default;

 private:
  static TDerived& CallCreateInstance(
      const std::function<TDerived&()> &kFunction) {
    static TDerived& instance_reference = kFunction();

    return instance_reference;
  }

  template <typename ... TArgs>
  static TDerived& CreateInstance(TArgs... args) {
    static TDerived instance{std::forward<TArgs>(args)...};

    return instance;
  }
};

}  // namespace util
}  // namespace fw

#endif  // FW_UTIL_SINGLETON_MIXIN_H_
