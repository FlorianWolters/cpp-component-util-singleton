# fw::util::Singleton

The *Singleton* and *Multiton* (a. k. a. *Registry of Singletons*) creational
design patterns as a reusable C++11 component.

[![Build Status](https://travis-ci.org/FlorianWolters/cpp-component-util-singleton.svg)](https://travis-ci.org/FlorianWolters/cpp-component-util-singleton)

## Table of Contents (ToC)

* [Introduction](#introduction)
* [Features](#features)
* [Requirements](#requirements)
* [Usage](#usage)
* [Installation](#installation)
* [Testing](#testing)
* [Contributing](#contributing)
* [Credits](#credits)
* [License](#license)

## Introduction

*Singleton* is a *creational* design pattern and defined as follows:

> "Ensure a class only has once instance, and provide a global access point to
> it."

-- E. Gamma, et al. Design Patterns: Elements of Reusable Object-Oriented
software. Westford: Addison-Wesley, 1995.

**fw::util::Singleton** offers modern implementations of the following two
creational design patterns:

* *Singleton*: Implemented in the *Mixin-from-above*
  [fw::util::SingletonMixin][10].
* *Multiton* (*Registry of Singletons*): Implemented in the *Mixin-from-above*
  [fw::util::MultitonMixin][11].

## Features

* Allows to pass parameters to the static *Creation Method* `GetInstance()`. The
  parameters are passed to the `private` or `protected` constructor of the class
  using the component. The C++ feature of *Perfect Forwarding* is used to
  implement that behavior.
* Allows a number of unlimited classes to use the component.
    * A class which uses the [`SingletonMixin`][10] (or [`MultitonMixin`][11])
      can still inherit from another class. The C++ feature *Multiple
      Inheritance* can be used used to implement such a structure.
    * A class which extends a class using the [`SingletonMixin`][10] (or
     [`MultitonMixin`][11]) is a **new** *Singleton* (or *Multiton*). Therefore
     the component supports inheritance.
* The [`SingletonMixin`][10] is thread-safe, the [`MultitonMixin`][11] is not
  thread-safe.

## Requirements

### Production

* [CMake][1]
* [GNU Compiler Collection (GCC)][2] >= 4.6

### Development

* [Google Test][3]

## Installation

WIP

## Usage

### Singleton

    #include "fw/util/singleton_mixin.h"

    class MySingleton final : public fw::util::SingletonMixin<MySingleton> {
      friend class fw::util::SingletonMixin<MySingleton>;
    };

### Multiton

    #include "fw/util/multiton_mixin.h"

    class MyMultiton final : public fw::util::MultitonMixin<MyMultiton> {
      friend class fw::util::MultitonMixin<MyMultiton>;
     protected:
      MyMultiton(std::string const &kKey) {
        // NOOP
      }
    };

## Testing

    mkdir build && cmake .. && make && ctest

## Contributing

Please see [CONTRIBUTING](CONTRIBUTING.md) for details.

## Credits

* [Florian Wolters][100]
* [All Contributors][101]

## License

Copyright Florian Wolters 2014 (http://blog.florianwolters.de).

Distributed under the Boost Software License, Version 1.0. (See accompanying
file [LICENSE_1_0.txt](LICENSE_1_0.txt) or copy at
<http://www.boost.org/LICENSE_1_0.txt>)

[1]: http://cmake.org
     "CMake"
[2]: https://gcc.gnu.org
     "GCC, the GNU Compiler Collection"
[3]: https://code.google.com/p/googletest
     "Google Test"
[10]: include/fw/util/singleton_mixin.cc
      "fw::util::SingletonMixin"
[11]: include/fw/util/multiton_mixin.cc
      "fw::util::MultitonMixin"
[100]: https://github.com/FlorianWolters
       "FlorianWolters · GitHub"
[101]: https://github.com/FlorianWolters/cpp-component-util-singleton/contributors
       "Contributors to FlorianWolters/cpp-component-util-singleton"
