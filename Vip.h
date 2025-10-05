#ifndef VIP_H
#define VIP_H

#include "checkout.h"

class vip : public checkout {
public:
    void show() override;
    int pay() override;
    void cost2() const;
    void cost() override;
    void member_in(string& i);
    int member_set(string& i);
    void showReceipt(int x, int y);

private:
    map<string, int> member;
    string mem_id = "notExist";
};

#endif