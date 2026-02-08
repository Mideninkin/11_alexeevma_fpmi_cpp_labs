#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>


struct Mark
{
    std::string subject_;
    size_t mark_;

    Mark (const std::string &subject, size_t mark) :
    subject_(subject), mark_(mark)
    {}

};

struct StudentData
{
    std::string name_;
    size_t number_;
    std::vector<Mark> marks_;

static StudentData MakeObjectsFromString(const std::string& line) 
{
        StudentData object;
        std::istringstream sstr(line);
        
        std::string surname, initials;
        sstr >> surname >> initials;
        object.name_ = surname + " " + initials;
        
        sstr >> object.number_;
        
        std::string subject;
        size_t mark;
        
        while (sstr >> subject >> mark) 
        {
            if (mark >= 1 && mark <= 10) 
            {
                object.marks_.emplace_back(subject, mark);
            } 
            else 
            {
                std::cerr << "Предупреждение: некорректная оценка " << mark << " по предмету " << subject << std::endl;
            }
        }
        
        if (sstr.fail() && !sstr.eof()) 
        {
            std::cerr << "Ошибка чтения строки: " << line << std::endl;
        }
        
        return object;
    }

    double CalculateAverage() const 
    {
        if (marks_.empty()) return 0.0;
        double sum = 0;
        for (const auto& mark : marks_)
        {
            sum += mark.mark_;
        }
        return sum / marks_.size();
    }

    bool HasUnsatisfactorymarks() const
    {
        for (const auto& mark : marks_)
        {
            if (mark.mark_ <= 3)
                return true;
        }
        return false;
    }

    bool HasSubject(const std::string& subject) const 
    {
        for (const auto& mark : marks_)
        {
            if (mark.subject_ == subject)
                return true;
        }
        return false;
    }

    size_t SumOfMarks() const
    {
        size_t sum = 0;
        for (const auto& mark : marks_)
        {
            sum += mark.mark_;
        }
        return sum;
    }
};

void MiddleMarkFromRange(const std::map<size_t, StudentData>& students) 
{
    if (students.empty())
    return;
    double min_avg, max_avg;
    std::cout << "Введите границы диапазона среднего балла: ";
    std::cin >> min_avg >> max_avg;
    
    if (min_avg > max_avg)
    std::swap(min_avg, max_avg);
    
    if (min_avg < 0) min_avg = 0;
    if (max_avg > 10) max_avg = 10;
    
    std::vector<std::pair<size_t, StudentData>> students_with_needed_mark;
    
    for (const auto& [number, student] : students) 
    {
        double avg = student.CalculateAverage();
        if (avg >= min_avg && avg <= max_avg) 
        {
            students_with_needed_mark.push_back({number, student});
        }
    }
    
    if (students_with_needed_mark.empty()) 
    {
        std::cout << "Нет студентов со средним баллом в этом промежутке" << std::endl;
        return;
    }
    
    std::sort(students_with_needed_mark.begin(), students_with_needed_mark.end(),
        [](const auto& a, const auto& b) 
        {
            return a.second.CalculateAverage() > b.second.CalculateAverage();
        });
    
    std::cout << "Найдено студентов: " << students_with_needed_mark.size() << std::endl;
    
    size_t order_number = 1;
    for (const auto& [number, student] : students_with_needed_mark) 
    {
        std::cout << order_number++ << ", " << student.name_ << ", "<< number
        << ", " << student.CalculateAverage() << std::endl;
    }
}

void PrintStudentsBasedOnSubject(const std::map<size_t, StudentData>& students) {
    
    if (students.empty())
    return;
    std::string subject;
    std::cout << "Введите название предмета: ";
    std::cin.ignore();
    getline(std::cin, subject);
    std::cout << "Студенты, сдававшие этот предмет:" << std::endl;
    
    bool Found = false;
    for (const auto& [number, student] : students) 
    {
        if (student.HasSubject(subject)) 
        {
            std::cout << student.name_ << ", "<< number
            << ", " << student.CalculateAverage() << std::endl;
            Found = true;
        }
    }
    
    if (!Found) 
    {
        std::cout << "Нет студентов, сдававших этот предмет." << std::endl;
    }
}

