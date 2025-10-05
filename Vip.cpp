#include "vip.h"

void vip::show() {
	cout << "purchased item: \n\n";
	for (const auto& i : keep) {
		int c = 0;
		for (const auto& j : id_info[i.first]) {
			c++;
			if (c == 2) {
				cout << "$";
				cout << setw(5) << left;
			}
			else if (c == 1) {
				cout << setw(25) << left;
			}
			if (c == 3) {
				cout << 100 - stoi(j) << "%off ";
				continue;
			}
			cout << j << " ";
		}
		cout << "x" << i.second << endl;
	}
	cout << endl;
}

int vip::pay() {
	string str;
	cout << "use point? (" << member[mem_id] << " left): ";
	for (; cin >> str;) {
		if (str == "yes") {
			if (sum < member[mem_id]) {
				member[mem_id] -= sum;
				showReceipt(0, sum);
				sum = 0;
				keep.clear();
				return 0;
			}
			sum -= member[mem_id];
			member[mem_id] = 0;
			break;
		}
		else if (str == "no") {
			break;
		}
		else {
			cout << "invalid entry\n:";
		}
	}
	reset();
	show();
	cost2();
	cout << "\npay: $";
	int s = 0;
	for (; cin >> s;) {

		if (s < sum) {
			reset();
			show();
			cost2();
			cout << "you are " << sum - s << " dollar shy: ";
		}
		else
			break;
	}

	member[mem_id] += (sum / 100);

	showReceipt(s - sum, s);
	return 0;
}

void vip::cost2() const {
	cout << "Total cost(with vip discount and vip points): $" << sum << "\n\n";
}

void vip::cost() {
	sum = 0;
	for (const auto& i : keep) {
		sum += (stoi(id_info[i.first][1]) * i.second * stoi(id_info[i.first][2])) / 100;
	}
	cout << "Total cost(with vip discount): $" << sum << "\n\n";
}

void vip::member_in(string& i) {
    member[i] = 100;
}

int vip::member_set(string& i) {
    if (member.find(i) == member.end()) {
        cout << "Member doesnt exist, please try again: ";
        return 1;
    }
    mem_id = i;
    return 0;
}

void vip::showReceipt(int x, int y) {
	reset();
	cout << "----------------------------------------\n";
	cout << "\n      Receipt\n\n";
	show();
	cost2();
	cout << "Paid: $" << y << "\nReturn: $" << x << "\nRemain Points: " << member[mem_id] << "\n\n";
	cout << "Serving cashier: " << caID << "\n\n";
	cout << "----------------------------------------\n";
	keep.clear();
}