#include <iostream>
#include <ctime>
#include<string>
#include<vector>
using namespace std;
#pragma warning(disable:4996);

void data_to_time_t(tm& data, time_t& t, int year, int mon, int day);

//������    wjc
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

//��������tm��ת��Ϊtime_t����    wjc
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

//��������ȡ������Ϣ
void getpersoninfo(vector<Person>& Persons)
{
    string name;
    string rel;
    int year;
    int mon;
    int day;
    cout << "������������";
    cin >> name;
    cout << "��������������ѵĹ�ϵ��";
    cin >> rel;
    cout << "����������ѵĳ������£��� �� �գ��Կո�ָ�����";
    cin >> year >> mon >> day;
    Persons.push_back(Person(name, rel, year, mon, day));
}

// ��������ȡ��һ����������     wjc
tm GetNextBirthday(const tm& today, const tm& birthday, time_t& nextBrithday_t) {
    tm nextBirthday;
    int nextBirthday_year = today.tm_year;

    if (today.tm_mon > birthday.tm_mon || (today.tm_mon == birthday.tm_mon && today.tm_mday > birthday.tm_mday)) {
        nextBirthday_year += 1;
    };

    data_to_time_t(nextBirthday, nextBrithday_t, nextBirthday_year + 1900, birthday.tm_mon + 1, birthday.tm_mday);

    std::cout << "�´�����" << nextBirthday.tm_year + 1900 << " �� " << nextBirthday.tm_mon + 1 << " �� " << nextBirthday.tm_mday << " ��\n";
    return nextBirthday;
}

// ��������ȡ�´����վ�����������     wjc
int GetDaysToNextBirthday(time_t& today_t, time_t& nextBirthday_t)
{
    double d = difftime(nextBirthday_t, today_t);
    return (int)(d / (60 * 60 * 24));
}



// ��������ȡ�´�����ǰn�������      wdy
tm GetPlanDate(const time_t& nextBirthday_t, int n) {
    tm planDate;
    time_t planDate_t = nextBirthday_t - (n * 24 * 60 * 60);
    planDate = *gmtime(&planDate_t);
    data_to_time_t(planDate, planDate_t, planDate.tm_year + 1900, planDate.tm_mon + 1, planDate.tm_mday);
    return planDate;
}

// �������ж������Ƿ�Ϊ������        wdy
bool IsWeekday(const tm& date) {
    int mon = date.tm_mon;
    int day = date.tm_mday;
    if ((mon == 4 && (day <= 3)) || (mon == 9 || (day <= 7)))//�ж��Ƿ�Ϊ����1��3��ʮ��1��7��
    {
        return false;
    }
    int dayOfWeek = date.tm_wday;
    return (dayOfWeek > 0 && dayOfWeek < 6);
}

