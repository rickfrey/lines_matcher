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
    Linienvektor.push_back(vektor);


}
void Bildinfo::setPosenvektor(vector<float> vektor)
{
    this->Posenvektor=vektor;
}


float Bildinfo::getPoseneintrag(int eintrag)
{
    return this->Posenvektor[eintrag];
}

int Bildinfo::getLinieneintrag(int liniennummer, int parameter)
{
    return this->Linienvektor[liniennummer][parameter];
}

int Bildinfo::getLinienanzahl()
{
    return Linienvektor.size();
}

void Bildinfo::setFehler(float Fehler)
{
    this->Fehler=Fehler;
}

float Bildinfo::getFehler()
{
    return this->Fehler;
}


Bildinfo::Bildinfo()
{
    this->Zeilenanzahl=0;   // Am Anfang hat Vektor 0 Zeilen
    this->Fehler=100000;    // Initialisierung von Fehler (muss auf jeden Fall größer sein als die erwarteten Werte)
}
Bildinfo::~Bildinfo()
{}
