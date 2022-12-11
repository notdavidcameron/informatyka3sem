#include<iostream>
#include<math.h>
using namespace std;

float inputvej()
{
    float vej;
    cin>>vej;
    while(cin.fail())
    {
        //cout<<"oj vej"<<endl;
        cin.clear();
        cin.ignore(1,'\n');
        cin>>vej;
    };
    
    return vej;
}

bool inputznak()
{
    char sign;
    bool warunek = true;
    while(warunek)
    {
        //cout << "znak" << endl;
        cin >> sign;
        if (sign == '-' || sign == '+') warunek = false;
    }
    
    if(sign == '-') return false;
    else return true;
}

int inputwykladnik()
{
    int wyk;
    cin>>wyk;
    while(cin.fail())
    {
        //cout << "wyk"<< endl;
        cin.clear();
        cin.ignore(1,'\n');
        cin>>wyk;
    }
    
    return wyk;
}

float inputmantysa()
{
    float man;
    cin>>man;
    while(cin.fail())
    {
        //cout << "mantysa" << endl;
        cin.clear();
        cin.ignore(1,'\n');
        cin>>man;
    }
    
    return man;
}

class IEEE
{
    private:
        bool znak_;
        int wykladnik_;
        float mantysa_;
    public:
        IEEE(bool znak, int wykladnik, float mantysa):
        znak_(znak), wykladnik_(wykladnik), mantysa_(mantysa)
        {
             //znak_ = inputznak();
             znak_ = znak;
    
             //wykladnik_ = inputwykladnik();
             wykladnik_ = wykladnik;
    
             //mantysa_ = inputmantysa();
             mantysa_ = mantysa;
             if(wykladnik_ == 0)
             {
                 znak_ = true;
                 wykladnik_ = 0;
                 mantysa_ = 0;
             }
        }
        IEEE(float vej)
        {
            if(!vej == 0)
            {
                int e = 0;
                znak_ = vej > 0;
                if(!znak_)vej*=(-1);
                float vejtemp = vej;
                if(vej>1)
                {
                    while(static_cast<int>(vejtemp)!=1)//znajdywanie e
                    {
                        vejtemp = vej;
                        vejtemp/=pow(2,e);
                        e++;
                    }
                }
                else if(vej<1)
                {
                    while(static_cast<int>(vejtemp)!=1)//normalizacja mantysy
                    {
                        vejtemp = vej;
                        vejtemp*=pow(2,e);
                        e++;
                    }
                }
                mantysa_ = vejtemp;
                wykladnik_ = e + 127 - 1;
            }
            else
            {
                znak_ = true;
                wykladnik_ = 0;
                mantysa_ = 0;
            //    cout<<"xd"<<endl;
            }
        }
        
