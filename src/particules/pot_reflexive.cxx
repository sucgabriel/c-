#include "particules/pot_reflexive.hxx"

const double epsilon =1 , sigma = 1;

PotReflexiveDecorator::PotReflexiveDecorator(std::unique_ptr<AbstractPart> wrapee, std::array<double,3> ld)
    : PartDecorator(move(wrapee)) {this->ld = ld;}

double PotReflexiveDecorator::calc_force(double r, double mass) {
    return 0;
}

void PotReflexiveDecorator::compute_pot(){
    double r_x = 0;
    double r_y = 0;
    double r_z = 0;
    double f_x = 0;
    double f_y = 0;
    double f_z = 0;
    Point pos  =this->get_position();

    r_x = fabs(std::min( (pos(0) - this->ld[0])*(pos(0) - this->ld[0]) , pos(0)*pos(0) ));
    r_y = fabs(std::min( (pos(1) - this->ld[1])*(pos(1) - this->ld[1]) , pos(1)*pos(1) ));
    r_z = fabs(std::min( (pos(2) - this->ld[2])*(pos(2) - this->ld[2]) , pos(2)*pos(2)));
    if (r_x != 0){
        f_x = - 24 * epsilon * (1 / (2*r_x)) * pow( (sigma/ (2*r_x)) , 6) * ( 1 - 2* pow( (sigma/(2*r_x)), 6));
    }
    if (r_y != 0){
        f_y = - 24 * epsilon * (1 / (2*r_y)) * pow( (sigma/ (2*r_y)) , 6) * ( 1 - 2* pow( (sigma/(2*r_y)), 6));
    }
    if (r_z != 0){
        f_z = - 24 * epsilon * (1 / (2*r_z)) * pow( (sigma/ (2*r_z)) , 6) * ( 1 - 2* pow( (sigma/(2*r_z)), 6));
    }
    this->set_force(this->get_force() + Point(f_x, f_y, f_z));
}