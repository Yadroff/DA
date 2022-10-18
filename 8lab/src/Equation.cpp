#include "Equation.h"

#include <utility>
#include <stdexcept>
Equation::Equation(std::vector<double> k, const int &cost, const int &ind)
	: coefficients_(std::move(k)), cost_(cost), ind_(ind) {}
double &Equation::operator[](const int &i) {
  if (coefficients_.size() <= i) {
	throw std::out_of_range("Выход за границы массива");
  }
  return coefficients_[i];
}
int Equation::cost() const {
  return cost_;
}
int Equation::ind() const {
  return ind_;
}
bool operator<(const Equation &left, const Equation &right) {
  return left.cost_ < right.cost_;
}
