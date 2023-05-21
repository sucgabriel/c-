/**
 * @file lennard_decorator.hxx
 * @brief Header pour la classe LennardDecorator
 */
#pragma once

#include "part_decorator.hxx"

extern const double epsilon, sigma, rcut;

/**
 * @brief Décorateur pour ajouter le calcul de la force de Lennard à une particule
 * 
 * Cette classe est un décorateur pour une particule qui ajoute le calcul de la
 * force de Lennard lors du calcul des forces entre deux particules dans l'espace.
 */
class LennardDecorator : public PartDecorator {
public:
    /**
     * @brief Constructeur de LennardDecorator
     * 
     * Ce constructeur crée un nouveau décorateur pour une particule en ajoutant
     * le calcul de la force de Lennard lors du calcul des forces entre deux
     * particules.
     * 
     * @param wrapee Un pointeur unique vers la particule à décorer.
     */
    LennardDecorator(std::unique_ptr<AbstractPart> wrapee);
    LennardDecorator(LennardDecorator&&) = default;

    /**
     * @brief Calcul de la force de Lennard entre deux particules
     * 
     * Cette méthode calcule le module de la force de Lennard entre cette particule et une
     * autre particule donnée
     * 
     * @param r La distance (au carré) entre les deux particules.
     * @param mass La masse de la seconde particule.
     */
    double calc_force(double r, double mass);

};