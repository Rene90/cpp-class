////////////////////////////////////////////////////////////////////////////////
// reverse.hpp
// Implements a reverse function for a graph class
// RK, 9.07.15
////////////////////////////////////////////////////////////////////////////////


#ifndef __REVERSE_HPP__
#define __REVERSE_HPP__

#include "labeledgraph.hpp"
#include "graphtransform.hpp"

namespace MyCoolGraphLibrary {
  
  template<typename GRAPHEDGE>
  struct GraphReverser
  {
    typedef GRAPHEDGE Edge;
    
    GraphReverser(LabeledDirectedGraph<GRAPHEDGE>& g) : graph(g) {}
    
    void prolog() {}
    void operator()(const typename GRAPHEDGE::Node& node){}
    void operator()(const GRAPHEDGE& edge)
    {
      graph.add(Edge(edge.target(),edge.label(),edge.source()));
    }
    void epilog(){}

    LabeledDirectedGraph<GRAPHEDGE>& graph;
  };
  
  template<class GRAPHEDGE>
  LabeledDirectedGraph<GRAPHEDGE> graph_reverse(const LabeledDirectedGraph<GRAPHEDGE>& g)
  {
    LabeledDirectedGraph<GRAPHEDGE> g_rev = LabeledDirectedGraph<GRAPHEDGE>();
    GraphReverser<GRAPHEDGE> reverser(g_rev);
    graph_transform(g,reverser);
    return g_rev;
  }
}

#endif
