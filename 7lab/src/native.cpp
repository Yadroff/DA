#include <iostream>
#include <chrono>

int main(){
  long long n, m;
  std::cin >> n >> m;
  std::string nString = std::to_string(n);
  long long ans = 0;
  for (int k = m; k < n; k += m){
	if (std::to_string(k) < nString){
	  ++ans;
	}
  }
  std::cout << ans << std::endl;
}