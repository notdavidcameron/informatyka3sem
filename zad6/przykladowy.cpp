
#include<iostream>
#include <memory> 

/* dynamiczne alokowanie pamięci poprzez używanie wskaźników

/*polimorfizm

*/

class Number
{
    public:
        virtual void dispType() const=0; 
        virtual void dispNumber() const=0;
        virtual ~Number()
        {
            std::cout << "Usuwam Number "<<std::endl;
        }
    
};
//klasa abstrakcyjna

class Complex : public Number
{
    public:
        void dispNumber() const
        {
            std::cout << mRe << " +/- " <<mIm << "i" << std::endl;
        }
        
        void dispType() const
        {
            std::cout << "Complex ";
        }
        
        Complex() = default;
        Complex(float re, float im) : mRe(re), mIm(im) {}
        ~Complex()
        {
            std::cout << "Usuwam Complex";
        }
    private:
        float mRe;
        float mIm;
};


class Rational : public Number
{
    public:
        void dispNumber() const
        {
            std::cout << mA << "/" << mB << "i" << std::endl;
        }
        
        void dispType() const
        {
            std::cout << "Rational ";
        }
        
        Rational() = default;
        Rational(float a, float b=1) : mA(a), mB(b) {}
        ~Rational()
        {
            std::cout << "Usuwam Rational";
        }
    private:
            float mA;
        float mB;
};

int main() {
    
    float re, im;
    std::cin >> re >> im;
    Complex* pMyComplex = new Complex(re, im);
    pMyComplex->dispType();
    pMyComplex->dispNumber();
    
    delete pMyComplex;
    
    float a, b;
    std::cin >> a >> b;
    //Number* pMyNumber= new Rational(a,b);
    std::shared_ptr<Number> pMyNumber = std::make_shared<Rational>(a,b); //#include <memory>
    pMyNumber->dispType();                  //odnoszenie sie do funkcji danej klasy w sposób virtualny
    pMyNumber->dispNumber();
    
    //delete pMyNumber;
    
    unsigned int size;
    std::cin >> size;
    Complex* pTabComplex= new Complex[size];
    for (int i = 0; i<size; i++) {
        //pTabComplex->dispType();
        //pTabComplex++;
        pTabComplex[i].dispType();
        pTabComplex[i].dispNumber();
    }
    
    delete [] pTabComplex;
    
    
    /* stworzyc tablice wskaznikow
    
    
    */
    
    Number ** pNumbers = new Number*[size];
    for (int i = 0; i < size; i++) {
        if (i % 2) pNumbers[i] = new Complex(i,i+1);
        else  pNumbers[i] = new Rational(i,i+1);
    }
    
    for (int i = 0; i < size; i++) {
        pNumbers[i]->dispType();
        pNumbers[i]->dispNumber();
    }
    
    //do wskaźnika klasy bazowej możemy stworzyć obiekty klasy pochodnej
    //jestesmy w stanie dla dowolnych indeksow przechodzic z jednej klasy do drugiej 
    return 0;
}
