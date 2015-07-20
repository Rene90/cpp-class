/* Lisanne Wiengarten
Matrikelnr. 764870
C++ II ThH SoSe15 */

#include <iostream>
#include <fstream>
#include "FiniteAutomaton.hpp"

int main()
{
  typedef FiniteAutomaton::State              State;
  //typedef FiniteAutomaton::Symbol             Symbol;
  //typedef FiniteAutomaton::SymbolStateMap     SymbolStateMap;

  FiniteAutomaton fsa;
  State eins = fsa.new_state();
  State zwei = fsa.new_state();
  State drei = fsa.add_transition(eins, 'a');
  State vier = fsa.add_transition(drei, 'f');
  State funf = fsa.add_transition(vier, 'f');
  State sechs = fsa.add_transition(funf, 'e');
  fsa.delete_state(zwei);
  State sieben = fsa.add_transition(eins, 'z');
  fsa.make_final(sechs);

  fsa.is_final(sechs) ? std::cout << sechs << " is final\n" : std::cout << sechs << " is not final\n";

  fsa.is_final(funf) ? std::cout << funf << " is final\n" : std::cout << funf << " is not final\n";

  fsa.has_transitions(sechs) ? std::cout << sechs << " has outgoing transitions\n" : std::cout << sechs << " does not have outgoing transitions\n";

  fsa.has_transitions(funf) ? std::cout << funf << " has outgoing transitions\n" : std::cout << funf << " does not have outgoing transitions\n";

  State acht = fsa.find_transition(eins, 'a');
  if (acht != -1)
    std::cout << eins << " -'a'-> " << acht << std::endl;

  State neun = fsa.last_child(eins);
  if (neun != -1)
    std::cout << "lexicographic last child of " << eins << " is " << neun << std::endl;

  std::ofstream dot_out("fsa.dot");
  fsa.print_dot(dot_out);

}
