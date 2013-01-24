#include "suffix_tree.h"
#include <gtest/gtest.h>
#include <iostream>


using namespace stree;

const int asize = 'z' + 1;
typedef std::vector<int> Text;


class ComponentsTest : public ::testing::Test
{
  protected:
    ComponentsTest() 
      : str("abcdabc"), text(str.begin(), str.end()), cx(text)
    {}

    virtual void SetUp(){
      root = new Node<int>(0, 0, asize);

      root_abc = new Node<int>(0, 3, asize);
      root->children['a'] = root_abc;

      root_c = new Node<int>(2, 3, asize);
      root->children['c'] = root_c;

      root_abc_a = new Node<int>(0,1, asize); 
      root_abc->children['a'] = root_abc_a;

      root_abc_d = new Node<int>(3, 4, asize);
      root_abc->children['d'] = root_abc_d;

      root_c_b = new Node<int>(1, 2, asize);
      root_c->children['b'] = root_c_b;
    }

    virtual void TearDown(){
      delete root; 
    }
  

    const std::string str;
    std::vector<int> text;
    Context<int> cx;

    Node<int> * root;
    Node<int> * root_abc, * root_c;
    Node<int> * root_abc_a, * root_abc_d, * root_c_b;
};


TEST(Substr, CalculatesSize)
{
  Substr s(0, 10);
  ASSERT_EQ(10, s.size());
}

TEST_F(ComponentsTest, CheckIfItsImplicit)
{
  RefPair<int> rp(0, 4, 5);
  ASSERT_TRUE(rp.implicit());
  rp.begin = 5;
  ASSERT_FALSE(rp.implicit());
}


TEST_F(ComponentsTest, NextReturnsCorrectChild)
{
  Node<int> * root = new Node<int>(0, 0, asize);
  Node<int> * child = new Node<int>(0, 3, asize);
  root->children['a'] = child;
  RefPair<int> rp(root, 0, 1);
  ASSERT_EQ(child, rp.next(cx));
  delete root;
}


TEST_F(ComponentsTest, HasTransitionForExplicitNode)
{
  RefPair<int> rp(root, 0, 0);
  ASSERT_TRUE(rp.has_trans(cx, 'a')); 
  ASSERT_TRUE(rp.has_trans(cx, 'c')); 
  ASSERT_FALSE(rp.has_trans(cx, 'b')); 
  ASSERT_FALSE(rp.has_trans(cx, 'd')); 
}


TEST_F(ComponentsTest, HasTransitionForImplicitNode)
{
  RefPair<int> rp(root, 4, 5);
  ASSERT_TRUE(rp.has_trans(cx, 'b'));
  ASSERT_FALSE(rp.has_trans(cx, 'a'));
  ASSERT_FALSE(rp.has_trans(cx, 'c'));
  ASSERT_FALSE(rp.has_trans(cx, 'd'));
}


TEST_F(ComponentsTest, CanonizeWorks)
{
  RefPair<int> rp(root, 0, 4);
  rp.canonize(cx);
  
  ASSERT_FALSE(rp.implicit());
  ASSERT_EQ(4, rp.begin);
  ASSERT_EQ(4, rp.end);
  ASSERT_EQ(root_abc_d, rp.node);
}


TEST_F(ComponentsTest, SplitWorks)
{
  RefPair<int> where(root, 4, 6);
  Node<int> * mid = root->split(cx, where);
  
  ASSERT_EQ(where.size(), mid->size());
  ASSERT_EQ(root_abc, mid->children['c']);
  ASSERT_EQ(1, root_abc->size());
  ASSERT_EQ(mid, root->children['a']);
}
