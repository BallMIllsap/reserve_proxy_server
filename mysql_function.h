#ifndef MYSQL_FUNCTION_H
#define MYSQL_FUNCTION_H
#define _CRT_SECURE_NO_WARNINGS
#define __LCC__
#include <mysql.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstddef>
using namespace std;

// ������� ����������� ������������ ��������� ����� + ������
bool conn_user(const char user[], const char passwd[]);
// ������� ������������ � �� � ��������

void mysql_function(const char query[],
	const char host[] = "localhost", const char user[] = "admin", const char passwd[] = "passwd123321",
	const char db[] = "cpp_data", const int port = 3306); // host[]-����, user[]-������������, passwd[]-������, 
										 // library[]-�������� ��, port-����


#endif MYSQL_FUNCTION_H

