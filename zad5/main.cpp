#include<iostream>
#include<algorithm>
#include<string>

using namespace std;



template<class T> class Container
{
    public:
        T object_;
        Container() : elementCounter_(0) {}
        
        int getElementsAmt() {return elementCounter_;};
        void addToContainer(T toAdd);
        void removeFromContainer(int idx);
        void printContainer();
        void sortContainer();
        void dispAllData();
        
        
    private:
        T objectArray_[6];
        int elementCounter_;

};


template<class T> void Container<T>::addToContainer(T toAdd)
{
    if (elementCounter_ < 6)
    {
        objectArray_[elementCounter_] = toAdd;
        elementCounter_++;
    }
    else
    {
        std::cout << "Container is full" << std::endl;
    }
}

template<class T> void Container<T>::removeFromContainer(int idx)
{

    if (idx < elementCounter_)
    {
        objectArray_[idx] = objectArray_[elementCounter_-1];
        elementCounter_--;
    }
    
}

template<class T> void Container<T>::printContainer()
{
    for (int i = 0; i < elementCounter_; i++)
    {
        std::cout << objectArray_[i].getName() << std::endl;
    }
}

template<class T> void Container<T>::sortContainer()
{
    std::sort(objectArray_, objectArray_ + elementCounter_);
}

template<class T> void Container<T>::dispAllData()
{
    for (int i = 0; i < elementCounter_; i++)
    {
        std::cout << objectArray_[i] << " ";
    }
}

bool containsSpace(string toCheck)
{
    for (int i = 0; i < toCheck.length(); i++)
    {
        if (toCheck[i] == ' ')
        {
            return true;
        }
    }
    return false;
}

float inputFloat()
{
    string input;
    
    bool warunek = true;
    
    while(warunek)
    {
        int counter = 0;
        cin >> input;
        for (int i = 0; i < input.length(); i++)
        {
            if( ((input[i]>47)&&(input[i]<58) || input[i] == '.') )
            {
                counter++;
            }
            if(counter == input.length())
            {
                warunek = false;
            }
            else
            {
                // std::cout << "fail" << std::endl;
            }
        }
    }
    return stof(input);
}

float inputInt()
{
    string input;
    
    bool warunek = true;
    
    while(warunek)
    {
        int counter = 0;
        cin >> input;
        for (int i = 0; i < input.length(); i++)
        {
            if( ((input[i]>47)&&(input[i]<58)))
            {
                counter++;
            }
            if(counter == input.length())
            {
                warunek = false;
            }
            else
            {
                // std::cout << "fail" << std::endl;
            }
        }
    }
    return stoi(input);
}



/* string inputString()
{
   string input;
    bool warunek = true;
    while(warunek)
    {
        getline(cin, input);
        if(!containsSpace(input))
        {
            warunek = false;
        }
        else
        {
            std::cout << "fail = " << input << std::endl;
        }
    }
    return input;
}*/


class Animal
{
    public:
        Animal() = default;
        
        Animal(string name, float weight, int birthYear, string id)
            : name_(name), weight_(weight), birthYear_(birthYear), id_(id)
            {}
        
        void dispAnimalData(Animal animal);
        string getName() {return name_;};

        void inputAnimal()
        {
            string name;
            float weight;
            int birthYear;
            string id;
            
            std::cin >> name;
            weight = inputFloat();
            birthYear = inputInt();
            std::cin >> id;
            
            name_ = name;
            weight_ = weight;
            birthYear_ = birthYear;
            id_ = id;
        }

        friend bool operator==(Animal animal1, Animal animal2)
        {
            return animal1.id_ == animal2.id_;
        }

        friend bool operator<(Animal animal1, Animal animal2)
        {
            if (animal1.birthYear_ == animal2.birthYear_)
                return animal1.weight_ < animal2.weight_;
            else
                return animal1.birthYear_ > animal2.birthYear_;
        }

        friend ostream &operator<<(std::ostream &out, const Animal &animal)
        {
            out << animal.name_ << " " << animal.weight_ << " " << animal.birthYear_ << " " << animal.id_;
            return out;
        }

    private:
        string name_;
        float weight_;
        int birthYear_;
        string id_;
};

class Building
{
    public:
        Building() = default;
    
        Building(string name, float gpsX, float gpsY, float buildingHeight)
            : name_(name), gpsX_(gpsX), gpsY_(gpsY), buildingHeight_(buildingHeight)
            {}
        void dispBuildingData(Building building);
        string getName() {return name_;};
        float sumGPS() {return gpsX_ + gpsY_;};
        void inputBuilding()
        {
            string name;
            float gpsX;
            float gpsY;
            float buildingHeight;
            
            std::cin >> name;
            gpsX = inputFloat();
            gpsY = inputFloat();
            buildingHeight = inputFloat();
            
            name_ = name;
            gpsX_ = gpsX;
            gpsY_ = gpsY;
            buildingHeight_ = buildingHeight;
        }

        friend bool operator==(Building building1, Building building2)
        {
            return building1.name_ == building2.name_;
        }

        friend bool operator<(Building building1, Building building2)
        {
            return building1.sumGPS() < building2.sumGPS();
        }

        friend ostream &operator<<(std::ostream &out, const Building &building)
        {
            out << building.name_ << " " << building.gpsX_ << " " << building.gpsY_ << " " << building.buildingHeight_;
            return out;
        }

    private:
        string name_;
        float gpsX_;
        float gpsY_;
        float buildingHeight_;
};


void Animal::dispAnimalData(Animal animal)
{
    cout << animal.name_ << " " << animal.weight_ << " " << animal.birthYear_ << " " << animal.id_ << endl;
}

void Building::dispBuildingData(Building building)
{
    cout << building.name_ << " " << building.gpsX_ << " " << building.gpsY_ << " " << building.buildingHeight_ << endl;
}


int main()
{
    Container<Animal> animalContainer;
    Container<Building> buildingContainer;

    // Animal animal1("Stefan", 12.5, 1998, "123456789");
    // Animal animal2("Grzegorz", 12.5, 1998, "123456789");
    // Building building1("Super", 12.5, 12.5, 300);
    // Building building2("wyjątkowy", 12.5, 12.5, 300);
    // animalContainer.addToContainer(animal1);

    // animalContainer.printContainer();

    // cout << "--------------------------------" << endl;

    // animalContainer.addToContainer(animal2);

    // animalContainer.printContainer();

    // cout << "--------------------------------" << endl;

    // animalContainer.removeFromContainer(animal1);

    // animalContainer.printContainer();

    // cout << "-----------------BUDYNKI:---------------" << endl;

    // buildingContainer.addToContainer(building1);
    // buildingContainer.printContainer();

    // cout<<"--------------------------------"<<endl;

    // buildingContainer.addToContainer(building2);
    // buildingContainer.printContainer();

    // cout<<"--------------------------------"<<endl;

    // buildingContainer.removeFromContainer(building1);
    // buildingContainer.printContainer();



    Animal a[4];
    for (int i = 0; i < 4; i++)
    {
        a[i].inputAnimal();
        animalContainer.addToContainer(a[i]);
    }

    Building b[4];
    for (int i = 0; i < 4; i++)
    {
        b[i].inputBuilding();
        buildingContainer.addToContainer(b[i]);
    }

    int idx;
    cin >> idx;
    
    
    animalContainer.removeFromContainer(idx);

    animalContainer.sortContainer();
    buildingContainer.sortContainer();

    animalContainer.dispAllData();
    buildingContainer.dispAllData();
    

}
