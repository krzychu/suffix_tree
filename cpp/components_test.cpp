#include "suffix_tree.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace stree;

const int asize = 10;

Text str2text(const char * str, const char * end = 0)
{
  Text t; 
  while(*str && str != end){
    t.push_back(*str - 'a');
    str++;
  }
  return t;
}


class ComponentsTest : public ::testing::Test
{
  protected:
    ComponentsTest() 
      : t(str2text("abcdabc")),
      cx(t)
    {}

    virtual void SetUp(){
      root = new Node(0, 0, asize);

      root_abc = new Node(0, 3, asize);
      root->children[0] = root_abc;

      root_c = new Node(2, 3, asize);
      root->children[2] = root_c;

      root_abc_a = new Node(0,1, asize); 
      root_abc->children[0] = root_abc_a;

      root_abc_d = new Node(3, 4, asize);
      root_abc->children[3] = root_abc_d;

      root_c_b = new Node(1, 2, asize);
      root_c->children[1] = root_c_b;
    }

    virtual void TearDown(){
      delete root; 
    }
  
    Text t;
    Context cx;

    Node * root;
    Node * root_abc, * root_c;
    Node * root_abc_a, * root_abc_d, * root_c_b;
};


TEST(Substr, CalculatesSize)
{
  Substr s(0, 10);
  ASSERT_EQ(10, s.size());
}


TEST_F(ComponentsTest, CheckIfItsImplicit)
{
  RefPair rp(0, 4, 5);
  ASSERT_TRUE(rp.implicit());
  rp.begin = 5;
  ASSERT_FALSE(rp.implicit());
}


TEST_F(ComponentsTest, NextReturnsCorrectChild)
{
  Node * root = new Node(0, 0, asize);
  Node * child = new Node(0, 3, asize);
  root->children[0] = child;
  RefPair rp(root, 0, 1);
  ASSERT_EQ(child, rp.next(cx));
  delete root;
}


TEST_F(ComponentsTest, HasTransitionForExplicitNode)
{
  RefPair rp(root, 0, 0);
  ASSERT_TRUE(rp.has_trans(cx, 0)); 
  ASSERT_TRUE(rp.has_trans(cx, 2)); 
  ASSERT_FALSE(rp.has_trans(cx, 1)); 
  ASSERT_FALSE(rp.has_trans(cx, 3)); 
}


TEST_F(ComponentsTest, HasTransitionForImplicitNode)
{
  RefPair rp(root, 4, 5);
  ASSERT_TRUE(rp.has_trans(cx, 1));
  ASSERT_FALSE(rp.has_trans(cx, 0));
  ASSERT_FALSE(rp.has_trans(cx, 2));
  ASSERT_FALSE(rp.has_trans(cx, 3));
}


TEST_F(ComponentsTest, CanonizeWorks)
{
  RefPair rp(root, 0, 4);
  rp.canonize(cx);
  
  ASSERT_FALSE(rp.implicit());
  ASSERT_EQ(4, rp.begin);
  ASSERT_EQ(4, rp.end);
  ASSERT_EQ(root_abc_d, rp.node);
}


TEST_F(ComponentsTest, SplitWorks)
{
  RefPair where(root, 4, 6);
  Node * mid = root->split(cx, where);
  
  ASSERT_EQ(where.size(), mid->size());
  ASSERT_EQ(root_abc, mid->children[2]);
  ASSERT_EQ(1, root_abc->size());
  ASSERT_EQ(mid, root->children[0]);
}
