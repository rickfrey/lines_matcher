#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
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

void error_calc(vector<int> permutation){
    // der übergebene Vektor permutation stellt die Beziehung zwischen den Vektoren
    // BildInfoVec und reales_Set her
    // Einzige Frage: Wie bestimme ich den statischen Vektor (der immer 1 2 3 4... durchläuft)
    //                und den Vektor, auf dessen Einträge mit der Permutationsvorschrift zugegriffen werden???

    // statischer Vektor ist immer der kleinere!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //Fall: synthetisches Set ist kleiner:
    float Fehler=0;
    //vector<float> Fehlervec;// Fehlervektor!! Fehler für jede Setkombination speichern, niedrigsten Wert an Objekt übergeben!
    if(BildInfoVector[Bildlaufvariable].getLinienanzahl() < reales_Set.size())//Stelle des Bildinfovectors muss fortlaufend sein (muss noch geändert werden)
    {
        //Fehler berechnen und in Bildobjekt speichern
        for(int x=0; x<BildInfoVector[Bildlaufvariable].getLinienanzahl();x++)
        {
            for(int z=0;z<4;z++)//Alle 4 Parameter durchlaufen
            {
                int test1=BildInfoVector[Bildlaufvariable].getLinieneintrag(x,z);
                int test2=reales_Set[permutation[x]][z];// permutation[5] gibt es z.B. gar nicht!!! FEHLER!!!!!!
                // combination-Vektor und permutation-Vektor beide mit 0 anfangen lassen (damit ich mir das (-1) sparen kann!!!!
                int test3= BildInfoVector[Bildlaufvariable].getLinieneintrag(x,z)-reales_Set[permutation[x]][z];
                //int test4= permutation[x];
                Fehler=Fehler+abs(BildInfoVector[Bildlaufvariable].getLinieneintrag(x,z)-reales_Set[permutation[x]][z]);
                int blub44=0;
            }
        }
        Fehler=Fehler/BildInfoVector[Bildlaufvariable].getLinienanzahl();//Mittelwert für die aktuelle Kombination
        int blub22=BildInfoVector[Bildlaufvariable].getFehler();
        int blub23=0;
        if(Fehler < BildInfoVector[Bildlaufvariable].getFehler())
        {
            BildInfoVector[Bildlaufvariable].setFehler(Fehler);// es wird jedes Mal überprüft ob aktueller Fehler kleiner ist als alle vorigen (nur dann wird er an Objekt übergeben)
            int blub34=0;
        }
        float testx=BildInfoVector[Bildlaufvariable].getFehler();
        int blub=0;
    }
    // wenn gleiche Anzahl an Linien (==) dann ist es egal welche Schleife! (hier die zweite genommen)
    else if(BildInfoVector[Bildlaufvariable].getLinienanzahl() >= reales_Set.size())//Stelle des Bildinfovectors muss fortlaufend sein (muss noch geändert werden)
    {
        //Fehler berechnen und in Bildobjekt speichern
        for(int x=0; x<reales_Set.size();x++)// Da reales_Set kleiner ist als Bildinfovektor[xy] nur bis reales_Set.size()!!!
        {
            for(int z=0;z<4;z++)//Alle 4 Parameter durchlaufen
            {
                Fehler=Fehler + abs(reales_Set[x][z] - BildInfoVector[Bildlaufvariable].getLinieneintrag(permutation[x],z) );//m=permutation[x] getLinieneintrag(m,z)
                //int blub33=0;
            }
        }
        Fehler=Fehler/reales_Set.size();//Mittelwert
        if(Fehler < BildInfoVector[Bildlaufvariable].getFehler())
        {
            BildInfoVector[Bildlaufvariable].setFehler(Fehler);
        }
    }
}

void calc_all_permutations() {
    vector<int> permutation;
    static int count = 0;
    error_calc(combination);// WICHTIG!!! 1. Durchlauf mit sortierter Permutation!!!
    cout << "combination no " << (++count) << ": [ ";
    for (int i = 0; i < combination.size(); ++i) {
        cout << combination[i] << " ";
    }
    cout << "] " << endl;


    while(next_permutation(combination.begin(), combination.end()) ){
        cout<<"[";
        for(vector<int>::iterator it = combination.begin(); it != combination.end(); it++)
        {
            cout << *it << " ";
            permutation.push_back(*it); // Hier wird der Wert des Iterators (Zeigers) in permutation gespeichert
        }
        error_calc(permutation); // Vektor permutation wird an Funktion error_calc übergeben
        permutation.clear();
        cout << "]" << endl;
    }
}

void calc_all_combinations(int offset, int k) {
    if (k == 0) { //
        calc_all_permutations();
        return;
    }
    for (int i = offset; i <= people.size() - k; ++i) { // 3. Schleife von 0 bis (n-k)
        combination.push_back(people[i]); // 4. Vektor "combination": i-te Stelle wird mit people[i] gefüllt
        //cout<<"Test: people["<<i<<"]= "<<people[i]<<endl;
        //cout<<"Test: combination["<<i<<"]= "<<combination[i]<<endl;
        calc_all_combinations(i+1, k-1);
        combination.pop_back(); // pop_back verkleinert Vektor um eine Stelle
    }
}

