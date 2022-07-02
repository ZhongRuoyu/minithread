# minithread

minithread is a lightweight, self-contained C++17 threading library
implemented with pthread. It is fully compatible with the standard library's
`std::thread`.

Since all the implementation is contained within a single header file, it can
be imported to other projects with no extra effort required.

As a lightweight version of
[stdthread](https://github.com/ZhongRuoyu/stdthread), its implementation is
also based on LLVM's
[libc++](https://github.com/llvm/llvm-project/tree/main/libcxx)
([license](https://github.com/llvm/llvm-project/blob/main/libcxx/LICENSE.TXT)).
However, its implementation details are self-contained, and can be built with
any implementation of C++ standard library.