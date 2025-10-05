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
	const int employeeId[3] = {1115520, 1115521, 1115532};  // 三個員工 ID 
	const string employeeName[3] = {"Toothless", "Rick Astley", "Hitler"}; // 員工名字
	int hasPunchedIn = -1;  // 標記是誰在上班

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
			cout << "員工 : " << employeeName[hasPunchedIn] << "\n\n";
		cout << "1. " << (hasPunchedIn != -1 ? "下班" : "輸入員工識別碼開始上班") << endl;
		cout << "2. 開始結帳" << endl;
		cout << "3. 顯示所有打卡紀錄" << endl;
		cout << "4. 離開" << endl;

		int choice;
		cout << "\n請輸入選項(1/2/3/4) : ";

		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			a.reset();
			cout << "\n非法輸入，請輸入選項(1/2/3/4)";
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
				cout << "請輸入員工識別碼開始上班\n\n";
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
				cout << "\n按任意按鍵繼續~~";
				cin >> go;
				a.reset();
			}
			else {
				a.reset();
				cout << "\n你還沒上班!\n\n";
			}
			break;
		case 3:
			a.reset();
			punchCardSystem.displayAllPunches();
			break;
		case 4:
			if (hasPunchedIn == -1) {
				a.reset();
				cout << "正在離開打卡系統......" << endl;
				return 0;
			}
			else {
				a.reset();
				cout << "你還在上班!\n\n";
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
				cout << "\n不存在的選項，請輸入選項(1/2/3/4)\n\n";
			}
		}
				
	}
}