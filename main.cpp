#include <iostream>
#include <ctime>
#include<string>
#include<vector>
using namespace std;
#pragma warning(disable:4996);

void data_to_time_t(tm& data, time_t& t, int year, int mon, int day);

//亲友类    wjc
class Person
{
public:
    string name;
    string relation;
    int birth_year;
    int birth_mon;
    int birth_day;
    tm birthday;
    time_t birthday_t;
    Person() {};
    Person(string name, string relation, int year, int mon, int day) :name(name), relation(relation), birth_year(year),
        birth_mon(mon), birth_day(day)
    {
        data_to_time_t(birthday, birthday_t, year, mon, day);
    }
};

//函数：将tm类转换为time_t类型    wjc
void data_to_time_t(tm& data, time_t& t, int year, int mon, int day)
{
    data.tm_sec = 0;
    data.tm_min = 0;
    data.tm_hour = 12;
    data.tm_mday = day;
    data.tm_mon = mon - 1;
    data.tm_year = year - 1900;
    data.tm_isdst = 0;
    t = mktime(&data);
    data = *gmtime(&t);
    data.tm_sec = 0;
    data.tm_min = 0;
    data.tm_hour = 12;
    return;
}

//函数：获取亲友信息
void getpersoninfo(vector<Person>& Persons)
{
    string name;
    string rel;
    int year;
    int mon;
    int day;
    cout << "请输入姓名：";
    cin >> name;
    cout << "请输入您与该亲友的关系：";
    cin >> rel;
    cout << "请输入该亲友的出生年月（年 月 日，以空格分隔）：";
    cin >> year >> mon >> day;
    Persons.push_back(Person(name, rel, year, mon, day));
}

// 函数：获取下一个生日日期     wjc
tm GetNextBirthday(const tm& today, const tm& birthday, time_t& nextBrithday_t) {
    tm nextBirthday;
    int nextBirthday_year = today.tm_year;

    if (today.tm_mon > birthday.tm_mon || (today.tm_mon == birthday.tm_mon && today.tm_mday > birthday.tm_mday)) {
        nextBirthday_year += 1;
    };

    data_to_time_t(nextBirthday, nextBrithday_t, nextBirthday_year + 1900, birthday.tm_mon + 1, birthday.tm_mday);

    std::cout << "下次生日" << nextBirthday.tm_year + 1900 << " 年 " << nextBirthday.tm_mon + 1 << " 月 " << nextBirthday.tm_mday << " 日\n";
    return nextBirthday;
}

// 函数：获取下次生日距离今天的天数     wjc
int GetDaysToNextBirthday(time_t& today_t, time_t& nextBirthday_t)
{
    double d = difftime(nextBirthday_t, today_t);
    return (int)(d / (60 * 60 * 24));
}



// 函数：获取下次生日前n天的日期      wdy
tm GetPlanDate(const time_t& nextBirthday_t, int n) {
    tm planDate;
    time_t planDate_t = nextBirthday_t - (n * 24 * 60 * 60);
    planDate = *gmtime(&planDate_t);
    data_to_time_t(planDate, planDate_t, planDate.tm_year + 1900, planDate.tm_mon + 1, planDate.tm_mday);
    return planDate;
}

// 函数：判断日期是否为工作日        wdy
bool IsWeekday(const tm& date) {
    int mon = date.tm_mon;
    int day = date.tm_mday;
    if ((mon == 4 && (day <= 3)) || (mon == 9 || (day <= 7)))//判断是否为五月1至3或十月1至7日
    {
        return false;
    }
    int dayOfWeek = date.tm_wday;
    return (dayOfWeek > 0 && dayOfWeek < 6);
}

// 函数：获取最近的一个周六日期       wdy
tm GetNearestSaturday(tm& date) {
    tm nearestSaturday;
    time_t nearestSaturday_t;
    time_t date_t = mktime(&date);
    int nearestSat;
    switch (date.tm_wday) {
    case 1://周一
        nearestSat = 2;
        break;
    case 2://周二
        nearestSat = 3;
        break;
    case 3://周三
        nearestSat = -3;
        break;
    case 4://周四
        nearestSat = -2;
        break;
    case 5://周五
        nearestSat = -1;
        break;
    default://周末
        nearestSat = 0;
        break;
    }
    nearestSaturday_t = date_t - (nearestSat * 24 * 60 * 60);
    nearestSaturday = *gmtime(&nearestSaturday_t);
    return nearestSaturday;
}

void get_cele_date(Person& P, int n)
{

}

int main_1()
{
    int res = 1;
    cout << "欢迎使用生日聚会计划便签程序！\n";
    cout << "输入亲友生日请按0，生成计划请按1（默认为1）：";
    cin >> res;
    cin.ignore();
    return res;
}

void main_2(vector<Person>& Persons)
{
    int i = 1;
    while (i)
    {
        getpersoninfo(Persons);
        cout << "是否继续输入信息：\n（继续请输入1，停止请输入0）：";
        cin >> i;
    }

}

