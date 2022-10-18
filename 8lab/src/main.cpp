#include <iostream>
#include "SystemOfEquations.h"

const int MAX_COST = 51;

int main() {
  int M, N;
  std::cin >> M >> N;
  SystemOfEquations system(MAX_COST, N);
  std::vector<double> coeff(N);
  int cost;
  for (int i = 0; i < M; ++i){
	for (int k = 0; k < N; ++k){
	  std::cin >> coeff[k];
	}
	std::cin >> cost;
	system.addEquation(coeff, cost);
  }
  auto ans = system.solve();
  for (const auto &answer: ans){
	std::cout << answer + 1 << " ";
  }
  std::cout << std::endl;
  return 0;
}
