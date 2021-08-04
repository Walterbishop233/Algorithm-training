//https://leetcode-cn.com/problems/merge-k-sorted-lists/
//�ϲ�K����������
class Solution {
public:
	ListNode* mergetwolists(ListNode* l1, ListNode* l2) {
		if (l1 == nullptr) return l2;
		if (l2 == nullptr) return l1;
		if (l1->val < l2->val) {
			l1->next = mergetwolists(l1->next, l2);
			return l1;
		}
		else {
			l2->next = mergetwolists(l1, l2->next);
			return l2;
		}
	}
	//����
	ListNode* merge(vector<ListNode*>& lists, int start, int end) {
		if (start == end) return lists[start];
		int mid = (start + end) / 2;
		ListNode* l1 = merge(lists, start, mid);
		ListNode* l2 = merge(lists, mid + 1, end);
		ListNode* ans = mergetwolists(l1, l2);
		return ans;
	}
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		if (lists.size() == 0) return nullptr;
		return merge(lists, 0, lists.size() - 1);
	}
};

//https://leetcode-cn.com/problems/degree-of-an-array/
//����Ķ�
class Solution {
public:
	int findShortestSubArray(vector<int>& nums) {
		//��ϣ���¼Ԫ�ش���
		unordered_map<int, int> hash;
		//���¶�
		int maxsize(0);
		for (auto n : nums) {
			hash[n]++;
			maxsize = max(maxsize, hash[n]);
		}
		int left(0), right(0), ans(nums.size());
		//hash���ȥһ�㣬��Ϊ�����漰�������ڱ���
		hash.erase(hash.begin(), hash.end());
		while (right < nums.size()) {
			hash[nums[right]]++;
			//����Ԫ�ش������ڶ�ʱ�����´𰸣��ƶ��󴰿�
			while (hash[nums[right]] == maxsize) {
				ans = min(ans, right - left + 1);
				hash[nums[left++]]--;
			}
			right++;
		}
		return ans;
	}
};