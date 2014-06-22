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

#include"bildinfo.h"

using namespace std;
//typedef <vector<vector<double> > Vektordef;

int main ( int argc, char *argv[] )
{
    // 1. Datei öffnen
    // 2. Objekt Bild1 anlegen
    // 3. Pose aus Textdatei lesen
    // 4. Pose über setPose an Bild1 übergeben
    // 5. folgende Zeilen (Linienpararmeter) in n x 4 - Array laden
    // 6. Array mit setLinienarray an Bild1 übergeben
    // 7. Alle Zeilen bis hierhin löschen (oder Zeile merken)
    // 8. So lange wiederholen bis Textdatei leer
    // !!!!MEMBERVARIABLE: FEHLER ZUM REALEN SET: FEHLER ALLER KLASSEN WIEDER IN VEKTOR SCHREIBEN!!!

    // isteam: general input stream class
    // ifstream works on files (that's what the f is for)
    // This means that the things you want to do with an istream like reading in characters or lines works the same way as on an
    // ifstream, but some file specific things like opening or closing files will not work on an istream as it's not that specific
    //    ifstream inputFile("Eigenschaften.txt"); //input file stream
    //    string line;

    QFile file("Eigenschaften.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    std::vector<Bildinfo> BildInfoVector;   // Vektor vom Typ Bildinfo!!!!! an jeder Stelle des
                                            // Vektors steht eine Objekt von Bildinfo!!!!
    int k =0;
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
    int test2=BildInfoVector[0].getLinieneintrag(1,1);
    cout<<"Linieneintrag[1][1]= "<<test2;

    return 0;
}
