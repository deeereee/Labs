#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <clocale>
#include <stdlib.h>
#include <locale>
#include <iostream>
#include <string.h>
using namespace std;

#define max 200


struct fio
{
	char* surname;
	char* name;
	char* middlename;
};
struct date
{
	int day;
	char* month;
	int year;
};
struct plane
{
	char* company;
	fio fio1;
	int flight;
	int cost;
	date date1;
};

void int_passenger(plane* pas, const int num);
void load(plane* pas, int& n);
void save(plane* pas, int n);
void print_passenger(plane* pas, const int num);
void list_pas(plane* pas, int n);
void compare_date(plane* pas, int n);

int main()
{
	setlocale(0, "Russian");

	plane* passengers = new plane[max];
	FILE* pf;
	int t, y, N_p = 0;
	if ((pf = fopen("data.bin", "rb+")) == NULL)
	{
		cout << "����� ���, ������������� � ���������� !" << endl;
		for (int i = 0; i < 2; i++)
		{

			int_passenger(passengers, N_p);
			N_p++;
		}
	}
	else			
		load(passengers, N_p);

	

	do
	{

		cout << "\n�������� ���������..........1\n";
		cout << "����� ���������.............2\n";
		cout << "����� ���������� ��������...3\n";
		cout << "������� ��� ����............4\n";
		cout << "����� �� ����...............5\n";
		cout << "�����.......................6\n";
		cout << "�������: ";

		scanf_s("%d",&t);
		
		switch (t) {
		case 1:

			int_passenger(passengers, N_p);
			N_p++;
			break;
		case 2:
			cout << "\n������� ����� ���������: ";
			cin >> y;

			if (y < N_p)
				print_passenger(passengers, y);
			else
				cout << "\n��������� � ����� ������� ���\n";

			break;
		case 3:
			char d[50];
			cout << "\n������� �������� ��������:";
			cin >> d;

			for (int i = 0; i < N_p; i++)
			{
				if (strcmp(d, passengers[i].company) == 0)
					print_passenger(passengers, i);
			}
			break;
		case 4:
			list_pas(passengers, N_p);
			break;
		case 5:
			compare_date(passengers, N_p);
			break;
		case 6:
			break;
		default:
			cout << "--------�������� ��������---------";
			break;
		}
	} while (t != 6);

	save(passengers, N_p);

	delete[]passengers;

	return 0;
}

void int_passenger(plane* pas, const int num)//������� ����� ������ ������ ���������

{
	int x = 0;
	char buff[50];
	plane* tpas;
	tpas = pas + num;

	cout << "\n�������� : ";
	fscanf(stdin, "%s", buff);
	tpas->company = new char[strlen(buff) + 1];
	memcpy(tpas->company, buff, (strlen(buff) + 1));
	fflush(stdin);

	cout << "\n�������: ";
	fscanf(stdin, "%s", buff);
	tpas->fio1.surname = new char[strlen(buff) + 1];
	memcpy(tpas->fio1.surname, buff, (strlen(buff) + 1));
	fflush(stdin);

	cout << "\n���: ";
	fscanf(stdin, "%s", buff);
	tpas->fio1.name = new char[strlen(buff) + 1];
	memcpy(tpas->fio1.name, buff, (strlen(buff) + 1));
	fflush(stdin);

	cout << "\n��������: ";
	fscanf(stdin, "%s", buff);
	tpas->fio1.middlename = new char[strlen(buff) + 1];
	memcpy(tpas->fio1.middlename, buff, (strlen(buff) + 1));
	fflush(stdin);

	cout << "\n����";
	do
	{
		cout << "\n����: ";
		cin >> tpas->date1.day;

		if (tpas->date1.day <= 0 || tpas->date1.day > 31)
			cout << "\n---------������! ����������� ����---------- ";
		else
			x = 1;

	} while (x != 1);

	x = 0;

	do
	{
		cout << "\n�����: ";
		fscanf(stdin, "%s", buff);

		if (strcmp(buff, "december") == 0 || strcmp(buff, "january") == 0 || strcmp(buff, "february") == 0 || strcmp(buff, "march") == 0
			|| strcmp(buff, "april") == 0 || strcmp(buff, "may") == 0 || strcmp(buff, "june") == 0 || strcmp(buff, "july") == 0
			|| strcmp(buff, "august") == 0 || strcmp(buff, "october") == 0 || strcmp(buff, "september") == 0 || strcmp(buff, "november") == 0)
		{
			tpas->date1.month = new char[strlen(buff) + 1];
			memcpy(tpas->date1.month, buff, (strlen(buff) + 1));
			fflush(stdin);
			x = 1;
		}
		else
		{
			cout << "\n---------������! ����������� ����---------- ";
		}

	} while (x != 1);





	x = 0;
	do
	{
		cout << "\n���: ";
		cin >> tpas->date1.year;


		if (tpas->date1.year < 2021 || tpas->date1.year > 2030)
			cout << "\n---------������! ����������� ����---------- ";
		else
			x = 1;

	} while (x != 1);

	cout << "\n����� �����: ";
	cin >> tpas->flight;

	cout << "\nC��������: ";
	cin >> tpas->cost;
	fflush(stdin);

}

