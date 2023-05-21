#include "particules/grav_decorator.hxx"

GravDecorator::GravDecorator(std::unique_ptr<AbstractPart> wrapee)
    : PartDecorator(move(wrapee)) {}

double GravDecorator::calc_force(double r, double mass) {
    return (this->get_mass() * mass) / (r * std::sqrt(r));

}