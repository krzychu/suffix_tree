Suffix Tree implementation
==========================

`suffix_tree` library is a C++ implementation of
[Ukkonen](http://www.cs.helsinki.fi/u/ukkonen/SuffixT1withFigs.pdf) algorithm.


## Compilation 
`suffix_tree` is header-only library, so you don't have to compile anything,
however if you want to run tests and examples your should compile them using
standard CMake procedure.


## Library overview
This library consists of three main components:

- **Suffix tree implementation** Ukkonen algorithm and necessary data structures,
all implemented as C++ templates.

- **Algorithm building blocks** DFS and root-to-node traversals, which allow 
use of custom visitors to achieve desired effects.

- **Examples and Doxygen documentation** 


## Example : printing all nodes along given path from root
code for this example is also avaliable in `test/path.cpp`

    #include <stree/suffix_tree.h>    
    #include <stree/algorithm/path.h>    
        
    #include <sstream>    
    #include <iostream>    
    #include <cstring>    
    #include <algorithm>    
        
    using namespace stree;    
        
        
        
    class PathDump : public RefPairVisitor<char, Array, Empty>    
    {    
      public:    
        void before    
          (const RefPairVisit<char, Array, Empty> & visit, const Context<char> & context)     
        {    
          // append last character to printed word    
          word_ << context.text[visit.current.end - 1];    
        
          // print current word    
          std::cout << visit.depth << " " << word_.str() << std::endl;    
        }    
        
      private:    
        std::stringstream word_;    
    };    
        
        
        
    int main()    
    {    
      const char * text = "abracadabra";    
        
      // alphabet size = 200, because we deal with ascii characters    
      SuffixTree<char> t(200);    
        
      // add text to the tree    
      std::copy(text, text + strlen(text), std::back_inserter(t));    
        
      // run visitor    
      PathDump dumper;    
      path(t, dumper, text, text + strlen(text));    
        
      return 0;    
    }    


