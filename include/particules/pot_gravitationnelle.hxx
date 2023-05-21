/**
 * @file grav_decorator.hxx
 * @brief Header pour la classe PotGravDecorator
 */
#pragma once

#include "part_decorator.hxx"

/**
 * @brief Décorateur pour ajouter une force de gravité à une particule ( champ de pesanteur)
 * 
 * Cette classe est un décorateur pour une particule qui ajoute une force de
 * gravité entre deux particules dans l'espace.
 */
class PotGravDecorator : public PartDecorator {
public:
    /**
     * @brief Constructeur de PotGravDecorator
     * 
     * Ce constructeur crée un nouveau décorateur pour une particule en ajoutant
     * une force de gravité à la particule.
     * 
     * @param wrapee Un pointeur unique vers la particule à décorer.
     */
    PotGravDecorator(std::unique_ptr<AbstractPart> wrapee);
    PotGravDecorator(PotGravDecorator&&) = default;

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
};
