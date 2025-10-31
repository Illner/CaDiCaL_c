#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "CaDiCaL/src/cadical.hpp"

class CNFGenerator {
public:
  CNFGenerator(int numVars, int numClauses, CaDiCaL::Solver &solver)
      : numVars(numVars), numClauses(numClauses), solver(solver) {
    // Seed random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));
  }

  void generate() {
    for (int i = 0; i < numClauses; ++i) {
      // Start a new clause
      int clauseLength = 4;
      for (int j = 0; j < clauseLength; ++j) {
        int var = std::rand() % numVars + 1; // Random from 1 to numVars
        bool negate = std::rand() % 2;       // Randomly decide polarity
        if (negate)
          var = -var;    // Negate the variable if needed
        solver.add(var); // Add the literal to the solver's clause
      }
      solver.add(0); // End the clause with 0
    }
  }

private:
  int numVars;             // Number of variables
  int numClauses;          // Number of clauses
  CaDiCaL::Solver &solver; // Reference to the CaDiCaL solver
};

void printVsidsScores(const CaDiCaL::Solver &solver,
                      std::vector<double> &scoreVector, int numVars) {
  std::cout << "eVSIDS" << std::endl;
  for (int var = 1; var <= numVars; ++var) {
    double score = solver.get_vsids_score(var);

    // assert (score >= scoreVector[var]);

    if (score == scoreVector[var]) {
      // std::cout << "\t" << std::to_string(var) << ": " <<
      // "same!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

      continue;
    }

    scoreVector[var] = score;

    std::cout << "\t" << std::to_string(var) << ": " << std::to_string(score)
              << std::endl;
  }

  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  std::cout << "CaDiCaL" << std::endl;

  // Create a solver instance
  CaDiCaL::Solver solver;

  // Add variables and clauses
  int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5;

  int numVars = 50;
  int numClauses = 500;

  CNFGenerator generator(numVars, numClauses, solver);
  generator.generate();

  std::vector<double> scoreVector(numVars + 1, 0);

  printVsidsScores(solver, scoreVector, numVars);

  // Check satisfiability
  int res = solver.solve();
  if (res == 10) {
    std::cout << "SAT\n";
  } else if (res == 20) {
    std::cout << "UNSAT\n";
  } else {
    std::cout << "UNKNOWN\n";
  }

  printVsidsScores(solver, scoreVector, numVars);

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
  std::cout << std::endl;

  // Add an assumption and check again
  solver.push_assumption(x2); // Assume x2 is true

  res = solver.solve();
  if (res == 10) {
    std::cout << "SAT under assumption x2\n";
  } else if (res == 20) {
    std::cout << "UNSAT under assumption x2\n";
  } else {
    std::cout << "UNKNOWN under assumption x2\n";
  }

  printVsidsScores(solver, scoreVector, numVars);

  solver.pop_assumption(x2);
  solver.push_assumption(-x2); // Assume x2 is false

  res = solver.solve();
  if (res == 10) {
    std::cout << "SAT under assumption -x2\n";
  } else if (res == 20) {
    std::cout << "UNSAT under assumption -x2\n";
  } else {
    std::cout << "UNKNOWN under assumption -x2\n";
  }

  printVsidsScores(solver, scoreVector, numVars);

  solver.pop_assumption(-x2);

  return 0;
}
