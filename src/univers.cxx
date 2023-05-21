#include "univers.hxx"
#include <random>
#include <iostream>

#include <particules/particules.hxx>
#include <particules/grav_decorator.hxx>
#include <particules/lennard_decorator.hxx>

// fonction utilitaire 


//Constructeur : 
Univers::Univers(int dim,std::array<double,3> ld, double rcut) : ld(ld) {
    this->dim = dim;
    this->rcut = rcut;
    this->ncd = {1,1,1};
    for (int k=0; k<dim; k++){
        this->ncd[k] = std::floor(ld[k]/rcut);
    }

    for (int i = 0; i < ncd[0]; i++) {
        for (int j = 0; j < ncd[1]; j++) {
            for (int k = 0; k < ncd[2]; k++) {
                std::array<int, 3> pos_maille = {i,j,k};
                Cellule new_cell = Cellule(pos_maille,dim);
                new_cell.set_voisin(get_voisins_index(new_cell));
                add_cellule(std::move(new_cell));
            }
        }
    }

    // if (dim == 1){
    //     for (int i=0; i<ncd[0]; i++){
    //         std::array<int, 3> pos_maille = {i,0,0};
    //         Cellule new_cell = Cellule(pos_maille,dim);
    //         new_cell.setVoisin(getVoisinsIndex(new_cell));
    //         addCellule(new_cell);
    //     }
    // }
    // else if (dim == 2){
    //     for (int i=0; i<ncd[0]; i++){
    //         for (int j=0; j<ncd[1];j++){
    //             std::array<int, 3> pos_maille = {i,j,0};
    //             Cellule new_cell = Cellule(pos_maille,dim);
    //             new_cell.setVoisin(getVoisinsIndex(new_cell));
    //             addCellule(new_cell);
    //         }
    //     }
    // }
    // else{ //Dim3

    //     for (int i=0; i<ncd[0]; i++){
    //         for (int j=0; j<ncd[1];j++){ // SI dim 1, ncd(1) = 0 donc en realité pas de boucle
    //             for (int k=0; k<ncd[2]; k++){ // Si dim 2, ncd(2) = 0 donc en realité pas de boucle for
    //                 std::array<int, 3> pos_maille = {i,j,k};
    //                 Cellule new_cell = Cellule(pos_maille,dim);
    //                 new_cell.setVoisin(getVoisinsIndex(new_cell));
    //                 addCellule(new_cell);
    //             }
    //         }
    //     }
    // }
}

std::list<int> Univers::get_voisins_index(const Cellule &cell) const{
    int i = cell.get_pos()[0];
    int j = cell.get_pos()[1];
    int k = cell.get_pos()[2];
    std::list<int> voisins;

    if (dim == 3){
        for (int di=-1; di<=1; di++){
            for (int dj=-1; dj<=1; dj++){
                for (int dk=-1; dk<=1; dk++){
                    int ni = i + di;
                    int nj = j + dj;
                    int nk = k + dk;
                    // Si les index sont dans le range de la simulation
                    if (ni >= 0 && ni < ncd[0] &&
                        nj >= 0 && nj < ncd[1] &&
                        nk >= 0 && nk < ncd[2]){
                        int index = ni + nj*ncd[0] + nk*ncd[0]*ncd[1];
                        voisins.push_back(index);
                    }
                }
            }
        }
    } else if( dim ==2){
        for (int l = -1; l <= 1; ++l) {
            for (int m = -1; m <= 1; ++m) {
                int index = i + l + (j + m)*ncd[0];
                if (i + l < 0 || i + l >= ncd[0] || j + m < 0 || j + m >= ncd[1]) continue;
                voisins.push_back(index);
            }
        }
    } else { // DIM 1 
        for (int x=-1; x<= 1; x++){
            int index = i+x;
            if (i+x < 0 ||i+x >=ncd[0]) continue;
            voisins.push_back(index);
        }
    }
    return voisins;
}

std::list<std::reference_wrapper<const Cellule>> Univers::get_voisin_cellule(const Cellule &cell) const{
    std::list<std::reference_wrapper<const Cellule>> cell_voisines = {};
    for (auto it : cell.get_voisin_index()){
        cell_voisines.push_back(this->cellules[it]);
    }
    return cell_voisines;
}

std::list<std::reference_wrapper<Cellule>> Univers::get_voisin_cellule(const Cellule &cell) {
    std::list<std::reference_wrapper<Cellule>> cell_voisines = {};
    for (auto it :cell.get_voisin_index() ){
        cell_voisines.push_back(this->cellules[it]);
    }
    return cell_voisines;
}

void Univers::update_cells() {
    for (auto &it : cellules) {
        auto &&vois = get_voisin_cellule(it);
        auto to_reassign = it.update_particules(rcut, vois);
        for (auto &&particule : to_reassign){
            //condition_limite_periodique(particule);
            assign_cell(move(particule));
        }
    }
}

void Univers::add_cellule(Cellule cell){
    cellules.push_back(std::move(cell));
}



void Univers::assign_cell(std::unique_ptr<AbstractPart> &&particule){
    auto it_cell = cellules.begin();
    bool has_been_assign = false;
    while (!has_been_assign && it_cell != cellules.end())
    {
        if ( (*it_cell).is_in_cell(particule, rcut)){
            (*it_cell).add_particule(move(particule));
            has_been_assign = true;
        } else{
            it_cell++;
        }
    }
    if ( has_been_assign != true && it_cell != cellules.end() ){
        throw std::range_error("la particule n'a pas des coordonées acceptable pour la simulation, pb de conditions limite");
    }
}

void Univers::affiche_univers(){
    for (auto &cell: cellules){
        cell.affiche_cellule();
    }
}

