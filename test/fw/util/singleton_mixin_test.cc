/**
 * Contains test cases for the `fw::util::SingletonMixin` class.
 *
 * @file    fw/util/singleton_mixin_test.cc
 * @author  Florian Wolters <wolters.fl@gmail.com>
 * @section License
 *
 * Copyright Florian Wolters 2014 (http://blog.florianwolters.de).
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "gtest/gtest.h"

#include "fw/util/singleton_mixin.h"

namespace fw {
namespace util {
namespace testing {

class SingletonExampleImpl final : public SingletonMixin<SingletonExampleImpl> {
  friend class SingletonMixin<SingletonExampleImpl>;
 private:
  /**
   * Initializes a new instance of the SingletonExampleImpl class with a value
   * of `false`.
   */
  SingletonExampleImpl() : SingletonExampleImpl{false} {
    // NOOP
  }

  /**
   * Initializes a new instance of the SingletonExampleImpl class with the
   * specified value.
   *
   * @param kValue The value.
   */
  explicit SingletonExampleImpl(bool const kValue) : kValue_(kValue) {
    // NOOP
  }

  /**
   * The value of this object.
   */
  bool const kValue_;
};

TEST(SingletonMixinTest, GetInstance_CalledTwiceWithoutArguments_ReturnsEqualReferences) {
  ASSERT_EQ(&SingletonExampleImpl::GetInstance(), &SingletonExampleImpl::GetInstance());
}

TEST(SingletonMixinTest, GetInstance_CalledTwiceWithEqualArguments_ReturnsEqualReferences) {
  ASSERT_EQ(&SingletonExampleImpl::GetInstance(true), &SingletonExampleImpl::GetInstance(true));
}

TEST(SingletonMixinTest, GetInstance_CalledTwiceWithNotEqualArguments_ReturnsEqualReferences) {
  ASSERT_EQ(&SingletonExampleImpl::GetInstance(false), &SingletonExampleImpl::GetInstance(true));
}

TEST(SingletonMixinTest, GetInstance_CalledOnceWithAndOnceWithoutArguments_ReturnsEqualReferences) {
  ASSERT_EQ(&SingletonExampleImpl::GetInstance(), &SingletonExampleImpl::GetInstance(true));
}

TEST(SingletonMixinTest, GetInstance_CalledTwiceWithoutArgumentsComparingConstAndNonConst_ReturnsEqualReferences) {
  auto const &kConstSingleton = SingletonExampleImpl::GetInstance();

  ASSERT_EQ(&kConstSingleton, &SingletonExampleImpl::GetInstance());
}

}  // namespace testing
}  // namespace util
}  // namespace fw

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
