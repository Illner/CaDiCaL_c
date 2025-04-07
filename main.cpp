#include <iostream>

// #include "cadical.hpp"
#include "CaDiCaL/src/cadical.hpp"

int main(int argc, char *argv[]) {
  std::cout << "CaDiCaL" << std::endl;

  // Create a solver instance
  CaDiCaL::Solver solver;

  // Add variables and clauses
  int x1 = 1, x2 = 2, x3 = 3;

  solver.add(x1);
  solver.add(-x2);
  solver.add(0); // Clause: (x1 OR ¬x2)
  solver.add(-x1);
  solver.add(x3);
  solver.add(0); // Clause: (¬x1 OR x3)
  solver.add(-x3);
  solver.add(0); // Clause: (¬x3)

  // Check satisfiability
  int res = solver.solve();
  if (res == 10) {
    std::cout << "SAT\n";
  } else if (res == 20) {
    std::cout << "UNSAT\n";
  } else {
    std::cout << "UNKNOWN\n";
  }

  // Perform unit propagation
  int prop_res = solver.propagate();
  if (prop_res == 10) {
    std::cout << "Propagation completed. Model values:\n";
    std::cout << "x1 = " << solver.val(x1) << "\n";
    std::cout << "x2 = " << solver.val(x2) << "\n";
    std::cout << "x3 = " << solver.val(x3) << "\n";
  } else {
    std::cout << "Unit propagation failed.\n";
  }

  // Add an assumption and check again
  solver.assume(x2); // Assume x2 is true

  res = solver.solve();
  if (res == 10) {
    std::cout << "SAT under assumption x2\n";
  } else if (res == 20) {
    std::cout << "UNSAT under assumption x2\n";
  } else {
    std::cout << "UNKNOWN under assumption x2\n";
  }

  solver.assume(-x2); // Assume x2 is true

  res = solver.solve();
  if (res == 10) {
    std::cout << "SAT under assumption -x2\n";
  } else if (res == 20) {
    std::cout << "UNSAT under assumption -x2\n";
  } else {
    std::cout << "UNKNOWN under assumption -x2\n";
  }

  return 0;
}
