#include "particules/part_decorator.hxx"

void PartDecorator::affiche() const {
    wrapee->affiche();
}

void PartDecorator::affiche_graphique() const {
    wrapee->affiche_graphique();
}

void PartDecorator::affiche_graphique_id() const {
    wrapee->affiche_graphique_id();
}

double PartDecorator::distance(const AbstractPart & other) const {
    return wrapee->distance(other);
}

void PartDecorator::advance_position(double dt) {
    wrapee->advance_position(dt);
}

void PartDecorator::advance_velocity(double dt) {
    wrapee->advance_velocity(dt);
}

Point PartDecorator::get_position() const {
    return wrapee->get_position();
}

void PartDecorator::set_position(const Point & p) {
    wrapee->set_position(p);
}

Point PartDecorator::get_force() const {
    return wrapee->get_force();
}

void PartDecorator::set_force(const Point &new_force) {
    wrapee->set_force(new_force);
}

int PartDecorator::get_dim() const {
    return wrapee->get_dim();
}
    
double PartDecorator::get_mass() const {
    return wrapee->get_mass();
}

int PartDecorator::get_id() const {
    return wrapee->get_id();
}

PartDecorator::PartDecorator(std::unique_ptr<AbstractPart> wrapee) {
    this->wrapee = move(wrapee);
}

Point PartDecorator::compute_force(std::unique_ptr<AbstractPart> &other){
    double r = 0;
    /// Calcul du vecteur résultat
    Point orientation = other->get_position() - this->get_position();
    r = orientation * orientation;
    orientation *= this->calc_force(r, other->get_mass());
    this->set_force(this->get_force() + orientation);
    return wrapee->compute_force(other) + orientation;
}