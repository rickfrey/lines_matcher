#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sstream>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QFile>
#include <algorithm>
#include <stdlib.h>
#include"bildinfo.h"
vector<int> people;
vector<int> combination;
vector<vector <int> > reales_Set;
std::vector<Bildinfo> BildInfoVector;   // Vektor vom Typ Bildinfo!!!!! an jeder Stelle des
// Vektors steht eine Objekt von Bildinfo!!!!
int Bildlaufvariable;
using namespace std;
//typedef <vector<vector<double> > Vektordef;



// In der Funktion error_calc wird der Fehler der aktuellen Kombination der synthetischen Linien mit den realen Linien berechnet
void error_calc(){
    // Der Vektor "combination" stellt die Beziehung zwischen den Vektoren "BildInfoVec" und "reales_Set" her

    // "statischer" Vektor ist immer der kleinere!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // Fall 1: synthetisches Set ist kleiner als reales Set:
    float Fehler=0;
    //vector<float> Fehlervec;// Fehlervektor!! Fehler für jede Setkombination speichern, niedrigsten Wert an Objekt übergeben!
    if(BildInfoVector[Bildlaufvariable].getLinienanzahl() < reales_Set.size())//Stelle des Bildinfovectors muss fortlaufend sein (muss noch geändert werden)
    {
        //Fehler berechnen und in Bildobjekt speichern
        for(int x=0; x<BildInfoVector[Bildlaufvariable].getLinienanzahl();x++)
        {
            for(int z=0;z<4;z++) // Alle 4 Parameter durchlaufen
            {
                //int test1=BildInfoVector[Bildlaufvariable].getLinieneintrag(x,z);
                //int test2=reales_Set[permutation[x]][z];// permutation[5] gibt es z.B. gar nicht!!! FEHLER!!!!!!
                // combination-Vektor und permutation-Vektor beide mit 0 anfangen lassen (damit ich mir das (-1) sparen kann!!!!
                //int test3= BildInfoVector[Bildlaufvariable].getLinieneintrag(x,z)-reales_Set[permutation[x]][z];
                //int test4= permutation[x];
                Fehler = Fehler + abs(BildInfoVector[Bildlaufvariable].getLinieneintrag(x,z) - reales_Set[combination[x]][z]);
                //int blub44=0;
            }
        }

        // Mittelwert für Fehler dieser Kombination berechnen
        Fehler=Fehler/BildInfoVector[Bildlaufvariable].getLinienanzahl();//Mittelwert für die aktuelle Kombination
        //int blub22=BildInfoVector[Bildlaufvariable].getFehler();
        //int blub23=0;

        // Wenn Fehler kleiner als in BildInfoVector für aktuelles Bildobjekt gespeicherter Fehler dann Fehler aktualisieren
        if(Fehler < BildInfoVector[Bildlaufvariable].getFehler())
        {
            BildInfoVector[Bildlaufvariable].setFehler(Fehler);// es wird jedes Mal überprüft ob aktueller Fehler kleiner ist als alle vorigen (nur dann wird er an Objekt übergeben)
            //int blub34=0;
        }
        float testx=BildInfoVector[Bildlaufvariable].getFehler();
        //int blub=0;
    }

    // Fall 2: Gleiche Anzahl an Linien (==) (eigentlich egal welcher Fall) oder oder synthetisches Set größer als reales Set
    else if(BildInfoVector[Bildlaufvariable].getLinienanzahl() >= reales_Set.size())
    {
        // Fehler berechnen und in Bildobjekt speichern
        // Da reales_Set kleiner ist als Bildinfovektor[xy] nur bis reales_Set.size()!!!
        for(int x=0; x<reales_Set.size();x++)
        {
            for(int z=0;z<4;z++) // Alle 4 Parameter durchlaufen
            {
                Fehler=Fehler + abs(reales_Set[x][z] - BildInfoVector[Bildlaufvariable].getLinieneintrag(combination[x],z) );//m=permutation[x] getLinieneintrag(m,z)
                //int blub33=0;
            }
        }

        // Mittelwert
        Fehler=Fehler/reales_Set.size();
        if(Fehler < BildInfoVector[Bildlaufvariable].getFehler())
        {
            BildInfoVector[Bildlaufvariable].setFehler(Fehler);
        }
    }
}

