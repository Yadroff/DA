#ifndef SRC__EQUATION_H
#define SRC__EQUATION_H

#include <vector>
class Equation {
public:
  Equation(std::vector<double> k, const int &cost, const int &ind);
  Equation(const Equation &other) = default;
  double &operator[](const int &i);
  int cost() const;
  int ind() const;
  friend bool operator<(const Equation &left, const Equation &right);
private:
  std::vector<double> coefficients_;
  int cost_;
  int ind_;
};

#endif //SRC__EQUATION_H
