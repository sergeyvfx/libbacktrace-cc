// Copyright (C) 2016 libbacktrace-cc authors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
// Author: sergey@blender.org (Sergey Sharybin)

#include "backtrace/symbolize.h"

namespace bt {

Symbolize *Symbolize::create(StackTrace *stack_trace) {
#ifdef BACKTRACE_HAS_BFD
  Symbolize *bfd_symbolie = internal::symbolize_create_bfd(stack_trace);
  if (bfd_symbolie != NULL) {
    return bfd_symbolie;
  }
#endif  // BACKTRACE_HAS_BFD
#ifdef BACKTRACE_HAS_EXECINFO
  return internal::symbolize_create_execinfo(stack_trace);
#else
  return internal::symbolize_create_stub(stack_trace);
#endif
}

Symbolize::~Symbolize() {
  if (stack_trace_ != NULL) {
    delete stack_trace_;
  }
}

}  // namespace bt