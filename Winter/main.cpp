#include <iostream>
#include <thread>
#include <stdio.h>
#include <cstring>
#include <cstdlib> 
#include <ctime>
#include <iomanip>
#include <windows.h>
#include <string>
#include <cmath>
#include <algorithm>

using namespace  std;
int* map, k = -1, kn = 0, * tem, * bf, com = 0, move = 0;
double jcount[100][7][2] = { 0 }, sum[7][2] = { 0 }, varz[7][2] = { 0 };
string rows = "+----------+----------+----------+----------+----------+----------+----------+----------+",
	   row1 = "|          | 冒泡排序 | 直接排序 | 选择排序 | 箱子排序 |  堆排序  | 快速排序 | 归并排序 |",
	   row2 = "| 比较次数 |",
	   row3 = "| 移动次数 |",
	   rowsf = "+--------------+----------+----------+----------+----------+----------+----------+----------+",
	   row1f = "|              | 冒泡排序 | 直接排序 | 选择排序 | 箱子排序 |  堆排序  | 快速排序 | 归并排序 |",
	   row2f = "| 比较次数方差 |",
	   row3f = "| 移动次数方差 |";
	   

string sx[] = { "   冒泡排序   ","   直接排序   ","   选择排序   ","   箱子排序   ","    堆排序    ","   快速排序   ","   归并排序   " },
	   frank[5][7],
	   rar[4] = { "+---+--------------+--------------+--------------+",
				  "|   | 比较次数排名 | 移动次数排名 |  总次数排名  |",
				  "+---+--------------+--------------+",
				  "|   | 比较次数排名 | 移动次数排名 |" };

string str1 = "", str2 = "";

int jbox[1001],tim=0;

