#include <iostream>
#include <math.h>
using namespace std;

// ----------------------------------------------
// ----------------Class Link--------------------
// ----------------------------------------------
template <class T> class Link
{
    private:
        Link* mpNext;
        Link* mpPrev;
        T mVal;

    public:
        Link(T val, Link* pNext= nullptr, Link* pPrev = nullptr)
            : mVal(val), mpNext(pNext),mpPrev(pPrev)
        {}
        
        ~Link()
        {}
      
        T getVal()
        {
            return mVal;
        }

        Link* getNext()
        {
            return mpNext;
        }

        Link* getPrev()
        {
            return mpPrev;
        }

        void setVal(T val)
        {
            mVal = val;
        }

        void setNext(Link* pNext)
        {
            mpNext = pNext;
        }

        void setPrev(Link* pPrev)
        {
            mpPrev = pPrev;
        }
};

// ----------------------------------------------
// ----------------Class List--------------------
// ----------------------------------------------

template <class T> class List
{
    private:
        Link<T>* mpFirst;
        Link<T>* mpLast;

    public:
        List(Link<T>* pFirst = nullptr, Link<T>* pLast = nullptr)
            : mpFirst(pFirst), mpLast(pLast)
        {}
        
        ~List()
        {}
      
        void addElement(T toAdd);
        void removeElement(T toRemove);

        friend ostream& operator<<(ostream& out, const List& toDisp)
        {
            Link<T>* temp = toDisp.mpLast;
            while(temp)
            {
                out<<temp->getVal() <<" ";
                temp=temp->getPrev();
            }
            return out;
        }

};

// ----------------------------------------------
// ----------------Class Complex-----------------
// ----------------------------------------------

class Complex
{
    private:
        float mRe;
        float mIm;
    public:
        Complex(float re = 0, float im = 0)
            : mRe(re), mIm(im)
        {}
        ~Complex()
        {}

        float abs()
        {
            return sqrt(mRe*mRe + mIm*mIm);
        }

        friend ostream& operator<<(ostream& out, const Complex& toDisp)
        {
            if(toDisp.mIm < 0)
                out<<toDisp.mRe<<toDisp.mIm<<"i";
            else
                out<<toDisp.mRe<<"+"<<toDisp.mIm<<"i";
            return out;
        }

        friend bool operator==(const Complex& c1, const Complex& c2)
        {
            return (c1.mRe == c2.mRe && c1.mIm == c2.mIm);
        }


        bool operator>(Complex& toCompare)
        {
            return this->abs() > toCompare.abs();
        }

        
};


// ----------------------------------------------
// ------------Class List Attributes-------------
// ----------------------------------------------


template <class T> void List<T>::addElement(T toAdd)
{
    Link<T>* temp = new Link<T>(toAdd);
    if (mpFirst == nullptr)
    {
        mpFirst = temp;
        mpLast = temp;
    }
    else
    {
        Link<T>* temp2 = mpFirst;
        while(temp2)
        {
            if (temp2->getVal() > toAdd)
            {
                temp->setNext(temp2);
                temp->setPrev(temp2->getPrev());
                temp2->setPrev(temp);
                if (temp->getPrev() != nullptr)
                {
                    temp->getPrev()->setNext(temp);
                }
                else
                {
                    mpFirst = temp;
                }
                break;
            }
            else if (temp2->getNext() == nullptr)
            {
                temp2->setNext(temp);
                temp->setPrev(temp2);
                mpLast = temp;
                break;
            }
            temp2 = temp2->getNext();
        }
    }
}
  

template <class T> void List<T>::removeElement(T toRemove)
{
    Link<T>* temp = mpFirst;
    while(temp)
    {
        if (temp->getVal() == toRemove)
        {
            if (temp->getPrev() != nullptr)
            {
                temp->getPrev()->setNext(temp->getNext());
            }
            else
            {
                mpFirst = temp->getNext();
            }
            if (temp->getNext() != nullptr)
            {
                temp->getNext()->setPrev(temp->getPrev());
            }
            else
            {
                mpLast = temp->getPrev();
            }
            delete temp;
            temp = mpFirst;
        }
        else
        {
            temp = temp->getNext();
        }
    }
}

int main()
{
    List<Complex> list;
    int M;
    cin>>M;
    for(int i=0; i<M; i++)
    {
        float re, im;
        cin>>re>>im;
        list.addElement(Complex(re, im));
    }
    cout<<list;
    int N;
    cin>>N;
    for(int i=0; i<N; i++)
    {
        float re, im;
        cin>>re>>im;
        list.removeElement(Complex(re, im));
    }
    cout<<list<<endl;
    
}