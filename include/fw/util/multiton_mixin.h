/**
 * Declares the `fw::util::MultitonMixin` template class.
 *
 * @file    fw/util/multiton_mixin.h
 * @author  Florian Wolters <wolters.fl@gmail.com>
 * @section License
 *
 * Copyright Florian Wolters 2014 (http://blog.florianwolters.de).
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef FW_UTIL_MULTITON_MIXIN_H_
#define FW_UTIL_MULTITON_MIXIN_H_

#include <functional>
#include <map>
#include <memory>
#include <string>

namespace fw {
namespace util {

/**
 * The `MultitonMixin<TDerived>` template class is a generic implementation of
 * the *Multiton* (a. k. a. *Registry of Singletons*) creational design pattern.
 *
 * The class is **not** thread-safe. It uses perfect forwarding to pass the
 * arguments given to the static `GetInstance` function to the corresponding
 * constructor.
 *
 * `MultitonMixin<TDerived>` implements the *Curiously Recurring Template
 * Pattern (CRTP)* (a. k. a. *Mixin-from-above*) idiom.
 *
 * @author Florian Wolters <wolters.fl@gmail.com>
 *
 * @tparam TDerived The type of the derived class.
 */
template <class TDerived, typename TKey = std::string>
class MultitonMixin {
 public:
  /**
   * Returns the *Multiton* instance of the class using this
   * *Mixin-from-above*.
   *
   * @tparam TArgs The types of the arguments passed to a constructor of the
   *    derived class.
   *
   * @param kKey The key used to identify the instance.
   * @param args The arguments passed to a constructor of the derived class.
   * @return The *Multiton* instance.
   */
  template <typename... TArgs>
  static TDerived& GetInstance(TKey const &kKey, TArgs... args) {
    auto const it = instances_.find(kKey);

    if (it != instances_.end()) {
      return *it->second;
    }

    return *instances_.emplace(
        kKey,
        std::shared_ptr<TDerived>{
            new TDerived{kKey, std::forward<TArgs>(args)...}}).first->second;
  }

  /**
   * Deleted copy constructor.
   */
  MultitonMixin(MultitonMixin const &) = delete;

  /**
   * Deleted assignment operator.
   *
   * @return n/a
   */
  MultitonMixin& operator=(MultitonMixin const &) = delete;

 protected:
  /**
   * Initializes a new instance of the `MultitonMixin<TDerived>` class.
   */
  MultitonMixin() = default;

  /**
   * Finalizes an instance of the `MultitonMixin<TDerived>` class.
   */
  ~MultitonMixin() = default;

 private:
  /**
   * Defines the mapping between the unique keys and the *Multiton* instances.
   */
  static std::map<TKey, std::shared_ptr<TDerived>> instances_;
};

template <typename TDerived, typename TKey>
std::map<TKey, std::shared_ptr<TDerived>> MultitonMixin<TDerived, TKey>::instances_;

}  // namespace util
}  // namespace fw

#endif  // FW_UTIL_MULTITON_MIXIN_H_
