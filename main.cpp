#include <iostream>
#include"polygon.h"
#include"point2d.h"
#include<vector>
#include <algorithm>    // std::sort

using namespace std;

int main()
{
    vector<Point2d> pVec{Point2d(0,0), Point2d(1.1, 0), Point2d(1.1, -1)};
    sort(pVec.begin(), pVec.end());
    Point2d p1(0.1, -9);
    Point2d p2(0.2, -9);

    cout << "the distance between p1 and p2 is: "<<p1.distance(p2)<<endl;
    if(p1<p2)
    {
        cout<<"p1 < p2"<<endl;
    }
    else
    {
        cout<<"p1 > p2"<<endl;
    }
    cout << "p1+p2= (" << (p1+p2).x << "," << (p1+p2).y <<")" <<endl;
    cout << "p1-p2= (" << (p1-p2).x << "," << (p1-p2).y <<")" <<endl;
    cout << "Hello World!" << endl;
    return 0;
}
