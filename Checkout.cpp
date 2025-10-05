#include "checkout.h"

ifstream file("bar.txt");

checkout::checkout() {}

void checkout::info(string& s, string& ss) {
    id_info[s].push_back(ss);
}

void checkout::code() {
    reset();
    cout << "code: ";
    for (const auto& i : id_info) {
        cout << i.first << " ";
    }
    cout << "\n\n";
}

int checkout::scan() {
    string ss;
    cout << "scan: ";
    cin >> ss;
    if (ss == "pay") {
        cout << endl;
        reset();
        show();
        cost();
        pay();
        return 0;
    }
    else if (id_info.find(ss) == id_info.end()) {
        reset();
        show();
        cost();
        cout << "Code doesnt exist!\n\n";
        return 1;
    }
    keep[ss]++;
    reset();
    show();
    cost();
    return 1;
}

void checkout::reset() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void checkout::show() {
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
                continue;
            }
            cout << j << " ";
        }
        cout << "\b x" << i.second << endl;
    }
    cout << endl;
}

void checkout::cost() {
    sum = 0;
    for (const auto& i : keep) {
        sum += stoi(id_info[i.first][1]) * i.second;
    }
    cout << "total cost: $" << sum << "\n\n";
}

int checkout::pay() {
    reset();
    show();
    cost();
    cout << "pay: $";
    int s;
    for (; cin >> s;) {

        if (s < sum) {
            reset();
            show();
            cost();
            cout << "you are " << sum - s << " dollar shy: ";
        }
        else
            break;
    }
    showReceipt(s - sum, s);
    return 0;
}

void checkout::showReceipt(int x, int y) {
    reset();
    cout << "----------------------------------------\n";
    cout << "\n      Receipt\n\n";
    show();
    cost();
    cout << "Paid: $" << y << "\nReturn: $" << x << "\n\n";
    cout << "Serving cashier: " << caID << "\n\n";
    cout << "----------------------------------------\n";
    keep.clear();
}

void checkout::set_caID(string d) {
    caID = d;
}