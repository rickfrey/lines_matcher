#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sstream>

using namespace std;


int main ( int argc, char *argv[] )
{
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
/*
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(void) {
    vector<vector<string> > m(10);

    for(int i = 0; i < 10; i++)
        m[i].resize(3);

    m[0][0] = "Peter";
    m[0][1] = "Lustig";
    m[0][2] = "31337";

    m[1][0] = "Dieter";
    m[1][1] = "Himmel";
    m[1][2] = "51";

    for(int i = 0; i < 3; i++)
        cout << m[1].at(i);



    return 0;
}
*/
return 0;
}
