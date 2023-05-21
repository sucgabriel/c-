
#include "particules/particules.hxx"
#include "particules/grav_decorator.hxx"
#include "point.hxx"

/* Simulation de l'Universe du TP 2, pas de classe particule */
void Simulation(std::list< std::unique_ptr<AbstractPart> > &);

void Simulation(std::list< std::unique_ptr<AbstractPart> > &particleList){
    for (auto && part_i = particleList.begin(); part_i != particleList.end(); part_i++) {
        for (auto && part_j = std::next(part_i); part_j != particleList.end(); part_j++) {
            auto &p_i = *part_i;
            auto &p_j = *part_j;
            p_i->compute_force(p_j);
        }
    }
    

    
    double delta_t = 0.045;
    double t = 0;
    double tend = 468.5;
    while(t < tend){
        t = t + delta_t;


        for (auto &&part : particleList) {
            part->advance_position(delta_t);
        }
        for (auto  &&part_i = particleList.begin(); part_i != particleList.end(); part_i++) {
            for (auto && part_j = next(part_i); part_j != particleList.end(); part_j++) {
                auto &p_i = *part_i;
                auto &p_j = *part_j;
                p_i->compute_force(p_j);
            }
        }

        for (auto &&part : particleList) {
            part->advance_velocity(delta_t);
            part->affiche_graphique();
        }
        
    }
}

int main(){
    Point position_soleil = Point();
    Point vitesse_soleil = Point();
    std::unique_ptr<AbstractPart> Soleil = std::make_unique<Particule>(position_soleil, vitesse_soleil, Point(), Point(), 1.0, 1, 1, true, 3);
    Soleil = std::make_unique<GravDecorator>(move(Soleil));
    

    Point pos_terre = Point(0,1,0);
    Point vitesse_terre = Point(-1,0,0);
    double masse_terre = 3E-6;
    std::unique_ptr<AbstractPart> Terre = std::make_unique<Particule>(pos_terre, vitesse_terre, Point(), Point(), masse_terre, 2, 1, true,3);
    Terre = std::make_unique<GravDecorator>(move(Terre));

    Point pos_jupiter = Point(0, 5.36, 0);
    Point vitesse_jupiter = Point(-0.425,0,0);
    double masse_jupiter = 9.55E-4;
    std::unique_ptr<AbstractPart> Jupiter =std::make_unique<Particule>(pos_jupiter, vitesse_jupiter, Point(), Point(), masse_jupiter, 3, 1, true,3);
    Jupiter = std::make_unique<GravDecorator>(move(Jupiter));

    Point pos_haley = Point(34.75, 0, 0);
    Point vit_haley = Point(0, 0.0296,0);
    double masse_haley = 1E-14;
    std::unique_ptr<AbstractPart> Haley = std::make_unique<Particule>(pos_haley, vit_haley, Point(), Point(), masse_haley, 4, 1, true,3); 
    Haley = std::make_unique<GravDecorator>(move(Haley));

    std::list< std::unique_ptr<AbstractPart> > liste_particules;
    liste_particules.push_front(move(Soleil));
    liste_particules.push_front(move(Terre)); 
    liste_particules.push_front(move(Jupiter)); 
    liste_particules.push_front(move(Haley)); 
    liste_particules.reverse();
    Simulation(liste_particules);
}