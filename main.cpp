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

//判断输入日期是否正确        // https://blog.csdn.net/wcc15256945095/article/details/123852026
bool check_date(int year, int month, int day)
{
    int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (year < 1900)
    {
        cout << "年份输入错误" << endl;
        return false;
    }

    if (month < 1 || month > 12)
    {
        cout << "月份输入错误" << endl;
        return false;
    }

    if (month == 2)
    {
        // 判断如果是闰年,则修改二月的monthDays[1]值为29
        if ((year % 400 == 0) || \
            (year % 100 != 0 && year % 4 == 0)
            )
        {
            monthDays[1] = 29;
        }
    }

    if (day < 1 || day > monthDays[month - 1])
    {
        cout << "日期输入错误" << endl;
        return false;
    }

    return true;
}

//函数：获取亲友信息
void getpersoninfo(vector<Person>& Persons)
{
    string name;
    string rel;

    cout << "请输入姓名：";
    cin >> name;
    cout << "请输入您与该亲友的关系：";
    cin >> rel;
    cout << "请输入该亲友的出生年月（年 月 日，以空格分隔）：";
    
    while (1)
    {
        int year;
        int mon;
        int day;
        cin >> year >> mon >> day;
        if (check_date(year, mon, day))
        {
            Persons.push_back(Person(name, rel, year, mon, day));
            break;
        }
        system("pause");
        cout << "请输入该亲友的出生年月（年 月 日，以空格分隔）：";
        }

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
    system("cls");
}

//函数：查询亲友信息
void main_2(vector<Person>& P)
{
    print_Person(P);
    system("pause");
}

//查询亲友信息在数组中的位置
int get_person_index(vector<Person>& P, string name, vector<int>& arr_i)
{
    int n = P.size();
    for (int j = 0; j < n; j++)
    {
        if (P[j].name == name)
        {
            arr_i.push_back(j);
        }
    }
    return arr_i.size();
}

struct birthday_plan
{
    Person* person;
    int birthday_plan_year;
    int birthday_plan_mon;
    int birthday_plan_day;
    int distance_day;
    int advance_day;
    birthday_plan() {};
    birthday_plan(Person& person, int birthday_plan_year, int birthday_plan_mon, int birthday_plan_day, int distance_day, int advance_day) :
        person(&person), birthday_plan_year(birthday_plan_year), birthday_plan_mon(birthday_plan_mon),
        birthday_plan_day(birthday_plan_day), distance_day(distance_day), advance_day(advance_day) {};
};

void main_4(vector<birthday_plan>& Plans)
{
    system("cls");
    int n = Plans.size();
    if (!n)
    {
        cout << "无已制定的计划" << endl;
        return;
    }
    cout << "已制定的所有计划如下:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "姓名：" << Plans[i].person->name << "\t关系：" << Plans[i].person->relation << "\n距离下次生日的天数" << Plans[i].distance_day
            << "\n预计准备生日聚会的日期：\n" << Plans[i].birthday_plan_year << "年 " << Plans[i].birthday_plan_mon << "月 "
            << Plans[i].birthday_plan_day << "日\n";
    }
}

void main_3(vector<Person>& P, vector<birthday_plan>& Plans)
{
    cout << "是否查看亲友信息（是：1，否：0）" << endl;
    int j;
    cin >> j;
    if (j)
        main_2(P);
    string name;
  Loop:
    cout << "请输入想要制定计划的亲友名字：" << endl;
    cin >> name;
    int i;
    vector<int>arr_i;
    switch (get_person_index(P, name, arr_i))
    {
    case 0:        
        cout << "未查询到该亲友" << endl;
        system("cls");
        goto Loop;
        return;
        break;
    case 1://有且仅有一个满足
        i = arr_i.front();
        break;
    default://重名
        cout << "出现以下重名：\n";
        int arr_i_n = arr_i.size();
        for (int j = 0; j < arr_i_n; j++)
        {
            cout << j << "：姓名：" << P[arr_i[j]].name << "\t关系：" << P[arr_i[j]].relation
                << "\t出生年月：" << P[arr_i[j]].birth_year << "年" << P[arr_i[j]].birth_mon
                << "月" << P[arr_i[j]].birth_day << "日\n";
        }
        cout << "请输入想查询的对应亲属姓名前的序号" << endl;
        int j;
        while (1)
        {
            cin >> j;
            if (0 <= j < arr_i_n)
            {
                i = arr_i[j];
                break;
            }
            cout << "输入错误,请重新输入" << endl;
        }
    }

    tm today;
    time_t today_t;
    int today_year, today_mon, today_day; 
    cout << "请输入今天的日期（年 月 日，以空格分隔）：";
    cin >> today_year >> today_mon >> today_day; 
    time_t nextBirthday_t;
    tm nextBirthday;
    int daysToNextBirthday;
    do
    {
        if (check_date(today_year, today_mon, today_day))
        {
            //判断输入日期是否合法
            data_to_time_t(today, today_t, today_year, today_mon, today_day);
            //判断输入的今天日期是否小于生日
            if (today_t > P[i].birthday_t)
            {
                nextBirthday = GetNextBirthday(today, P[i].birthday, nextBirthday_t);
                daysToNextBirthday = GetDaysToNextBirthday(today_t, nextBirthday_t);
                break;
            }
            else
            {
                cout << "输入的今天日期晚于该亲友生日" << endl;
            }
        }
        cout << "请重新输入今天的日期（年 月 日，以空格分隔）：";
        cin >> today_year >> today_mon >> today_day;
    } while (true);

    cout << "今天距离下次生日还有 " << daysToNextBirthday << " 天。\n";
    cout << "请确定您希望提前多少天做聚会计划：";
    int n;
    while (true)
    {
        cin >> n;
        if (n >= 0) {
            break;
        }
        else
        {
            cout << "输入错误，请重新输入n:" << endl;
        }
    }

    tm planDate = GetPlanDate(nextBirthday_t, n);
    if (IsWeekday(planDate)) {
        tm nearestSaturday = GetNearestSaturday(planDate);
        std::cout << "下次生日前 " << n << " 天是工作日，计划日期将改为 " << nearestSaturday.tm_year + 1900 << " 年 " << nearestSaturday.tm_mon + 1 << " 月 " << nearestSaturday.tm_mday << " 日（周六）。\n";
        planDate = nearestSaturday;
    }
    else {
        std::cout << "下次生日前 " << n << " 天是 " << planDate.tm_year + 1900 << " 年 "
            << planDate.tm_mon + 1 << " 月 " << planDate.tm_mday << "日（休息日）\n";
    }
    birthday_plan this_plan(P[i], planDate.tm_year + 1900, planDate.tm_mon + 1, planDate.tm_mday, daysToNextBirthday, n);

    cout << "是否重新为该亲友生成计划（是：1，否：0）" << endl;
    int i_1;
    cin >> i_1;
    if (i_1)
    {
        goto Loop;
    }

    Plans.push_back(this_plan);

    cout << "是否继续生成下一个亲友的生日计划（是：1，否：0）" << endl;
    int k;
    cin >> k;
    if (k)
    {
        goto Loop;
    }
    system("pause");
}


int main()
{
    vector<Person>Persons;
    vector<birthday_plan>Plans;
    while (1)
    {
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
            main_3(Persons, Plans);
        case 4:
            main_4(Plans);
            return 0;
        default:
            break;
        }
    }

}
