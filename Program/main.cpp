// Lab_11_1_1
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void write_file(FILE *f) // ��������� ����� ������� � �������� �����
{
	fseek(f, 0, SEEK_SET);
	int tmp;
	char ch;
	do
	{
		cout << "enter digit: "; cin >> tmp;
		fwrite((char*)&tmp, sizeof(int), 1, f);
		cout << "continue? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
}

void draw_file(FILE* f) {
	fseek(f, 0, SEEK_SET);
	int tmp;
	while (!feof(f)) {
		fread((char*)&tmp, sizeof(int), 1, f);
		if (feof(f))
			break;
		cout << tmp << endl;
	}
}

void change(FILE* in, FILE* out) {
	int tmp, sum = 0;
	fseek(in, 0, SEEK_SET);
	while (!feof(in)) {
		fread((char*)&tmp, sizeof(int), 1, in);
		if (feof(in))
			break;
		sum += tmp;
		fwrite((char*)&sum, sizeof(int), 1, out);
	}
}

void main() {
	char t[256];

	cout << "Input in filename: "; cin >> t;

	FILE* fin;
	if ((fin = fopen(t, "rb")) == NULL)
	{
		if ((fin = fopen(t, "wb+")) != NULL) 
			write_file(fin);
		else {
			cout << "Incorrect in file name!";
			return;
		}
	}
	
	cout << "Input out filename: "; cin >> t;
	FILE* fout;
	if ((fout = fopen(t, "wb+")) != NULL) {
		change(fin, fout);
		draw_file(fout);
		fclose(fout);
	}
	else cout << "Incorrect out file name!";
	fclose(fin);
}