// In dieser Funktion werden nacheinander alle Kombinationen für k Zahlen aus dem Vektor "people" (in dem die Zahlen 0 bis n-1 sind) berechnet
void calc_all_combinations(int offset, int k) {
    if (k == 0) { //
        cout << "Kombination = [";
        for(int komb_len = 0; komb_len < combination.size(); komb_len++){
            cout << combination[komb_len] << " ";
        }
        cout << "]" << endl;
        error_calc();
        return;
    }
    for (int i = offset; i <= people.size() - k; ++i) { // 3. Schleife von 0 bis (n-k)
        combination.push_back(people[i]); // 4. Vektor "combination": i-te Stelle wird mit people[i] gefüllt
        vector<int> blub = combination;
        //cout<<"Test: people["<<i<<"]= "<<people[i]<<endl;
        //cout<<"Test: combination["<<i<<"]= "<<combination[i]<<endl;
        calc_all_combinations(i+1, k-1);
        combination.pop_back(); // pop_back verkleinert Vektor um eine Stelle
    }
    // In People sind immernoch die n Zahlen des vorigen sets! Nach allen Kombinationen muss people gelöscht und neu eingelesen werden!!!
}
int main ( int argc, char *argv[] )
{
    // Textdatei öffnen
    QFile file("Eigenschaften.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;
    QTextStream in(&file);
    while (!in.atEnd()) {

        // Jeweils eine Zeile auslesen so lange Daten in Datei und bestimmen wie viele Spalten in aktueller Zeile
        QString line = in.readLine();
        int numOfCol = line.count(QLatin1Char(' '));
        numOfCol++; // Anzahl der Spalten = Anzahl Leerzeichen +1

        // Wenn 6 Spalten: Bildobjekt anlegen und Zeile in Posenvektor speichern:
        if(numOfCol==6)
        {
            //   QString Objektname= QString("Bild%1").arg(k);
            // k++;
            Bildinfo bi; //neues Bildobjekt anlegen
            vector<float> posenvektor;
            QStringList list1 = line.split(" ");
            for(int i = 0; i < list1.size(); ++i)
            {
                posenvektor.push_back(list1.at(i).toFloat());
            }
            bi.setPosenvektor(posenvektor);
            //int Poseneintrag=bi.getPoseneintrag();
            //cout<<"Eintrag aus Posenvektor: "<<Poseneintrag<<endl;
            BildInfoVector.push_back(bi);   // Objekt bi wird an aktuell letzte Position des Vektors BildInfoVector geschrieben
        }

        // Wenn 4 Spalten: Einträge an Linienvektor des aktuellen Objekts anhängen:
        int m=0,p; // Vektorlaufvariable
        if(numOfCol==4)
        {
            vector<int> linienparameter;
            QStringList list1 = line.split(" ");
            for(int i = 0; i < list1.size(); ++i)
            {
                linienparameter.push_back(list1.at(i).toInt());
            }

            // Hier wird die Memberfunktion "addLinienvektor" aufgerufen und eine Zeile angehängt
            // Anschließend wird das an die passende Stelle von BildInfoVector geschrieben
            BildInfoVector.at(BildInfoVector.size()-1).addLinienvektor(linienparameter);
        }
        //cout<<line<<endl;
    }
    file.close();
    float test=BildInfoVector[0].getPoseneintrag(0);
    cout<<"Poseneintrag[0]= "<< test << endl;
    int test2=BildInfoVector[0].getLinieneintrag(3,2);
    cout<<"Linieneintrag[3][2]= "<<test2<<endl;
    cout<<"Linienanzahl= "<<BildInfoVector[0].getLinienanzahl();
    ///////////////
    //      1. k und n ermitteln
    //      2. Alle Permutationen berechnen (gibt an welche Linien miteinander verglichen werden)
    //      3. in Schleife mit jeder einzelnen Permutation: Berechnung eines Fehlers für jede Linie
    //         => Addieren der Fehler aller Linien dieser Permutation, anschließend durch Anzahl teilen
    //            (Mittelwert)
    //      4. Gesamtfehler des Liniensets in jeweiligem Objekt speichern
    ////////////

    // reales Linienset laden
    for(int i = 0; i < 6; i++)// es werden 6 Zeilen reserviert
    {
        vector<int> row;
        reales_Set.push_back(row);
    }
    reales_Set[0].push_back(100); reales_Set[0].push_back(300); reales_Set[0].push_back(25); reales_Set[0].push_back(200);
    reales_Set[1].push_back(100); reales_Set[1].push_back(400); reales_Set[1].push_back(28); reales_Set[1].push_back(220);
    reales_Set[2].push_back(200); reales_Set[2].push_back(300); reales_Set[2].push_back(90); reales_Set[2].push_back(50);
    reales_Set[3].push_back(350); reales_Set[3].push_back(300); reales_Set[3].push_back(-15); reales_Set[3].push_back(230);
    reales_Set[4].push_back(350); reales_Set[4].push_back(400); reales_Set[4].push_back(-20); reales_Set[4].push_back(240);
    reales_Set[5].push_back(124); reales_Set[4].push_back(523); reales_Set[4].push_back(-23); reales_Set[4].push_back(856);

    // Größen des synthetischen Linienvektors und des reales_Set-Vektors vergleichen um n und k zu bestimmen
    for (Bildlaufvariable=0; Bildlaufvariable<BildInfoVector.size();Bildlaufvariable++)
    {
        int n, k;

        if(BildInfoVector[Bildlaufvariable].getLinienanzahl() > reales_Set.size())
        {
            n=BildInfoVector[Bildlaufvariable].getLinienanzahl();
            k=reales_Set.size();
        }
        else if (BildInfoVector[Bildlaufvariable].getLinienanzahl() < reales_Set.size())
        {
            n=reales_Set.size();
            k=BildInfoVector[Bildlaufvariable].getLinienanzahl();
        }
        else if (BildInfoVector[Bildlaufvariable].getLinienanzahl() == reales_Set.size())
        {
            n=reales_Set.size(); // beide gleich groß!
            k=reales_Set.size();
        }
        cout<<"k= "<<k<<endl;
        cout <<"n= "<<n<<endl;

        // Vektor "people" mit 0,2,3,4...bis n-1 füllen
        for (int i = 0; i < n; ++i) {
            people.push_back(i);
            //int testblubblub = people[i];
            //cout << "Vektor people: " << people[i];
        }

        // Aufruf der Funktion calc_all_combinations mit k als Parameter
        calc_all_combinations(0, k);
        people.clear();
    }
    //TEST:
    //    cout<< "Geringster durchschnittlicher Fehler (pro Linie) des ersten sets: " <<BildInfoVector[0].getFehler()<<endl;
    //    cout<< "Geringster durchschnittlicher Fehler (pro Linie) des zweiten sets: "<<BildInfoVector[1].getFehler()<<endl;
    //    cout<< "Geringster durchschnittlicher Fehler (pro Linie) des dritten sets: "<<BildInfoVector[2].getFehler()<<endl;

    // Suchen des Objekts mit kleinstem Fehler
    int SetMitKleinstemFehler = 0, relativerFehler = 1000;
    for(int m = 0; m <= BildInfoVector.size(); m++)
    {
        if(BildInfoVector[m].getFehler() < relativerFehler)
        {
            relativerFehler = BildInfoVector[m].getFehler();
            SetMitKleinstemFehler = m;
        }
    }

    // Ausgabe der Pose mit dem geringsten Fehler
    cout << "Set mit geringster Pose ist Set Nummer: " << SetMitKleinstemFehler << std::endl;
    cout << "Pose: " << endl << "x=" << BildInfoVector[SetMitKleinstemFehler].getPoseneintrag(0) << endl << "y=" << BildInfoVector[SetMitKleinstemFehler].getPoseneintrag(1) << endl;
    cout << "z=" << BildInfoVector[SetMitKleinstemFehler].getPoseneintrag(2) << endl << "roll=" << BildInfoVector[SetMitKleinstemFehler].getPoseneintrag(3) << endl;
    cout << "pitch=" << BildInfoVector[SetMitKleinstemFehler].getPoseneintrag(4) << endl << "yaw=" << BildInfoVector[SetMitKleinstemFehler].getPoseneintrag(5) << endl;

    return 0;
}

