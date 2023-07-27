#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Info {
	string name;
	string content;
	int year;
	int month;
	int day;
};

void printinfo(Info info) {
	cout << "name :" << info.name << endl;
	cout << "content :" << info.content << endl;
	cout << "year :" << info.year << endl;
	cout << "month :" << info.month << endl;
	cout << "day :" << info.day << endl;
}
Info resetStruct(Info info) {
	Info temp{ "","",0,0,0};
	info = temp;
	return info;
}

void testInfo(Info *info, string name) {
	cout << "now name is " << info->name << endl;
	info->name = name;

	cout << name << "||" << info->name << endl;
}

void setInfo(Info *info, string name,string content, int year, int month, int day) {
	info->name = name;
	info->content = content;
	info->year = year;
	info->month = month;
	info->day = day;
}

void inputInfo(Info *info) {
	cout << "�̸� �Է� : "; getline(cin, info->name);
	cout << "���� �Է� : "; getline(cin, info->content);
	cout << "�⵵ �Է� :"; cin >> info->year;
	cout << "�� �Է� : "; cin >> info->month;
	cout << "�� �Է� :"; cin >> info->day;
}

int main(void) {
	Info a1{ "kim jung mu","hello world",2023,7,27 };

	printinfo(a1);

	a1=resetStruct(a1);
	cout << "main print name :" << a1.name << endl;
	testInfo(&a1, "������");
	printinfo(a1);

	inputInfo(&a1);
	cout << endl;
	printinfo(a1);
	return 0;
}

