#ifndef __FINITEAUTOMATON_HPP__
#define __FINITEAUTOMATON_HPP__

#include <vector>
#include <unordered_set>
#include <iostream>
#include <cassert>
#include <limits>
#include <cstdlib> // for abort()

#include <boost/container/flat_map.hpp>

/// FiniteAutomaton implements a simple finite state automaton
class FiniteAutomaton
{
  public: // Types
    typedef int                                       State;
    typedef unsigned char                             Symbol;
    typedef boost::container_flat_map<Symbol,State>   SymbolStateMap; 

  private: // Types
    typedef std::unordered_set<State>     StateSet;
    typedef std::vector<SymbolStateMap>   Delta;

  public: // Static functions
    inline static State NoState() { return -1; }
 
  public: // Functions
    /// Returns the number of the final states in the FSA
    inline unsigned no_of_final_states() const
    {
      return final_states.size();
    }

    /// Returns the number of the states in the FSA
    inline unsigned no_of_states() const
    {
      return delta.size();
    }

    /// Returns the number of the transitions in the FSA
    inline unsigned no_of_transitions() const
    {
      unsigned nt = 0;
      for (unsigned q = 0; q < delta.size(); ++q) {
        nt += delta[q].size();
      }
      return nt;
    }

    /// Returns the out-degree of the FSA
    inline unsigned out_degree() const
    {
      unsigned od = 0;
      for (unsigned q = 0; q < delta.size(); ++q) {
        if (delta[q].size() > od) 
          od = delta[q].size();
      }
      return od;
    }

    /// Returns the outgoing transitions of state q
    inline const SymbolStateMap& operator[](State q) const
    {
      // 'static' since it is a fault to return a reference to a local object
      static SymbolStateMap no_transitions;
      return (q >= 0 && q < delta.size()) ? delta[q] : no_transitions;
    }

    void reserve(unsigned n)
    {
      delta.reserve(n);
    }

    /// Print a dot representation of the FSA to stream 'out'
    void print_dot(std::ofstream& out) const
    {
      out << "digraph FSM {\n";
      out << "graph [rankdir=LR, fontsize=14, center=1, orientation=Portrait];\n";
      out << "node  [font = \"Arial\", shape = circle, style=filled, fontcolor=black, color=lightgray]\n";
      out << "edge  [fontname = \"Arial\"]\n\n";

      for (unsigned q = 0; q < delta.size(); ++q) {
        out << q << " [label = \"" << q << "\"";
        out << (is_final(State(q)) ? ", shape=doublecircle]\n" : "]\n");
        const SymbolStateMap& q_tr = delta[q];
        for (auto t = q_tr.begin(); t != q_tr.end(); ++t) {
          out << q << " -> " << t->second << " [label = \"" << t->first << "\"]\n";
        }
      }
      out << "}\n";
    }
  
    /// Find target state p of the transition q --a-> p . 
    /// Returns NoState() if p is undefined.
    inline State find_transition(State q, Symbol a) const
    {
      // DONE
      if (q < 0 || q >= delta.size()) return NoState();
      const State& nextState = delta[q].find(a);
      if (nextState == deta[q].end()) return NoState();
      return nextState
    }

    /// Makes q final
    inline void make_final(State q)
    {
      final_states.insert(q);
    }

    /// Returns true iff q is final
    inline bool is_final(State q) const
    {
      return final_states.find(q) != final_states.end();
    }

    /// Add a transition from q with symbol a to an unused state
    inline State add_transition(State q, Symbol a)
    {
      // DONE
      delta[q][a] = new_state();
    }

    /// Returns true iff state q has outgoing transitions
    inline bool has_transitions(State q) const
    {
      // DONE
      return (delta[q].size() > 0);
    }

    /// Find the lexicographic last child of q
    inline State last_child(State q) const
    {
      // DONE
      return delta[q].rbegin();
    }

    /// Returns an unused state 
    inline State new_state()
    {
      // DONE - (UNSURE)
      // Ensure that in the delta-vector an empty symbol-state map exists
      // at a formerly unused position and return that position index 
      // Instead of using numeric_limits for the states, we make use of
      // vector's max_size() function
      if (!free_states.empty()) {
        auto const_it = free_states.cbegin();
        State freeState = *const_it;
        free_states.erase(const_it);
        return freeState;
      } else {
        if (delta.size() < delta.max_size()) {
          SymbolStateMap ssm;
          delta.push_back(ssm);
          return delta.size();
        } else {
          return NoState();
        }
      }
    }

    inline void replace_state(State p, State q)
    {
      // DONE
      delta[q].insert(delta[p].begin(), delta[p].end());
      for (unsigned tmp = 0; tmp < delta.size(); ++tmp) {
        for (auto it = delta[tmp].begin(), delta[tmp].end()) {
          if (it->second == p) delta[tmp][it->first] = q;
        }
      }
    }

    /// Delete state by clearing its transition map and putting it on the free list
    inline void delete_state(State q)
    {
      // DONE
      delta[q].clear();
      free_states.insert(q);
    }
  
  private:
    Delta delta;                   ///< Delta-function
    StateSet free_states;          ///< Free states
    StateSet final_states;         ///< Final states 
  }; // FiniteAutomaton

#endif
