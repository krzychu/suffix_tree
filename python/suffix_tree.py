import sys
import pdb
import math


class Node:
  def __init__(self, begin, end = sys.maxint, slink = None):
    self.slink = slink
    self.t = {}
    self.begin = begin
    self.end = end

  def __getitem__(self, idx):
    if idx in self.t:
      return self.t[idx]
    else: 
      return None

  def __setitem__(self, idx, itm):
    self.t[idx] = itm
  
  def split(self, ref, text):
    assert ref.node == self
    first_letter = text[ref.begin]
    son = self.t[first_letter]
    last_letter = text[son.begin + len(ref)]
    new = Node(ref.begin, ref.end)
    
    self.t[first_letter] = new
    new[last_letter] = son
    son.begin += len(ref)
    return new

  def __len__(self):
    return self.end - self.begin

  def debug(self, indent = ""):
    sys.stdout.write("%slen = %d\n" % (indent, len(self)))
    sys.stdout.write("%sslink = %s\n" % (indent, str(self.slink)))
    sys.stdout.write("%sself = %s\n" % (indent, str(self)))
    sys.stdout.write("%sbegin = %s\n" % (indent, str(self.begin)))

    for k in self.t:
      sys.stdout.write("%sletter = %s\n" % (indent, str(k)))
      self.t[k].debug(indent + "   ")



class Aux(Node):
  def __init__(self, root):
    self.root = root

  def __getitem__(self, x):
    return self.root



class RefPair:
  def __init__(self, node, begin, end):
    self.node = node
    self.begin = begin
    self.end = end
  
  def explicit(self):
    return len(self) <= 0

  def canonize(s, text):
    while not s.explicit() and len(s.next(text)) <= len(s):
      s.node = s.next(text)
      s.begin += len(s.node)

  def next(self, text):
    return self.node[text[self.begin]]

  def __len__(self):
    return self.end - self.begin
    
  def has_transition(self, x, text):
    if self.explicit():
      return self.node[x] != None
    else:
      child = self.node[text[self.begin]] 
      pos = child.begin + len(self)
      return text[pos] == x

       
  
  def debug(self):
    sys.stdout.write("===============REF\n")
    sys.stdout.write("node : " + str(self.node))
    sys.stdout.write("\nbegin : " + str(self.begin))
    sys.stdout.write("\nend : " + str(self.end))
    sys.stdout.write("\n")
    


class Tree:
  def __init__(self):
    self.root = Node(-1, 0)
    self.aux = Aux(self.root)
    self.root.slink = self.aux
    self.active = RefPair(self.root, 0, 0)
    self.text = []


  def append(self, x):
    last_parent = self.root
    parent = None
    self.text.append(x)
    while not self.active.has_transition(x, self.text):
      parent = self.active.node
      # add that transition
      if not self.active.explicit():
        parent = parent.split(self.active, self.text)

      # add new edge
      parent[x] = Node(self.active.end, sys.maxint)

      # update suffix link
      if last_parent != self.root: last_parent.slink = parent
      last_parent = parent

      # move active
      self.active.node = self.active.node.slink
      self.active.canonize(self.text)
      

    # add last suffix link
    if last_parent != self.root: last_parent.slink = parent

    # move active
    self.active.end += 1
    self.active.canonize(self.text)

  

if __name__ == "__main__":
  t = Tree()
  for l in "bananax":
    t.append(l)
  print "\n\n\n tree dump"
  t.root.debug()
  print "ok"
