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

void error_calc(vector<int> permutation){
    // der übergebene Vektor permutation stellt die Beziehung zwischen den Vektoren
    // BildInfoVec und reales_Set her
    // Einzige Frage: Wie bestimme ich den statischen Vektor (der immer 1 2 3 4... durchläuft)
    //                und den Vektor, auf dessen Einträge mit der Permutationsvorschrift zugegriffen werden???

    // statischer Vektor ist immer der kleinere!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //Fall: synthetisches Set ist kleiner:
    float Fehler;
    //vector<float> Fehlervec;// Fehlervektor!! Fehler für jede Setkombination speichern, niedrigsten Wert an Objekt übergeben!
    if(BildInfoVector[Bildlaufvariable].getLinienanzahl() < reales_Set.size())//Stelle des Bildinfovectors muss fortlaufend sein (muss noch geändert werden)
    {
        //Fehler berechnen und in Bildobjekt speichern
        for(int x=0; x<BildInfoVector[Bildlaufvariable].getLinienanzahl();x++)
        {
            for(int z=0;z<4;z++)//Alle 4 Parameter durchlaufen
            {
                int test1=BildInfoVector[Bildlaufvariable].getLinieneintrag(x,z);
                int test2=reales_Set[permutation[x]-1][z];// permutation[5] gibt es z.B. gar nicht!!! FEHLER!!!!!!
                                                            // combination-Vektor und permutation-Vektor beide mit 0 anfangen lassen (damit ich mir das (-1) sparen kann!!!!
                int test3= BildInfoVector[Bildlaufvariable].getLinieneintrag(x,z)-reales_Set[permutation[x]-1][z];
                //int test4= permutation[x];
                Fehler=Fehler+abs(BildInfoVector[Bildlaufvariable].getLinieneintrag(x,z)-reales_Set[permutation[x]-1][z]);
            }
        }
        Fehler=Fehler/BildInfoVector[Bildlaufvariable].getLinienanzahl();//Mittelwert

        if(Fehler < BildInfoVector[Bildlaufvariable].getFehler())
        {
            BildInfoVector[Bildlaufvariable].setFehler(Fehler);// es wird jedes Mal überprüft ob aktueller Fehler kleiner ist als alle vorigen (nur dann wird er an Objekt übergeben)
        }
        float testx=BildInfoVector[Bildlaufvariable].getFehler();
        int blub=0;
    }
    // wenn gleiche Anzahl an Linien (==) dann ist es egal welche Schleife! (hier die zweite genommen)
    else if(BildInfoVector[Bildlaufvariable].getLinienanzahl() >= reales_Set.size())//Stelle des Bildinfovectors muss fortlaufend sein (muss noch geändert werden)
    {
        //Fehler berechnen und in Bildobjekt speichern
        for(int x=0; x<BildInfoVector[Bildlaufvariable].getLinienanzahl();x++)
        {
            for(int z=0;z<4;z++)//Alle 4 Parameter durchlaufen
            {
                //int m = permutation[x];
                //Fehler=Fehler+abs(reales_Set(x,z) - BildInfoVector[Bildlaufvariable].getLinieneintrag(*permutation[x]-1,z));
            }
        }
        Fehler=Fehler/BildInfoVector[Bildlaufvariable].getLinienanzahl();//Mittelwert
        if(Fehler < BildInfoVector[Bildlaufvariable].getFehler())
        {
            BildInfoVector[Bildlaufvariable].setFehler(Fehler);
        }
    }
}

void print_combinations() {
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

void go(int offset, int k) {
    if (k == 0) { //
        print_combinations();
        return;
    }
    for (int i = offset; i <= people.size() - k; ++i) { // 3. Schleife von 0 bis (n-k)
        combination.push_back(people[i]); // 4. Vektor "combination": i-te Stelle wird mit people[i] gefüllt
        //cout<<"Test: people["<<i<<"]= "<<people[i]<<endl;
        //cout<<"Test: combination["<<i<<"]= "<<combination[i]<<endl;
        go(i+1, k-1);
        combination.pop_back(); // pop_back verkleinert Vektor um eine Stelle
    }
}

int main ( int argc, char *argv[] )
{
    QFile file("Eigenschaften.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    //int k =0;
    QTextStream in(&file);
    while (!in.atEnd()) {

        //So lange Daten in Datei
        QString line = in.readLine();
        int numOfCol = line.count(QLatin1Char(' '));
        numOfCol++; // Anzahl der Spalten = Anzahl Leerzeichen +1

        //////////////////////////
        // Bis hier wurde eine Zeile eingelesen und die Anzahl der Spalten in der Variablen "numOfCol" gespeichert
        /////////////////////////

        /////////////////////////
        // Wenn 6 Spalten: Objekt anlegen und Zeile in Posenvektor speichern:
        ////////////////////////
        if(numOfCol==6)
        {
            //   QString Objektname= QString("Bild%1").arg(k);
            // k++;
            Bildinfo bi; //neues Bildobjekt anlegen
            vector<int> posenvektor;//hier werden die 6 DoF reingespeichert
            QStringList list1 = line.split(" ");
            for(int i = 0; i < list1.size(); ++i)
            {
                posenvektor.push_back(list1.at(i).toInt()); // Eingelesene Elemente werden in posenvektor geschrieben (und gleichzeitig zu int convertiert)
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
    cout<<"Poseneintrag[0]= "<<test;
    int test2=BildInfoVector[1].getLinieneintrag(3,2);
    cout<<"Linieneintrag[3][2]= "<<test2<<endl;
    cout<<"Linienanzahl= "<<BildInfoVector[0].getLinienanzahl();

    /***************************
      1. k und n ermitteln
      2. Alle Permutationen berechnen (gibt an welche Linien miteinander verglichen werden)
      3. in Schleife mit jeder einzelnen Permutation: Berechnung eines Fehlers für jede Linie
         => Addieren der Fehler aller Linien dieser Permutation, anschließend durch Anzahl teilen
            (Mittelwert)
      4. Gesamtfehler des Liniensets in jeweiligem Objekt speichern
      *************************/

    // reales Linienset laden

    for(int i = 0; i < 5; i++)// es werden 5 Zeilen reserviert
    {
        vector<int> row;
        reales_Set.push_back(row);
    }
    reales_Set[0].push_back(100); reales_Set[0].push_back(300); reales_Set[0].push_back(25); reales_Set[0].push_back(200);
    reales_Set[1].push_back(100); reales_Set[1].push_back(400); reales_Set[1].push_back(28); reales_Set[1].push_back(220);
    reales_Set[2].push_back(200); reales_Set[2].push_back(300); reales_Set[2].push_back(90); reales_Set[2].push_back(50);
    reales_Set[3].push_back(350); reales_Set[3].push_back(300); reales_Set[3].push_back(-15); reales_Set[3].push_back(230);
    reales_Set[0].push_back(350); reales_Set[0].push_back(400); reales_Set[0].push_back(-20); reales_Set[0].push_back(240);


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

        for (int i = 0; i < n; ++i) { people.push_back(i+1);} // 1. Hier wird lediglich Vektor people mit 1,2,3,4...bis n gefüllt
        go(0, k); // 2. Aufruf der Funktion go mit k als Parameter
    }
    //TEST:
    cout<< "Fehler des ersten sets: " <<BildInfoVector[0].getFehler()<<endl;

    return 0;
}
