//lc200岛屿数量
//https://leetcode-cn.com/problems/number-of-islands/
class Solution {
public:
	//‘1’的四周有‘1’，就归为一类。遍历一遍grid。最后更新答案
	int numIslands(vector<vector<char>>& grid) {
		this->m = grid.size();
		this->n = grid[0].size();
		visited = vector<vector<bool>>(m, vector<bool>(n, false));
		fa = vector<int>(n*m, 0);
		//并查集初始化
		for (int i(0); i < m; i++) {
			for (int j(0); j < n; j++) fa[get(i, j)] = get(i, j);
		}
		fa[0] = 0;
		//遍历grid,不为0且四周不越界且为'1',就指向fa
		for (int i(0); i < m; i++) {
			for (int j(0); j < n; j++) {
				if (grid[i][j] == '0') continue;
				for (int k(0); k < 4; k++) {
					int x = i + dirx[k];
					int y = j + diry[k];
					if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == '0') continue;
					else if (grid[x][y] == '1' && !visited[x][y]) {
						fa[get(x, y)] = find(get(i, j));
						visited[x][y] = true;
					}
					//如果两个1相邻但是不属于同一个fa，就合并
					else if (grid[x][y] = '1'&&visited[x][y]) {
						if (find(get(i, j)) != find(get(x, y))) fa[find(get(i, j))] = find(get(x, y));
					}
				}
			}
		}
		// for(int i(0);i<m;i++){
		//   for(int j(0);j<n;j++){
		//     if(grid[i][j]='0') continue;
		//     for(int k(0);k<4;k++){   
		//       int x=i+dirx[k];
		//       int y=j+diry[k];         
		//       if(x<0||x>=m||y<0||y>=n||grid[x][y]=='0') continue;
		//       else if(find(get(i,j))!=find(get(x,y))) fa[find(get(i,j))]=find(get(x,y));
		//       cout<<x<<" "<<y<<endl;
		//       }
		//     }
		//   }
		// }
		//统计不同区域的fa
		int ans(0);
		for (int i(0); i < m; i++)
			for (int j(0); j < n; j++) {
				if (grid[i][j] == '0') continue;
				if (find(get(i, j)) == get(i, j)) ans++;
			}
		return ans;
	}
private:
	const int dirx[4] = { 0,-1,0,1 };
	const int diry[4] = { -1,0,1,0 };
	vector<int>fa;
	vector<vector<bool>>visited;
	int m, n;
	int get(int x, int y) {
		return x * n + y;
	}
	//查找fa，找不到就路径压缩
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
};

//lc684冗余连接
//https://leetcode-cn.com/problems/redundant-connection/submissions/
class Solution {
public:
	vector<int> findRedundantConnection(vector<vector<int>>& edges) {
		int n(0);
		for (auto edge : edges) {
			n = max(n, edge[0]);
			n = max(n, edge[1]);
		}
		fa = vector<int>(n + 1, 0);
		for (int i(0); i < n; i++) fa[i] = i;
		for (auto edge : edges) {
			int x(edge[0]), y(edge[1]);
			if (find(x) != find(y)) unionSet(x, y);
			else return edge;
		}
		return {};
	}
private:
	vector<int>fa;
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	void unionSet(int x, int y) {
		fa[find(x)] = find(y);
	}
};
