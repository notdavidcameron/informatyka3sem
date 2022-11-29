#include<iostream>
#include<algorithm>

using namespace std;


class simpleCircle
{
    private:
        string name_;
        float radius_;
    public:

        double perimeter() const
        {
            return 2*3.14*radius_;
        }

        void print() const
        {
            cout<< name_ << " " << perimeter() << " ";
        }

        void inputData1();
};

void simpleCircle :: inputData1()
{
    cin >> name_ >> radius_;
}



class Shape
{
    public:
        virtual void print() = 0;
        virtual double perimeter()= 0;
        virtual void inputData() = 0;
};






class Rectangle : public Shape
{
    private:
        string name_;
        float a_;
        float b_;
    public:
        Rectangle() 
        {
            // name_ = "rectangle";
        }
        
        void inputData()
        {
            // std::cout << "input rectangle data" << std::endl;
            cin >> name_ >> a_ >> b_;
        }


        double perimeter() 
        {
            return 2*a_ + 2*b_;
        }    
        
        double calcRectArea()
        {
            return a_*b_;
        }
        
        void print() 
        {
            cout<< name_ << " " << a_  << " " << b_;
        }
        

};

class Circle : public Shape
{
    private:
        string name_;
        float radius_;
    public:
        Circle() {
            // name_ = "circle";
        }
        
        void inputData()
        {
            // std::cout << "input circle data:" << std::endl;
            cin >> name_; 
            cin >> radius_;
        }
        
        double perimeter() 
        {
            return 2*3.14*radius_;
        }    
        
        double calcCircleArea()
        {
            return 3.14*radius_*radius_;
        }
        void print() 
        {
            cout<< name_ << " " << radius_ << " ";
        }
        

       
  
};



int main()
{
    short int task;
    cin >> task;
    switch(task)
    {
        case(1):
        {
            simpleCircle c;
            int n;
            cin >> n;
            simpleCircle * array = new simpleCircle[n];
            for(int i=0; i<n; i++)
            {
                array[i].inputData1();
            }
            std::sort(array, array+n, [](simpleCircle a, simpleCircle b){return a.perimeter() > b.perimeter();});
            for(int i=0; i<n; i++)
            {
                array[i].print();
            }

            break;
        }   
     case(2):
        {
            int rows;
            int columns;
            cin >> rows >> columns;
            Shape*** array = new Shape**[rows];
            for(int i=0; i<rows; i++)
            {   
                    array[i] = new Shape*[columns];
            }
        
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    if(i % 2 == 0)
                        array[i][j] = new Circle(); 
                    else
                        array[i][j] = new Rectangle(); 
                }
            }
            
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    array[i][j]->inputData();
                }
            }
            int inputRow;
            int inputColumn;
            cin >> inputRow >> inputColumn;
            array[inputRow][inputColumn]->print();
            break;
        }
    }
        
        
    return 1;
}
