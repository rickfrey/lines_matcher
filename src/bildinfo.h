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
    vector<int> Posenvektor;
    vector< vector<int> > Linienvektor;

public:
    Bildinfo();
    ~Bildinfo();


    void addLinienvektor(vector<int> vektor);
    void setPosenvektor(vector<int> vektor);
    int getPoseneintrag();
    int getLinieneintrag();
};

#endif
