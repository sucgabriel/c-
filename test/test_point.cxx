#include "point.hxx"

int main(){
    Point p1 = Point();
    Point p2 = Point(1,2,3);
    Point p3 = p2;
    std::cout << "normalement on a :" << p2 << " = " << p3 << std::endl;
    std::cout << "normalement " << p1 <<" = " << "le vecteur nulle" << std::endl;
    std::cout << "Constructeur bon" << std::endl;
    bool test = ( p1 == p2);
    bool test2 = (p2 == p3);
    std::cout << "on a false / true :" << test <<" / " << test2 <<  "donc == et != bon " << std::endl;
    p2.normalize();
    std::cout << "on a normalisé p2 :" << p2 << std::endl;
    Point p4 = Point(1,1,1);
    Point p5 = Point(2,0,0);
    p4 += p5; 
    std::cout << " ont a (3,1,1) : " << (p4 == Point(3,1,1)) << "donc +, += , - , -= bon" << std::endl;
    p4 *=2;
    p5 =2* p5;
    bool result = (p4 == Point(6,2,2) )&&( p5 == Point(4,0,0));
    std::cout << result << " donc * par un scalaire bon" << std::endl;
    int k = p5(2);
    bool result2 = (k == 0);
    std::cout << result2 << " donc () ok" << std::endl;

    std::cout << "classe point ok !";
}   