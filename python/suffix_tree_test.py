import unittest
from suffix_tree import *


class NodeTest(unittest.TestCase):
  def test_holds_children_references(self):
    node = Node(1)
    c1 = Node(2)
    c2 = Node(4)
    node['a'] = c1
    node['b'] = c2

    self.assertEqual(c1, node['a'])
    self.assertEqual(c2, node['b'])
    self.assertEqual(None, node['c'])

  def test_splits(self):
    text = "abcdefgh"
    node = Node(0)
    child = Node(5)
    node['a'] = child;
    ref = RefPair(node, 0, 3)

    u = node.split(ref, text)
    
    self.assertEqual(3, u.to_parent)
    self.assertEqual(u, node['a'])
    self.assertEqual(child, u['d'])
    self.assertEqual(2, child.to_parent)





class AuxTest(unittest.TestCase):
  def test_always_returns_root(self):
    root = Node(3)
    aux = Aux(root)

    self.assertEqual(root, aux['a'])
    self.assertEqual(root, aux[None])





class RefPairTest(unittest.TestCase):

  def test_explicit(self):
    ref = RefPair(None, 10, 10)
    self.assertTrue(ref.explicit())

    ref = RefPair(None, 10, 12)
    self.assertFalse(ref.explicit())


  def test_canonize(self):
    text = "programming motherfucker"  
    nodes = []
    step = 3
    for k in range(5):
      node = Node(step)
      if k:
        nodes[-1][text[(k-1) * step]] = node
      nodes.append(node)
  

    ref = RefPair(nodes[1], 3, 8)
    ref.canonize(text)

    self.assertEqual(nodes[2], ref.node)
    self.assertEqual(6, ref.begin)
    self.assertEqual(8, ref.end)


  def test_has_transition(self):
    text = "abcd" 
    root = Node(0)
    child = Node(3)
    root['a'] = child

    ref = RefPair(root, 0, 0)
    self.assertEqual(True, ref.has_transition('a', text))
    self.assertEqual(False, ref.has_transition('b', text))
    
    ref = RefPair(root, 0, 1)
    self.assertEqual(True, ref.has_transition('b', text))
    self.assertEqual(False, ref.has_transition('c', text))


    

unittest.main()
