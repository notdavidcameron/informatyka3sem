#include<iostream>
#include<algorithm>

using namespace std;
enum Gender {woman, man}; //deklaracja enuma

class Person 
{
    private:
        string name_;
        string surname_;
        float weight_;
        float height_;
        int age_;
        
    public:
        
        Person()//konsturktor używany do skreślania i tworzenia domyślnych 
        {
            age_ = 0;
        }
    
        Person(string name, string surname, float weight, float height, int age, Gender gender)
            :name_(name), surname_(surname), weight_(weight), height_(height), age_(age), gender_(gender)
        {}
        
        void inputPerson()
        {
            string name;
            string surname;
            float weight;
            float height;
            int age;
            Gender gender;
            
            cin >> name;
            cin >> surname;
            cin >> weight;
            cin >> height;
            cin >> age;
            char gend;
            cin >> gend;
            if(gend == 'M')//zamiana str na enuma
            {
                gender_ = man;
            }
            else if(gend == 'K')
            {
                gender_ = woman;
            }
            name_ = name;
            surname_ = surname;
            weight_ = weight;
            height_ = height;
            age_ = age;
        }
        //funkcje dostępowe
        float getWeight() {return weight_;};
        float getHeight() {return height_;};
        int getAge() {return age_;};
        string getName() {return name_;};
        string getSurname() {return surname_;};
        Gender getGender() {return gender_;};
                
        double calcBMI(Person person);
        void dispData(Person person);
        
    protected:
        Gender gender_;
    
};


class Student : public Person
{
    
        
    public:
        Student(string name, string surname, float weight, float height, int age, Gender gender, string studentIdx, int year, double grades[])
            :studentIdx_(studentIdx), year_(year), Person(name, surname, weight, height, age, gender)
            {
                
            }
        Student() = default;//konstruktor domyślny
        
        void inputStudent()
        {
            inputPerson();
            string studentIdx; 
            int year;
            cin >> studentIdx;
            cin >> year;
            studentIdx_ = studentIdx;
            year_ = year;
            double grades;
            for (int i = 0; i < 5; i++) //wejście ocen
           {
               cin >> grades;
               grades_[i] = grades;
           }
        }
        
        double calcGradeAverage() const//średnia i const żeby nie zmienić orginału przypadkiem
        {
            
            int length = 0;
            for (int i = 0; i < 10; i++)
            {
                if (grades_[i] != 0)
                    length++;
            }
            
            double sum = 0;
            for (int i = 0; i < length; i++)
            {
                sum += grades_[i];
            }
            double avg = sum/length;
            return avg;
        
        }
        //funkcje dostępowe
        int getYear() {return year_;};
        string getIdx() {return studentIdx_;};
        

        
    private:
        string studentIdx_;
        int year_;
        double grades_[10] = {};
    
};


class Employee : public Person
{
    public:
        Employee() = default;
        Employee(string companyName, string position, float wage, float seniority)
            :companyName_(companyName), position_(position), wage_(wage), seniority_(seniority)
            {}
            
        void timeUntilRetirement(Employee employee);
        
        void inputEmployee()
        {
            inputPerson();
            string companyName;
            cin >> companyName;
            string position;
            cin >> position;
            float wage;
            cin >> wage;
            float seniority;
            cin >> seniority;
            
            companyName_ = companyName;
            position_ = position;
            wage_ = wage;
            seniority_ = seniority;
            
        }
    
    private:
        string companyName_;
        string position_;
        float wage_;
        float seniority_;
};

void Employee::timeUntilRetirement(Employee employee)
{
    if (gender_ == man)
        std::cout << 65 - employee.getAge() << " ";
    else
        std::cout << 60 - employee.getAge() << " ";
}

std::ostream &operator<<(std::ostream &out, Student &toDisp)//przeciążenie operatora <<
{
    string nrIdx = toDisp.getIdx();
    string name = toDisp.getName();
    string surname = toDisp.getSurname();
    
    return out << nrIdx << " " << name << " " << surname;
}   


