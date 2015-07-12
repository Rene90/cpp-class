////////////////////////////////////////////////////////////////////////////////
// wgraphedge.hpp
// Implements a weighted graph edge type based on template parameters
// RK, 12.07.2015
////////////////////////////////////////////////////////////////////////////////

#ifndef __WGRAPH_EDGE_HPP__
#define __WGRAPH_EDGE_HPP__

#include "graphedge.hpp"

namespace MyCoolGraphLibrary {
  
  /// WeightedGraphEdge represents a weighted directed graph edge
  template<typename NODE,typename LABEL>
  struct WeightedGraphEdge : public SimpleGraphEdge<NODE,LABEL>
  {
  public:
    typedef NODE    Node;
    typedef LABEL   Label;
    typedef unsigned int Weight;

    WeightedGraphEdge(const Node& s, const Label& l, const Node& t, const Weight& w)
    : SimpleGraphEdge<NODE,LABEL>(s, l, t), m_weight(w)
    {}

    WeightedGraphEdge(const Node& s, const Label& l, const Node& t)
    : SimpleGraphEdge<NODE,LABEL>(s, l, t), m_weight(1)
    {}
    
    const Weight& weight() const { return m_weight; }
    
  protected:
    Weight m_weight;
  }; // WeightedGraphEdge

} // namespace MyCoolGraphLibrary

#endif
