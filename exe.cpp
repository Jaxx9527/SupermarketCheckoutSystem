#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>
#include "Cashier.h"
#include "Vip.h"

using namespace std;

int main() {
	PunchCardSystem punchCardSystem;
	const int employeeId[3] = {1115520, 1115521, 1115532};  // �T�ӭ��u ID 
	const string employeeName[3] = {"Toothless", "Rick Astley", "Hitler"}; // ���u�W�r
	int hasPunchedIn = -1;  // �аO�O�֦b�W�Z

	int info_q = 3;

	checkout a;
	vip v;

	string go;

	ifstream file("bar.txt");
	for (string s, ss; file >> s;) {
		for (int i = 0; i < info_q; i++) {
			file >> ss;
			a.info(s, ss);
			v.info(s, ss);
		}
	}
	file.close();

	ifstream filev("vip.txt");
	for (string i; filev >> i;) {
		v.member_in(i);
	}
	filev.close();

	a.reset();

	while (true) {
		if(hasPunchedIn != -1)
			cout << "���u : " << employeeName[hasPunchedIn] << "\n\n";
		cout << "1. " << (hasPunchedIn != -1 ? "�U�Z" : "��J���u�ѧO�X�}�l�W�Z") << endl;
		cout << "2. �}�l���b" << endl;
		cout << "3. ��ܩҦ����d����" << endl;
		cout << "4. ���}" << endl;

		int choice;
		cout << "\n�п�J�ﶵ(1/2/3/4) : ";

		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			a.reset();
			cout << "\n�D�k��J�A�п�J�ﶵ(1/2/3/4)";
		}

		switch (choice) {
		case 1:
			if (hasPunchedIn != -1) {
				a.reset();
				punchCardSystem.punchOut(hasPunchedIn);
				hasPunchedIn = -1;
				break;
			}
			else {
				a.reset();
				cout << "�п�J���u�ѧO�X�}�l�W�Z\n\n";
			}
			break;
		case 2:
			if (hasPunchedIn != -1) {
				a.reset();
				cout << "Membership? (Enter \"yes\" or \"no\") : ";
				for (string str; cin >> str;) {

					if (str == "yes") {
						a.reset();
						cout << "Enter member number: ";
						cin >> str;
						a.reset();
						for (; v.member_set(str); cin >> str);
						v.set_caID(employeeName[hasPunchedIn]);
						v.code();
						for (; v.scan(););
						break;
					}

					else if (str == "no") {
						a.set_caID(employeeName[hasPunchedIn]);
						a.code();
						for (; a.scan(););
						break;
					}
					else
						a.reset();
						cout << "Membership? (Enter \"yes\" or \"no\") : ";
						cout << "\nInvalid Entry!! \n\n";
				}
				cout << "\n�����N�����~��~~";
				cin >> go;
				a.reset();
			}
			else {
				a.reset();
				cout << "\n�A�٨S�W�Z!\n\n";
			}
			break;
		case 3:
			a.reset();
			punchCardSystem.displayAllPunches();
			break;
		case 4:
			if (hasPunchedIn == -1) {
				a.reset();
				cout << "���b���}���d�t��......" << endl;
				return 0;
			}
			else {
				a.reset();
				cout << "�A�٦b�W�Z!\n\n";
				break;
			}
		default:
			bool b = false;
			for (int i = 0; i < 3; i++) {
				if (employeeId[i] == choice && hasPunchedIn == -1) {
					a.reset();
					hasPunchedIn = i;
					punchCardSystem.punchIn(i);
					b = true;
					break;
				}
			}
			if (b == false) {
				a.reset();
				cout << "\n���s�b���ﶵ�A�п�J�ﶵ(1/2/3/4)\n\n";
			}
		}
				
	}
}