int main ( int argc, char *argv[] )
{
    // Textdatei öffnen
    QFile file("Eigenschaften.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    // So lange Daten in Datei wird jeweils eine ausgelesen und Anzahl der Spalten in "numOfCol" gespeichert
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        int numOfCol = line.count(QLatin1Char(' '));
        numOfCol++; // Anzahl der Spalten = Anzahl Leerzeichen +1

        // Wenn 6 Spalten: Objekt anlegen und Zeile in Posenvektor speichern:
        if(numOfCol==6)
        {
            //neues Bildobjekt anlegen
            Bildinfo bi;
            vector<int> posenvektor;
            QStringList list1 = line.split(" ");
            for(int i = 0; i < list1.size(); ++i)
            {
                // Eingelesene Elemente werden in posenvektor geschrieben (und gleichzeitig zu int convertiert)
                posenvektor.push_back(list1.at(i).toInt());
            }
            bi.setPosenvektor(posenvektor); // posenvektor wird an Objekt an Posenvektor von Objekt bi übergeben
            //int Poseneintrag=bi.getPoseneintrag();
            //cout<<"Eintrag aus Posenvektor: "<<Poseneintrag<<endl;
            BildInfoVector.push_back(bi);   // Objekt bi wird an aktuell letzte Position des Vektors BildInfoVector geschrieben
        }

        ////////////////////////
        // Wenn 4 Spalten: Einträge in Linienvektor des aktuellen Objekts speichern:
        ////////////////////////
        int m=0,p; // Vektorlaufvariable
        if(numOfCol==4)
        {
            vector<int> linienparameter;
            QStringList list1 = line.split(" ");
            for(int i = 0; i < list1.size(); ++i)
            {
                linienparameter.push_back(list1.at(i).toInt());
            }
            // ???? NOCH NICHT SO GANZ VERSTANDEN WARUM DAS FUNKTIONIERT ????????
            // funktioniert das evtl. weil der Linienvektor einfach hinten drangeschrieben wird (an BildInfoVector)?
            BildInfoVector.at(BildInfoVector.size()-1).addLinienvektor(linienparameter);// ??? Hier wird die Memberfunktion "addLinienvektor" aufgerufen und eine Zeile angehängt.
            // Anschließend wird das an die passende Stelle von BildInfoVector geschrieben
        }

        //cout<<line<<endl;

    }
    file.close();

    int test=BildInfoVector[0].getPoseneintrag(0);
    cout<<"Poseneintrag[0]= "<<test<<endl;
    int test2=BildInfoVector[1].getLinieneintrag(3,2);
    cout<<"Linieneintrag[3][2]= "<<test2<<endl;
    cout<<"Linienanzahl= "<<BildInfoVector[0].getLinienanzahl()<<endl;

    /***************************
      1. k und n ermitteln
      2. Alle Permutationen berechnen (gibt an welche Linien miteinander verglichen werden)
      3. in Schleife mit jeder einzelnen Permutation: Berechnung eines Fehlers für jede Linie
         => Addieren der Fehler aller Linien dieser Permutation, anschließend durch Anzahl teilen
            (Mittelwert)
      4. Gesamtfehler des Liniensets in jeweiligem Objekt speichern
      *************************/

    // reales Linienset laden
    for(int i = 0; i < 12; i++)// es werden 12 Zeilen reserviert
    {
        vector<int> row;
        reales_Set.push_back(row);
    }
    reales_Set[0].push_back(490); reales_Set[0].push_back(168); reales_Set[0].push_back(6); reales_Set[0].push_back(444);
    reales_Set[1].push_back(483); reales_Set[1].push_back(351); reales_Set[1].push_back(12); reales_Set[1].push_back(427);
    reales_Set[2].push_back(276); reales_Set[2].push_back(299); reales_Set[2].push_back(-87); reales_Set[2].push_back(198);
    reales_Set[3].push_back(107); reales_Set[3].push_back(225); reales_Set[3].push_back(-84); reales_Set[3].push_back(163);
    reales_Set[4].push_back(195); reales_Set[4].push_back(352); reales_Set[4].push_back(-29); reales_Set[4].push_back(188);
    reales_Set[4].push_back(697); reales_Set[4].push_back(222); reales_Set[4].push_back(83); reales_Set[4].push_back(161);
    reales_Set[4].push_back(182); reales_Set[4].push_back(168); reales_Set[4].push_back(-16); reales_Set[4].push_back(189);
    reales_Set[4].push_back(59); reales_Set[4].push_back(314); reales_Set[4].push_back(9); reales_Set[4].push_back(108);
    reales_Set[4].push_back(49); reales_Set[4].push_back(146); reales_Set[4].push_back(4); reales_Set[4].push_back(98);
    reales_Set[4].push_back(739); reales_Set[4].push_back(145); reales_Set[4].push_back(-8); reales_Set[4].push_back(56);
    reales_Set[4].push_back(333); reales_Set[4].push_back(386); reales_Set[4].push_back(12); reales_Set[4].push_back(117);
    reales_Set[4].push_back(726); reales_Set[4].push_back(314); reales_Set[4].push_back(-17); reales_Set[4].push_back(83);

    for (Bildlaufvariable=0; Bildlaufvariable<BildInfoVector.size();Bildlaufvariable++)
    {
        int n, k;
        // Größen des synthetischen Linienvektors und des reales_Set-Vektors vergleichen
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

        for (int i = 0; i < n; ++i) { people.push_back(i);} // 1. Hier wird lediglich Vektor people mit 1,2,3,4...bis n gefüllt NEIN: JEZT MIT 0,1,2...n
        calc_all_combinations(0, k); // 2. Aufruf der Funktion calc_all_combinations mit k als Parameter
    }
    //TEST:
    cout<< "Geringster durchschnittlicher Fehler (pro Linie) des ersten sets: " <<BildInfoVector[0].getFehler()<<endl;
    cout<< "Geringster durchschnittlicher Fehler (pro Linie) des zweiten sets: "<<BildInfoVector[1].getFehler()<<endl;
    cout<< "Geringster durchschnittlicher Fehler (pro Linie) des dritten sets: "<<BildInfoVector[2].getFehler()<<endl;

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
