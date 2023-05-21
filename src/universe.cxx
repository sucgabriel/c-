#include <random>
#include <iostream>

#include "universe.hxx"
#include "particules/grav_decorator.hxx"
#include "particules/lennard_decorator.hxx"

void Universe::simulation(double tend, double delta_t){
    compute_forces();

    for (double current_t = 0; current_t < tend; current_t += delta_t) {
        simulation_step(delta_t);
    }
}

void Universe::simulation_step(double delta_t) {
    compute_positions(delta_t);
    compute_forces();
    compute_velocities(delta_t);
}

void Universe::compute_positions(double delta_t) {
    for (auto &&part : this->particules) {
        part->advance_position(delta_t);
    }
}

void Universe::compute_velocities(double delta_t) {
    for (auto &&part : this->particules) {
        part->advance_velocity(delta_t);
    }
}

void Universe::compute_forces() {
    auto &pts = this->particules;
    for (auto&&part_i = pts.begin(); part_i < pts.end(); part_i++) {
        (*part_i)->compute_pot();
        for (auto &&part_j = part_i; part_j < pts.end(); part_j++) {
            auto &p_i = *part_i;
            auto &p_j = *part_j;


            Point f = p_i->compute_force(p_j);
            p_j->set_force(p_j->get_force() - f);
        }
    }
}

void Universe::add_particule(const Point &position, const Point &vitesse,
const Point &force, const Point &old_force, double masse, Flag f) {

    int cat = f();
    std::unique_ptr<AbstractPart> p = std::make_unique<Particule>(position, vitesse,
    force, old_force, masse, this->nbre_particules, cat, true);

    if (f[GRAVITY]) {
        p = std::make_unique<GravDecorator>(move(p));
    }
    if (f[LENNARD]) {
        p = std::make_unique<LennardDecorator>(move(p));
    }

    this->particules.push_back(move(p));
    this->nbre_particules++;
}

void Universe::add_copy_particules(int n, const Particule & part, Flag f) {
    for (int i = 0; i < n; i++) {
        add_particule(part.get_position(), part.get_velocity(), part.get_force(),
        part.get_force_old(), part.get_mass(), f);
    }
}

//Affiche l'état de l'Universe : 
void Universe::afficheUniverse(){
    std::cout << "DEBUT ITER";
    for (auto &it : this->particules){
        it->affiche();
        std::cout << '\n';
    }
    std::cout << "FIN ITER";
}


void Universe::createPartRandomly(long nb,double masse, const Flag &flag){
    int dimension = this->dim;
    for(long i=0; i<nb; i++){
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_real_distribution<> dis(0.0, 1.0);
        Point pos_part;
        if (dimension == 1){
            pos_part = Point(dis(gen), 0, 0);
        }else if (dimension == 2){
            pos_part = Point(dis(gen), dis(gen), 0);
        } else{
            pos_part = Point(dis(gen), dis(gen), dis(gen));
        }
        add_particule(pos_part, Point(), Point(), Point(), masse, flag);
    }
}


//Constructeur : 
Universe::Universe(int dim){
    this->dim = dim;
    this->particules = std::vector<std::unique_ptr<AbstractPart>>();
    this->nbre_particules = 0;
}
