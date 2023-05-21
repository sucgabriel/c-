
#include "universe.hxx"

#include "time.h"

/* Simulation de l'Universe du TP 3 */


int main(){
    Universe universe = Universe(3);
    //Point default_point =Point();
    //Particule default_particule = Particule(default_point, default_point, default_point, default_point, 1,0,1,1);
    //Universe.addParticule(default_particule);
    //Universe.afficheUniverse();
    Flag f =Flag(GRAVITY);
    for (int i=0; i<22; i++){
        double t1 = clock();
        universe.createPartRandomly( pow(2, i), 1, f);
        double t2 = clock() - t1;
        double tps_seconde = t2/CLOCKS_PER_SEC;
        std::cout << "temps pour la création et l'insertition de 2^: "<< i << " particules :"<< tps_seconde << std::endl;

        t1 = clock();
        universe.simulation(1,1);
        t2 = clock() - t1;
        tps_seconde = t2/CLOCKS_PER_SEC;
        std::cout << "temps pour le calcul de l'interactions dans un univers avec  2^: "<< i << " particules :"<< tps_seconde << std::endl;
    }
}