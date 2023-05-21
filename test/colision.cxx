#include "univers.hxx"
#include "particules/particules.hxx"
#include "particules/abstract_part.hxx"
#include "particules/lennard_decorator.hxx"
#include "particules/grav_decorator.hxx"
#include "point.hxx"


// Fichier qui correspond a la collision entre objet du lab 4 
int main(){
    Univers univers = Univers(2, {250, 100, 0},2.5);
    univers.set_epsilon(5);
    int N1 = 1600;
    int N2 = 6400;
    double masse = 1;
    Point vitesse_initiale_cube = Point(0,10,0);
    Point vitesse_initiale_rec = Point();
    double delta_t = 0.005;
    double tend = 3;
    double dpart = pow(2.0, 1.0/6.0);

    // construction du cube 

    double xdepart_cube = 60*dpart;
    double ydepart_cube = 0;
    for (int i=0; i<40; i++){
        for(int j=0; j<40; j++){
            Point pos_part = Point(xdepart_cube+i*dpart, ydepart_cube +j*dpart,0);
            std::unique_ptr<AbstractPart> particule = std::make_unique<Particule>(pos_part, vitesse_initiale_cube, Point(), Point(), masse, i+j, 1, true, 2);
            particule = std::make_unique<LennardDecorator>(move(particule));
            particule = std::make_unique<GravDecorator>(move(particule));
            univers.assign_cell(move(particule));
        }
    }

    // construction du rectangle
    double ecart = 3*dpart; // ptit ecart pour la simulation
    double xdepart_rectangle = 0;
    double ydepart_rectangle = 40*dpart + ecart;
    for (int i=0; i<160; i++){
        for (int j=0; j<40; j++){
            Point pos_part = Point(xdepart_rectangle+i*dpart, ydepart_rectangle +j*dpart,0);
            std::unique_ptr<AbstractPart> particule = std::make_unique<Particule>(pos_part, vitesse_initiale_rec, Point(), Point(), masse, N1+i+j, 2, true, 2);
            particule = std::make_unique<LennardDecorator>(move(particule));
            particule = std::make_unique<GravDecorator>(move(particule));
            univers.assign_cell(move(particule));
        }
    }
    //univers.affiche_all_part();
    univers.simulation(tend, delta_t, false);
    univers.affiche_all_part();
    
}   