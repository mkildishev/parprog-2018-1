#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include <cstdio>
#include <cmath>
#include <string>
#include <iostream>
using namespace std;
int* read_from_file(const char * a, int& t, double& time)
{

	FILE *matr = NULL;
	matr = fopen(a, "rb");
	int n;
	
	fread(&n, sizeof(n), 1, matr);
	t = n;
	int* graph = new int[n];

	fread(graph, sizeof(int), n, matr);
	if (time != -1)
		fread(&time, sizeof(double), 1, matr);
	fclose(matr);
	return graph;
}
// ������������ ��� �������������� � ����������� ��������
////////////////////////////////////////////////////////////////////////////////////////////
/*
// Checker ����� ������������� ��� ��� ��� ��������:
AC = Accepted = ������� ����� ���������� ��������� �� ������ �����
WA = Wrong Answer = ������� ����� ������������ ��������� �� ������ �����
PE = Presentation Error = ������ ������� �������� ������

// ��������� �������� checker �� ����� �������������
NO = No verdict = ������� �����������
CE = Compilation Error = ������ ����������
ML = Memory Limit Exceeded = ��������� ����������� �� ������
TL = Time Limit Exceeded = ��������� ����������� �� ������� ������
RE = Runtime Error = ������ ������� ���������� ���������
IL = Idle Limit Exceeded = ��������� ����� ������� (�����������) ���������
DE = Deadly Error = ������ ����������� �������
*/
enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };
class result
{
private:
	FILE * bur;
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
	result(bool read = false)
	{
		if (read) bur = fopen("result.txt", "r"); else bur = fopen("result.txt", "w");
	}
	~result() { fclose(bur); }
	void write_type(ext_cls t) { fwrite(&t, sizeof(t), 1, bur); }
	// �������� ����������� �������, ��� ������� �������� ���� �� ��������� verdict
	void write_verdict(verdict v)
	{
		write_type(ext_cls::VERDICT); fwrite(&v, sizeof(v), 1, bur);
	}
	// �������� ��������� �� checker'a ������������.
	// ��������, ��� ������� ������, ��� ��������.
	// ������������ ������ ��������� ����� � ����� ����������
	void write_message(string str)
	{
		write_type(ext_cls::MESSAGE); int l = str.size(); fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);
	}
	// �������� ����������� ������� ����� ������ ��������� ���������,
	// ����������� � ������� before_code
	// x ����� ����������� 100 �� = 10 ^ (-7) ���
	void write_time(long long x)
	{
		write_type(ext_cls::TIME); fwrite(&x, sizeof(x), 1, bur);
	}
	// �������� ����������� �������, ������ ������������� ���������� ���������
	void write_memory(unsigned long long x)
	{
		write_type(ext_cls::MEMORY); fwrite(&x, sizeof(x), 1, bur);
	}
} checker_result;


int main(int argc, char * argv[])
{
	char* pans = NULL;
	char* tans = NULL;
	if (argc > 1)
	{
		pans = argv[1];
		tans = argv[2];
	}
	int * ans = NULL, *res = NULL;
	int n; double stab_t = -1; double time = 0;
	ans = read_from_file(pans,n,time);
	res = read_from_file(tans,n,stab_t);
	
	bool isPassed = true;
	for (int i = 0; i < n; i++)
	{
		if (ans[i] != res[i])
		{
			isPassed = false;
			break;
		}
	}
	if (isPassed)
	{
		checker_result.write_message("AC. Numbers are equal."); 
		checker_result.write_verdict(verdict::AC);
	}
	else
	{
		checker_result.write_message("WA. Output is not correct.");
		checker_result.write_verdict(verdict::WA);
	}
	checker_result.write_time(time);
	std::cout << time;
	
}