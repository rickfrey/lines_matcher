#include<vector>
#include<iostream>
#include<string>
#include"bildinfo.h"

using namespace std;

void addLinienvektor(vector<int> vektor)
{
    // Hier immer eine neue Zeile zum Linienvektor dazu
    // neue Zeile resizen (Linienvektor[aktueller Zeile].resize(4))
    // anschließend die Werte des übergebenen Vektors in Linienvektor (Membervariable) speichern

    this->Zeilenanzahl=Zeilenanzahl+1;//ändert die aktuelle Anzahl der Zeilen
    this->Linienvektor.resize(Zeilenanzahl);
    this->Linienvektor[this->Zeilenanzahl -1].resize(4); // aktuelle Zeile soll 4 Spalten haben
    for(int i=0;i<4;i++)
    {
        this->Linienvektor[Zeilenanzahl - 1][i]=vektor[i];// übergebener Vektor wird in neue Zeile übernommen
    }
}
void Bildinfo::setPosenvektor(vector<int> vektor)
{
this->Posenvektor=vektor;
}


int Bildinfo::getPoseneintrag()
{
    return this->Posenvektor[5];
}

int Bildinfo::getLinieneintrag()
{
    return this->Linienvektor[1][1];
}


Bildinfo::Bildinfo()
{
this->Zeilenanzahl=0;//Am Anfang hat Vektor 0 Zeilen
}
Bildinfo::~Bildinfo()
{}
