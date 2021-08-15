//设计推特
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
		// //将旧的推文pop掉
		// if(user.tweets.size()>=maxSize) user.tweets.pop_back();
		//新推文插入tweets前面，从时间属性将，组成降序链表
		user.tweets.emplace_front(time++, tweetId);
	}

	/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
	vector<int> getNewsFeed(int userId) {
		//记录推文时间和推文ID
		priority_queue<pair<int, int>> q;
		vector<int> res;
		//根据用户ID确定用户信息
		auto& user = id2user[userId];
		//压入自己的推文
		for (auto follower : user.tweets) q.push(follower);
		//压入自己关注者的推文
		for (auto followeeId : user.followeeSet) {
			for (auto followee : id2user[followeeId].tweets) {
				q.push(followee);
			}
		}
		//将最新的10条推文，压入答案
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
	//User包含信息：自己关注的人，发的推文(时间，推文ID)
	struct User {
		unordered_set<int> followeeSet;
		deque<pair<int, int>> tweets;
	};
	const int maxSize = 10;
	int time;
	//id2user为用户ID和User的映射
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

//寻找旋转排序数组的最小值2
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