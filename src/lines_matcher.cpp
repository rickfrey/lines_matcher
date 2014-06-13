#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sstream>
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
    ifstream inputFile("Eigenschaften.txt"); //input file stream
    string line;

    while(inputFile.good())//So lange Daten in Datei
    {
    getline(inputFile,line);// hier wird eine Zeile aus Textdatei gelesen und in stringstream gespeichert
    istringstream is(line); //class for char input memory streams
    istringstream is2(line); // zweimal selbe Zeile einlese weil einmal um Spalten zu zählen und anschließend im zweiten stringstream um in Vektor zu schreiben
    int n, columns=0,i=0,j=0,k=1;
    while(is>>n)
    {
    columns++;//Zählen der Spalten in eingelesener Zeile
    }
    //////////////////////////
    // Bis hier wurde eine Zeile eingelesen und die Anzahl der Spalten in der Variablen "columns" gespeichert
    /////////////////////////

    /////////////////////////
    // Wenn 6 Spalten: Objekt anlegen und Zeile in Posenvektor speichern:
    ////////////////////////
    if(columns==6)
    {
    std::stringstream Objektname;
    Objektname<<"Bild"<<k;//k muss für jede 6er Zeile hochgezählt werden
    Bildinfo Bild1; //neues Bildobjekt anlegen //EIGENTLICH: "Objektname" anstatt Bild1!!! wenn Bildinfo *Bild1 habe ich einen Zeiger!
    vector<int> Posenvektor(6);//hier werden die 6 DoF reingespeichert
    int l=0; // Vektorlaufvariable
    while(is2>>n)
    {
        Posenvektor[l]=n;
        l++;
    }
    Bild1.setPosenvektor(Posenvektor);
    int Poseneintrag=Bild1.getPoseneintrag();
    cout<<"Eintrag aus Posenvektor: "<<Poseneintrag<<endl;
    }

    ////////////////////////
    // Wenn 4 Spalten: Einträge in Linienvektor des aktuellen Objekts speichern:
    ////////////////////////
    vector<int> Linienparameter(4);
    int m=0,p; // Vektorlaufvariable
    if(columns==4)
    {
        while(is2>>p)
        {
            Linienparameter[m]=p;
            cout<<"Linienparamter["<<m<<"]= "<<Linienparameter[m]<<endl;
            m++;
        }
        Bild1.addLinienvektor(Linienparameter);
    }

    //cout<<line<<endl;

    }

   /*
    int c=0;
    int Zeilenanzahl=10;//Beispiel
    vector<vector<int> > matrix(); // Zweidimensionalen Vektor (Matrix mit einer Zeile??)
    matrix.resize(Zeilenanzahl);
    ifstream iFile("Eigenschaften.txt");//input file stream
    string line;
    istringstream is(line); //class for char input memory streams
    while(getline(iFile,line))//Zeile für Zeile durchgehen
                                // getline extracts characters from iFile and stores them into line
                                // the extraction also stops if end of file is reached
    {
        int j=0;//Laufvariable für Zeilen

        //jetzt Anzahl der Spalten ermitteln
        std::stringstream test(line);
        int n,columns=0;
        while( test >> n )
        {
        columns++;//am Ende dieser Schleife gibt k Anzahl der Spalten in dieser Zeile an!
        cout<<n<<"; "<<columns<<endl;
        }
        //jetzt einzelne Elemente der Zeile in jeweils richtige Spalte schreiben
        //matrix[j].resize(columns);//wie für 2D-Matrix??
        for( int i=0;i<columns;i++)
        {
            //matrix[j][i]=n; //FEHLER!!! WEGEN RESIZE??
        }
        //matrix[0][0].push_back(5);
        matrix.push_back(n);

        cout<<"number of columns: "<<columns<<endl;

        //{matrix[i].resize(CC);}
        //matrix[0][0]=4;

       cout<<line<<endl;
       j++; //Zeilennummer um 1 erhöht!
    }
    */
    /*
    ifstream read("Eigenschaften.txt");
    int array[6][10],i,j;
    std::string line("3 5 3.5 4 1 11");
    std::istringstream iss(line);
    int columns=0;
    do
    {
        std::string sub;
        iss>>sub;
        if(sub.length())
        {
            ++columns;
        }
    }
    while(iss);
    cout<<"number of columns: "<<columns<<endl;

    for(j=0;j<10;j++)
    {
        for(i=0;i<6;i++)
        {
            //Wenn \n: Break
            read>>array[j][i];
            cout<<array[j][i]<<";"<<endl;
            i++;
        }
    j++;
    }
*/
    /*
    int c1[20],c2[20],n,m,i=1;
    ifstream read("Eigenschaften.txt");
    int lines=0;
    while(read>>n>>m)
    {
        c1[i]=n;
        c2[i]=m;
        cout<<c1[i]<<";"<<c2[i]<<endl;
        i++;
    }
*/
/*
    int RR=6;
    int CC=3;
    vector<vector<int> > matrix(RR);
    for ( int i = 0 ; i < RR ; i++ )
       {matrix[i].resize(CC);}
    matrix[0][0]=4;
    cout<<matrix[0][0]<<endl;
*/
/*
    vector<vector<int> > testvektor(6);
    testvektor[0][0]=5;
    cout<< "blah"<<endl;
    cout<< testvektor[0][0] <<endl;
    //test[3][0] = 10;
    //cout<<test[2][3]<<endl;
*/
return 0;
}