void CountStudentsOfSubject(const std::map<size_t, StudentData>& students) 
{
    if (students.empty())
    return;

    std::map<std::string, size_t> subject_count;
    
    std::map<std::string, std::map<size_t, bool>> temp;
    
    for (const auto& [number, student] : students) 
    {
        for (const auto& mark : student.marks_) 
        {
            if (temp[mark.subject_].find(number) == temp[mark.subject_].end())
            {
                temp[mark.subject_][number] = true;
                subject_count[mark.subject_]++;
            }
        }
    }
    
    std::cout << "Предметы и количество студентов: " << std::endl;

    for (const auto& [subject, count] : subject_count) 
    {
        std::cout << subject << ": " << count << " студент(ов)" << std::endl;
    }
}

void MiddleMarkOfSubjects(const std::map<size_t, StudentData>& students) 
{
    if (students.empty())
    return;
    std::cout << "Средний балл по предметам" << std::endl;
    
    std::map<std::string, std::pair<int, int>> data;
    
    for (const auto& [num, student] : students) 
    {
        for (const auto& mark : student.marks_) 
        {
            data[mark.subject_].first += mark.mark_;
            data[mark.subject_].second++;
        }
    }
    
    std::vector<std::pair<std::string, double>> averages;
    for (const auto& [subject, numbers] : data) 
    {
        double avg = static_cast<double>(numbers.first) / numbers.second;
        averages.push_back({subject, avg});
    }
    
    std::sort(averages.begin(), averages.end(),
        [](const auto& a, const auto& b) 
        {
            return a.second > b.second;
        });
    
    for (const auto& [subject, avg] : averages) 
    {
        std::cout << subject << ": " << avg << std::endl;
    }
}

void FindStudentsWithMaxSum(const std::map<size_t, StudentData>& students) 
{
    if (students.empty()) 
    {
        std::cout << "Нет данных";
        return;
    }
    
    size_t max_sum = 0;
    for (const auto& [number, student] : students) 
    {
        size_t sum = student.SumOfMarks();
        if (sum > max_sum) 
        {
            max_sum = sum;
        }
    }
    
    std::vector<std::pair<size_t, StudentData>> top_students;
    for (const auto& [number, student] : students) 
    {
        if (student.SumOfMarks() == max_sum) 
        {
            top_students.push_back({number, student});
        }
    }
    
    std::cout << "Максимальная сумма баллов: " << max_sum << std::endl;
    std::cout << "Количество студентов с этой суммой: " << top_students.size() << std::endl;
    
    std::sort(top_students.begin(), top_students.end(),
        [](const auto& a, const auto& b) 
        {
            return a.second.name_ < b.second.name_;
        });
    
    std::cout << "Студенты с максимальной суммой баллов:" << std::endl;
    for (const auto& [number, student] : top_students) 
    {
        std::cout << student.name_ << ", " << number
        << ", " << student.SumOfMarks()
        << ", " << student.CalculateAverage()
        << ", предметов: " << student.marks_.size() << std::endl;
    }
}

void ShowBadStudents(const std::map<size_t, StudentData>& students) 
{
    if (students.empty())
    return;
    std::cout << "Студенты с плохими оценками (1, 2, 3):" << std::endl;
    
    int count = 0;
    for (const auto& [number, student] : students) 
    {
        if (student.HasUnsatisfactorymarks()) 
        {
            count++;
            std::cout << student.name_ << ", " << number << ", " 
            << student.CalculateAverage() << std::endl;
        }
    }
    
    if (count == 0) 
    {
        std::cout << "Нет студентов с неудовлетворительными отметками!" << std::endl;
    } 
    else 
    {
        std::cout << "Всего: " << count << " студент(ов)" << std::endl;
    }
}

