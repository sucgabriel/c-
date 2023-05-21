#include "particules/lennard_decorator.hxx"

const double sigma = 1, epsilon = 1, rcut = 1;

LennardDecorator::LennardDecorator(std::unique_ptr<AbstractPart> wrapee) :
    PartDecorator(move(wrapee)) {}

double LennardDecorator::calc_force(double r, double masse) {
    double f = 0;
    if (r <= rcut){
      f = 24 * epsilon *(1/r) *( pow(sigma/std::sqrt(r), 6) * (1 - 2*pow(sigma/std::sqrt(r), 6)));
    }

    return f;
}