// ��������ȡ�����һ����������       wdy
tm GetNearestSaturday(tm& date) {
    tm nearestSaturday;
    time_t nearestSaturday_t;
    time_t date_t = mktime(&date);
    int nearestSat;
    switch (date.tm_wday) {
    case 1://��һ
        nearestSat = 2;
        break;
    case 2://�ܶ�
        nearestSat = 3;
        break;
    case 3://����
        nearestSat = -3;
        break;
    case 4://����
        nearestSat = -2;
        break;
    case 5://����
        nearestSat = -1;
        break;
    default://��ĩ
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
    cout << "��ӭʹ�����վۻ�ƻ���ǩ����\n";
    cout << "�������������밴0�����ɼƻ��밴1��Ĭ��Ϊ1����";
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
        cout << "�Ƿ����������Ϣ��\n������������1��ֹͣ������0����";
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
        cout << "������" << Persons[i].name << endl;
        cout << "��ϵ��" << Persons[i].relation << endl;
    }
    cout << "�Ƿ�Ҫ�������ɼƻ�: \n������������1��ֹͣ������0��" << endl;
    cin >> t;
    if (t)
    {
    loop1:
        cout << "���������ɼƻ�����������" << endl;
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
                std::cout << "�������������ڣ��� �� �գ��Կո�ָ�����";
                int today_year, today_mon, today_day;
                std::cin >> today_year >> today_mon >> today_day;
                data_to_time_t(today, today_t, today_year, today_mon, today_day);
                tm nextBirthday = GetNextBirthday(today, birthday, nextBirthday_t);
                int daysToNextBirthday = GetDaysToNextBirthday(today_t, nextBirthday_t);
                std::cout << "��������´����ջ��� " << daysToNextBirthday << " �졣\n";
            loop:
                std::cout << "��ȷ����ϣ����ǰ���������ۻ�ƻ���";
                int n;
                std::cin >> n;

                tm planDate = GetPlanDate(nextBirthday_t, n);
                if (IsWeekday(planDate)) {
                    tm nearestSaturday = GetNearestSaturday(planDate);
                    std::cout << "�´�����ǰ " << n << " ���ǹ����գ��ƻ����ڽ���Ϊ " << nearestSaturday.tm_year + 1900 << " �� " 
                        << nearestSaturday.tm_mon + 1 << " �� " << nearestSaturday.tm_mday << " �գ���Ϣ�գ���\n";
                    planDate = nearestSaturday;
                }
                else {
                    std::cout << "�´�����ǰ " << n << " ���� " << planDate.tm_year + 1900 << " �� " 
                        << planDate.tm_mon + 1 << " �� " << planDate.tm_mday << " �գ�" << (planDate.tm_wday == 0 ? "����" : "��Ϣ��") << "����\n";

                }
                // 5. �����ʾ����        wdy
                std::cout << "���վۻ�ƻ����ƶ�������Ϣ��\n";
                std::cout << "����������" << Persons[i].name << " " << "��ϵ��" << Persons[i].relation << endl;
                std::cout << "�������գ�" << Persons[i].birth_year << "��" << Persons[i].birth_mon << "��" << Persons[i].birth_day << "��" << endl;
                std::cout << "�´��������ڣ�" << nextBirthday.tm_year + 1900 << "��" << nextBirthday.tm_mon + 1 << "��" << nextBirthday.tm_mday << "��\n";
                std::cout << "�´����վ�������������" << daysToNextBirthday << "��\n";
                std::cout << "�����´�����ǰ" << n << "������ڣ�" << planDate.tm_year + 1900 << "��" << planDate.tm_mon + 1 << "��" << planDate.tm_mday << "��\n";
                std::cout << "Ԥ��׼���ƶ����ռƻ������ڣ�" << planDate.tm_year + 1900 << "��" << planDate.tm_mon + 1 << "��" << planDate.tm_mday << "��\n";
                std::cout << "�����ƶ��ƻ�1��Ϊ���������ƶ��ƻ�2���˳�3��";
                k[i] = planDate;
                int choice;
                std::cin >> choice;

                if (choice == 1) {
                    // ���ص�����4�������ƶ��ƻ�����
                    std::cout << "\n";
                    goto loop;
                }
                Persons_1.push_back(Persons[i]);
                if (choice == 2) {
                    // ���ص�����4�������ƶ��ƻ�����
                    std::cout << "\n";
                    goto loop1;
                }


            }
        }
    }

    // 6. ��������
    std::cout << "���ռƻ����ƶ������ѣ�" << endl;
    for (int i = 0; i < Persons_1.size(); i++) {
        cout << "������" << Persons_1[i].name << endl;
        cout << "��ϵ��" << Persons_1[i].relation << endl;
        cout << "���գ�" << Persons_1[i].birth_year << "��" << Persons_1[i].birth_mon << "��" << Persons_1[i].birth_day << "��" << endl;
        cout << "Ԥ��ʱ��" << k[i].tm_year + 1900 << "��" << k[i].tm_mon + 1 << "��" << k[i].tm_mday << "��\n";
    }
    std::cout << "���������������\n";
    std::cin.ignore();
    std::cin.get();


}

