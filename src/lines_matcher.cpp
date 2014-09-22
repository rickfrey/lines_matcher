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
#include <QTime>
#include <algorithm>
#include <stdlib.h>
#include"bildinfo.h"
#include <cmath>
#include <queue>

vector<int> people;
vector<int> combination;
vector<vector <int> > reales_Set;
std::vector<Bildinfo> BildInfoVector;   // Vektor vom Typ Bildinfo!!!!! an jeder Stelle des
// Vektors steht eine Objekt von Bildinfo!!!!
int Bildlaufvariable;
QTime myTimer;
QTime myTimer2;
using namespace std;
//typedef <vector<vector<double> > Vektordef;


/////////////  Werte definieren  /////////////

// Auflösung der Handkamerabilder (Pixel). Hier kann auch das Seitenverhältnis (bzw. senkrechter, waagerechter Kamerasensor) verändert werden
int Rxi = 2048 , Reta = 1536 , Thetamax = 90;
int lmax = sqrt( pow(Rxi,2) + pow(Reta,2) );
//////////////////////////////////////////////


// In der Funktion error_calc wird der Fehler der aktuellen Kombination der synthetischen Linien mit den realen Linien berechnet
// Der Vektor "combination" stellt die Beziehung zwischen den Vektoren "BildInfoVec" und "reales_Set" her
// "statischer" Vektor ist immer der kleinere!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void error_calc(){
    myTimer.restart();

    float Fehler = 0, FehlerTheta=0, FehlerXi=0, FehlerEta=0, FehlerL=0;

    // Fall 1: synthetisches Set ist kleiner als reales Set:
    if(BildInfoVector[Bildlaufvariable].getLinienanzahl() < reales_Set.size())//Stelle des Bildinfovectors muss fortlaufend sein (muss noch geändert werden)
    {
        //Fehler berechnen und in Bildobjekt speichern
        for(int x=0; x<BildInfoVector[Bildlaufvariable].getLinienanzahl();x++)
        {
            for(int z=0;z<4;z++) // Alle 4 Parameter durchlaufen
            {
                // Wert für Theta: ΔΘi/90
                if(z==0){
                    FehlerTheta = abs(BildInfoVector[Bildlaufvariable].getLinieneintrag(x,z) - reales_Set[combination[x]][z]);
                    Fehler = Fehler + (FehlerTheta/90);
                }

                // Wert für mxi,i: Δmxi,i/Rxi
                else if(z==1){
                    FehlerXi = abs(BildInfoVector[Bildlaufvariable].getLinieneintrag(x,z) - reales_Set[combination[x]][z]);
                    Fehler = Fehler + (FehlerXi/Rxi);
                }

                // Wert für Theta: Δmxi,i/Reta
                else if(z==2){
                    FehlerEta = abs(BildInfoVector[Bildlaufvariable].getLinieneintrag(x,z) - reales_Set[combination[x]][z]);
                    Fehler = Fehler + (FehlerEta/Reta);
                }

                // Wert für Theta: Δl,i/lmax
                else if(z==3){
                    FehlerL = abs(BildInfoVector[Bildlaufvariable].getLinieneintrag(x,z) - reales_Set[combination[x]][z]);
                    Fehler = Fehler + (FehlerL/lmax);
                }
            }
        }
        // Gütewert Grel berechnen (ab hier ist Fehler eigentlich die falsche Bezeichnung)
        Fehler = Fehler / BildInfoVector[Bildlaufvariable].getLinienanzahl();
        Fehler = (4 - Fehler) / ( 4 );

        // Wenn Fehler größer als in BildInfoVector für aktuelles Bildobjekt gespeicherter Fehler dann Fehler aktualisieren
        if(Fehler > BildInfoVector[Bildlaufvariable].getFehler())
        {
            BildInfoVector[Bildlaufvariable].setFehler(Fehler);// es wird jedes Mal überprüft ob aktueller Fehler größer ist als alle vorigen (nur dann wird er an Objekt übergeben) (für jedes Set wird nur der kleinste Fehler gespeichert)
        }

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

                if(z==0){
                    FehlerTheta = abs(reales_Set[x][z] - BildInfoVector[Bildlaufvariable].getLinieneintrag(combination[x],z) );
                    Fehler = Fehler + (FehlerTheta/90);
                }

                if(z==1){
                    FehlerXi= abs(reales_Set[x][z] - BildInfoVector[Bildlaufvariable].getLinieneintrag(combination[x],z) );
                    Fehler = Fehler + (FehlerXi/Rxi);
                }

                if(z==2){
                    FehlerEta = abs(reales_Set[x][z] - BildInfoVector[Bildlaufvariable].getLinieneintrag(combination[x],z) );
                    Fehler = Fehler + (FehlerEta/Reta);
                }

                if(z==3){
                    FehlerL = abs(reales_Set[x][z] - BildInfoVector[Bildlaufvariable].getLinieneintrag(combination[x],z) );
                    Fehler = Fehler + (FehlerL/lmax);
                }
            }
        }

        // Gütewert Grel berechnen (ab hier ist Fehler eigentlich die falsche Bezeichnung)
        Fehler = Fehler / BildInfoVector[Bildlaufvariable].getLinienanzahl();
        Fehler = (4 - Fehler) / ( 4 );

        if(Fehler > BildInfoVector[Bildlaufvariable].getFehler())
        {
            BildInfoVector[Bildlaufvariable].setFehler(Fehler);
        }
    }

}

