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

using namespace  std;
int* map, k = 0, kn = 0, * tem, * bf, com = 0, move = 0;
double jcount[100][7][2] = { 0 }, sum[7][2] = { 0 }, varz[7][2] = { 0 };
string rows = "+----------+----------+----------+----------+----------+----------+----------+----------+",
	   row1 = "|          | ð������ | ֱ������ | ѡ������ | �������� |  ������  | �������� | �鲢���� |",
	   row2 = "| �Ƚϴ��� |",
	   row3 = "| �ƶ����� |",
	   rowsf = "+--------------+----------+----------+----------+----------+----------+----------+----------+",
	   row1f = "|              | ð������ | ֱ������ | ѡ������ | �������� |  ������  | �������� | �鲢���� |",
	   row2f = "| �Ƚϴ������� |",
	   row3f = "| �ƶ��������� |";

int jbox[1001],tim=0;

//�������߳�
void function_1() {
	int all_block_num = 10000;
	for (int i = 0; i < all_block_num; i += 10)
	{
		if (i < all_block_num - 10)
		{
			printf("\r���ڲ���[%.1lf%%]:", i * 100.0 / (all_block_num - 10));
		}
		else
		{
			printf("\r�������[%.1lf%%]:", i * 100.0 / (all_block_num - 10));
		}
		int show_num = i * 20 / all_block_num;
		for (int j = 1; j <= show_num; j++)
		{
			std::cout << "��";
			Sleep(0.8);
		}

	}
	std::cout << std::endl;
}
/*
+---------+---------+---------+--------+---------+-------+---------+---------+
|         | ð������ | ֱ������ | ѡ������ | �������� | ������ | �������� | �鲢���� |
+---------+---------+---------+--------+---------+-------+---------+---------+
| �Ƚϴ��� |    0    |    0    |    0   |    0    |   0   |    0    |    0    |  
+---------+---------+---------+--------+---------+-------+---------+---------+
| �ƶ����� |    0    |    0    |    0   |    0    |   0   |    0    |    0    | 
+---------+---------+---------+--------+---------+-------+---------+---------+
*/
//��ʽ�����
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
//�������
string toit(int a,int b) {

	if (abs(varz[a][b] - 0) < 1e-4) {
		return "0.00";
	}
	int aim = varz[a][b] * 100;
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
void prt() {
	string em = " ";
	cout << rowsf << endl;
	cout << row1f << endl;
	cout << rowsf << endl;
	cout << row2f;
	for (int i = 0;i < 7;i++) {
		string now = toit(i,0);
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
		string now = toit(i,1);
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


//���ɷ�Χ��l~r��n������� 
void Random(int* a, int n, int l, int r,bool pf)
{
	srand(time(0));  //����ʱ������
	if(pf) srand(map[rand()%(k-1)]);
	for (int i = 0;i < n;i++) {
		a[i] = rand() % (r - l + 1) + l;//��������� 
		
	}
}
//����
void renew() {
	for (int i = 0;i < k;i++) {
		map[i] = bf[i];
		//tem[i] = 2000;
	}
}
//����
void update() {
	for (int i = 0;i < 7;i++) {
		for (int j = 0;j < 2;j++) {
			sum[i][j] += jcount[tim][i][j] / kn;
		}
	}
	tim++;
}
//ð������
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
//ֱ������
void direct() {
	
	tem[0] = map[0];
	for (int i = 1;i < k;i++) {
		jcount[tim][0][0]++;
		tem[i] = 2000;
	}
	for (int i = 1;i < k;i++) {
		jcount[tim][0][0]++;
		int aim = 0;
		for (int j = 0;j < k;j++) {
			jcount[tim][0][0]+=2;
			if (map[i] < tem[j]) {
				aim = j;
				break;
			}
		}
		for (int x = i;x > aim;x--) {
			jcount[tim][0][0]++;
			tem[x] = tem[x - 1];
			jcount[tim][1][1]++;
		}
		tem[aim] = map[i];
	}
}
//ѡ������
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
//��������
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
//������
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
//��������
void quick(int le,int ri) {
	jcount[tim][5][0]++;
	if (le < ri) {
		
		int x = le;
		int y = ri;
		int temp = map[le];
		while (x < y) {
			jcount[tim][5][0]++;
			while (y > x&& map[y] > temp) {
				y--;
				jcount[tim][5][0] += 2;
			}
			jcount[tim][5][0]++;
			if (x < y) {
				map[x] = map[y];
				x++;
				
				jcount[tim][5][1]++;
			}
			while (x < y && map[x] <= temp) {
				x++;
				jcount[tim][5][0] += 2;
			}
			jcount[tim][5][0]++;
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
//�鲢����
void mix(int l, int mid, int r)
{
	int k = 0;
	int i = l;int j = mid;
	while (i < mid && j <= r)
	{
		jcount[tim][6][0]+=3;
		jcount[tim][6][1]++;
		if (map[i] <= map[j]) {
			tem[k++] = map[i++];
		}
		else {
			tem[k++] = map[j++];
		}
			
	}
	while (j <= r) { 
		jcount[tim][6][0]++;
		jcount[tim][6][1]++;
		tem[k++] = map[j++]; 
	}
	while (i < mid) {
		jcount[tim][6][0]++;
		jcount[tim][6][1]++;
		tem[k++] = map[i++];
	}
	for (int i = l;i <= r;i++) {
		jcount[tim][6][0]++;
		jcount[tim][6][1]++;
		map[i] = tem[i - l];
	}
}
void merge(int start, int end) {
	jcount[tim][6][0]++;
	if (start == end) {
		return;
	}
	int mid = (start + end) / 2;
	merge(start, mid);
	merge(mid + 1, end);
	mix(start, mid + 1, end);
}
int main() {
	cout << "Input:" << endl;
	cout << "������һ������100��������Ϊ����������鳤��:";
	cin >> k;
	cout << "�����������������:";
	cin >> kn;
	//��Ӳ���������
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
		buble();renew();
		direct();renew();
		select();renew();
		box();renew();
		heap(k-1);renew();
		quick(0, k - 1);renew();
		merge(0, k - 1);
		t1.join();
		cout << "��" << (i + 1) << "�β��Խ����" << endl;
		prt(jcount[tim]);
		/*cout << "��ʼ����:";
		for (int j = 0;j < k;j++) {
			cout << bf[j] << " ";
		}
		cout << endl;
		cout << "���:";
		for (int j = 0;j < k;j++) {
			cout << map[j] << " ";
		}
		cout << endl;*/
		update();
	}
	cout << kn << "�β���ƽ�������" << endl;
	prt(sum);

	for (int i = 0;i < 7;i++) {
		for (int j = 0;j < 2;j++) {
			for (int q = 0;q < kn;q++) {
				varz[i][j] += pow((jcount[q][i][j] - sum[i][j]), 2) / kn;	
			}
		}
	}
	cout << "����ͳ��" << endl;
	prt();

	cout << "End" << endl;
	free(map);
	free(tem);
	free(bf);
	//delete map;
	//delete tem;//ɾ��
	return 0;
}