//lc200��������
//https://leetcode-cn.com/problems/number-of-islands/
class Solution {
public:
	//��1���������С�1�����͹�Ϊһ�ࡣ����һ��grid�������´�
	int numIslands(vector<vector<char>>& grid) {
		this->m = grid.size();
		this->n = grid[0].size();
		visited = vector<vector<bool>>(m, vector<bool>(n, false));
		fa = vector<int>(n*m, 0);
		//���鼯��ʼ��
		for (int i(0); i < m; i++) {
			for (int j(0); j < n; j++) fa[get(i, j)] = get(i, j);
		}
		fa[0] = 0;
		//����grid,��Ϊ0�����ܲ�Խ����Ϊ'1',��ָ��fa
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
					//�������1���ڵ��ǲ�����ͬһ��fa���ͺϲ�
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
		//ͳ�Ʋ�ͬ�����fa
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
	//����fa���Ҳ�����·��ѹ��
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
};

//lc684��������
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
