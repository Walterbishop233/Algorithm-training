//�������
//https://leetcode-cn.com/problems/design-twitter/submissions/
class Twitter {
public:
	/** Initialize your data structure here. */
	Twitter() {
		time = 0;
	}

	/** Compose a new tweet. */
	void postTweet(int userId, int tweetId) {
		auto& user = id2user[userId];
		// //���ɵ�����pop��
		// if(user.tweets.size()>=maxSize) user.tweets.pop_back();
		//�����Ĳ���tweetsǰ�棬��ʱ�����Խ�����ɽ�������
		user.tweets.emplace_front(time++, tweetId);
	}

	/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
	vector<int> getNewsFeed(int userId) {
		//��¼����ʱ�������ID
		priority_queue<pair<int, int>> q;
		vector<int> res;
		//�����û�IDȷ���û���Ϣ
		auto& user = id2user[userId];
		//ѹ���Լ�������
		for (auto follower : user.tweets) q.push(follower);
		//ѹ���Լ���ע�ߵ�����
		for (auto followeeId : user.followeeSet) {
			for (auto followee : id2user[followeeId].tweets) {
				q.push(followee);
			}
		}
		//�����µ�10�����ģ�ѹ���
		for (int i(0); i < 10 && !q.empty(); i++) {
			res.push_back(q.top().second);
			q.pop();
		}
		return res;
	}

	/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
	void follow(int followerId, int followeeId) {
		auto& follower = id2user[followerId];
		follower.followeeSet.insert(followeeId);
	}

	/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
	void unfollow(int followerId, int followeeId) {
		auto& follower = id2user[followerId];
		follower.followeeSet.erase(followeeId);
	}
private:
	//User������Ϣ���Լ���ע���ˣ���������(ʱ�䣬����ID)
	struct User {
		unordered_set<int> followeeSet;
		deque<pair<int, int>> tweets;
	};
	const int maxSize = 10;
	int time;
	//id2userΪ�û�ID��User��ӳ��
	unordered_map<int, User> id2user;
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

//Ѱ����ת�����������Сֵ2
//https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/
class Solution {
public:
	int findMin(vector<int>& nums) {
		long long left(0), right(nums.size() - 1);
		while (left < right) {
			long long mid = (right + left) / 2;
			if (nums[mid] < nums[right]) right = mid;
			else if (nums[mid] > nums[right]) left = mid + 1;
			else right = right - 1;
		}
		return nums[right];
	}
};