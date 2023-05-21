#include "particules/particules.hxx"
#include "particules/grav_decorator.hxx"
#include "point.hxx"
#include "time.h"

int main(){
    std::list< std::unique_ptr<AbstractPart> > liste_particules;
    for (int i=1; i<25; i++){
        liste_particules.clear();
        double t1 = clock();
        for (int k=0; k<pow(2,i); k++){
            std::unique_ptr<AbstractPart> part = std::make_unique<Particule>(Point(), Point(), Point(), Point(), 1.0, k, 1, true, 3);
            part = std::make_unique<GravDecorator>(move(part));
            liste_particules.push_front(move(part));
        }
        double t2 = clock() - t1;
        double tps_seconde = t2/CLOCKS_PER_SEC;
        std::cout << "pour 2^" << i << " particules, le temps d'éxécution est de :" << tps_seconde << " secondes" << std::endl;
    }
}