//����͵ĸ���
//https://leetcode-cn.com/problems/count-of-range-sum/
class Solution {
private:
	int lower, upper;
public:
	int countRangeSum(vector<int>& nums, int lower, int upper) {
		this->lower = lower;
		this->upper = upper;
		//ע����Ŀ���ݷ�Χ����long
		vector<long>sum(nums.size() + 1, 0);
		for (int i(1); i <= nums.size(); i++) {
			sum[i] = sum[i - 1] + nums[i - 1];
		}
		return mergesort(sum, 0, sum.size() - 1);
	}
	int mergesort(vector<long>& sum, int left, int right) {
		if (left >= right) return 0;
		int mid = left + (right - left) / 2;
		//ans����ȫ�ֱ���������lc493��ͬ������𰸻�����
		int ans(0);
		ans += mergesort(sum, left, mid);
		ans += mergesort(sum, mid + 1, right);
		//calculate
		ans += calculate(sum, left, mid, right);
		merge(sum, left, mid, right);
		return ans;
	}
	void merge(vector<long>& sum, int left, int mid, int right) {
		//ע��sum������long
		vector<long>temp(right - left + 1);
		int i(left), j(mid + 1), k(0);
		for (k = 0; k < temp.size(); k++) {
			if (j > right || (i <= mid && sum[j] >= sum[i])) temp[k] = sum[i++];
			else temp[k] = sum[j++];
		}
		for (i = left, k = 0; k < temp.size();) sum[i++] = temp[k++];
	}
	int calculate(vector<long>& sum, int left, int mid, int right) {
		//low��up�ֱ����lower,upperָ��
		int L = left, low = mid + 1, up = mid + 1, answer(0);
		while (L <= mid) {
			//��sum[low] - sum[L]< lower��lowָ������
			while (low <= right && sum[low] - sum[L] < lower) low++;
			//��sum[up] - sum[L] <= upper��upָ������
			while (up <= right && sum[up] - sum[L] <= upper) up++;
			L++;
			//up��low�ľ������һ��������
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
