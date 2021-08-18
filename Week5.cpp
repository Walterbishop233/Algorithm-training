//区间和的个数
//https://leetcode-cn.com/problems/count-of-range-sum/
class Solution {
private:
	int lower, upper;
public:
	int countRangeSum(vector<int>& nums, int lower, int upper) {
		this->lower = lower;
		this->upper = upper;
		//注意题目数据范围，用long
		vector<long>sum(nums.size() + 1, 0);
		for (int i(1); i <= nums.size(); i++) {
			sum[i] = sum[i - 1] + nums[i - 1];
		}
		return mergesort(sum, 0, sum.size() - 1);
	}
	int mergesort(vector<long>& sum, int left, int right) {
		if (left >= right) return 0;
		int mid = left + (right - left) / 2;
		//ans不是全局变量，这与lc493不同，否则答案会算重
		int ans(0);
		ans += mergesort(sum, left, mid);
		ans += mergesort(sum, mid + 1, right);
		//calculate
		ans += calculate(sum, left, mid, right);
		merge(sum, left, mid, right);
		return ans;
	}
	void merge(vector<long>& sum, int left, int mid, int right) {
		//注意sum数组是long
		vector<long>temp(right - left + 1);
		int i(left), j(mid + 1), k(0);
		for (k = 0; k < temp.size(); k++) {
			if (j > right || (i <= mid && sum[j] >= sum[i])) temp[k] = sum[i++];
			else temp[k] = sum[j++];
		}
		for (i = left, k = 0; k < temp.size();) sum[i++] = temp[k++];
	}
	int calculate(vector<long>& sum, int left, int mid, int right) {
		//low，up分别代表lower,upper指针
		int L = left, low = mid + 1, up = mid + 1, answer(0);
		while (L <= mid) {
			//当sum[low] - sum[L]< lower，low指针右移
			while (low <= right && sum[low] - sum[L] < lower) low++;
			//当sum[up] - sum[L] <= upper，up指针右移
			while (up <= right && sum[up] - sum[L] <= upper) up++;
			L++;
			//up与low的距离代表一个答案区间
			answer += up - low;
		}
		return answer;
	}
};

//在D天内送达包裹的能力
//https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/
//二分+贪心
class Solution {
public:
	int shipWithinDays(vector<int>& weights, int days) {
		int left(0), right(0);
		for (auto weight : weights) {
			left = max(left, weight);
			right += weight;
		}
		while (left < right) {
			int mid = left + (right - left) / 2;
			//贪心，若加上货物，超了当前猜的T值，就不装该货物，留到第二天装
			int need(1), cur(0);
			for (auto weight : weights) {
				if (weight + cur > mid) {
					need++;
					cur = 0;
				}
				cur += weight;
			}
			if (need <= days) right = mid;
			else left = mid + 1;
		}
		return right;
	}
};
//二分
class Solution {
public:
	int shipWithinDays(vector<int>& nums, int m) {
		int left(0), right(0);
		//最坏情况，单个元素为1组，此时最大和为单个元素对应的最大值，二分左
		//最好情况，所有元素为1组，此时总和为最大值，二分右
		for (int i(0); i < nums.size(); i++) {
			left = max(left, nums[i]);
			right += nums[i];
		}
		while (left < right) {
			int mid = (left + right) / 2;
			//解的右边，true，T合法，但不是最小的T
			if (isValid(nums, m, mid)) right = mid;
			else left = mid + 1;
		}
		return right;
	}
	//将数组分成<=m组，对应各组元素和<=T
	bool isValid(vector<int>& nums, int m, int T) {
		//初始各组和为0，组数1
		int groupSum(0), groupCount(1);
		//遍历数组，根据T分组
		for (int i(0); i < nums.size(); i++) {
			//加入nums[i]仍<=T,将其加入
			if (groupSum + nums[i] <= T) groupSum += nums[i];
			else { //否则另开一数组
				groupSum = nums[i];
				groupCount++;
			}
		}
		//返回的组数是否<=m,<是因为可以再拆开
		return groupCount <= m;
	}
};
