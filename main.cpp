#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ranges>
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
  int zeroLit = 0;
  int litPos1 = 1, litPos2 = 2, litPos3 = 3, litPos4 = 4, litPos5 = 5,
      litPos6 = 6, litPos7 = 7, litPos8 = 8, litPos9 = 9, litPos10 = 10;
  int litNeg1 = -1, litNeg2 = -2, litNeg3 = -3, litNeg4 = -4, litNeg5 = -5,
      litNeg6 = -6, litNeg7 = -7, litNeg8 = -8, litNeg9 = -9, litNeg10 = -10;

  solver.add(litPos1);
  solver.add(zeroLit); // 0
  solver.add(litNeg3);
  solver.add(zeroLit); // 1
  solver.add(litNeg1);
  solver.add(litPos2);
  solver.add(zeroLit); // 2
  solver.add(litPos3);
  solver.add(litNeg4);
  solver.add(zeroLit); // 3

  solver.add(litPos5);
  solver.add(litPos7);
  solver.add(zeroLit); // 4
  solver.add(litNeg7);
  solver.add(litNeg9);
  solver.add(zeroLit); // 5
  solver.add(litNeg6);
  solver.add(litNeg7);
  solver.add(litPos8);
  solver.add(zeroLit); // 6

  std::vector<std::vector<int>> assumptionsVector{
      {},
      {litNeg2},
      {litNeg5},
      {litPos6},
      {litNeg5, litPos6},
      {litPos1, litPos2, litNeg3, litNeg4, litNeg5},
      {litPos1, litPos2, litNeg3, litNeg4, litPos6},
      {litPos1, litPos2, litNeg3, litNeg4, litNeg5, litPos6}};

  for (const std::vector<int> &assumptions : assumptionsVector) {
    std::cout << "Assumptions:";
    for (int lit : assumptions) {
      std::cout << " " << std::to_string(lit);

      solver.push_assumption(lit);
    }
    std::cout << std::endl;

    int prop_res = solver.propagate();
    if (prop_res == 20) {
      std::cout << "Conflict" << std::endl;
    } else if (prop_res == 0) {
      std::vector<int> implicants;
      solver.get_entrailed_literals(implicants);
      std::sort(implicants.begin(), implicants.end());

      std::cout << "Implied literals:";
      for (int lit : implicants)
        std::cout << " " << std::to_string(lit);
      std::cout << std::endl;
    } else {
      std::cout << "Full assignment:";
      for (int var = 1; var <= solver.vars(); ++var)
        std::cout << " " << std::to_string(solver.val(var));
      std::cout << std::endl;
    }

    for (int assumption : std::ranges::reverse_view(assumptions)) {
      solver.pop_assumption(assumption);
    }

    std::cout << std::endl;
    std::cout << "---------------------------";
    std::cout << std::endl;
  }

  /*
  int res = solver.solve();
  if (res == 10) {
    std::cout << "SAT\n";
  } else if (res == 20) {
    std::cout << "UNSAT\n";
  } else {
    std::cout << "UNKNOWN\n";
  }
   */

  return 0;
}
