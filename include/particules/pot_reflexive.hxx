/**
 * @file grav_decorator.hxx
 * @brief Header pour la classe PotReflexiveDecorator
 */
#pragma once

#include "part_decorator.hxx"

/**
 * @brief Décorateur pour prendre en compte une force qui correspond à la condition limite reflexive
 * 
 * Cette classe est un décorateur pour une particule qui ajoute une force pour repousser de manière reflexive les particules du bord de l'univers
 */
class PotReflexiveDecorator : public PartDecorator {
public:
    /**
     * @brief Constructeur de PotReflexiveDecorator
     * 
     * Ce constructeur crée un nouveau décorateur pour une particule en ajoutant
     * une force qui correspond à la condition limite réfléxive.
     * 
     * @param wrapee Un pointeur unique vers la particule à décorer.
     * @param ld dimension de l'univers
     */
    PotReflexiveDecorator(std::unique_ptr<AbstractPart> wrapee, std::array<double,3> ld);
    PotReflexiveDecorator(PotReflexiveDecorator&&) = default;

    /**
     * @brief Applique la force de pesanteur à la particules
     * 
     * Cette méthode calcule le module de la force de Gravitation entre cette particule et une
     * autre particule donnée
     * 
     * @param r parametre de distance entre 2 particules dans le cas général, inutile ici
     * @param mass La masse de la seconde particule.
     */
    double calc_force(double r, double mass);

    void compute_pot();
private:
    std::array<double,3> ld = {0,0,0};
};
