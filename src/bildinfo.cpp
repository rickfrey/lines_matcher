#include<vector>
#include<iostream>
#include<string>
#include"bildinfo.h"

using namespace std;

void Bildinfo::addLinienvektor(vector<int> vektor)
{
    // Hier immer eine neue Zeile zum Linienvektor dazu
    // neue Zeile resizen (Linienvektor[aktueller Zeile].resize(4))
    // anschließend die Werte des übergebenen Vektors in Linienvektor (Membervariable) speichern

    this->Zeilenanzahl++;//ändert die aktuelle Anzahl der Zeilen
    //Linienvektor.push_back(vektor);

    std::vector<int>* clone = new std::vector<int>();
    for(int i = 0; i< vektor.size(); i++)
        clone->push_back(vektor.at(i));

    Linienvektor.push_back(clone);
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
    return this->Linienvektor[1]->at(1);
}


Bildinfo::Bildinfo()
{
this->Zeilenanzahl=0;//Am Anfang hat Vektor 0 Zeilen
}
Bildinfo::~Bildinfo()
{}
