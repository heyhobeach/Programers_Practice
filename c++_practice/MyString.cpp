#include <iostream>
//#include <string.h>
using namespace std;

class MyString {
	char* string_content;
	int string_length;
	int memory_capacity;
public:
	MyString(char c);
	MyString(const char* str);
	MyString(const MyString& str);

	~MyString();

	int calc_length(const char* str);//const?

	MyString& assign(const char* str);
	MyString& assign(const MyString& str);

	MyString& insert(int loc,char c);
	MyString& insert(int loc,const char *str);
	MyString& insert(int loc, const MyString& str);

	MyString& erase(int loc, int num);

	void reserve(int size);

	int capacity()const;

	int get_length()const;

	int find(int find_from,const MyString& str)const;
	int find(int find_from, const char* str)const;
	int find(int find_from, const char c)const;

	int compare(const MyString& str)const;

	int KMP_find(const MyString& str)const;
	
	char at(int i)const;

	void print()const;
	void println()const;
};

MyString::MyString(char c) {
	string_content = new char[1];
	string_content[0] = c;
	string_length = 1;
	memory_capacity = 1;
}


MyString::MyString(const char* str) {
	cout << str << endl;
	string_length=calc_length(str);
	memory_capacity = string_length;
	cout <<"length:"<< string_length << endl;
	string_content = new char[string_length];
	for (int i = 0; i != string_length; i++) {
		string_content[i] = str[i];
	}
}
MyString::MyString(const MyString& str) {
	string_length = str.string_length;
	string_content = new char[string_length];
	memory_capacity = str.string_length;
	for (int i = 0; i != string_length; i++) {
		string_content[i] = str.string_content[i];
	}
}


int MyString::calc_length(const char* str) {
	int calc_length = 0;
	while (true) {
		if (str[calc_length] == NULL) {
			break;
		}
		calc_length++;
	}
	return calc_length;
}

MyString& MyString::assign(const char *str) {
	int str_len = calc_length(str);
	cout << memory_capacity << endl;
	if (str_len>memory_capacity) {
		delete string_content;
		string_content = new char[str_len];
		cout << "�޸� �����Ҵ�\t" <<str_len<< endl;
		memory_capacity = str_len;
	}

	for (int i = 0; i != str_len; i++) {
		string_content[i] = str[i];
	}
	string_length = str_len;


	return *this;
}

MyString& MyString::assign(const MyString& str) {
	if (str.string_length > memory_capacity) {
		delete string_content;
		string_content = new char[str.string_length];
		cout << "�޸� �����Ҵ�\t" <<str.string_length<< endl;
		memory_capacity = str.string_length;
	}

	for (int i = 0; i != str.string_length; i++) {
		string_content[i] = str.string_content[i];
	}
	string_length = str.string_length;
	cout << "asignȣ��" << endl;

	return *this;
}

void MyString::reserve(int size) {
	if (size > memory_capacity) {
		char* prv_string_content = string_content;
		string_content = new char[size];
		memory_capacity = size;
		cout << "�޸� �Ҵ�" << endl;

		for (int i = 0; i != string_length; i++) {
			string_content[i] = prv_string_content[i];
		}
		delete[] prv_string_content;
	}
}

int MyString::capacity()const { 
	return memory_capacity; 
}


int MyString::get_length()const {
	return string_length;
}

void MyString::print() const{
	for (int i = 0; i != string_length; i++) {
		cout << string_content[i];
	}
}

void MyString::println() const{
	for (int i = 0; i != string_length; i++) {
		cout << string_content[i];
	}
	cout << endl;
}

int MyString::find(int find_from, const MyString& str)const {//�Է¹��� str �� ã�� ����
	int i, j;
	if (str.string_length == 0) {
		cout << "�Է� ���� ���� ����" << endl;
		return -1;
	}
	for (i = find_from; i <= string_length-str.string_length; i++) {//�������� ���������� �˻����ʿ� ���� ��) leo sleeps at my desk ���� dest�� ã�µ� desk ���� k���� ���ʿ� ���ٴ� �� ��� ã�����ϴ� ���� ���̺��ٴ� ª������
		for (j = 0; j < str.string_length; j++) {
			if (string_content[i + j] != str.string_content[j]) {
				break;//���ڿ��� ã�� ���ڿ� ���ؼ� �ٸ��ٸ� break ������ �ݺ�
			}
			if (j == str.string_length) {//j���� �ݺ��ϸ鼭 ������ ã�¹��ڿ� ���̰� ���������� �� ã������
				return i;
			}
		}
	}
	return -1;//��� �ݺ��� ���������� ã������
}

int MyString::find(int find_from, const char* str)const {
	MyString temp(str);
	return find(find_from, temp);
}

int MyString::find(int find_from, char c)const {
	MyString temp(c);
	return find(find_from, temp);
}

