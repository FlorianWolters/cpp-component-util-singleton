/**
 * Contains test cases for the `fw::util::MultitonMixin` class.
 *
 * @file    fw/util/multiton_mixin_test.cc
 * @author  Florian Wolters <wolters.fl@gmail.com>
 * @section License
 *
 * Copyright Florian Wolters 2014 (http://blog.florianwolters.de).
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <gtest/gtest.h>

#include "fw/util/multiton_mixin.h"

namespace fw {
namespace util {
namespace testing {

class MultitonExampleImpl final : public MultitonMixin<MultitonExampleImpl> {
  friend class MultitonMixin<MultitonExampleImpl>;
 private:
  /**
   * Initializes a new instance of the MultitonExampleImpl class with the
   * specified key and a value of `false`.
   *
   * @param kKey The key used to identify the object.
   */
  MultitonExampleImpl(std::string const &kKey)
      : MultitonExampleImpl{kKey, false} {
    // NOOP
  }

  /**
   * Initializes a new instance of the MultitonExampleImpl class with the
   * specified key and the specified value.
   *
   * @param kKey The key used to identify the object.
   * @param kValue The value.
   */
  explicit MultitonExampleImpl(std::string const &kKey, bool const kValue)
      : kValue_(kValue) {
    // NOOP
  }

  /**
   * The value of this object.
   */
  bool const kValue_;
};

TEST(MultitonMixinTest, GetInstance_CalledTwiceWithEqualKeysAndEqualValues_ReturnsEqualReferences) {
  ASSERT_EQ(&MultitonExampleImpl::GetInstance("first"), &MultitonExampleImpl::GetInstance("first"));
}

TEST(MultitonMixinTest, GetInstance_CalledTwiceWithEqualKeysAndEqualValuesAndDifferentNumberOfArguments_ReturnsEqualReferences) {
  ASSERT_EQ(&MultitonExampleImpl::GetInstance("first"), &MultitonExampleImpl::GetInstance("first", false));
}

TEST(MultitonMixinTest, GetInstance_CalledTwiceWithEqualKeysAndNotEqualValues_ReturnsEqualReferences) {
  ASSERT_EQ(&MultitonExampleImpl::GetInstance("first"), &MultitonExampleImpl::GetInstance("first", true));
}

TEST(MultitonMixinTest, GetInstance_CalledTwiceWithNotEqualKeysAndEqualValues_ReturnsNotEqualReferences) {
  ASSERT_FALSE(&MultitonExampleImpl::GetInstance("first") == &MultitonExampleImpl::GetInstance("second"));
}

TEST(MultitonMixinTest, GetInstance_CalledTwiceWithNotEqualKeysAndNotEqualValues_ReturnsNotEqualReferences) {
  ASSERT_FALSE(&MultitonExampleImpl::GetInstance("first") == &MultitonExampleImpl::GetInstance("second", true));
}

}  // namespace testing
}  // namespace util
}  // namespace fw
