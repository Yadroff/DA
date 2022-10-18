#include "SystemOfEquations.h"

#include <algorithm>

SystemOfEquations::SystemOfEquations(const int &maxCost, const int &n) :
	equations_(), maxCost_(maxCost), curMinCostInd_(-2), curMinCost_(0), size_(0), numOfUnknowns_(n) {}
void SystemOfEquations::addEquation(const std::vector<double> &coeff, const int &cost) {
  equations_.emplace_back(coeff, cost, size_);
  ++size_;
}
void SystemOfEquations::findMinCost(const int &ind) {
  curMinCost_ = maxCost_;
  curMinCostInd_ = -1;
  if (size_ == 0) {
	return;
  }
  for (int i = ind; i < size_; ++i) {
	if (equations_[i].cost() < curMinCost_ and equations_[i][ind] != 0) {
	  curMinCost_ = equations_[i].cost();
	  curMinCostInd_ = i;
	}
  }
}
std::vector<int> SystemOfEquations::solve() {
  if (size_ == 0) {
	return {-1};
  }
  std::sort(equations_.begin(), equations_.end());
  std::vector<int> ans;
  curMinCostInd_ = -2;
  for (int i = 0; i < numOfUnknowns_; ++i, curMinCostInd_ = -2) {
	if (curMinCostInd_ == -2) {
	  findMinCost(i);
	}
	if (curMinCostInd_ == -1) {
	  return std::move(std::vector<int>{-2});
	}
	// переносим вверх строку, которую не будем обнулять
	std::swap(equations_[i], equations_[curMinCostInd_]);
	// обнуляем остальные столбцы
	for (int j = i + 1; j < size_; ++j) {
	  zero(i, j);
	}
	ans.emplace_back(equations_[i].ind());
  }
  std::sort(ans.begin(), ans.end());
  return std::move(ans);
}
void SystemOfEquations::zero(const int &base, const int &ind) {
  double k = equations_[ind][base] / equations_[base][base];
  for (int i = ind; i < numOfUnknowns_; ++i) {
	equations_[ind][i] -= k * equations_[base][i];
  }
}
