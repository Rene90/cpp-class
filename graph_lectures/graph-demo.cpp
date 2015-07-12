////////////////////////////////////////////////////////////////////////////////
// graph-demo.cpp
// Demonstrates the new very cool graph library
// TH, 6.7.15
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "graphedge.hpp"
#include "wgraphedge.hpp"
#include "labeledgraph.hpp"
#include "dfs.hpp"
#include "bfs.hpp"
#include "graphoutput.hpp"
#include "reverse.hpp"
#include "dijkstra.hpp"

// Import some graph data types
using MyCoolGraphLibrary::SimpleGraphEdge;
using MyCoolGraphLibrary::WeightedGraphEdge;
using MyCoolGraphLibrary::LabeledDirectedGraph;

// Define a graph edge
typedef WeightedGraphEdge<std::string,std::string> Edge;

/// Visitor object which prints a node on a stream
template<typename NODE>
struct NodePrinter
{
  /// Constructor
  NodePrinter(std::ostream& o=std::cout) : out(o) {}
  /// Overloaded function call operator which is called when a graph node
  /// is discovered
  void operator()(const NODE& n) { out << n << std::endl; }

  std::ostream& out;  
}; // NodePrinter

/// Visitor object which stores a node in a vector
template<typename NODE>
class NodeStorer
{
public:  
  /// Constructor
  NodeStorer(std::vector<NODE>& v) : store(v) {}
    
  /// Overloaded function call operator which is called when a graph node
  /// is discovered
  void operator()(const NODE& n) { store.push_back(n); }

  // Return the nodes
  const std::vector<NODE>& get_nodes() const { return store; }
    
private: 
  std::vector<NODE>& store;
}; // NodeStorer

  
int main()
{
  LabeledDirectedGraph<Edge> movies;
  
  movies.add(Edge("Sigourny Weaver","performed_in","Alien"));
  movies.add(Edge("Ridley Scott ","directed","Alien"));
  movies.add(Edge("Ridley Scott ","directed","Body of lies"));
  movies.add(Edge("John Hurt","performed_in","Alien"));
  movies.add(Edge("Leonardo diCaprio","performed_in","Titanic"));
  movies.add(Edge("Leonardo diCaprio","performed_in","Body of lies"));
  movies.add(Edge("Leonardo diCaprio","performed_in","The Departed"));
  movies.add(Edge("Martin Scorsese","directed","The Departed"));
  movies.add(Edge("Kate Winslet","performed_in","Titanic"));
  movies.add(Edge("James Cameron","directed","Titanic"));
  std::cout << movies << std::endl;

  std::cout << "\nDo a DFS on the graph and print the nodes in the discovery order:\n";
  NodePrinter<Edge::Node> output_nodes_on(std::cout);
  MyCoolGraphLibrary::depth_first_search(movies,output_nodes_on,true);
  
  LabeledDirectedGraph<Edge> man_dress_up;
  man_dress_up.add(Edge("troucers","before","shoes"));
  man_dress_up.add(Edge("socks","before","shoes"));
  man_dress_up.add(Edge("slip","before","troucers"));
  man_dress_up.add(Edge("undershirt","before","shirt"));
  man_dress_up.add(Edge("shirt","before","jacket"));
  man_dress_up.add(Edge("jacket","before","coat"));
  man_dress_up.add(Edge("shirt","before","tie"));
  
  std::ofstream dot_out("dress-up.dot");
  MyCoolGraphLibrary::graph_as_dot(man_dress_up,dot_out);

  std::cout << "\nDo a DFS on the dressing graph:\n";
  // Create a function object which stores nodes in a vector
  std::vector<Edge::Node> topological_order;
  NodeStorer<Edge::Node> node_storer(topological_order);
  
  // Perform the topological search
  MyCoolGraphLibrary::depth_first_search(man_dress_up,node_storer,false);
  
  // Output the topological order
  std::cout << "A possible order for a man to dress is the following:\n";
  for (auto n = topological_order.rbegin(); n != topological_order.rend(); ++n) {
    std::cout << *n << std::endl;
  }
  
  LabeledDirectedGraph<Edge> lexicon;
  
  lexicon.add(Edge("<>","c","c"));
  lexicon.add(Edge("<>","f","f"));
  lexicon.add(Edge("<>","d","d"));
  lexicon.add(Edge("<>","r","r"));
  lexicon.add(Edge("c","a","ca"));
  lexicon.add(Edge("ca","t","cat"));
  lexicon.add(Edge("d","o","do"));
  lexicon.add(Edge("do","g","dog"));
  lexicon.add(Edge("f","o","fo"));
  lexicon.add(Edge("f","r","fr"));
  lexicon.add(Edge("r","a","ra"));
  lexicon.add(Edge("ra","t","rat"));
  lexicon.add(Edge("fr","o","fro"));
  lexicon.add(Edge("fro","g","frog"));
  
  std::cout << "\nDo a BFS on the lexicon trie:\n";
  MyCoolGraphLibrary::breadth_first_search(lexicon,"<>",output_nodes_on);
  
  std::cout << "\nPrint graph in dot representation:\n";
  std::ofstream dot_out2("lexicon.dot");
  MyCoolGraphLibrary::graph_as_dot(lexicon,dot_out2);

  LabeledDirectedGraph<Edge> lexiconRev;
  lexiconRev = MyCoolGraphLibrary::graph_reverse(lexicon);

  std::cout << lexiconRev << std::endl;
  std::cout << "\nDo a BFS on the lexiconRev trie:\n";
  MyCoolGraphLibrary::breadth_first_search(lexiconRev,"cat",output_nodes_on);
  
  std::cout << "\nPrint graph 2 in dot representation:\n";
  std::ofstream dot_out3("lexiconRev.dot");
  MyCoolGraphLibrary::graph_as_dot(lexiconRev,dot_out3);

  std::cout << "\nUse Dijkstras algorithm to find shortest paths from start to every other node:\n";
  MyCoolGraphLibrary::distance_search(lexicon,"<>",output_nodes_on);
}
