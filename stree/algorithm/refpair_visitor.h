#ifndef STREE_REFPAIR_VISITOR_H_
#define STREE_REFPAIR_VISITOR_H_

namespace stree
{

template<class T, template<class> class CC, class NE>
struct RefPair;

template<class T>
class Context;



/*!
 * Reference pair visitor parameters
 */
template<class T, template<class> class CC, class NE>
struct RefPairVisit 
{
  //! reference pair to process 
  RefPair<T, CC, NE> current;

  //! length of uncompressed path from root to current state
  int depth;

  /*!
   * @param rp reference pair to process
   * @param d depth of reference pair 
   */
  RefPairVisit(const RefPair<T, CC, NE> & rp, int d)
    : current(rp), depth(d) {}
};



/*!
 * Visitor that processes every state on path
 */
template<class T, template<class> class CC, class NE>
struct RefPairVisitor 
{

  /*!
   * Gets called before next states are visited
   * @param visit Visit object describing current state 
   * @param context tree context
   */
  virtual void before
    (const RefPairVisit<T, CC, NE> & visit, const Context<T> & context) 
  {}

  /*!
   * Gets called after next states are visited
   * @param visit Visit object describing current state 
   * @param context tree context
   */
  virtual void after
    (const RefPairVisit<T, CC, NE> & visit, const Context<T> & context) {}

  virtual ~RefPairVisitor() {}
};


}

#endif