        void operator +=(const IEEE &liczba)
        {
            int tempwyk = wykladnik_;
            //cout<<liczba.wykladnik_<<endl;
            int diffwyk= 0;
            float pommanty;
            int norma = 0;
            bool znaktemp;
            znaktemp = (znak_==liczba.znak_)? true : false;
            //cout<<znak_<<" ";
            //cout << wykladnik_;
            if(wykladnik_!=liczba.wykladnik_)
            {
                if(wykladnik_>liczba.wykladnik_)
                {
                    diffwyk = wykladnik_-liczba.wykladnik_;//o ile przesunąć mantysę 
                    pommanty = liczba.mantysa_/pow(2,diffwyk);
                    if(znaktemp)
                        mantysa_ = mantysa_+pommanty;
                    else 
                        mantysa_ = mantysa_-pommanty;
                }
                else if(wykladnik_<liczba.wykladnik_)
                {
                    diffwyk = liczba.wykladnik_-wykladnik_;
                    pommanty=mantysa_/pow(2,diffwyk);
                    if(znaktemp)
                        mantysa_ = pommanty+liczba.mantysa_;
                    else 
                    {
                        mantysa_ = liczba.mantysa_-pommanty;
                        znak_ = liczba.znak_;
                    }
                    tempwyk= liczba.wykladnik_;
                }
            }
            else
            {
                if(znak_)
                    mantysa_ = mantysa_+liczba.mantysa_;
                else 
                    mantysa_ = mantysa_-liczba.mantysa_;
            }
            
            if(mantysa_<0)
            mantysa_*=-1;
            float hwdp = mantysa_;
            if(mantysa_>1)
            {
                while(static_cast<int>(hwdp)!=1)//normalizacja mantysy
                {
                    --norma;
                    hwdp = mantysa_;
                    //cout<<static_cast<int>(mantysa_)<<" "<<endl;
                    hwdp*=pow(2,norma);
                }
            }
            else if(mantysa_<1&&mantysa_!=0)
                {
                    while(static_cast<int>(hwdp)!=1)//normalizacja mantysy
                    {
                        ++norma;
                        hwdp = mantysa_;
                        //cout<<static_cast<int>(mantysa_)<<" "<<endl;
                        hwdp*=pow(2,norma);
                    }
                }
            mantysa_=hwdp;
            wykladnik_ = tempwyk - norma;
            //cout<<wykladnik_<<endl;
        }
        void operator -=(const IEEE &liczba)
        {
            int tempwyk = wykladnik_;
            int diffwyk= 0;
            float pommanty;
            int norma = 0;
            if(znak_&&liczba.znak_)
            {
                if(wykladnik_>liczba.wykladnik_)
                {
                    //cout << mantysa_ << " " << liczba.mantysa_<< endl;
                    diffwyk = wykladnik_-liczba.wykladnik_;
                    pommanty = liczba.mantysa_/pow(2,diffwyk);
                    //cout<< pommanty << endl;
                    mantysa_ = (-1)*mantysa_ + pommanty;
                    //cout << mantysa_ << " " << "po" << endl;
                }
                else if(wykladnik_<liczba.wykladnik_)
                {
                    diffwyk = liczba.wykladnik_-wykladnik_;
                    pommanty = mantysa_/pow(2,diffwyk);
                    mantysa_ = liczba.mantysa_ + (pommanty*(-1));
                    znak_=false;
                    tempwyk= liczba.wykladnik_;
                }
                else if(wykladnik_ == liczba.wykladnik_)
                {
                    mantysa_ = mantysa_ + (liczba.mantysa_*(-1));
                }
            }
            else if(!znak_&&!liczba.znak_)
            {
                if(wykladnik_>liczba.wykladnik_)
                {
                    diffwyk = wykladnik_-liczba.wykladnik_;
                    pommanty = liczba.mantysa_/pow(2,diffwyk);
                    mantysa_ = mantysa_ + (pommanty*(-1));
                }
                else if(wykladnik_<liczba.wykladnik_)
                {
                    diffwyk = liczba.wykladnik_-wykladnik_;
                    pommanty = mantysa_/pow(2,diffwyk);
                    mantysa_ = liczba.mantysa_+(pommanty*(-1));
                    znak_=true;
                    tempwyk= liczba.wykladnik_;
                }
                else if(wykladnik_ == liczba.wykladnik_)
                {
                    mantysa_ = liczba.mantysa_ + (mantysa_*(-1));
                }
            }
            else if(znak_!=liczba.znak_)
            {
                if(wykladnik_>liczba.wykladnik_)
                {
                    diffwyk = wykladnik_-liczba.wykladnik_;
                    pommanty = liczba.mantysa_/pow(2,diffwyk);
                    mantysa_ = mantysa_+pommanty;
                }
                else if(wykladnik_<liczba.wykladnik_)
                {
                    diffwyk = liczba.wykladnik_-wykladnik_;
                    pommanty = mantysa_/pow(2,diffwyk);
                    mantysa_ = liczba.mantysa_+pommanty;
                    tempwyk= liczba.wykladnik_;
                }
                else if(wykladnik_ == liczba.wykladnik_)
                {
                    mantysa_ = mantysa_ + liczba.mantysa_;
                }
                
            }
             if(mantysa_<0)
                mantysa_*=-1;
                float hwdp = mantysa_;
                //cout << tempwyk << " " << endl;
                if(mantysa_>1)
            {
                while(static_cast<int>(hwdp)!=1)//normalizacja mantysy
                {
                    --norma;
                    hwdp = mantysa_;
                    //cout<<static_cast<int>(mantysa_)<<" "<<endl;
                    hwdp*=pow(2,norma);
                    //cout<< hwdp << endl;
                }
            }
            else if(mantysa_<1&&mantysa_!=0)
                {
                    while(static_cast<int>(hwdp)!=1)//normalizacja mantysy
                    {
                        ++norma;
                        hwdp = mantysa_;
                        //cout<<static_cast<int>(mantysa_)<<" "<<endl;
                        hwdp*=pow(2,norma);
                        
                    }
                }
                mantysa_=hwdp;
                wykladnik_ = tempwyk - norma;
        }
        friend ostream& operator<<(std::ostream& out, const IEEE& toDisp);
        friend IEEE operator +(const IEEE& x1, const IEEE& x2);
        friend IEEE operator -(const IEEE& x1, const IEEE& x2);
};

std::ostream& operator<<(std::ostream& out, const IEEE& toDisp)
{
    float liczb = 1.0;
    liczb = toDisp.mantysa_*pow(2, toDisp.wykladnik_-127);
    if(toDisp.znak_)
    {
        return out << liczb;
    }
    else if(!liczb)
    {
        return out << liczb;
    }
    else
    {
        return out <<'-'<< liczb;
    }
}

IEEE operator +(const IEEE& x1, const IEEE& x2)
{
    IEEE temp = x1;
    temp+=x2;
    return temp;
}

IEEE operator -(const IEEE& x1, const IEEE& x2)
{
    IEEE temp = x1;
    temp-=x2;
    return temp;
}


int main() 
{
    bool zn;
    int wy;
    float ma;
    float vej;
    zn = inputznak();
    wy = inputwykladnik();
    ma = inputmantysa();
    IEEE x0(zn ,wy, ma);
    //cout << x0 << endl;
    zn = inputznak();
    wy = inputwykladnik();
    ma = inputmantysa();
    IEEE x1(zn ,wy, ma);
    //cout << x1 << endl;
    vej = inputvej();
    IEEE x2(vej);
    //cout << x2 << endl;
    vej = inputvej();
    IEEE x3(vej);
    //cout << x3 << endl;
    x0 += x1;
    x3 -= x2;
    IEEE x4 = x1 + x3;
    IEEE x5 = x4 - x2;
    
    cout << x0 << " " << x1 << " " << x2 << " " << x3 << " " << x4 << " " << x5 << endl;
    
    return 0;
}
