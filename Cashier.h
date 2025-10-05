#ifndef cashier_h
#define cashier_h

#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

class PunchCardSystem {
public:
    bool isEmployeeOnShift(int employeeId) {
        return punches.find(employeeId) != punches.end() && punches[employeeId].size() % 2 == 1;
    }

    void punchIn(int employeeId) {
        if (!isEmployeeOnShift(employeeId)) {
            time_t timestamp = time(nullptr);
            punches[employeeId].push_back(timestamp);

            struct tm localTime;
            localtime_s(&localTime, &timestamp);

            char buffer[80];
            strftime(buffer, sizeof(buffer), "%c", &localTime);

            cout << "���u " << employeeId + 1 << " �W�Z�ɶ�: " << buffer << "\n\n";
        }
        else {
            cout << "���u " << employeeId + 1 << " �w�g���d�A�Фŭ��ƥ��d" << endl;
        }
    }

    void punchOut(int employeeId) {
        if (isEmployeeOnShift(employeeId)) {
            time_t timestamp = time(nullptr);
            punches[employeeId].push_back(timestamp);

            struct tm localTime;
            localtime_s(&localTime, &timestamp);

            char buffer[80];
            strftime(buffer, sizeof(buffer), "%c", &localTime);

            cout << "���u " << employeeId + 1 << " �U�Z�ɶ�: " << buffer << endl;


            time_t punchInTime = punches[employeeId][0];
            time_t punchOutTime = punches[employeeId][1];

            double durationInSeconds = difftime(punchOutTime, punchInTime);
            int hours = static_cast<int>(durationInSeconds / 3600);
            int minutes = static_cast<int>((durationInSeconds - hours * 3600) / 60);
            int seconds = static_cast<int>(durationInSeconds - hours * 3600 - minutes * 60);

            cout << "����u��: " << hours << " �p�� " << minutes << " �� " << seconds << " ��" << endl;

            cout << "��^�D����\n\n";
        }
        else {
            cout << "���u " << employeeId+1 << " �|�����d " << endl;
        }
    }

    void displayAllPunches() {
        if (punches.empty()) {
            cout << "�L���d����\n\n";
            return;
        }

        cout << "�Ҧ����d����:" << endl;
        for (const auto& entry : punches) {
            int employeeId = entry.first;
            const vector<time_t>& punchTimes = entry.second;

            cout << "���u " << employeeId+1 << " ���d�ɶ�: " << endl;
            for (const auto& punch : punchTimes) {
                struct tm localTime;
                localtime_s(&localTime, &punch);

                char buffer[80];
                strftime(buffer, sizeof(buffer), "%c", &localTime);
                cout << buffer << endl;
            }
            cout << "\n";
        }
    }
private:
    map<int, vector<time_t>> punches;

};
#endif