void load(plane* pas, int& n)
{

	FILE* pf;
	char buff[80];

	if ((pf = fopen("data.bin", "rb")) == NULL)
	{
		perror("������ �������� �����: ����� load_bin");
	}

	plane* tpas;

	for (tpas = pas; !feof(pf); tpas++)
	{
		fread(tpas, sizeof(plane), 1, pf);
		n++;

		
	}
	// ������ 1��� ���������
	fclose(pf);

	n--;

	if ((pf = fopen("data.txt", "r")) == NULL)
	{
		perror("������ �������� �����: ����� load_txt");
	}
	for (tpas = pas; !feof(pf); tpas++)
	{
		fscanf(pf, "%s\n", buff);
		tpas->fio1.surname = new char(strlen(buff) + 1);
		strcpy(tpas->fio1.surname, buff);

		fscanf(pf, "%s\n", buff);
		tpas->fio1.name = new char(strlen(buff) + 1);
		strcpy(tpas->fio1.name, buff);

		fscanf(pf, "%s\n", buff);
		tpas->fio1.middlename = new char(strlen(buff) + 1);
		strcpy(tpas->fio1.middlename, buff);

		fscanf(pf, "%s\n", buff);
		tpas->company = new char(strlen(buff) + 1);
		strcpy(tpas->company, buff);

		fscanf(pf, "%s\n", buff);
		tpas->date1.month = new char(strlen(buff) + 1);
		strcpy(tpas->date1.month, buff);
	}
	fclose(pf);

}

void save(plane* pas, int n)
{
	plane* tpas;
	FILE* pf;
	pf = fopen("data.bin", "wb");
	if (pf == NULL)
	{
		perror("������ �������� �����: ����� save_bin");
	}

	
	fwrite(pas, sizeof(plane), n, pf);
	fclose(pf);

	if ((pf = fopen("data.txt", "w")) == NULL)
	{
		perror("������ �������� �����: ����� save_txt");
	}

	for (tpas = pas; tpas < pas + n; tpas++)
	{
		fprintf(pf, "%s\n", tpas->fio1.surname);
		fprintf(pf, "%s\n", tpas->fio1.name);
		fprintf(pf, "%s\n", tpas->fio1.middlename);
		fprintf(pf, "%s\n", tpas->company);
		fprintf(pf, "%s\n", tpas->date1.month);
	}
	fclose(pf); // ������� ��������� ����
};

void print_passenger(plane* pas, const int num)//������� ������ ������ ������ ���������
{
	plane* tpas = pas+num;
	printf( "\n------------------------------�������� � %d ------------------------------------\n", num);
	cout << "��������: " << pas[num].company << "\n";
	cout << "�������: " << pas[num].fio1.surname << "\n";
	cout << "���: " << pas[num].fio1.name << "\n";
	cout << "��������: " << pas[num].fio1.middlename << "\n";
	cout << "����" << "\t"; fprintf(stdout, "%d\t%s\t%d\n", tpas->date1.day, tpas->date1.month , tpas->date1.year );
	cout << "����� �����: "; fprintf(stdout,"%d\n", pas[num].flight );
	cout << "C��������: "; fprintf(stdout,"%d\n", pas[num].cost);
	cout << "------------------------------------------------------------------------------";
}

void list_pas(plane* pas, int n)
{
	int i = 0;
	plane* tpas;
	char  buff[80]; // ����� ��� ���������� (��������) �����
	// ������ ������ �������
	cout << "�" << '\t' << '\t' << "���" << '\t' << '\t' << "��������" << '\t' << '\t' << "����" << '\t' << '\t' << "   ����� �����" << '\t' << '\t' << "���������" << endl;
	for (tpas = pas; tpas < pas + n; tpas++)
	{
		strcpy(buff, "");	//------------------------------ �������� ��� � ���� ������
		strcat(buff, tpas->fio1.surname); strcat(buff, " ");
		strcat(buff, tpas->fio1.name); strcat(buff, " ");
		strcat(buff, tpas->fio1.middlename); //----------------------------
	  /*����� �� ����� �� ���� ������ ���, ����������� � ����������������� ����� �� ����� ��������� 25 ������, ��� �� �������� ����� �� ������� ������� �������*/
		fprintf(stdout, "\n%d %-30s %-17s %d %10s %5d %12d %18d\n", i, buff, tpas->company, tpas->date1.day, tpas->date1.month, tpas->date1.year, tpas->flight, tpas->cost);
		i++;
	}
};

