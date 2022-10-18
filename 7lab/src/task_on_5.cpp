#include <iostream>
#include <vector>
#include <map>

enum class state{
  first = 0, ///< есть акция
  second, ///< нет акции, нет кулдауна
  third ///< нет акции, есть кулдаун
};

int DP(const state &st, const int &day, const std::vector<int> &costs, std::map<std::pair<int, state>, int> &memory){
	if (day >= costs.size()){
	  return 0;
	}
	auto findIterator = memory.find(std::pair<int, state>(day, st));
	if (findIterator != memory.end()){
	  return findIterator->second;
	}
  switch (st) {
	  case state::first:{
	  int ans = std::max(DP(state::first, day + 1, costs, memory), DP(state::third, day + 1, costs, memory) + costs[day]);
	  return memory[std::pair<int, state>(day, st)] = ans;
	}
	case state::second:{
		int ans = std::max(DP(state::first, day + 1, costs, memory) - costs[day], DP(state::second, day + 1, costs, memory));
		return memory[std::pair<int, state> (day, st)] = ans;
	  }
	  case state::third:{
		return DP(state::second, day + 1, costs, memory);
	  }
  }
}

int main(){
  int n, ans;
  std::cin >> n;
  std::vector<int> costs(n);
  for (int i = 0; i < n; ++i){
	std::cin >> costs[i];
  }
  std::map<std::pair<int, state>, int> memory;
  ans = DP(state::first, 0, costs, memory);
  std::cout << ans << std::endl;
}