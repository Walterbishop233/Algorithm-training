//����͵ĸ���
//https://leetcode-cn.com/problems/count-of-range-sum/
class Solution {
private:
	int ans;
public:
	int countRangeSum(vector<int>& nums, int lower, int upper) {
		ans = 0;
		vector<int>sum(nums.size(), 0);
		sum[0] = nums[0];
		for (int i(1); i < nums.size(); i++) {
			sum[i] = sum[i - 1] + nums[i];
		}
		return mergesort(sum, 0, sum.size() - 1, lower, upper);
	}
	int mergesort(vector<int>& sum, int left, int right, int lower, int upper) {
		if (left >= right) return 0;
		int mid = left + (right - left) / 2;
		ans += mergesort(sum, left, mid, lower, upper);
		ans += mergesort(sum, mid + 1, right, lower, upper);
		//calculate
		ans += calculate(sum, left, mid, right, lower, upper);
		merge(sum, left, mid, right);
		return ans;
	}
	void merge(vector<int>& sum, int left, int mid, int right) {
		vector<int>temp(right - left + 1);
		int i(left), j(mid + 1), k(0);
		for (k = 0; k < temp.size(); k++) {
			if (j > right || (i <= mid && sum[j] >= sum[i])) temp[k] = sum[i++];
			else temp[k] = sum[j++];
		}
		for (i = left, k = 0; k < temp.size();) sum[i] = temp[k++];
	}
	int calculate(vector<int>& sum, int left, int mid, int right, int lower, int upper) {
		int L = left, low = mid + 1, up = mid + 1, answer(0);
		while (L <= mid) {
			while (low <= right && sum[low] - sum[L] < lower) low++;
			while (up <= right && sum[up] - sum[L] <= upper) up++;
			L++;
			answer += up - low;
		}
		return answer;
	}
};

//��D�����ʹ����������
//https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/
//����+̰��
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
			//̰�ģ������ϻ�����˵�ǰ�µ�Tֵ���Ͳ�װ�û�������ڶ���װ
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
//����
class Solution {
public:
	int shipWithinDays(vector<int>& nums, int m) {
		int left(0), right(0);
		//����������Ԫ��Ϊ1�飬��ʱ����Ϊ����Ԫ�ض�Ӧ�����ֵ��������
		//������������Ԫ��Ϊ1�飬��ʱ�ܺ�Ϊ���ֵ��������
		for (int i(0); i < nums.size(); i++) {
			left = max(left, nums[i]);
			right += nums[i];
		}
		while (left < right) {
			int mid = (left + right) / 2;
			//����ұߣ�true��T�Ϸ�����������С��T
			if (isValid(nums, m, mid)) right = mid;
			else left = mid + 1;
		}
		return right;
	}
	//������ֳ�<=m�飬��Ӧ����Ԫ�غ�<=T
	bool isValid(vector<int>& nums, int m, int T) {
		//��ʼ�����Ϊ0������1
		int groupSum(0), groupCount(1);
		//�������飬����T����
		for (int i(0); i < nums.size(); i++) {
			//����nums[i]��<=T,�������
			if (groupSum + nums[i] <= T) groupSum += nums[i];
			else { //������һ����
				groupSum = nums[i];
				groupCount++;
			}
		}
		//���ص������Ƿ�<=m,<����Ϊ�����ٲ�
		return groupCount <= m;
	}
};
