#include <math.h>
#include <iostream>
using namespace std;

class IEEE754 {
  private:
    bool sign_;
    int exponent_;
    float mantissa_;

  public:
    IEEE754(bool s, int e, float m) {
        sign_ = s;
        exponent_ = e;
        mantissa_ = m;
    }

    IEEE754(float f) {
        if (f < 0)
            sign_ = 1;
        else
            sign_ = 0;

        int i = *(int *)&f;
        exponent_ = ((i >> 23) & 0xff);
        mantissa_ = 1 + (i & 0x7fffff) / (float)(1 << 23);
    }

    bool getSign() { return sign_; };
    int getExponent() { return exponent_; };
    float getMantissa() { return mantissa_; };

    void IEEEToDouble(IEEE754 number);

    bool operator>(const IEEE754 toComp) const;
    void operator+=(const IEEE754 toAdd);
    void operator-=(const IEEE754 toSub);

    friend ostream &operator<<(std::ostream &out, const IEEE754 &toDisp);
    friend IEEE754 operator+(const IEEE754 &num1, const IEEE754 &num2);
    friend IEEE754 operator-(const IEEE754 &num1, const IEEE754 &num2);
};

void IEEE754::operator+=(const IEEE754 toAdd) {
    bool sameSign = sign_ == toAdd.sign_;
    const IEEE754 *largerE, *smallerE;

    if(exponent_ >= toAdd.exponent_) {
        largerE = this;
        smallerE = &toAdd;
    } else {
        largerE = &toAdd;
        smallerE = this;
    }

    float smolMantissa = smallerE->mantissa_ / pow(2, largerE->exponent_ - smallerE->exponent_);
    if(!sameSign)
        smolMantissa = -smolMantissa;
    
    mantissa_ = largerE->mantissa_ + smolMantissa;
    exponent_ = largerE->exponent_;

    if(mantissa_ < 0)
        mantissa_ = -mantissa_;
    
    if(!sameSign) {
        if(toAdd.exponent_ > exponent_) {
            sign_ = !sign_; 
        }
        else if(toAdd.exponent_ == exponent_) {
            if(toAdd.mantissa_ > mantissa_) {
                sign_ = toAdd.sign_;
            }
        }
    }

    if(mantissa_ == 0.f)
        sign_ = 0;
}

void IEEE754::operator-=(IEEE754 toSub) {
    toSub.sign_ = !toSub.sign_;
    (*this) += toSub;
}

IEEE754 operator+(const IEEE754 &num1, const IEEE754 &num2) {
    IEEE754 temp(num1);
    temp += num2;
    return temp;
}

IEEE754 operator-(const IEEE754 &num1, const IEEE754 &num2) {
    IEEE754 temp(num1);
    temp -= num2;
    return temp;
}

std::ostream &operator<<(std::ostream &out, const IEEE754 &number) {
    const int bias = 127;
    bool s = number.sign_;
    int e = number.exponent_;
    double m = number.mantissa_;

    double value = pow(2, e - bias) * m;
    if(abs(value) < 1e-37)
        return out << "0";

    return out << (s == 0 ? "" : "-") << value;
}

int inputExponent()
{
    int exponent;
    std::cin >> exponent;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1,'\n');
        
        std::cin >> exponent;
    }
    return exponent;
}


float inputMantissa()
{
    float mantissa;
    std::cin >> mantissa;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1,'\n');
        
        std::cin >> mantissa;
    }
    return mantissa;
}

bool inputSign()
{
    char sign;
    bool warunek = true;
    while(warunek)
    {
        std::cin >> sign;
        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(1,'\n');
            
            std::cin >> sign;
        }
        if (sign == '-' || sign == '+') warunek = false;
    }
    
    if(sign == '-') return 1;
    return 0;
}

float inputFloat()
{
    float input;
    std::cin >> input;
        while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1,'\n');
        
        std::cin >> input;
    }
    return input;
}


int main()
{
   bool s;
   int e;
   float m;
   float f;
   
   s = inputSign();
   e = inputExponent();
   m = inputMantissa();
   IEEE754 x0(s, e, m);
   
   s = inputSign();
   e = inputExponent();
   m = inputMantissa();
   IEEE754 x1(s, e, m);
   
   f = inputFloat();
   IEEE754 x2(f);
   
   f = inputFloat();
   IEEE754  x3(f);
   
   x0 += x1;
   x3 -= x2;
   IEEE754 x4 = x1 + x3;
   IEEE754 x5 = x4 - x2;
   
   cout << x0<< " " << x1 <<" "<< x2 <<" "<< x3 <<" "<< x4 << " " << x5;
}
