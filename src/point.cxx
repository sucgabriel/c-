#include "point.hxx"

Point::Point():val({0,0,0}){}

Point::Point(const Point &p){
  for (int i = 0; i < 3; i++) {
    this->val[i] = p.val[i];
  }
}

void Point::normalize(){
  float norme = std::sqrt(val[0]*val[0] + val[1]*val[1] + val[2]*val[2]);
  val[0] = val[0]/norme;
  val[1] = val[1]/norme;
  val[2] = val[2]/norme;
}
Point &Point::operator=(const Point &p){
  this->val[0] = p.val[0];
  this->val[1] = p.val[1];
  this->val[2] = p.val[2];
 
  return *this;
}

Point Point::operator+(const Point &p) const {
  return Point(p.val[0]+val[0],p.val[1]+val[1],p.val[2]+val[2]);
}

Point & Point::operator+=(const Point &p){
  for(auto k =0 ; k < 3; ++k) {
    this->val[k] += p.val[k];
  }
  return *this;
}

Point Point::operator-(const Point &p) const {
  return Point(val[0]-p.val[0],val[1]-p.val[1],val[2]-p.val[2]);
}

Point & Point::operator-=(const Point &p){
  for(auto k =0 ; k < 3; ++k) {
    this->val[k] -= p.val[k];
  }
  return *this;
}

Point & Point::operator*=(double s){
  for(auto k =0 ; k < 3; ++k) {
    val[k] *= s;
  }
  return *this;
}

Point Point::operator*(double s) const {
  return Point(s*val[0], s*val[1], s*val[2]);
}

double Point::operator*(const Point &p) const {
  double d = 0;
  for (auto k = 0; k <3; k++) {
    d += val[k] * p.val[k];
  }
  return d;
}

bool Point::operator==(const Point & other) const {
  return val[0] == other.val[0] && val[1] == other.val[1] && val[2] == other.val[2];
}

bool Point::operator!=(const Point & other) const {
  return !(*this == other);
}
double Point::operator()(int k){
    return val[k];
}

double Point::operator()(int k) const {
    return val[k];
}


std::ostream & operator<<(std::ostream & out, const Point & p){
  for(auto v:p.val){
    out<<v<<" ";
  }
  return out;
}

Point::~Point(){}

/**
 * @brief Constructeur à partir de coordonnées.
 * @param x La coordonnée x.
 * @param y La coordonnée y.
 * @param z La coordonnée z.
 */
Point::Point(double x, double y, double z){
  val = {x,y,z};
}

Point operator*(double lambda, const Point &point){
  return point*lambda;
}

 Point Point::operator-() const{
    return Point(-val[0], -val[1], -val[2]);
 }