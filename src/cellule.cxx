#include "cellule.hxx"

Cellule::Cellule(const std::array<int, 3> pos, int dim)
{
    set_pos(pos);
    this->dim = dim;
}

Cellule::Cellule(int dim){
    this->pos_maille = {0,0,0};
    this->dim = dim;
}


bool Cellule::is_voisine(const Cellule &cell) const {
    std::array<int, 3> cell_pos = cell.get_pos();
    bool res = false;

    for (int i = 0; i < dim; i++) {
        res = res || std::abs(this->pos_maille[i] - cell_pos[i]) <= 1;
    }

    return res;
}

bool Cellule::is_in_cell(const std::unique_ptr<AbstractPart> &part, double rcut) const {
    Point position_part = part->get_position();
    if (position_part(0) >= this->pos_maille[0]*rcut
        && (position_part(1) >= this->pos_maille[1]*rcut )
        && (position_part(2) >= this->pos_maille[2]*rcut )
        && (position_part(0) <= (this->pos_maille[0]+1)*rcut )
        && (position_part(1) <= (this->pos_maille[1]+1)*rcut )
        && (position_part(2) <= (this->pos_maille[2]+1)*rcut )
    ){
        return true;
    }
    return false;
}



void Cellule::affiche_cellule() const {
    if (!this->particules.empty()){
        std::cout << "Coordonées de la cellule de dim "<<this->dim<<" : x =" << this->pos_maille[0] << ",y =" << this->pos_maille[1] << ", z =" << this->pos_maille[2] << std::endl;
        std::cout << "Particules sur cette cellule :" << std::endl;
        for (auto &&part : this->particules){
            part->affiche();
        }
    }

}

void Cellule::affiche_part_cellule() const {
    for (auto &&part : this->particules){
        part->affiche_graphique();
    }
}
void Cellule::affiche_part_cellule_id() const {
    for (auto &&part : this->particules){
        part->affiche_graphique_id();
    }
}
void Cellule::add_particule(std::unique_ptr<AbstractPart> part){
    if (part->get_dim() != this->dim){
        throw std::range_error("dimension de la particule != de l'univers");
    }
    this->particules.emplace_back(std::move(part));
}

void Cellule::remove_particule(std::unique_ptr<AbstractPart> &part){
    this->particules.remove(part);
}

std::list<std::unique_ptr<AbstractPart>> Cellule::update_particules(double rcut, std::list<std::reference_wrapper<Cellule>> &voisins) {
    std::list<std::unique_ptr<AbstractPart>> part_to_reasign;
    std::list<decltype(this->particules.begin())> to_remove;

    for (auto part_it = this->particules.begin(); part_it != this->particules.end(); ++part_it) {
        bool reassigned = false;

        if (!this->is_in_cell(*part_it, rcut)) {
            for (auto &it2: voisins){
                if (it2.get().is_in_cell(*part_it ,rcut)){
                    it2.get().add_particule(std::move(*part_it));
                    to_remove.push_back(part_it);
                    reassigned = true;
                    break;
                }
            }
            if (!reassigned){
                part_to_reasign.emplace_back(std::move(*part_it));
                to_remove.push_back(part_it);
            }
        }
    }

    for(auto &it : to_remove){
        this->particules.erase(it);
    }

    return part_to_reasign;
}


void Cellule::cell_compute_forces(double rcut, std::list<std::reference_wrapper<Cellule>> cell_voisine){
    for (auto &&part_i = this->particules.begin(); part_i != this->particules.end(); part_i++) {
        (*part_i)->compute_pot();
        for(auto &&cell : cell_voisine){
            for (auto &&part_j = cell.get().particules.begin(); part_j != cell.get().particules.end(); part_j++){
                if (*part_i != *part_j){
                    auto &p_i = *part_i;
                    auto &p_j = *part_j;
                    p_i->compute_force(p_j);
                }
            }
        }
    }
}

void Cellule::cell_compute_positions(double delta_t) {
    for (auto &&part : this->particules) {
        part->advance_position(delta_t);
    }
}

void Cellule::cell_compute_velocities(double delta_t) {
    for (auto &&part : this->particules) {
        part->advance_velocity(delta_t);
    }
}

bool Cellule::operator==(const Cellule &otherCell) const {
  std::array<int, 3> cell_pos = otherCell.get_pos();
  if( ( cell_pos[0]==this->pos_maille[0] ) && ( cell_pos[1]==this->pos_maille[1] ) && ( cell_pos[2]==this->pos_maille[2] )){
    return true;
  }
  return false;
}

inline bool Cellule::operator!=(const Cellule &otherCell) const {
    return !(*this == otherCell);
}

//Getter 


std::list<int> Cellule::get_voisin_index() const{
    return this->index_voisins;
}

std::array<int, 3> Cellule::get_pos() const {
    return this->pos_maille;
}
int Cellule::get_dim() const {
    return this->dim;
}

//Setter

void Cellule::set_voisin(const std::list<int> &index_voisins){
    this->index_voisins = index_voisins;
}
void Cellule::set_pos(const std::array<int, 3> pos){
    for (int i = 0; i < 3; i++) {
        this->pos_maille[i] = pos[i];
    }
}

