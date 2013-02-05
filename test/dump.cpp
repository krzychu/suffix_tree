#include <algorithm>
#include <iostream>
#include <cstring>

#include <stree/suffix_tree.h>
#include <stree/algorithm/dump.h>

using namespace stree;

int main(){
  SuffixTree<char> t(200);  
  const char * text = "abracadabra";
  std::copy(text, text + strlen(text), std::back_inserter(t));

  dump(t, std::cout);
}
