#include <iostream>

using namespace std;

class Link
{
    public:
        int data;
        Link* next;
        Link(int d, Link* n = NULL) : data(d), next(n) {}

};

class List
{
    public:
        Link* first;
        Link* last;

        List() : first(NULL), last(NULL) {}

        void addFirst(int d)
        {
            Link* newLink = new Link(d);
            if (first == NULL)
            {
                first = newLink;
                last = newLink;
            }
            else
            {
                newLink->next = first;
                first = newLink;
            }
        }



        void remove(int d)
        {
            Link* current = first;
            Link* previous = NULL;
            while (current != NULL)
            {
                if (current->data == d)
                {
                    if (previous == NULL)
                    {
                        first = current->next;
                        delete current;
                        current = first;
                    }
                    else
                    {
                        previous->next = current->next;
                        delete current;
                        current = previous->next;
                    }
                }
                else
                {
                    previous = current;
                    current = current->next;
                }
            }
        }
        
};

void displayList(List list)
{
    Link* current = list.first;
    while (current != NULL)
    {
        cout << current->data << " ";
        current = current->next;  
    }
}

int main()
{
    List aList;
    int M;
    cin >> M;
    for (int i = 0; i < M; i++)
    {
        int x;
        cin >> x;
        aList.addFirst(x);
    }

    //display the list
    displayList(aList);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        aList.remove(x);
    }

    displayList(aList);



}
