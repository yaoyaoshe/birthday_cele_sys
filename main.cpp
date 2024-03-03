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

//函数：获取庆祝日期
void get_cele_date(Person& P, int n)
{
    
}

//函数：打印亲友信息
void print_Person(vector<Person>& P)
{
    int n = P.size();
    for (int i = 0; i < n; i++)
    {
        cout << "姓名：" << P[i].name << "\t关系：" << P[i].relation
            << "\t出生年月：" << P[i].birth_year << "年" << P[i].birth_mon
            << "月" << P[i].birth_day << "日\n";
    }
}

//函数：录入亲友信息
void main_1(vector<Person>& Persons)
{
    system("cls");
    int i = 0;
    do
    {
        getpersoninfo(Persons);
        cout << "是否继续录入其他亲友信息？\n";
        cout << "(是请输入1，不是请输入0)\n";
        cin >> i;
    } while (i);
}

//函数：查询亲友信息
void main_2(vector<Person>& P)
{
    print_Person(P);
    system("pause");
}

void main_3(vector<Person>& P)
{

}

int main()
{
    vector<Person>Persons;
    while (1)
    {
        system("cls");
        cout << "欢迎使用生日聚会计划便签程序！\n";
        cout << "输入亲友信息请按1\n";
        cout << "查看亲友信息请按2\n";
        cout << "生成生日聚会计划请按3\n";
        cout << "退出系统请按4\n";
        int i;
        cin >> i;

        switch (i)
        {
        case 1:
            main_1(Persons);
            break;
        case 2:
            main_2(Persons);
            break;
        case 3:
        case 4:return 0;
        default:
            break;
        }
    }

}

/*
int main() {
    // 1. 欢迎界面     wdy
    std::cout << "欢迎使用生日聚会计划便签程序！请按任意键继续。\n";
    std::cin.ignore();

    // 2. 输入出生日期和今天的日期      wjc
    tm birthday, today;
    time_t birthday_t, today_t;

    std::cout << "请输入您的出生日期（年 月 日，以空格分隔）：";
    int birth_year, birth_mon, birth_day;
    std::cin >> birth_year >> birth_mon >> birth_day;
    data_to_time_t(birthday, birthday_t, birth_year, birth_mon, birth_day);

    std::cout << "请输入今天的日期（年 月 日，以空格分隔）：";
    int today_year, today_mon, today_day;
    std::cin >> today_year >> today_mon >> today_day;
    data_to_time_t(today, today_t, today_year, today_mon, today_day);


    // 3. 计算下次生日和距离今天的天数    wjc
    time_t nextBirthday_t;
    tm nextBirthday = GetNextBirthday(today, birthday, nextBirthday_t);
    int daysToNextBirthday = GetDaysToNextBirthday(today_t, nextBirthday_t);

    // 4. 生日聚会计划制定日期        wdy
    std::cout << "今天距离下次生日还有 " << daysToNextBirthday << " 天。\n";
    std::cout << "请确定您希望提前多少天做聚会计划：";
    int n;
    std::cin >> n;

    tm planDate = GetPlanDate(nextBirthday_t, n);
    if (IsWeekday(planDate)) {
        tm nearestSaturday = GetNearestSaturday(planDate);
        std::cout << "下次生日前 " << n << " 天是工作日，计划日期将改为 " << nearestSaturday.tm_year + 1900 << " 年 " << nearestSaturday.tm_mon + 1 << " 月 " << nearestSaturday.tm_mday << " 日（周六）。\n";
        planDate = nearestSaturday;
    }
    else {
        std::cout << "下次生日前 " << n << " 天是 " << planDate.tm_year + 1900 << " 年 " << planDate.tm_mon + 1 << " 月 " << planDate.tm_mday << " 日（" << (planDate.tm_wday == 0 ? "周日" : "周六") << "）。\n";
    }

    // 5. 结果显示界面        wdy
    std::cout << "生日聚会计划的制定日期信息：\n";
    std::cout << "下次生日日期：" << nextBirthday.tm_year + 1900 << "年" << nextBirthday.tm_mon + 1 << "月" << nextBirthday.tm_mday << "日\n";
    std::cout << "下次生日距离今天的天数：" << daysToNextBirthday << "天\n";
    std::cout << "距离下次生日前" << n << "天的日期：" << planDate.tm_year + 1900 << "年" << planDate.tm_mon + 1 << "月" << planDate.tm_mday << "日\n";
    std::cout << "预计准备制定生日计划的日期：" << planDate.tm_year + 1900 << "年" << planDate.tm_mon + 1 << "月" << planDate.tm_mday << "日\n";

    std::cout << "是否需要重新确定计划日期？（是/否）：";
    std::string choice;
    std::cin >> choice;

    if (choice == "是") {
        // 返回到步骤4，重新制定计划日期
        std::cout << "\n";
        main();
    }
    else {
        // 6. 结束界面
        std::cout << "生日计划已制定于：" << planDate.tm_year + 1900 << "年" << planDate.tm_mon + 1 << "月" << planDate.tm_mday << "日\n";
        std::cout << "按任意键结束程序。\n";
        std::cin.ignore();
        std::cin.get();
    }

    return 0;
}
*/
