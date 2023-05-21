#include <iostream>
#include <cmath>

#include "particules/particules.hxx"

Particule::Particule(const Point &position, const Point &vitesse, const Point &force, const Point &old_force, double masse, int id, int categorie, bool active )
{
  this->position = position;
  this->vitesse= vitesse;
  this->force = force;
  this->force_old = old_force;
  this->masse = masse;
  this->id = id;
  this->categorie = categorie;
  this->active = active;
}

Particule::Particule(const Point &position, const Point &vitesse, const Point &force, const Point &old_force, double masse, int id, int categorie, bool active, int dim )
{
  this->position = position;
  this->vitesse= vitesse;
  this->force = force;
  this->force_old = old_force;
  this->masse = masse;
  this->dim = dim;
  this->id = id;
  this->categorie = categorie;
  this->active = active;
}

Point Particule::compute_force(std::unique_ptr<AbstractPart> &other) {
  return Point();
}

void Particule::affiche_position() const{
  std::cout<<position;
}

void Particule::affiche_vitesse() const{
  std::cout<<vitesse;
}

void Particule::affiche_force() const{
  std::cout<<force;
}

void Particule::affiche() const {
  this->affiche_position();
  std::cout<<" ";
  this->affiche_vitesse();
  std::cout<<" ";
  this->affiche_force();
  std::cout<<std::endl;
}

void Particule::affiche_graphique() const{
  for(int k=0; k<dim; k++){
    std::cout << position(k) << std::endl;
  }
  // affiche_position();
  // std::cout << '\n';
}

void Particule::affiche_graphique_id() const{
  std::cout << id << std::endl;
  for(int k=0; k<3; k++){
    std::cout << position(k) << std::endl ;
  }
}

double Particule::distance(const AbstractPart &p) const{
  Point orientation = p.get_position() - this->position;

  return std::sqrt(orientation*orientation);
}

void Particule::advance_position(double dt){
  this->position +=  dt * (this->vitesse + dt * (0.5/this->masse) *this->force);
  this->force_old = this->force;
  this->force = Point(0,0,0);
}

void Particule::advance_velocity(double dt){
  this->vitesse += (this->force + this->force_old)*dt*(0.5/this->masse);
}


// Operateur 
bool Particule::operator==(const Particule &otherPart){
  return otherPart.id == this->id;
}

bool Particule::operator!=(const Particule &otherPart){
  return !(*this == otherPart);
}

//Getter
Point Particule::get_position() const{
  return this->position;
}

Point Particule::get_velocity() const{
  return this->vitesse;
}

Point Particule::get_force() const {
  return this->force;
}

Point Particule::get_force_old() const {
  return this->force_old;
}

double Particule::get_mass() const {
  return this->masse;
}

int Particule::get_dim() const{
  return this->dim;
}

int Particule::get_id() const{
  return this->id;
}


void Particule::set_force(const Point &force){
  this->force = force;
}

void Particule::set_force_old(const Point &force_old){
  this->force_old = force_old;
}

void Particule::set_statut(bool statut){
  this->active = statut;
}

void Particule::set_position(const Point& pos){
  this->position = pos;
}
