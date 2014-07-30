#ifndef BILDINFO_H
#define BILDINFO_H

using namespace std;

class Bildinfo
{
private:
    //int x,y,z,r,p,ya;//Pose
    //int Linienanzahl;
    //int a=6;
    //int Linienarray[a];
//    std::vector<int> Pose(6);
    int Zeilenanzahl;
    vector<float> Posenvektor;
    vector< vector<int> > Linienvektor;
    float Fehler;

public:
    Bildinfo();
    ~Bildinfo();


    void addLinienvektor(vector<int> vektor);
    void setPosenvektor(vector<float> vektor);
    int getLinienanzahl();
    float getPoseneintrag(int eintrag);
    int getLinieneintrag(int liniennummer, int parameter);
    void setFehler(float Fehler);
    float getFehler();
};

#endif
