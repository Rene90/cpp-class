////////////////////////////////////////////////////////////////////////////////
// dijkstra.hpp
// Implements the Dijkstra algorithm for a weighted directed graph class
// RK, 9.07.15
////////////////////////////////////////////////////////////////////////////////


#ifndef __DIJKSTRA_HPP__
#define __DIJKSTRA_HPP__

#include <queue>

#include "labeledgraph.hpp"
#include "graphtransform.hpp"



namespace MyCoolGraphLibrary {
    
  namespace detail {
    template<typename GRAPHEDGE> class GraphShortestPath;
  }

  /**
    @brief depth_first_search() implements depth-first search from a given node
  */  
  template<typename GRAPHEDGE, typename VISITOR>
  void distance_search(const LabeledDirectedGraph<GRAPHEDGE>& g, 
                          const typename GRAPHEDGE::Node& start,
                          VISITOR& visitor)
  {
    // Instantiate the algorithm with the given graph
    detail::GraphShortestPath<GRAPHEDGE> shortest_path_algorithm(g);
    // Start the search at the node
    shortest_path_algorithm.dijkstra(start,visitor);
  }

  namespace detail {
    
    template<typename GRAPHEDGE>
    class GraphShortestPath
    {
    public:
      typedef unsigned int                                  Weight;
      typedef typename GRAPHEDGE::Node                      Node;

    private:
      struct DijkstraComp {
        typedef std::pair<GRAPHEDGE,Weight> NodeDist;
        
        bool operator() (const NodeDist& lhs, const NodeDist& rhs) const
        {
          return (lhs.second < rhs.second);
        }
      };
    public:
      /** 
        @brief Constructor
        @param g the graph
        @param action_when_first_discovered when true, the action defined by
               the visitor object will be performed when a node is seen for
               the first time (when it gets grey). Otherwise, the action takes
               place when the node gets black
      */
      GraphShortestPath(const LabeledDirectedGraph<GRAPHEDGE>& g) 
      : graph(g)
      {}

      template<typename VISITOR>
      void dijkstra(const Node& start_node, VISITOR& visitor)
      {
        NodeDist tmpDist;
        
        visitor(start_node);
        distances[start_node] = 0;
        auto& neighbours = graph[start_node];
        for(auto e = neighbours.begin(); e != neighbours.end(); ++e) {
          distHeap.emplace(NodeDist(*e,e->weight()));
        }

        while(!distHeap.empty()) {
          tmpDist = distHeap.top();
          distHeap.pop();

          if(distances.find(tmpDist.first.target()) != distances.end()) {
            // We already have this node in the distance map
            continue;
          }
          visitor(tmpDist.first.target());
          distances[tmpDist.first.target()] = tmpDist.second;
          

          auto& nextNodes = graph[tmpDist.first.target()];
          for(auto e = nextNodes.begin(); e != nextNodes.end(); ++e) {
            distHeap.emplace(NodeDist(*e,tmpDist.second + e->weight()));
          }
        }
      }

    private:
      typedef std::map<Node,Weight> DistanceMap;
      typedef std::pair<GRAPHEDGE,Weight> NodeDist;
      typedef std::priority_queue<NodeDist, std::vector<NodeDist>, DijkstraComp> DistanceHeap; 
      
      const LabeledDirectedGraph<GRAPHEDGE>& graph;
      DistanceMap distances;
      DistanceHeap distHeap;
    };
  }
}

#endif