int main()
{
    time_t nextBirthday_t;
    int t;
    string s;
    vector<Person>Persons;
    vector<Person>Persons_1;
    int s_1 = main_1();
    tm k[100];
    if (!s_1)
        main_2(Persons);
    for (size_t i = 0; i < Persons.size(); ++i) {
        cout << "姓名：" << Persons[i].name << endl;
        cout << "关系：" << Persons[i].relation << endl;
    }
    cout << "是否要继续生成计划: \n（继续请输入1，停止请输入0）" << endl;
    cin >> t;
    if (t)
    {
    loop1:
        cout << "请输入生成计划的亲友名字" << endl;
        cin >> s;
        for (size_t i = 0; i < Persons.size(); i++)
        {
            if (Persons[i].name == s)
            {

                tm birthday, today;
                time_t birthday_t, today_t;
                int birthday_year, birthday_mon, birthday_day;
                //birthday_year = Persons[i].birth_year;
                //birthday_mon = Persons[i].birth_mon;
                //birthday_day = Persons[i].birth_day;
                birthday = Persons[i].birthday;
                std::cout << "请输入今天的日期（年 月 日，以空格分隔）：";
                int today_year, today_mon, today_day;
                std::cin >> today_year >> today_mon >> today_day;
                data_to_time_t(today, today_t, today_year, today_mon, today_day);
                tm nextBirthday = GetNextBirthday(today, birthday, nextBirthday_t);
                int daysToNextBirthday = GetDaysToNextBirthday(today_t, nextBirthday_t);
                std::cout << "今天距离下次生日还有 " << daysToNextBirthday << " 天。\n";
            loop:
                std::cout << "请确定您希望提前多少天做聚会计划：";
                int n;
                std::cin >> n;

                tm planDate = GetPlanDate(nextBirthday_t, n);
                if (IsWeekday(planDate)) {
                    tm nearestSaturday = GetNearestSaturday(planDate);
                    std::cout << "下次生日前 " << n << " 天是工作日，计划日期将改为 " << nearestSaturday.tm_year + 1900 << " 年 " 
                        << nearestSaturday.tm_mon + 1 << " 月 " << nearestSaturday.tm_mday << " 日（休息日）。\n";
                    planDate = nearestSaturday;
                }
                else {
                    std::cout << "下次生日前 " << n << " 天是 " << planDate.tm_year + 1900 << " 年 " 
                        << planDate.tm_mon + 1 << " 月 " << planDate.tm_mday << " 日（" << (planDate.tm_wday == 0 ? "周日" : "休息日") << "）。\n";

                }
                // 5. 结果显示界面        wdy
                std::cout << "生日聚会计划的制定日期信息：\n";
                std::cout << "亲友姓名：" << Persons[i].name << " " << "关系：" << Persons[i].relation << endl;
                std::cout << "亲友生日：" << Persons[i].birth_year << "年" << Persons[i].birth_mon << "月" << Persons[i].birth_day << "日" << endl;
                std::cout << "下次生日日期：" << nextBirthday.tm_year + 1900 << "年" << nextBirthday.tm_mon + 1 << "月" << nextBirthday.tm_mday << "日\n";
                std::cout << "下次生日距离今天的天数：" << daysToNextBirthday << "天\n";
                std::cout << "距离下次生日前" << n << "天的日期：" << planDate.tm_year + 1900 << "年" << planDate.tm_mon + 1 << "月" << planDate.tm_mday << "日\n";
                std::cout << "预计准备制定生日计划的日期：" << planDate.tm_year + 1900 << "年" << planDate.tm_mon + 1 << "月" << planDate.tm_mday << "日\n";
                std::cout << "重新制定计划1，为其他亲友制定计划2，退出3：";
                k[i] = planDate;
                int choice;
                std::cin >> choice;

                if (choice == 1) {
                    // 返回到步骤4，重新制定计划日期
                    std::cout << "\n";
                    goto loop;
                }
                Persons_1.push_back(Persons[i]);
                if (choice == 2) {
                    // 返回到步骤4，重新制定计划日期
                    std::cout << "\n";
                    goto loop1;
                }


            }
        }
    }

    // 6. 结束界面
    std::cout << "生日计划已制定的亲友：" << endl;
    for (int i = 0; i < Persons_1.size(); i++) {
        cout << "姓名：" << Persons_1[i].name << endl;
        cout << "关系：" << Persons_1[i].relation << endl;
        cout << "生日：" << Persons_1[i].birth_year << "年" << Persons_1[i].birth_mon << "月" << Persons_1[i].birth_day << "日" << endl;
        cout << "预计时间" << k[i].tm_year + 1900 << "年" << k[i].tm_mon + 1 << "月" << k[i].tm_mday << "日\n";
    }
    std::cout << "按任意键结束程序。\n";
    std::cin.ignore();
    std::cin.get();


}

