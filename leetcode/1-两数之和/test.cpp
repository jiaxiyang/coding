#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

//思路：
// 1. 暴力法： 两重for, 遍历，何为target输出

std::vector<int> twoSum(std::vector<int> &nums, int target) {
  std::vector<int> result = {};
  for (auto i = 0; i < nums.size(); ++i) {
    for (auto j = i + 1; j < nums.size(); ++j) {
      if (nums[i] + nums[j] == target) {
        return {i, j};
      }
    }
  }

  return result;
}

// 2. 使用哈希表，把遍历过的(nums[i], i)存到哈希表中，找target -
// nums[j]是否在表中, 返回i, j
std::vector<int> twoSum1(std::vector<int> &nums, int target) {
  std::vector<int> result = {};
  std::unordered_map<int, int> l;
  for (auto i = 0; i < nums.size() - 1; ++i) {
    if (l.find(target - nums[i]) != l.end())
      return {l[target - nums[i]], i};
  }
  return result;
}

int main(int argc, char *argv[]) {
  // std::vector<int> input = {2, 7, 11, 15};
  // int target = 9;
  std::vector<int> input = {3, 2, 4};
  int target = 6;
  auto result = twoSum(input, target);
  for (auto &i : result) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  return 0;
}