// In dieser Funktion werden nacheinander alle Kombinationen für k Zahlen aus dem Vektor "people" (in dem die Zahlen 0 bis n-1 sind) berechnet
void calc_all_combinations(int offset, int k) {

    if (k == 0) { //
        //        cout << "Kombination = [";
        //        for(int komb_len = 0; komb_len < combination.size(); komb_len++){
        //            cout << combination[komb_len] << " ";
        //        }
        //        cout << "]" << endl;
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
    QFile file("TestLinesmatcher.txt");
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
    //    int test2=BildInfoVector[0].getLinieneintrag(3,2);
    //    cout<<"Linieneintrag[3][2]= "<<test2<<endl;
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
    // EINSTELLEN, WIE VIELE ZEILEN RESERVIERT WERDEN MÜSSEN!!!!!!!!! (NACHDEM LINIEN AUS HANDYBILD EXTRAHIERT WURDEN)
    for(int i = 0; i < 2; i++)// es werden 2 Zeilen reserviert
    {
        vector<int> row;
        reales_Set.push_back(row);
    }
    reales_Set[0].push_back(-10); reales_Set[0].push_back(300); reales_Set[0].push_back(200); reales_Set[0].push_back(200);
    reales_Set[1].push_back(10); reales_Set[1].push_back(400); reales_Set[1].push_back(400); reales_Set[1].push_back(700);
    //    reales_Set[2].push_back(50); reales_Set[2].push_back(300); reales_Set[2].push_back(90); reales_Set[2].push_back(50);
    //    reales_Set[3].push_back(350); reales_Set[3].push_back(300); reales_Set[3].push_back(-15); reales_Set[3].push_back(230);
    //    reales_Set[4].push_back(350); reales_Set[4].push_back(400); reales_Set[4].push_back(-20); reales_Set[4].push_back(240);
    //    reales_Set[5].push_back(124); reales_Set[4].push_back(523); reales_Set[4].push_back(-23); reales_Set[4].push_back(856);

    // Größen des synthetischen Linienvektors und des reales_Set-Vektors vergleichen um n und k zu bestimmen
    cout << "Starting Combinations..." << endl;
    for (Bildlaufvariable=0; Bildlaufvariable<BildInfoVector.size();Bildlaufvariable++)
    {
        myTimer2.restart();
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

        // Vektor "people" mit 0,1,2,3,4...bis n-1 füllen
        for (int i = 0; i < n; ++i) {
            people.push_back(i);
            //int testblubblub = people[i];
            //cout << "Vektor people: " << people[i];
        }

        // Aufruf der Funktion calc_all_combinations mit k als Parameter
        calc_all_combinations(0, k);
        people.clear();
        cout << "Ellapsed " << myTimer2.elapsed() << "\n";

    }
    cout << "End Combinations ..";
    //TEST:
    //    cout<< "Geringster durchschnittlicher Fehler (pro Linie) des ersten sets: " <<BildInfoVector[0].getFehler()<<endl;
    //    cout<< "Geringster durchschnittlicher Fehler (pro Linie) des zweiten sets: "<<BildInfoVector[1].getFehler()<<endl;
    //    cout<< "Geringster durchschnittlicher Fehler (pro Linie) des dritten sets: "<<BildInfoVector[2].getFehler()<<endl;

    // Suchen des Objekts mit kleinstem Fehler
    int SetMitBestemGuetewert = 0;
    float relativerFehler = 0;
    for(int m = 0; m < BildInfoVector.size(); m++)
    {
        if(BildInfoVector[m].getFehler() > relativerFehler)
        {
            relativerFehler = BildInfoVector[m].getFehler();
            float guetewert = BildInfoVector[m].getFehler();// kann auskommentiert werden
            SetMitBestemGuetewert = m;
            int blub33=0;
        }
    }
    //float blub22 = BildInfoVector[SetMitBestemGuetewert].getFehler();

    // Ausgabe der Pose mit dem geringsten Fehler
    cout << "Set (Pose) mit bestem Gütewert ist Set (Pose) Nummer: " << SetMitBestemGuetewert << std::endl;
    cout << "Pose: " << endl << "x=" << BildInfoVector[SetMitBestemGuetewert].getPoseneintrag(0) << endl << "y=" << BildInfoVector[SetMitBestemGuetewert].getPoseneintrag(1) << endl;
    cout << "z=" << BildInfoVector[SetMitBestemGuetewert].getPoseneintrag(2) << endl << "roll=" << BildInfoVector[SetMitBestemGuetewert].getPoseneintrag(3) << endl;
    cout << "pitch=" << BildInfoVector[SetMitBestemGuetewert].getPoseneintrag(4) << endl << "yaw=" << BildInfoVector[SetMitBestemGuetewert].getPoseneintrag(5) << endl;
    cout << "relativer Gütewert = " << BildInfoVector[SetMitBestemGuetewert].getFehler() << endl;


    // Die 20 besten Posen ermitteln
//    std::vector<double> test25;
//    test25.push_back(3), test25.push_back(1.0), test25.push_back(0.01), test25.push_back(0.2), test25.push_back(0.002), test25.push_back(-1.0), test25.push_back(-20);
    std::priority_queue<std::pair< float,int> > q;
    for (int i = 0; i < BildInfoVector.size(); ++i) {
        q.push(std::pair<float, int>(BildInfoVector[i].getFehler(), i));
    }
    int k = 2; // number of indices we need
    for (int i = 0; i < k; ++i) {
      int ki = q.top().second;
      std::cout << "index[" << i << "] = " << ki << std::endl;
      q.pop();
    }

    return 0;
}