MyString& MyString::insert(int loc, const MyString& str) {
	if (loc > string_length || loc < 0) {
		cout << "out of range" << endl;
		return *this;
	}
	if (string_length + str.string_length > memory_capacity) {
		if (memory_capacity * 2 > string_length + str.string_length) {
			memory_capacity *= 2;
		}
		else {
			memory_capacity = string_length + str.string_length;
		}
		char* prv_string_content = string_content;
		string_content = new char[memory_capacity];

		int i;
		for (i = 0; i != loc; i++) {
			string_content[i] = prv_string_content[i];
		}
		for (int j = 0; j != str.string_length; j++) {//str.strstring���� ���� ��������
			string_content[j + i] = str.string_content[j];
		}
		for (; i < string_length; i++) {//str.string_length �� insert�ϴ� ��ü�� ���̸�ŭ ���� �������� �����ĺ��� ���� ���� ����
			string_content[i + str.string_length] = prv_string_content[i];
			//string_content[str.string_length + i] = prv_string_content[i];
		}
		delete[]prv_string_content;
		string_length = string_length + str.string_length;//���ڿ� ���� ������Ʈ

		return *this;
	}
	else {
		for (int i = string_length - 1; i >= loc; i--) {
			string_content[i + str.string_length] = string_content[i];//���������͸� �ڷ� �̴��۾� 
		}
		for (int i = 0; i < str.string_length; i++) {
			string_content[i + loc] = str.string_content[i];
		}
	}
	string_length = string_length + str.string_length;
	return *this;

}

MyString& MyString::insert(int loc, const char* str) {
	MyString temp(str);//���ڿ��� ���� ��ü����
	return insert(loc, temp);//��ü�����͸� insert�ϸ鼭 ������ insert(��ü) �Լ��� ���ϰ��� insert(const char *str)�� ���ϰ��� �����ϱ⿡ �����Ҷ� ������ ����
}

MyString& MyString::insert(int loc, const char c) {
	MyString temp(c);//char ������ ��ü����
	return insert(loc, temp);//��ü�����͸� insert�ϸ鼭 ������ insert(��ü) �Լ��� ���ϰ��� insert(const char c)�� ���ϰ��� �����ϱ⿡ �����Ҷ� ������ ����
}

MyString& MyString::erase(int loc, int num) {
	if (num<0 || loc<0 || loc>string_length || num + loc>string_length) {
		return *this;
	}
	for (int i = num + loc; i < string_length; i++) {
		string_content[i - num] = string_content[i];//num��ġ��ŭ �ڿ��ִ°��� ������ �����
	}
	
	string_length -= num;
	return *this;
}

int MyString::compare(const MyString& str)const {
	for (int i = 0; i < min(string_length, str.string_length); i++) {
		if (string_content[i] > str.string_content[i]) {
			return 1;
		}
		else
		{
			return -1;
		}
	}
	if (string_length == str.string_length) {
		return 0;
	}
	else if (string_length > str.string_length) {
		return 1;
	}
	return -1;
}

int MyString::KMP_find(const MyString& str) const{
	int m = str.string_length,j = 0,k=0;
	int count;
	cout << "length:" << m << endl;
	cout << "input string:";
	str.println();
	int* pi = new int[m]();//0�����ʱ�ȭ

	cout << "get pi" << endl;
	cout << endl;
	for (int i = 1; i < m; i++) {
		while (j > 0 && str.string_content[j] != str.string_content[i]) {
			cout << "�ٸ� " << j << endl;
			j = pi[j - 1];
		}
		if (str.string_content[j] == str.string_content[i]) {
			//count = 0;
			pi[i] = ++j;
			cout<<"pi " << pi[i] << endl;
			cout << "���� :" <<i <<"\t���� " <<str.string_content[i] << endl;
		}
		else {
			cout << "��ġ�ϴ� ���� ����" << endl;
		}
	}
	cout << "KMP" << endl;
	cout << endl;
	//cout << "string i\t\t string k \t" << endl;
	for (int i = 0; i < string_length; i++) {
		cout << "text" << i << string_content[i] << "\t\t" << "pattern" << k << "\t" << str.string_content[k] << endl;
		while (k > 0 && string_content[i] != str.string_content[k]) {
			cout << "����ġ" << endl;
			k = pi[k - 1];
			cout << "k��:" << k<<pi[k] << endl;
		}
		if (string_content[i] == str.string_content[k]) {
			if (k == m-1) {//k�� ���̱��� ã�� m-1�� ���� �迭�Ǳ������� ���� �ܾ�� 0~string_length-1�� ���� ���̰� ���� ���̻� m���� �ϰԵǸ� �״����� ���� ����
				k = pi[k];//�ٽ� k�� 0���� �ʱ�ȭ ���� ��� �Ѵܾ ã�����Ƿ� �ʱ�ȭ ���� ������ ���� ������ �߻�
				cout << "��ġ��" << endl;
			}
			else {//�����ѵ� k�� �񱳴��ũ����� �������Ѱ��

				k++;
			}
		}
	}
	return 0;
}

char MyString::at(int i)const {
	if (i > string_length || i < 0) {
		return 0;
	}
	else
	{
		return string_content[i];
	}
}



MyString::~MyString() {
	delete[]string_content;
}

int main(void) {
	MyString str1("acbasdf");
	//cout <<"length:"<< str1.get_length() << endl;
	MyString str2("a");
	MyString str3("aadsfsdaa");
	str1.println();
	//str1.assign("ab");
	str1.println();
	//str1.assign("abds");
	str1.assign(str2.assign(str3)).assign("new string ");
	str1.println();
	cout << "capacity: "<<str1.capacity() << endl;;
	//str1.reserve(1000);
	str1.println();
	cout << "capacity: " << str1.capacity()<<"\tlen: "<<str1.get_length() << endl;

	str2.println();
	str1.insert(2,str2);
	cout << "inset" << endl;

	str1.println();
	str1.assign("ban ana & banana & banana & banana");
	str1.println();
	str2.assign("banana");
	str3.assign("banana on my banana");
	cout << str3.KMP_find(str2) << endl;
	cout << "" << endl;
	return 0;
}