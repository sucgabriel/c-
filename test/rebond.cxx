#include "univers.hxx"
#include "particules/particules.hxx"
#include "particules/abstract_part.hxx"
#include "particules/pot_gravitationnelle.hxx"
#include "point.hxx"


int main(){
    Univers univers = Univers(2, {100, 100, 0}, 100);
    Point pos_initiale = Point(50, 80,0);
    Point vit_initiale = Point(0, 1,0);
    std::unique_ptr<AbstractPart> balle = std::make_unique<Particule>(pos_initiale, vit_initiale, Point(), Point(), 1.0, 1, 1, true, 2);
    balle = std::make_unique<PotGravDecorator>(move(balle));
    univers.assign_cell(move(balle));
    univers.simulation(20, 0.5, true);

}
