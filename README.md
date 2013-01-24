Suffix Tree implementation
==========================

This is a C++ implementation of [Ukkonen](http://www.cs.helsinki.fi/u/ukkonen/SuffixT1withFigs.pdf) algorithm.

## Compilation ##
`suffix_tree` is header-only library, so you don't have to compile anything : just put
        
        #include <suffix_tree.h> 

in your program. If you want to run unit tests, you have to compile them using CMake
and GTest library.

TODO:
  - Create node pool for faster node adding
  - Compare speed with other open-source implementations
