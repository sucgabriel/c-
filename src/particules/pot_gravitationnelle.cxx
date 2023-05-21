#include "particules/pot_gravitationnelle.hxx"

const double G = 9.81;

PotGravDecorator::PotGravDecorator(std::unique_ptr<AbstractPart> wrapee)
    : PartDecorator(move(wrapee)) {}

double PotGravDecorator::calc_force(double r, double mass) {
    return 0;
}

void PotGravDecorator::compute_pot(){
    this->set_force(this->get_force() + Point(0,-this->get_mass() *G,0));
}