int main() 
{
    setlocale(LC_ALL, "ru");
    std::map<size_t, StudentData> number_and_student;
    std::ifstream fin("IN1.TXT");

    if (!fin.is_open()) 
    {
        std::cerr << "Ошибка: не удалось открыть файл IN.TXT" << std::endl;
        return 1;
    }

    if (fin.peek() == EOF)
    {
        std::cerr << "Ошибка: файл IN.TXT пуст!" << std::endl;
        return 1;
    }
    
    std::string line;
    size_t line_number = 0;
    
    while (getline(fin, line)) 
    {
        line_number++;
        
        if (line.empty()) continue;
        
            StudentData student = StudentData::MakeObjectsFromString(line);
        
            if (number_and_student.find(student.number_) != number_and_student.end()) 
            {
                std::cerr << "Предупреждение: студент под номером " << student.number_<< " уже существует" << std::endl;
            }

            number_and_student[student.number_] = student;
    }
    
    fin.close();
    
    if (number_and_student.empty()) 
    {
        std::cout << "Файл не содержит корректных данных (или пустой)" << std::endl;
        return 0;
    }

    std::cout << "Список студентов (сортировка по номеру зачёток):" << std::endl;
    
    for (const auto& [number, student] : number_and_student) 
    {
        std::cout << "Номер зачётной книжки: " << number << ", Студент: " 
        << student.name_ << "\n";
    }

    std::cout << "Вывод в алфавитном порядке:" << std::endl;

    std::vector<std::pair<size_t, StudentData>> students_vector;
    students_vector.reserve(number_and_student.size());
    
    for (const auto& pair : number_and_student) 
    {
        students_vector.push_back(pair);
    }


    std::sort(students_vector.begin(), students_vector.end(),
    [](const auto& a, const auto& b) 
        {
            const StudentData& studentA = a.second;
            const StudentData& studentB = b.second;
            
            if (studentA.name_ != studentB.name_) 
            {
                return studentA.name_ < studentB.name_;
            }
            
            return studentA.CalculateAverage() > studentB.CalculateAverage();
        });

    
    size_t order_number = 1;
    for (const auto& [number, student] : students_vector) 
    {
        std::cout << order_number++ << ", " << student.name_ << ", "<< number
        << ", " << student.CalculateAverage() << std::endl;
    }

    MiddleMarkFromRange(number_and_student);

    PrintStudentsBasedOnSubject(number_and_student);

    CountStudentsOfSubject(number_and_student);

    MiddleMarkOfSubjects(number_and_student);

    FindStudentsWithMaxSum(number_and_student);

    ShowBadStudents(number_and_student);

    return 0;
}

/*Текстовые файлы для тестов:
IN1.TXT
Киселёва Е.В. 5362 Литература 2 Русский 1
Миронов П.Н. 9137 Физкультура 9 ОБЖ 8
Фролова И.Г. 2846 Алгебра 8 Геометрия 7
Богданов Д.К. 6974 Информатика 5 Программирование 4
Назарова М.П. 3510 История 10 Обществознание 9*/

/*Текстовые файлы для тестов:
IN2.TXT
Кузьмин А.А. 1945 Математика 6 Физика 5 Химия 4
Соловьёва М.С. 8273 Биология 7 География 8
Баранов П.И. 4562 Физкультура 10 ОБЖ 9
Воробьёва Д.К. 6391 Литература 8 История 7
Герасимов Н.Л. 2784 Экономика 5 Право 6*/

/*Текстовые файлы для тестов:
IN3.TXT
Калинин Н.М. 2169 Физкультура 4 ОБЖ 3
Гусева А.К. 6852 Алгебра 9 Геометрия 10
Тихонов И.П. 3497 Информатика 7 Программирование 6
Кудрявцева Е.С. 9271 История 4 Обществознание 3
Блинов Д.В. 4583 Математика 2 Физика 1*/

/*Текстовые файлы для тестов:
IN4EMP.TXT

*/