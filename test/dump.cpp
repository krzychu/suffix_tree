#include <algorithm>
#include <iostream>
#include <cstring>

#include <suffix_tree.h>
#include <algorithm/dump.h>

using namespace stree;

int main(){
  SuffixTree<char> t(200);  
  const char * text = "abracadabra";
  std::copy(text, text + strlen(text), std::back_inserter(t));

  dump(t, std::cout);
}