void compare_date(plane* pas, int n)
{
	plane* tpas;
	int d1, d2, y1, y2, m_1, m_2, m_3, x=0, i=0;
	char m1[20], m2[20];
	cout << "������� ������ ����\n";
	do
	{
		cout << "\n����: ";
		cin >> d1;

		if (d1 <= 0 || d1 > 31)
			cout << "\n---------������! ����������� ����---------- ";
		else
			x = 1;

	} while (x != 1);

	x = 0;
	
	do
	{
		cout << "\n�����: ";
		fscanf(stdin, "%s", m1);

		if (strcmp(m1, "december") == 0 || strcmp(m1, "january") == 0 || strcmp(m1, "february") == 0 || strcmp(m1, "march") == 0
			|| strcmp(m1, "april") == 0 || strcmp(m1, "may") == 0 || strcmp(m1, "june") == 0 || strcmp(m1, "july") == 0
			|| strcmp(m1, "august") == 0 || strcmp(m1, "october") == 0 || strcmp(m1, "september") == 0 || strcmp(m1, "november") == 0)
		{
			x = 1;
		}
		else
		{
			cout << "\n---------������! ����������� ����---------- ";
		}

	} while (x != 1);

	x = 0;

	do
	{
		cout << "\n���: ";
		cin >> y1;


		if (y1 < 2021 || y1 > 2030)
			cout << "\n---------������! ����������� ����---------- ";
		else
			x = 1;

	} while (x != 1);

	cout << "������� ������ ����\n";
	x = 0;
	do
	{
		cout << "\n����: ";
		cin >> d2;

		if (d2 <= 0 || d2 > 31)
			cout << "\n---------������! ����������� ����---------- ";
		else
			x = 1;

	} while (x != 1);

	x = 0;

	do
	{
		cout << "\n�����: ";
		fscanf(stdin, "%s", m2);

		if (strcmp(m2, "december") == 0 || strcmp(m2, "january") == 0 || strcmp(m2, "february") == 0 || strcmp(m2, "march") == 0
			|| strcmp(m2, "april") == 0 || strcmp(m2, "may") == 0 || strcmp(m2, "june") == 0 || strcmp(m2, "july") == 0
			|| strcmp(m2, "august") == 0 || strcmp(m2, "october") == 0 || strcmp(m2, "september") == 0 || strcmp(m2, "november") == 0)
		{
			x = 1;
		}
		else
		{
			cout << "\n---------������! ����������� ����---------- ";
		}

	} while (x != 1);

	x = 0;

	do
	{
		cout << "\n���: ";
		cin >> y2;


		if (y2 < 2021 || y2 > 2030)
			cout << "\n---------������! ����������� ����---------- ";
		else
			x = 1;

	} while (x != 1);

	
	if (strcmp(m1, "january") == 0) m_1 = 1; if (strcmp(m1, "february") == 0) m_1 = 2; if (strcmp(m1, "march") == 0) m_1 = 3;
	if (strcmp(m1, "april") == 0) m_1 = 4; if (strcmp(m1, "may") == 0) m_1 = 5; if (strcmp(m1, "june") == 0) m_1 = 6;
	if (strcmp(m1, "july") == 0) m_1 = 7; if (strcmp(m1, "august") == 0) m_1 = 8; if (strcmp(m1, "october") == 0) m_1 = 9;
	if (strcmp(m1, "september") == 0) m_1 = 10; if (strcmp(m1, "november") == 0) m_1 = 11; if (strcmp(m1, "december") == 0) m_1 = 12;

	if (strcmp(m2, "january") == 0) m_2 = 1; if (strcmp(m2, "february") == 0) m_2 = 2; if (strcmp(m2, "march") == 0) m_2 = 3;
	if (strcmp(m2, "april") == 0) m_2 = 4; if (strcmp(m2, "may") == 0) m_2 = 5; if (strcmp(m2, "june") == 0) m_2 = 6;
	if (strcmp(m2, "july") == 0) m_2 = 7; if (strcmp(m2, "august") == 0) m_2 = 8; if (strcmp(m2, "october") == 0) m_2 = 9;
	if (strcmp(m2, "september") == 0) m_2 = 10; if (strcmp(m2, "november") == 0) m_2 = 11; if (strcmp(m2, "december") == 0) m_2 = 12;



	for (tpas = pas; tpas < pas + n; tpas++)
	{
		if (strcmp(tpas->date1.month, "january") == 0) m_3 = 1; if (strcmp(tpas->date1.month, "february") == 0) m_3 = 2; if (strcmp(tpas->date1.month, "march") == 0) m_3 = 3;
		if (strcmp(tpas->date1.month, "april") == 0) m_3 = 4; if (strcmp(tpas->date1.month, "may") == 0) m_3 = 5; if (strcmp(tpas->date1.month, "june") == 0) m_3 = 6;
		if (strcmp(tpas->date1.month, "july") == 0) m_3 = 7; if (strcmp(tpas->date1.month, "august") == 0) m_3 = 8; if (strcmp(tpas->date1.month, "october") == 0) m_3 = 9;
		if (strcmp(tpas->date1.month, "september") == 0) m_3 = 10; if (strcmp(tpas->date1.month, "november") == 0) m_3 = 11; if (strcmp(tpas->date1.month, "december") == 0) m_3 = 12;

		if ((y1 * 365 + m_1 * 31 + d1) <= (tpas->date1.year * 365 + m_3 * 31 + tpas->date1.day) && (y2 * 365 + m_2 * 31 + d2) >= (tpas->date1.year * 365 + m_3 * 31 + tpas->date1.day))
		{
			print_passenger(pas,i);
		}
		i++;
	}
	

}
