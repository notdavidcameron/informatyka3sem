#include <iostream>
class Link
{
  public:
  Link* mpNext;
  Link* mpPrev;
  double mVal;
  Link(double val, Link* pNext= nullptr, Link* pPrev = nullptr)
    : mVal(val), mpNext(pNext),mpPrev(pPrev)
  {
  }
};
class List
{
  public:
  Link* mpFirst;
  Link* mpLast;
  List(Link* pFirst = nullptr, Link* pLast = nullptr)
    : mpFirst(pFirst), mpLast(pLast)
    {
    }
    void addElement(double toAdd);
    void removeElement(double toRemove);
};
void List::addElement(double toAdd)
{
    if(!mpFirst)
    {
        mpFirst = new Link(toAdd);
        mpLast = mpFirst;
    }
    else
    {
        mpFirst= new Link(toAdd, mpFirst);
        mpFirst -> mpNext -> mpPrev = mpFirst;
    }
}
void List::removeElement(double toRemove)
{
    Link* temp = mpLast;
    while(temp)
    {
        if(temp -> mVal == toRemove)
        {
            if(temp -> mpNext) temp -> mpNext -> mpPrev = temp -> mpPrev;
            else mpLast = temp -> mpPrev;
            if(temp->mpPrev) temp -> mpPrev -> mpNext = temp -> mpNext;
            else mpFirst = temp -> mpNext;
            delete temp;
            return;
        }
        temp = temp -> mpPrev;
    }
}
std::ostream& operator<<(std::ostream& out, const List& toDisp)
{
    Link* temp = toDisp.mpFirst;
    while(temp)
    {
        out<<temp -> mVal <<" ";
        temp=temp-> mpNext;
    }
    out<<std::endl;
    temp= toDisp.mpLast;
    while(temp)
    {
        out<<temp -> mVal<<" ";
        temp=temp-> mpPrev;
    }
    return out;
}
// ======================================================================
//                            main
// ======================================================================

int main() {
    int M,N;
    List myList;
    double toAdd, toRemove;
    std::cin >> M;
    for(int i=0; i<M;i++)
    {
        std::cin>>toAdd;
        myList.addElement(toAdd);
        std::cout<<myList<<std::endl;
    }
    std::cin>>N;
    for(int i=0; i<N;i++)
    {
        std::cin>>toRemove;
        myList.removeElement(toRemove);
        std::cout<<myList<<std::endl;
    }
    return 0;
}
// ======================================================================
