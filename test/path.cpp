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
      word_ << context.text[visit.current.end - 1];
      std::cout << visit.depth << " " << word_.str() << std::endl;
    }

  private:
    std::stringstream word_;
};



int main()
{

  const char * text = "abracadabra";
  SuffixTree<char> t(200);
  std::copy(text, text + strlen(text), std::back_inserter(t));

  PathDump dumper;
  path(t, dumper, text, text + strlen(text));

  return 0;
}