//进度条线程
void function_1() {
	int all_block_num = 10000;
	for (int i = 0; i < all_block_num; i += 10)
	{
		if (i < all_block_num - 10)
		{
			printf("\r正在测试[%.1lf%%]:", i * 100.0 / (all_block_num - 10));
		}
		else
		{
			printf("\r测试完成[%.1lf%%]:", i * 100.0 / (all_block_num - 10));
		}
		int show_num = i * 20 / all_block_num;
		for (int j = 1; j <= show_num; j++)
		{
			std::cout << "█";
			Sleep(0.8);
		}

	}
	std::cout << std::endl;
}
/*
+---------+---------+---------+--------+---------+-------+---------+---------+
|         | 冒泡排序 | 直接排序 | 选择排序 | 箱子排序 | 堆排序 | 快速排序 | 归并排序 |
+---------+---------+---------+--------+---------+-------+---------+---------+
| 比较次数 |    0    |    0    |    0   |    0    |   0   |    0    |    0    |  
+---------+---------+---------+--------+---------+-------+---------+---------+
| 移动次数 |    0    |    0    |    0   |    0    |   0   |    0    |    0    | 
+---------+---------+---------+--------+---------+-------+---------+---------+
*/
//格式化输出
void prt(double aim[7][2]) {
	string em = " ";
	cout << rows << endl;
	cout << row1 << endl;
	cout << rows << endl;
	cout << row2;
	for (int i = 0;i < 7;i++) {
		string now = to_string((int)aim[i][0]);
		int rlength = now.length();
		int yv = 10 > rlength ? 10 - rlength : 0;
		int byv = yv / 2;
		for (int j = 0;j < byv;j++) {
			cout << em;
		}
		cout << (int)aim[i][0];
		for (int j = byv;j < yv;j++) {
			cout << em;
		}
		cout << "|";
	}
	cout << endl;
	cout << rows << endl;
	cout << row3;
	for (int i = 0;i < 7;i++) {
		string now = to_string((int)aim[i][1]);
		int rlength = now.length();
		int yv = 10 > rlength ? 10 - rlength : 0;
		int byv = yv / 2;
		for (int j = 0;j < byv;j++) {
			cout << em;
		}
		cout << (int)aim[i][1];
		for (int j = byv;j < yv;j++) {
			cout << em;
		}
		cout << "|";
	}
	cout << endl;
	cout << rows << endl;
}
//方差输出
string toit(int a,int b, double ai[7][2]) {

	if (abs(ai[a][b] - 0) < 1e-4) {
		return "0.00";
	}
	int aim = ai[a][b] * 100;
	string ti = to_string(aim);
	int l = ti.length();
	string fin = "";
	for (int i = 0;i < l - 2;i++) {
		fin += ti[i];
	}
	fin += ".";
	for (int i = l - 2;i < l;i++) {
		fin += ti[i];
	}
	return fin;
}
void prtd(double aim[7][2]) {
	string em = " ";
	cout << rowsf << endl;
	cout << row1f << endl;
	cout << rowsf << endl;
	cout << row2f;
	for (int i = 0;i < 7;i++) {
		string now = toit(i,0,aim);
		int rlength = now.length();
		int yv = 10 > rlength ? 10 - rlength : 0;
		int byv = yv / 2;
		for (int j = 0;j < byv;j++) {
			cout << em;
		}
		cout << now;
		for (int j = byv;j < yv;j++) {
			cout << em;
		}
		cout << "|";
	}
	cout << endl;
	cout << rowsf << endl;
	cout << row3f;
	for (int i = 0;i < 7;i++) {
		string now = toit(i,1,aim);
		int rlength = now.length();
		int yv = 10 > rlength ? 10 - rlength : 0;
		int byv = yv / 2;
		for (int j = 0;j < byv;j++) {
			cout << em;
		}
		cout << now;
		for (int j = byv;j < yv;j++) {
			cout << em;
		}
		cout << "|";
	}
	cout << endl;
	cout << rowsf << endl;
}
//排名输出-conclusion
void rrank(double org[7],int c) {
	bool mark[7] = { 0 };
	double order[7];
	for (int i = 0;i < 7;i++) {
		order[i] = org[i];
	}
	sort(order,order+7);
	for (int i = 0;i < 7;i++) {
		for (int j = 0;j < 7;j++) {
			if (order[i] == org[j]&&(!mark[j])) {
				frank[c][i] = sx[j];
				mark[j] = true;
				break;
			}
		}
	}
}
void sran() {
	double tem[7];
	for (int i = 0;i < 7;i++) {
		tem[i] = sum[i][0];
	}
	rrank(tem, 0);
	for (int i = 0;i < 7;i++) {
		tem[i] = sum[i][1];
	}
	rrank(tem, 1);
	for (int i = 0;i < 7;i++) {
		tem[i] = sum[i][1]+sum[i][0];
	}
	rrank(tem, 2);
	for (int i = 0;i < 7;i++) {
		tem[i] = varz[i][0];
	}
	rrank(tem, 3);
	for (int i = 0;i < 7;i++) {
		tem[i] = varz[i][1];
	}
	rrank(tem, 4);
	str1 += rar[0] + "\n";
	str1 += rar[1] + "\n";
	str1 += rar[0] + "\n";
	for (int i = 0;i < 7;i++) {
		str1 += "| ";
		char xh = '1'+i;
		str1 += xh;
		str1 += " |";
		for (int j = 0;j < 3;j++) {
			str1 += frank[j][i];
			str1 += "|";
		}
		str1 += "\n";
	}
	str1 += rar[0] + "\n";

	str2 += rar[2] + "\n";
	str2 += rar[3] + "\n";
	str2 += rar[2] + "\n";
	for (int i = 0;i < 7;i++) {
		str2 += "| ";
		char xh = '1' + i;
		str2 += xh;
		str2 += " |";
		for (int j = 3;j < 5;j++) {
			str2 += frank[j][i];
			str2 += "|";
		}
		str2 += "\n";
	}
	str2 += rar[2] + "\n";
}
//生成范围在l~r的n个随机数 
void Random(int* a, int n, int l, int r,bool pf)
{
	srand(time(0));  //设置时间种子
	if(pf) srand(map[rand()%(k-1)]);
	for (int i = 0;i < n;i++) {
		a[i] = rand() % (r - l + 1) + l;//生成随机数 
		
	}
}
//备份
void renew() {
	for (int i = 0;i < k;i++) {
		map[i] = bf[i];
		//tem[i] = 2000;
	}
}
//更新
void update() {
	for (int i = 0;i < 7;i++) {
		for (int j = 0;j < 2;j++) {
			sum[i][j] += jcount[tim][i][j] / kn;
		}
	}
	tim++;
}
//冒泡排序
void buble() {
	bool hdo = false;
	for (int i = 1;i < k;i++) {
		jcount[tim][0][0]++;
		if (map[i - 1] > map[i]) {
			map[i] += map[i - 1];
			map[i - 1] = map[i] - map[i - 1];
			map[i] = map[i] - map[i - 1];
			jcount[tim][0][1] += 3;
			hdo = true;
		}

	}
	if (!hdo) {
		return;
	}
	else {
		buble();
	}
}
//直接排序
void direct() {
	
	tem[0] = map[0];
	for (int i = 1;i < k;i++) {
		
		tem[i] = 2000;
	}
	for (int i = 1;i < k;i++) {
		
		int aim = 0;
		for (int j = 0;j < k;j++) {
			jcount[tim][1][0]++;
			if (map[i] < tem[j]) {
				aim = j;
				break;
			}
		}
		for (int x = i;x > aim;x--) {
			
			tem[x] = tem[x - 1];
			jcount[tim][1][1]++;
		}
		tem[aim] = map[i];
		jcount[tim][1][1]++;
	}
}
//选择排序
void select() {
	for (int i = 0;i < k - 1;i++) {
		int min = i;
		bool pd = false;
		for (int j = i + 1;j < k;j++) {
			jcount[tim][2][0]++;
			if (map[j] < map[min]) {
				min = j;
				pd = true;
			}

		}
		if (pd) {
			int zh = map[i];
			map[i] = map[min];
			map[min] = zh;
			jcount[tim][2][1] += 3;
		}
	}
}
//箱子排序
void box() {
	for (int i = 0;i < 1001;i++) {
		jbox[i] = 0;
	}
	for (int i = 0;i < k;i++) {
		jbox[map[i]]++;
	}
	int y = 0;
	for (int i = 0;i < 1001;i++) {
		for (int j = 0;j < jbox[i];j++) {
			map[y] = i;
			y++;
			//if (y < k)y++;
		}
	}

}
//堆排序
void heap(int st) {
	int kk = (st - 1) / 2;
	for (int i = kk;i >= 0;i--) {
		int z = i * 2 + 1, y = i * 2 + 2;
		bool zy;
		if (y > st) {
			zy = true;
		}
		else {
			zy = map[z] > map[y];
		}
		jcount[tim][4][0]++;
		if (zy) {
			jcount[tim][4][0]++;
			if (map[z] > map[i]) {
				map[z] += map[i];
				map[i] = map[z] - map[i];
				map[z] -= map[i];
				jcount[tim][4][1] += 3;
				
			}
		}
		else {
			jcount[tim][4][0]++;
			if (map[y] > map[i]) {
				map[y] += map[i];
				map[i] = map[y] - map[i];
				map[y] -= map[i];
				jcount[tim][4][1] += 3;
			}
		}
	}
	map[0] += map[st];
	map[st] = map[0] - map[st];
	map[0] -= map[st];
	jcount[tim][4][1]+=3;
	if (st > 1) {
		heap(st - 1);
	}
}
//快速排序
void quick(int le,int ri) {
	if (le < ri) {
		int x = le;
		int y = ri;
		int temp = map[le];
		while (x < y) {
			while (y > x&& map[y] > temp) {
				y--;
				jcount[tim][5][0] ++;
			}
			
			if (x < y) {
				map[x] = map[y];
				x++;
				
				jcount[tim][5][1]++;
			}
			while (x < y && map[x] <= temp) {
				x++;
				jcount[tim][5][0] ++;
			}
			
			if (x < y) {
				map[y] = map[x];
				y--;
				jcount[tim][5][1]++;
			}
		}
		map[x] = temp;
		jcount[tim][5][1]++;
		quick(le, x - 1);
		quick(x + 1, ri);
	}
}
//归并排序
void mix(int l, int mid, int r)
{
	int k = 0;
	int i = l;int j = mid;
	while (i < mid && j <= r)
	{
		jcount[tim][6][0]++;
		jcount[tim][6][1]++;
		if (map[i] <= map[j]) {
			tem[k++] = map[i++];
		}
		else {
			tem[k++] = map[j++];
		}
			
	}
	while (j <= r) { 
		
		jcount[tim][6][1]++;
		tem[k++] = map[j++]; 
	}
	while (i < mid) {
		
		jcount[tim][6][1]++;
		tem[k++] = map[i++];
	}
	for (int i = l;i <= r;i++) {
		
		jcount[tim][6][1]++;
		map[i] = tem[i - l];
	}
}
void merge(int start, int end) {
	if (start == end) {
		return;
	}
	int mid = (start + end) / 2;
	merge(start, mid);
	merge(mid + 1, end);
	mix(start, mid + 1, end);
}
int inint() {
	string temin="";
	cin >> temin;
	bool is = true;
	for (int i = 0;i < temin.length();i++) {
		if (temin[i] > '9' || temin[i] < '0')
			is = false;
	}
	if (!is) {
		cout << "请输入整数:";
		return inint();
	}
	else {
		int res = atoi(temin.c_str());
		return res;
	}
}
void ink() {
	k = inint();
	if (k < 100) {
		cout << "输入应不小于100:";
		ink();
	}
}
int main() {
	cout << "Input:" << endl;
	
	cout << "请输入一个不小于100的整数作为测试随机数组长度:";
	ink();
	
	cout << "请输入测试数据组数:";
	kn = inint();

	cout << endl;
	cout << "即将开始长为 " << k << " 随机数组的 " << kn << " 次排序测试" << endl;
	cout << endl;
	Sleep(3000);

	//添加不定长数组
	map = new int[k];
	Random(map, k, 0, 1000, false);
	tem = new int[k];
	//for (int i = 0;i < k;i++)tem[i] = 2000;
	bf = new int[k];
	
	for (int i = 0;i < kn;i++) {
	
		std::thread t1(function_1);
		Random(map, k, 0, 1000, true);
		for (int i = 0;i < k;i++) {
			//tem[i] = map[i];
			bf[i] = map[i];
		}
		buble();			renew();
		direct();			renew();
		select();			renew();
		box();				renew();
		heap(k-1);			renew();
		quick(0, k - 1);	renew();
		merge(0, k - 1);
		t1.join();
		cout << "第" << (i + 1) << "次测试结果：" << endl;
		prt(jcount[tim]);
		//排序测试
		/*cout << "初始数据:";
		for (int j = 0;j < k;j++) {
			cout << bf[j] << " ";
		}
		cout << endl;
		cout << "结果:";
		for (int j = 0;j < k;j++) {
			cout << map[j] << " ";
		}
		cout << endl;*/
		update();
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << kn << "次测试平均结果：" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	prtd(sum);
	double force = pow(kn, 0.5);
	for (int i = 0;i < 7;i++) {
		for (int j = 0;j < 2;j++) {
			for (int q = 0;q < kn;q++) {
				varz[i][j] += ((jcount[q][i][j] - sum[i][j]) / force)* ((jcount[q][i][j] - sum[i][j]) / force);
			}
		}
	}
	sran();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    cout << "平均结果排名(升序):" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << str1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "稳定性(方差)统计:" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	prtd(varz);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "稳定性排名(升序):" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << str2;

	cout << "End" << endl;
	free(map);
	free(tem);
	free(bf);
	//delete map;
	//delete tem;//删除
	return 0;
}