void Univers::affiche_voisin_cellule( Cellule &cell){
    int compteur = 0;
    for (auto index : cell.get_voisin_index()){
        std::array<int, 3>  coordonnes = cellules[index].get_pos();
        std::cout << "voisine numéro " << compteur<<": i=" << coordonnes[0] << " j=" << coordonnes[1] << " k=" << coordonnes[2]<< std::endl;
        compteur += 1;
    }
    std::cout << std::endl;
}

void Univers::affiche_all_part(){
    for (auto &cell : cellules){
        cell.affiche_part_cellule_id();
    }
}

/*
    *Créer N particules dans un endroit random de l'univers sans vitesse initiale
    *avec la même masse et qui vont avoir les mêmes forces qui agissent dessus
*/
void Univers::create_random_part(int N, double masse, const Flag &flag){
    this->nbre_particules += N;
    for(long i=0; i<N; i++){
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis_x(0.0, ld[0]);
        std::uniform_real_distribution<> dis_y(0.0, ld[1]);
        std::uniform_real_distribution<> dis_z(0.0, ld[2]);
        Point pos_part, empty;
        if (dim == 1){
            pos_part = Point(dis_x(gen), 0, 0);
        }else if (dim == 2){
            pos_part = Point(dis_x(gen), dis_y(gen), 0);
        } else{
            pos_part = Point(dis_x(gen), dis_y(gen), dis_z(gen));
        }
        this->create_particule(pos_part, empty, masse, this->nbre_particules+i, flag);
    }
}

void Univers::condition_limite_periodique(std::unique_ptr<AbstractPart> &particule){
    Point p;
    if (dim <= 1){
        p += Point(fabs(fmod(particule->get_position()(0), ld[0])),0,0);
    } if (dim <= 2){
        p += Point(0, fabs(fmod(particule->get_position()(1), ld[1])), 0);
    } if (dim <= 3){
        p += Point(0, 0, fabs(fmod(particule->get_position()(2), ld[2])));
    }
    particule->set_position(p);

}

void Univers::condition_limite_absorption(std::unique_ptr<AbstractPart> &particule){
    particule.release();
}

void Univers::condition_limite_reflexive(std::unique_ptr<AbstractPart> &particule){
    Point p;
    if (particule->get_position()(0) < 0 || particule->get_position()(0)>ld[0] ){
        p = Point(-particule->get_position()(0), particule->get_position()(1), particule->get_position()(2));
    }
    else if (particule->get_position()(1) < 0 || particule->get_position()(1)>ld[1] ){
        p = Point(particule->get_position()(0), -particule->get_position()(1), particule->get_position()(2));
    } else if (particule->get_position()(2) < 0 || particule->get_position()(2)>ld[2] ){
        p = Point(particule->get_position()(0), particule->get_position()(1), -particule->get_position()(2));
    }
    particule->set_position(p);
}

void Univers::create_particule(Point &position, Point &vitesse, double masse, bool active, Flag f){
    auto p = Point();
    this->create_particule_avec_force(position, vitesse, p, p, masse, active, f);
}


void Univers::create_particule_avec_force(Point &position, Point &vitesse, Point &force, Point &old_force, double masse, bool active, Flag f){
    int cat = f();
    std::unique_ptr<AbstractPart> p = std::make_unique<Particule>(position, vitesse,
    force, old_force, masse, this->nbre_particules, cat, true, this->dim);

    if (f[GRAVITY]) {
        p = std::make_unique<GravDecorator>(move(p));
    }
    if (f[LENNARD]) {
        p = std::make_unique<LennardDecorator>(move(p));
    }

    //this->condition_limite_periodique(p);
    this->assign_cell(move(p));
    this->nbre_particules++;
}


void Univers::simulation(double tend, double delta_t, bool afficher){
    compute_forces();

    for (double current_t = 0; current_t < tend; current_t += delta_t) {
        simulation_step(delta_t);
        if (afficher) affiche_all_part();
    }
}

void Univers::simulation_step(double delta_t) {
    compute_positions(delta_t);
    compute_forces();
    compute_velocities(delta_t);
    update_cells();
}

void Univers::compute_positions(double delta_t) {
    for (auto &&cell : this->cellules) {
        cell.cell_compute_positions(delta_t);
    }
}

void Univers::compute_velocities(double delta_t) {
    for (auto &&cell : this->cellules) {
        cell.cell_compute_velocities(delta_t);
    }
}

void Univers::compute_forces() {
    for (auto &&cell : this->cellules){
        cell.cell_compute_forces(this->rcut, get_voisin_cellule(cell));
    }
}

void Univers::set_dim(const int dim){
    this->dim = dim;
}
void Univers::set_nb_part(const long nbre_particules){
    this->nbre_particules = nbre_particules;
}

void Univers::set_ld(const std::array<double,3> ld){
    this->ld = ld;
}
void Univers::set_rcut(const double rcut){
    this->rcut = rcut;
}

void Univers::set_epsilon(const double epsilon){
    this->epsilon = epsilon;
}
void Univers::set_sigma(const double sigma){
    this->sigma = sigma;
}

void Univers::set_ncd(){
    for (int k=0; k<3; k++){
        this->ncd[k] = floor(this->ld[k]/this->rcut);
    }
}

    // Getter 

std::vector<Cellule> & Univers::get_list_cell(){
    return this->cellules;
}
int Univers::get_dim(){
    return this->dim;
}
long Univers::get_nbre_part(){
    return this->nbre_particules;
}

std::array<double,3> Univers::get_ld(){
    return this->ld;
}
double Univers::get_rcut(){
    return this->rcut;
}
double Univers::get_epsilon(){
    return this->epsilon;
}
double Univers::get_sigma(){
    return this->sigma;
}