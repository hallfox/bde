// bsls_arithmetic.h -*-C++-*-
#ifndef INCLUDED_BSLS_ARITHMETIC
#define INCLUDED_BSLS_ARITHMETIC

#include <bsls_compilerfeatures.h>

namespace BloombergLP {
namespace bsls {

  template <typename T>
  struct Arithmetic_IsStandardInteger;


  struct ArithmeticUtil {

  /// Add two integers, with saturation in case of overflow.
  template <typename T>
  #ifdef BSLS_COMPILERFEATURES_SUPPORT_CONCEPTS
  requires Arithmetic_IsStandardInteger<T>::value
  #endif

  };


}
} // namespace BloombergLP

#endif

// ----------------------------------------------------------------------------
// Copyright 2025 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------- END-OF-FILE ----------------------------------
