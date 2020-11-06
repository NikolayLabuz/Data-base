// Kumite.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <exception>
using namespace std;
bool Flag;
// Реализуйте функции и методы классов и при необходимости добавьте свои
class Date {
public:
    Date(){
        Year = 0;
        Month = 0;
        Day = 0;
    }
    Date(const int& year,const int& month,const int& day) {
        Year = year;            
        Month = month;
        Day = day;
    }
    int GetYear() const {
        return Year;
    }
    int GetMonth() const {
        return Month;
    }
    int GetDay() const {
        return Day;
    }
private:
    int Year;
    int Month;
    int Day;
};

istream& operator >> (istream& stream, Date& date) {
    int year, month, day;
    char def1, def2;
    try {
        string Date;
        stringstream Input;
        stream >> Date;
        Input.str(Date);
        if ((Input >> year >> def1 >> month >> def2 >> day) && Input.peek() == EOF) {
            if (def1 != '-' && def2 != '-') {
                throw runtime_error(Input.str());
            }
        }
        else {
            throw runtime_error(Input.str());
        }
    }
    catch (exception& ex) {
        cout << "Wrong date format: " << ex.what() << endl;
        Flag = true;
        return stream;
    }
    try {
        if (month > 12 || month <= 0) {
            string out = "Month value is invalid: " + to_string(month);
            throw invalid_argument(out);
        }
        if (day > 31 || day <= 0) {
            string out = "Day value is invalid: " + to_string(day);
            throw invalid_argument(out);
        }
        date = Date(year, month, day);
    }
    catch (exception& x) {
        cout << x.what();
        Flag = true;
    }
    return stream;
}

bool operator<(const Date& lhs, const Date& rhs) {
    if ((lhs.GetYear() * 365 + lhs.GetMonth() * 31 + lhs.GetDay()) <
        (rhs.GetYear() * 365 + rhs.GetMonth() * 31 + rhs.GetDay())) {
        return true;
    }
    else {
        return false;
    }
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        DateAndEvent[date].insert(event);
    };
    bool DeleteEvent(const Date& date, const string& event) {
        for (string item1 : DateAndEvent[date]) {
            if (item1 == event) {
                DateAndEvent[date].erase(event);
                cout << "Deleted successfully" << endl;
                return true;
            }
        }
        cout << "Event not found"<<endl;
        return false;
    };

    int DeleteDate(const Date& date) {
        int count;
        try {
            count = DateAndEvent.at(date).size();
        }
        catch (out_of_range&) {
            return 0;
        }
        DateAndEvent.erase(date);
        return count;
    }

    void Find (const Date& date) const{
        try {
            set<string> Event = DateAndEvent.at(date);
            for (string item : Event) {
                cout << item << endl;
            }
        } 
        catch (out_of_range&) {

        }
    };

    void Print() const {
        for (auto item1 : DateAndEvent) {
            int Year = item1.first.GetYear();
            int Month = item1.first.GetMonth();
            int Day = item1.first.GetDay();
            string Date;
            if (Year < 0) {
                Date += "-";
                Year *= -1;
            }
            if (!(Year / 1000)) {
                Date += "0";
                if (!(Year / 100)) {
                    Date += "0";
                    if (!(Year / 10)) {
                        Date += "0";
                    }
                }
            }          
            Date += to_string(Year) + "-";
            if (!(Month / 10)) {
             Date += "0";
            }
            Date += to_string(Month) + "-";
            if (!(Day / 10)) {
             Date += "0";
            }
            Date += to_string(Day);
            for (string item2 : item1.second) {
                cout << Date <<" "<< item2 << endl;
            }
        }
    };
private:
    map<Date, set<string>> DateAndEvent;
};
int main() {
    Database db;
    string command;
    while (cin >> command) {
        Flag = false;
        Date date;
        string event = "";
        if (command == "Add") {
            cin >> date;
            cin >> event;
            if (Flag == false) {
                db.AddEvent(date, event);
            }
        }
        else if (command == "Del"){
            cin >> date;
            if (cin.peek()==('\n')) {
                if (Flag == false) {
                    int count = db.DeleteDate(date);
                    cout << "Deleted " << count << " events" << endl;
                }
            }
            else {
                cin >> event;
                if (Flag == false) {
                    db.DeleteEvent(date, event);
                }
            }
        }
        else if (command == "Find") {
            cin >> date;
            db.Find(date);
        }
        else if (command == "Print") {
            db.Print();
        }
        else {
            cout << "Unknown command: " << command << endl;
        }
    }

    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
