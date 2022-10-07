#include <iostream>
#include <chrono>
long long DP(const long long &r, const long long &l, const long long &m) {
  if (r < l) {
	return 0;
  }
  long long right = r - r % m;
  long long left, ost = l % m;
  if (ost == 0){
	left = l;
  } else{
	left = l + m - ost;
  }
  if (left > right or right <= 0) {
	return 0;
  }
  return (right - left) / m + 1;
}

int main() {
  std::string N;
  long long n = 0, m, tenPow = 1, ans = 0;
  std::cin >> N >> m;
  for (char i : N) {
	n = n * 10 + i - '0';
	ans += DP(n, tenPow, m);
	tenPow *= 10;
  }
  std::cout << ans - (n % m == 0) << std::endl;
  return 0;
}
