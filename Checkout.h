#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

class checkout {
public:
    checkout();
    void info(string& s, string& ss);
    void code();
    int scan();
    void reset();
    virtual void show();
    virtual void cost();
    virtual int pay();
    void showReceipt(int x, int y);
    void set_caID(string d);

protected:
    map<string, vector<string>> id_info;
    map<string, int> keep;
    int sum = 0;
    string caID;
};

#endif
