//从中序与后序构造二叉树
//https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
class Solution {
public:
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		return build(postorder, inorder, 0, postorder.size() - 1, 0, inorder.size() - 1);
	}
	TreeNode* build(vector<int>& postorder, vector<int>& inorder, int l1, int r1, int l2, int r2) {
		if (l1 > r1) return nullptr;
		TreeNode* root = new TreeNode(postorder[r1]);
		int mid(l2);
		while (inorder[mid] != root->val) mid++;
		int rootrs = r2 - mid;
		root->right = build(postorder, inorder, r1 - rootrs, r1 - 1, mid + 1, r2);
		root->left = build(postorder, inorder, l1, r1 - rootrs - 1, l2, mid - 1);
		return root;
	}
};

//课程表2
//https://leetcode-cn.com/problems/course-schedule-ii/
//class Solution {
public:
	vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
		n = numCourses;
		edge = vector<vector<int>>(n, vector<int>());
		inDeg = vector<int>(n, 0);
		for (auto pre : prerequisites) {
			int ai = pre[0];
			int bi = pre[1];
			addEdge(bi, ai);
		}
		auto learned = topsort();
		if (learned.size() != n) return {};
		else return learned;
	}
private:
	int n;
	vector<vector<int>> edge;
	vector<int> inDeg;

	void addEdge(int x, int y) {
		edge[x].push_back(y);
		inDeg[y]++;
	}
	vector<int> topsort() {
		vector<int> learned;
		queue<int> q;
		for (int i(0); i < n; i++) {
			if (inDeg[i] == 0) q.push(i);
		}
		while (!q.empty()) {
			int x = q.front();
			q.pop();
			learned.push_back(x);
			for (auto y : edge[x]) {
				inDeg[y]--;
				if (inDeg[y] == 0) q.push(y);
			}
		}
		return learned;
	}
};

//被围绕的区域
//https://leetcode-cn.com/problems/surrounded-regions/
class Solution {
public:
	void solve(vector<vector<char>>& board) {
		this->m = board.size();
		this->n = board[0].size();
		visited = vector<vector<bool>>(m, vector<bool>(n, false));
		for (int i(0); i < m; i++) {
			for (int j(0); j < n; j++) {
				if (board[i][j] == 'O' && !visited[i][j])
					bfs(board, i, j);
			}
			for (int i(0); i < m; i++) {
				for (int j(0); j < n; j++) {
					if (board[i][j] == 'Y')
						board[i][j] = 'O';
				}
			}
		}
	}
private:
	void bfs(vector<vector<char>>& board, int sx, int sy) {
		//v记录‘O’点，flag代表边界点
		vector<pair<int, int>>v;
		int flag = false;
		queue<pair<int, int>> q;
		q.push(make_pair(sx, sy));
		visited[sx][sy] = true;
		while (!q.empty()) {
			int x = q.front().first;
			int y = q.front().second;
			q.pop();
			//队头压入v中
			v.push_back(make_pair(x, y));
			//边界点，标记flag
			if (x == 0 || y == 0 || x == m - 1 || y == n - 1) flag = true;
			//设置为‘X’
			board[x][y] = 'X';
			for (int i(0); i < 4; i++) {
				int dx = x + dirx[i];
				int dy = y + diry[i];
				if (dx < 0 || dy < 0 || dx >= m || dy >= n) continue;
				if (board[dx][dy] == 'O' && !visited[dx][dy]) {
					q.push(make_pair(dx, dy));
					//设置为‘X’
					board[dx][dy] = 'X';
					visited[dx][dy] = true;
				}
			}
		}
		//边界点为Y
		if (flag) {
			for (auto p : v)
				board[p.first][p.second] = 'Y';
		}
	}
	int m, n;
	vector<vector<bool>>visited;
	const int dirx[4] = { -1,0,0,1 };
	const int diry[4] = { 0,-1,1,0 };
};