/**
 * @file grav_decorator.hxx
 * @brief Header pour la classe GravDecorator
 */
#pragma once

#include "part_decorator.hxx"

/**
 * @brief Décorateur pour ajouter une force de gravité à une particule
 * 
 * Cette classe est un décorateur pour une particule qui ajoute une force de
 * gravité entre deux particules dans l'espace.
 */
class GravDecorator : public PartDecorator {
public:
    /**
     * @brief Constructeur de GravDecorator
     * 
     * Ce constructeur crée un nouveau décorateur pour une particule en ajoutant
     * une force de gravité à la particule.
     * 
     * @param wrapee Un pointeur unique vers la particule à décorer.
     */
    GravDecorator(std::unique_ptr<AbstractPart> wrapee);
    GravDecorator(GravDecorator&&) = default;

    /**
     * @brief Calcul de la force de Gravitation entre deux particules
     * 
     * Cette méthode calcule le module de la force de Gravitation entre cette particule et une
     * autre particule donnée
     * 
     * @param r La distance (au carré) entre les deux particules.
     * @param mass La masse de la seconde particule.
     */
    double calc_force(double r, double mass);
};