class Course
{
    public:
        Course(string courseName)
        {
            courseName_ = courseName;
            studentsAmt_ = 0;
        }
    
        void addStudent(Student student);
        void updateStudentsAmt();
        void removeStudent(Student student);
        void sortByGrades(int year);
        void dispBestStudents(int year);
        
        int getStudentsAmt() {return studentsAmt_;};
        
        void dispStudents()//funkcja do debugowania
        {
            for (int i = 1; i < 6; i++)
            {
                
                for (int j = 0; j < 10; j++)
                {
                    std::cout << "[" << students_[i][j] << "]";
                }
                std::cout << std::endl;
                
            }
        }
        
        friend bool operator<(const Student& student1, const Student& student2);
        friend ostream &operator<<(std::ostream &out, const Student& toDisp);
    
    private:
        string courseName_;
        Student students_[6][10];
        int studentsAmt_;
};

bool operator<(const Student& student1, const Student& student2)//przeciążony operator żeby porównywał średnią studenta (jest odwrócony xd, bo w sorcie wyjebywało)
{
    return student1.calcGradeAverage() > student2.calcGradeAverage();

}

void Person::dispData(Person person)//to nigdzie nie jest używane ale jest w poleceniu nie wiem czemu xd
{
    std::cout << person.getName() << " " << person.getSurname() << " " << person.getWeight() << " " << person.getHeight() << " " << person.getAge() << " " << person.getGender() << std::endl;
}

double Person::calcBMI(Person person)
    {
        double bmi = 10000*person.getWeight()/((person.getHeight()*person.getHeight()));
        return bmi;
    }



void Course::addStudent(Student student)//dodawanie studenta
{
    int year = student.getYear();
    for (int i = 0; i < 10; i++)
    {
        if (students_[year][i].getAge() == 0)
        {
            students_[year][i] = student;
            break;
        }
            
    }
    updateStudentsAmt();
}


void Course::removeStudent(Student student)//skreślanie studenta
{
    int year = student.getYear();
    int tab[5] = {0, 0, 0, 0, 0};
    
    for (int i = 0; i < 10; i++)
    {
        if (students_[year][i].getIdx() == student.getIdx())
        {
            students_[year][i] = Student();
            break;
        }
            
    }
    
    updateStudentsAmt();
}

void Course::updateStudentsAmt()//sprawdza ilość studentów na kierunku (w tablicy)
{
    studentsAmt_ = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (students_[i][j].getAge() != 0)
                studentsAmt_++;
        }
    }
}
    
void Course::sortByGrades(int year)//sortuje studentów podanego roku malejąco i pomija puste miejsca w tablicy
{
    int studentsOnYear = 0;
    
    for (int i = 0; i < 10; i++)
        {
            if (students_[year][i].getAge() != 0)
                studentsOnYear++;
        }
    sort(students_[year], students_[year]+studentsOnYear);
}

void Course::dispBestStudents(int year)//wyświetla najlepszych studentów na podanym roku (int year)
{
    Student bestStudents[10];
    for (int i = 0; i < 10; i++)
    {
        bestStudents[i] = students_[year][i];
    }
    sort(bestStudents, bestStudents+10);
    
    for (int i = 0; i < 3; i++)
    {
        if (bestStudents[i].getAge() != 0)//żeby nie wyświetlało nie istniejącego studenta (gdy na roku jest mniej niż 3)
            std::cout << bestStudents[i] << " ";
    }
}


int main() {
    
    string courseName;
    std::cin >> courseName;
    Course course(courseName);
    Student s[10];
    for(int i=0; i<10; i++)
    {
        s[i].inputStudent();
        course.addStudent(s[i]);
    }
    int year;
    cin >> year;
    course.dispBestStudents(year);
    
    Employee e1;
    e1.inputEmployee();
    Employee e2;
    e2.inputEmployee();
    
    e1.timeUntilRetirement(e1);
    e2.timeUntilRetirement(e2);
    
    return 0;
}