#ifndef SRC__SYSTEMOFEQUATIONS_H
#define SRC__SYSTEMOFEQUATIONS_H

#include "Equation.h"
class SystemOfEquations {
public:
  explicit SystemOfEquations(const int &maxCost, const int &n);
  void addEquation(const std::vector<double> &coeff, const int &cost);
  void findMinCost(const int &ind);
  void zero(const int &base, const int &ind);
  std::vector<int> solve();
private:
  std::vector<Equation> equations_;
  int curMinCostInd_;
  int curMinCost_;
  int size_;
  int numOfUnknowns_;
  int maxCost_;
};

#endif //SRC__SYSTEMOFEQUATIONS_H
