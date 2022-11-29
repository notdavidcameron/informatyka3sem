#include <iostream>
#include <cassert>
#include<list> //dodatkowa biblioteka

using namespace std;

template <class T> class Link;
template <class T> class Iterator;

// ======================================================================
//                    Class Template List
// ======================================================================
template <class T>
class List {
protected:
    Link <T> *first;

public:
    List() : first(nullptr) {}
    List(const List &source);
    virtual ~List() {};

    virtual void add(T value);
    virtual void deleteAll();
    T firstElement() const;
    virtual bool includes(T value) const;
    bool isEmpty() const;
    virtual void removeFirst();

    friend class Iterator <T>;
};
// ======================================================================
//                    Class Template Link
// ======================================================================
template <class T>
class Link {
private:
    T value;
    Link <T> *next;
   
    Link(T val, Link *ptr) : value(val), next(ptr) { }
public:
    Link <T> *insert(T value);

    friend class List <T>;
    friend class Iterator <T>;
};


// ======================================================================

//                    Class Template Iterator
// ======================================================================
template <class T> class Iterator {
public:
    Iterator(List <T> &aList);
    virtual bool init();
    virtual T operator()();
    virtual bool operator !();
    virtual bool operator++(); // for prefix, for postfix add dummy int
    virtual bool operator++(int); //dopisane
    virtual void operator=(T value);
    void removeCurrent();
    void addBefore(T val);
    void addAfter(T val);
 protected:
    List <T> &myList;   // data fields
    Link <T> *previous;
    Link <T> *current;
 };

// ======================================================================
//                    Class Template Link - attributes
// ======================================================================
template <class T> Link <T> * Link <T> :: insert(T value) {
    next = new Link <T>(value, next);
    return next;
}

// ======================================================================
//                    Class Template List - attributes
// ======================================================================
template <class T> void List <T> :: add(T value) {
    first = new Link <T>(value, first);
}

template <class T> T List <T> :: firstElement() const {
    assert(first != nullptr);
    return first->value;
}


template <class T> bool List <T> :: isEmpty() const {
    return first == nullptr;
}


template <class T> bool List <T> :: includes(T value) const {
    for (Link <T> *p = first; p; p = p->next)
        if (value == p->value)return true;
    return false;
}

template <class T> void List <T> :: removeFirst() {
    assert(first != nullptr);
    Link <T> *ptr = first;
    first = ptr->next;
    delete ptr;
}

template <class T> void List <T> :: deleteAll() {
    Link <T> *next;
    for (Link <T> *p = first; p; p = next) {
        next = p->next;
        delete p;
    }
    first = nullptr;
}

// ======================================================================
//                    Class Template Iterator - attributes
// ======================================================================
template <class T> Iterator <T> ::
    Iterator(List <T> &aList) : myList(aList) {
    init();
}
template <class T> bool Iterator <T> :: init() {
    previous = nullptr;
    current = myList.first;
    return current != nullptr;
}
template <class T> T Iterator <T> :: operator()() {
    assert(current != nullptr);
    return current->value;
}
template <class T> void Iterator <T> :: operator=(T val) {
    assert(current != nullptr);
    current->value = val;
}

template <class T> bool Iterator <T> :: operator++() {
    if (current == nullptr){    // move current pointer
        if (previous == nullptr) // to next element
            current = myList.first;
        else
            current = previous->next;
    }
    else {
        previous = current;
        current = current->next;
    }
    return current != nullptr;
} // valid for prefix operator only

template <class T> bool Iterator <T> :: operator++(int) //mozna tak bo jest to powyzej
{
    return operator++();
}



template <class T> bool Iterator <T> :: operator !() {
    if (current == nullptr and previous != nullptr)
        current = previous->next;
    return current != nullptr;
}

template <class T> void Iterator <T> :: removeCurrent() {
    assert(current != nullptr);
    if (previous == nullptr)
        myList.first = current->next;
    else
        previous->next = current->next;
    delete current;
    current = nullptr;
}

template <class T> void Iterator <T> :: addBefore(T val) {
    if (previous) previous = previous->insert(val);
    else {
        myList.List<T>::add(val);     // to avoid subclass
        previous = myList.first;
        current = previous->next;      // if current is NULL
    }
}

template <class T> void Iterator <T> :: addAfter(T val) {
    if (current){current->insert(val); return;}  // not shown
    if (previous)current = previous->insert(val);
    else myList.List<T>::add(val);
}



class Apple
{
    public:
    string mName;
    int mWeight;
    Apple(string name, int weight) : mName(name), mWeight(weight)
    {
        
    }
    
    bool operator ==(const Apple& toCompare)
    {
        return mName == toCompare.mName && mWeight == toCompare.mWeight;
    }
        
};


ostream& operator<<(ostream& out, const Apple& toDisp)
{
    return out << toDisp.mName << " " << toDisp.mWeight;
}


// ======================================================================
//                            main
// ======================================================================

int main() {
    
     List<Apple> myList;
    
    unsigned int n = 4;
    string name;
    int weight;
    for(int i=0;i<n;i++)
    {
        cin >> name >>weight;
        Apple* toAdd = new Apple(name ,weight);
        myList.add(*toAdd);
        delete toAdd; //aby nie bylo wycieku pamieci
    }
    
    
    Iterator<Apple> iter(myList);
     
    cout << iter()<< " ";
     
    
    for(iter.init();!iter;++iter)
    {
        cout <<iter() << " ";
    }
    
    
    iter.init();
    iter++;
    ++iter;
    cout <<iter() << " ";
    
    
    cin >> name >>weight;
    Apple* toAdd = new Apple(name ,weight);
    myList.add(*toAdd);
    delete toAdd;
    
    
     for(iter.init();!iter;++iter)
    {
        cout <<iter() << " ";
    }
    cout << endl << "----------------------"<< endl;
    
    
    /*list<Apple>myList;
    unsigned int n = 4;
    string name;
    int weight;
    for(int i=0;i<n;i++)
    {
        cin >> name >>weight;
        Apple* toAdd = new Apple(name ,weight);
        myList.push_front(*toAdd);
        delete toAdd; //aby nie bylo wycieku pamieci
    }
    
    
    cout << *myList.cbegin() <<endl;
    
    for(auto i: myList)
    {
        cout <<i << " ";
    }
    
    
    auto iter = myList.cbegin();
    iter++;
    ++iter;
    cout << *iter <<" ";
    
    cin >> name >>weight;
        Apple* toAdd = new Apple(name ,weight);
        myList.push_front(*toAdd);
        delete toAdd;
    
      for(auto i = myList.cbegin();i != myList.cend();i++)
    {
        cout <<*i<< " ";
    }*/ // za pomoca biblioteki dodatkowej
    
    return 0;
}
// ======================================================================
