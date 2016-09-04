#include<iostream>
#include<cstdlib>
#include<fstream>
#include<windows.h>
#include<vector>
#include<algorithm>
#include<queue>
#include<time.h>
using namespace std;
struct node
{
    string slo;
    string def;
    int tru=1;
    bool operator < (const node &x)const
      {
        if(tru<x.tru)
            return true;
        else
            return false;
      }
};
void dodaj(vector<node> &v)
{
    v.resize(v.size()+1);
    cout<<"Podaj slowo:\n";
    cin>>v[v.size()-1].slo;
    cout<<"Podaj definicje:\n";
    cin>>v[v.size()-1].def;
}
void otworz(vector<node> &v)
{
    fstream plik;
    plik.open("key.txt", ios::in);
    string q;
    while(getline(plik,q))
    {
        string slowo;
        string definicja;
        int trudnosc;
        definicja.resize(q.size());
        slowo.resize(q.size());
        int c=0;
        while(q[c]!=' ')
            c++;
        slowo=q;
        slowo.resize(c);
        int i=0;
        c++;
        while(q[c]!=' ')
        {
            definicja[i]=q[c];
            i++;
            c++;
        }
        definicja.resize(c-1-slowo.size());
       // cout<<slowo<<" "<<definicja;
        c++;
        trudnosc=q[c]-48;
        node n;
        n.slo=slowo;
        n.def=definicja;
        n.tru=trudnosc;
        v.push_back(n);
    }
    plik.close();
}
void zapisz(vector<node> &v)
{
    fstream plik;
    plik.open("key.txt", ios::trunc);
    plik.close();
    plik.open("key.txt", ios::out);
    for(int i=0; i<v.size(); i++)
        plik<<v[i].slo<<" "<<v[i].def<<" "<<v[i].tru<<"\n";
    plik.close();
}
void powtarzaj(vector<node> &v)
{
    cout<<"Ile slow chcesz powtarzac?\n";
    int n,vsize;
    vsize=v.size();
    cin>>n;
    n=min(vsize,n);
    int r;
    for(int i=0; i<n; i++)
    {
        r=rand();
        r%=v.size();
        int d=rand()%2;
        if(d==0)
        {
            cout<<"Podaj definicje slowa: "<<v[r].slo<<"\n";
            string d;
            cin>>d;
            if(d==v[r].def)
            {
                cout<<"Dobrze!\n";
                v[r].tru=max(0,v[r].tru-1);
            }
            else
            {
                cout<<"Zle! Wlasciwa definicja to: "<<v[r].def<<"\n";
                v[r].tru=min(9,v[r].tru+1);
            }
        }
        else
        {
            cout<<"Jakie to slowo: "<<v[r].def<<"\n";
            string d;
            cin>>d;
            if(d==v[r].slo)
            {
                cout<<"Dobrze!\n";
                v[r].tru=max(0,v[r].tru-1);
            }
            else
            {
                cout<<"Zle! Wlasciwe slowo to: "<<v[r].slo<<"\n";
                v[r].tru=min(9,v[r].tru+1);
            }
        }
    }
    Sleep(2000);
    }

int main()
{
    srand(time(NULL));
    int z;
    vector<node> v;
    v.resize(0);
    otworz(v);
  //  for(int i=0; i<v.size(); i++)
  //          cout<<v[i].slo<<" "<<v[i].def<<" "<<v[i].tru<<"\n";
    while(true)
    {
        cout<<"1.Dodaj nowe slowo\n2.Zamknij\n3.Powtarzaj slowka\n";
        z=getchar();
        z-=48;
        switch(z)
        {
        case 1:
            dodaj(v);
            break;
        case 2:
            if(v.size()!=0)
                sort(v.begin(), v.end());
            zapisz(v);
            return 0;
            break;
        case 3:
            powtarzaj(v);
            break;
        }
        system("cls");
    }
    return 0;
}

