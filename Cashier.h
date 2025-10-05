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

            cout << "員工 " << employeeId + 1 << " 上班時間: " << buffer << "\n\n";
        }
        else {
            cout << "員工 " << employeeId + 1 << " 已經打卡，請勿重複打卡" << endl;
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

            cout << "員工 " << employeeId + 1 << " 下班時間: " << buffer << endl;


            time_t punchInTime = punches[employeeId][0];
            time_t punchOutTime = punches[employeeId][1];

            double durationInSeconds = difftime(punchOutTime, punchInTime);
            int hours = static_cast<int>(durationInSeconds / 3600);
            int minutes = static_cast<int>((durationInSeconds - hours * 3600) / 60);
            int seconds = static_cast<int>(durationInSeconds - hours * 3600 - minutes * 60);

            cout << "今日工時: " << hours << " 小時 " << minutes << " 分 " << seconds << " 秒" << endl;

            cout << "返回主頁面\n\n";
        }
        else {
            cout << "員工 " << employeeId+1 << " 尚未打卡 " << endl;
        }
    }

    void displayAllPunches() {
        if (punches.empty()) {
            cout << "無打卡紀錄\n\n";
            return;
        }

        cout << "所有打卡紀錄:" << endl;
        for (const auto& entry : punches) {
            int employeeId = entry.first;
            const vector<time_t>& punchTimes = entry.second;

            cout << "員工 " << employeeId+1 << " 打卡時間: " << endl;
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