#include "particules/particules.hxx"
#include "point.hxx"

void affiche_potentiel(int N);

void affiche_potentiel(int N){
    for (int i=2; i<N; i++){
        double r = i*3.0/N;
        std::cout<< r<< std::endl;
        double V = 4* (pow(1/r , 12) - pow(1/r , 6) );
        std::cout<< V << std::endl;
    }
}

int main(){
    affiche_potentiel(500);
}