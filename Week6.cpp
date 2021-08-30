//lc279��ȫƽ����
//https://leetcode-cn.com/problems/perfect-squares/
class Solution {
public:
	int numSquares(int n) {
		//��Ʒ����ȫƽ�������������ȫƽ������ֵ�����������n
		vector<int>f(n + 1);
		for (int i(1); i <= n; i++) {
			int minval = 1e9;
			for (int j(1); j*j <= i; j++) {
				minval = min(minval, f[i - j * j]);
			}
			f[i] = minval + 1;
		}
		return f[n];
	}
};

//lc70��¥��
//https://leetcode-cn.com/problems/climbing-stairs/submissions/
class Solution {
public:
	int climbStairs(int n) {
		vector<int> f(n + 1, 0);
		//��0��1�����ݶ���1��
		f[0] = 1;
		f[1] = 1;
		for (int i(2); i <= n; i++) {
			f[i] = f[i - 1] + f[i - 2];
		}
		return f[n];
	}
};

