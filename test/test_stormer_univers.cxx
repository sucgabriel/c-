#include "univers.hxx"
#include "particules/particules.hxx"
#include "particules/abstract_part.hxx"
#include "particules/grav_decorator.hxx"
#include "point.hxx"


int main(){
    Univers univers = Univers(2, {120, 60,0}, 30);
    Point translate = Point(10,10,0); // translate pour la condition limite 
    Point position_soleil = Point() + translate;
    Point vitesse_soleil = Point();
    Point default_point = Point();
    double masse_soleil = 1;
    std::unique_ptr<AbstractPart> Soleil = std::make_unique<Particule>(position_soleil, vitesse_soleil, Point(), Point(), 1.0, 1, 1, true, 2);
    Soleil = std::make_unique<GravDecorator>(move(Soleil));
    univers.assign_cell(move(Soleil));
    //std::cout << "create particule : univers "<< std::endl;
    //  univers.affiche_univers();

    Point pos_terre = Point(0,1,0) + translate;
    Point vitesse_terre = Point(-1,0,0);
    double masse_terre = 3E-6;
    std::unique_ptr<AbstractPart> Terre = std::make_unique<Particule>(pos_terre, vitesse_terre, Point(), Point(), masse_terre, 2, 1, true,2);
    Terre = std::make_unique<GravDecorator>(move(Terre));
    univers.assign_cell(move(Terre));

    //univers.afficheUnivers();

    Point pos_jupiter = Point(0, 5.36, 0) + translate;
    Point vitesse_jupiter = Point(-0.425,0,0);
    double masse_jupiter = 9.55E-4;
    std::unique_ptr<AbstractPart> Jupiter =std::make_unique<Particule>(pos_jupiter, vitesse_jupiter, Point(), Point(), masse_jupiter, 3, 1, true,2);
    Jupiter = std::make_unique<GravDecorator>(move(Jupiter));
    univers.assign_cell(move(Jupiter));

    //univers.afficheUnivers();

    Point pos_haley = Point(34.75, 0, 0) + translate;
    Point vit_haley = Point(0, 0.0296,0);
    double masse_haley = 1E-14;
    std::unique_ptr<AbstractPart> Haley = std::make_unique<Particule>(pos_haley, vit_haley, Point(), Point(), masse_haley, 4, 1, true,2); 
    Haley = std::make_unique<GravDecorator>(move(Haley));
    univers.assign_cell(move(Haley));

    univers.affiche_all_part();
    univers.simulation(468.5, 0.015, true);
}