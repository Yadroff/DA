#include <vector>
#include <iostream>
#include <algorithm>

struct Equation {
  std::vector<double> coefficients;
  int cost{};
  explicit Equation(const int &N) : coefficients(N), cost(0) {}
  Equation() = default;
};

bool hasSolution(std::vector<Equation> &system) {
  int N = static_cast<int>(system.size());
  for (int col = 0; col < N; ++col) {
	// ищем ведущий элемент
	int elemInd = -1;
	for (int row = col; row < N; ++row) {
	  if (system[row].coefficients[col] != 0) {
		elemInd = row;
		break;
	  }
	}
	if (elemInd == -1) {
	  return false;
	}
	std::swap(system[col], system[elemInd]);
	// обнуляем столбец оставшихся строк
	for (int row = col + 1; row < N; ++row) {
	  double k = system[row].coefficients[col] / system[col].coefficients[col];
	  for (int i = col; i < N; ++i) {
		system[row].coefficients[i] -= k * system[col].coefficients[i];
	  }
	}
  }
  return true;
}

int cost(const std::vector<Equation> &subSystem) {
  int ans = 0;
  for (const auto &Item : subSystem) {
	ans += Item.cost;
  }
  return ans;
}

int main() {
  int N, M;
  std::cin >> M >> N;
  std::vector<Equation> system(M, Equation(N));
  std::vector<int> indexes(M);
  int ansCost = 0;
  bool hasSol = false;
  std::vector<int> ansIndexes;
  for (int i = 0; i < M; ++i) {
	for (int k = 0; k < N; ++k) {
	  std::cin >> system[i].coefficients[k];
	}
	std::cin >> system[i].cost;
	ansCost += system[i].cost;
	indexes[i] = i;
  }
  do {
	std::vector<Equation> subSystem(N);
	for (int i = 0; i < N; ++i) {
	  subSystem[i] = system[indexes[i]];
	}
	int costSys = cost(subSystem);
	if (hasSolution(subSystem) and costSys < ansCost) {
	  ansCost = costSys;
	  ansIndexes = std::vector<int>(indexes.begin(), indexes.begin() + N);
	  hasSol = true;
	}
  } while (std::next_permutation(indexes.begin(), indexes.end()));
  if (!hasSol) {
	std::cout << "-1" << std::endl;
  } else {
	for (const auto &ans : ansIndexes) {
	  std::cout << ans + 1 << " ";
	}
	std::cout << std::endl;
  }
  return 0;
}