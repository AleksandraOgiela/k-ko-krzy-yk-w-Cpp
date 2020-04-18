#include <iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
using namespace std;

void Rys_planszy(char tab[]);
void Ruch_czlowieka(char,char tab[]);
bool Spr_wygranej(char tab[], char c);
bool Spr_plansze(char tab[]);
int min_max(char tab[],char c, int poziom);
char znak_kom, znak;

int main()
{

    char t[] = {' ','1','2','3','4','5','6','7','8','9'};
    cout<<"\n GRA KOLKO I KRZYZYK \n"<<endl;
    Rys_planszy(t);
    char wybor;
    do
    {
        cout<<"Kto zaczyna? k-komputer, g-gracz:"<<endl;
        cin>>wybor;
        if((wybor!='k')&&(wybor != 'g')&&(wybor != 'G')&&(wybor != 'K'))
            cout<<"Wybrales niepoprawny znak."<<endl;
    }while((wybor!='k')&&(wybor != 'g')&&(wybor != 'G')&&(wybor != 'K'));


    do
    {
        cout<<"Wybierz znak: \n  o lub x "<<endl;
        cin>>znak;
       if((znak !='o') && (znak!='x') && (znak!='O') && (znak!='X'))
       {
        cout<<"Nie wybrales znaku! "<<endl;
        }
    }while((znak !='o') && (znak!='x')&& (znak!='O') && (znak!='X'));

    cout<<"Wybrales "<<znak<<endl;
    znak_kom = (znak == 'x'|| znak== 'X') ? 'o' : 'x';
    for(int i=1;i<=9;i++) t[i]=' ';


    if(wybor=='g'||wybor=='G')
    {
        cout<<"Gre zczyna gracz"<<endl;
    }
    else if(wybor=='k'||wybor=='K')
    {
         cout<<"Gre zaczyna komputer"<<endl;
         t[5] = znak_kom;
         Rys_planszy(t);
    }

     do
    {
       Ruch_czlowieka(znak,t);
       Rys_planszy(t);

       if(Spr_wygranej(t,znak)) break;

       else if(Spr_plansze(t))
       {
         cout<<"Remis - koniec gry. Brak miejsca na planszy."<<endl;
         break;
       }
        else
         min_max(t,znak_kom,0);
         Rys_planszy(t);


        if(Spr_wygranej(t,znak_kom))
        {
         cout<<"Koniec gry!!! Wygral komputer."<<endl;
         break;
        }
          else if(Spr_plansze(t))
        {
         cout<<"Remis - koniec gry. Brak miejsca na planszy."<<endl;
         break;
        }


    }while(true);




    system("pause");
    return 0;
}

void Rys_planszy(char tab[])
{
for(int i=1;i<=9;i++)
    {
        cout<<setw(2)<<tab[i]<<setw(2);
        if(i%3)  cout<<"|";
        else if(i != 9) cout << "\n---+---+---\n";
        else  cout <<"\n-----------\n"<< endl;
    }

}
void Ruch_czlowieka(char z, char tab[])
{
    bool zla_pozycja;
    bool zla_pozycja2;
    do
    {
    zla_pozycja = true;
    zla_pozycja2=true;
    int i=0;
    cout<<"Podaj pozycje pola"<<endl;
    cin>>i;

    if(i>=1 && i<=9)
    {
        if(tab[i]== ' ')
        {
            tab[i]=z;
        }
        else
        {
            cout<<"Ta pozycja nie jest pusta. Wybiesz inna pozycje"<<endl;
            zla_pozycja=false;
        }
    }
    else
     {
         cout<<"Ten numer pozycji nie jest aktywny. Wybierz pozycje z zakresu 1-9."<<endl;
         zla_pozycja2=false;
     }

    }while(!zla_pozycja || !zla_pozycja2);

}
    bool Spr_wygranej(char tab[], char c)
    {
        int i;
        for(i=1;i<=7;i+=3)
            {
              if((tab[i]==c )&& (tab[i+1]==c) && (tab[i+2]==c)) return true;
            }
        for(i=1;i<=3;i++)
            {
              if((tab[i]==c )&& (tab[i+3]==c)&& (tab[i+6]==c))  return true;
            }
        if((tab[1]==c) && (tab[5]==c) && (tab[9]==c))  return true;
        if((tab[3]==c) && (tab[5]==c) && (tab[7]==c))  return true;

        return false;
    }
bool Spr_plansze(char tab[])
{
    int licz=0;
    for(int i=1;i<=9;i++)
    {
        if(tab[i]==' ')
            licz++;
    }
      if(licz==0) return true;
      else return false;
}
int min_max(char tab[],char c, int poziom)
{
    int k,licznik=0;



    for(int i=1;i<=9;i++)
       {
           if(tab[i]==' ')
        {
            tab[i]=c;
            k=i;
            licznik++;
            bool spr = Spr_wygranej(tab,c);

            tab[i]= ' ';

            if(spr)
            {
                if(!poziom) tab[i]=c;
                return (c == znak_kom) ? -1 : 1;
            }
        }
       }


    if(licznik ==1)
    {
        if(!poziom) tab[k] = c;
        return 0;
    }



    int r,ruch_max;

    ruch_max = (c==znak_kom) ? 2 : -2;

    for(int i=1;i<=9;i++)
       {

         if(tab[i]== ' ')
        {
            tab[i] = c;
            r = min_max(tab,(c == znak_kom) ? znak : znak_kom,poziom +1);


            tab[i] = ' ';

            if(((c == znak_kom) && (r<ruch_max)) || ((c == znak) && (r>ruch_max)))
            {
                ruch_max = r;
                k = i;
            }

        }
       }
    if(!poziom) tab[k] = c;

    return ruch_max;

}
