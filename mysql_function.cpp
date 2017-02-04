#define _CRT_SECURE_NO_WARNINGS
#define __LCC__
#include <mysql.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstddef>
using namespace std;


// ������� ����������� ������������ ��������� ����� + ������
bool conn_user(const char user[], const char passwd[])
{
	MYSQL mysql; // ���������� ����������
	mysql_init(&mysql);  // �������������
	if (mysql_real_connect(&mysql, "localhost", user, passwd, "", 3306, NULL, 0)) {
		return true;
	}
	else
		return false;
}
// ������� ������������ � �� � ��������
void mysql_function(const char query[],
	const char host[] = "localhost", const char user[] = "admin", const char passwd[] = "passwd123321",
	const char db[] = "cpp_data", const int port = 3306) // host[]-����, user[]-������������, passwd[]-������, 
														 // library[]-�������� ��, port-����
{
	const char resultOfQuery[] = "resultOfQuery.txt";
	ofstream fout(resultOfQuery); // ���-� ������� ��������� � ���� ����
	if (!fout.is_open()) // ���� ���� ����� ������
	{
		throw 1; // ������ ��� �������� �����
	}
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	mysql_init(&mysql);
	mysql_real_connect(&mysql, host, user, passwd, db, port, NULL, 0);
	if (mysql_query(&mysql, query) > 0) // ������. ���� ������ ���, �� ���������� ������
	{
		// ���� ���� ������, ...
		fout << mysql_error(&mysql);	// ... ������� ��
		return; // � �������� ������
	}
	res = mysql_store_result(&mysql); // ����� ���������,
	int num_fields = mysql_num_fields(res); // ���������� �����
	long long num_rows = mysql_num_rows(res); // � ���������� �����.
	size_t t = 0; // ������� ��� ������ ������, ����������� '-'
	for (int i = 0; i < num_fields; i++) // ������� �������� �����
	{
		char *field_name = mysql_fetch_field_direct(res, i)->name;
		fout << setw(strlen(field_name) + 3) << field_name << " |";
		t += strlen(field_name) + 5;
	}

	fout << '\n';
	for (int i = 0; i < t; i++) {	// �������� ����� ������� �� ������
		fout << '-';
	}
	fout << '\n';

	for (int i = 0; i < num_rows; i++) // ����� �������
	{
		row = mysql_fetch_row(res); // �������� ������
		for (int l = 0; l < num_fields; l++) {
			char *field_name = mysql_fetch_field_direct(res, l)->name; // ���������� ��� ������������ ���-��
			fout << setw(strlen(field_name) + 3) << row[l] << " |";
		}
		fout << "\n";
	}
	fout << "Count records = " << num_rows; // ����� ���������� � ���������� �������
	mysql_free_result(res); // ������� ����������
	mysql_close(&mysql); // ��������� ����������
	fout.close(); // ��������� ����
}

