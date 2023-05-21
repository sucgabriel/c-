/**
 * @file part_decorator.hxx
 * @brief Header pour la classe PartDecorator
 */
#pragma once

#include <memory>

#include "abstract_part.hxx"

/**
 * @brief Décorateur pour la classe particule
 */
class PartDecorator: public AbstractPart {
    public:

    /**
     * @brief Affiche les informations générales de la particule (position, vitesse et force)
     * 
     */
    void affiche() const;

    /**
     * @brief Fonction d'affichage utilisée par le script python qui permet d'afficher la simulation. 
     * 
     */
    void affiche_graphique() const;

    /**
     * @brief Fonction d'affichage utilisée par le script python qui permet d'afficher la simulation. 
     * 
     */
    void affiche_graphique_id() const;

    /**
     * @brief Calcule la distance entre 2 particules
     * 
     */
    double distance(const AbstractPart &p) const;

    /**
     * @brief Met à jour la position de la particule en fonction de sa vitesse et du temps écoulé
     * 
     * @param dt Le pas de temps
     */
    void advance_position(double dt);

    /**
     * @brief Met à jour la vitesse de la particule en fonction de la force qui lui est appliquée et du temps écoulé
     * 
     * @param dt Le pas de temps
     */
    void advance_velocity(double dt);

    // Getters et Setters

    Point get_position() const;
    void set_position(const Point&);
    Point get_force() const;
    void set_force(const Point &);
    int get_dim() const;
    double get_mass() const;
    int get_id() const;

    // Interfaces pour les décorateurs

    /**
     * @brief Calcule les forces appliquées en utilisant les décorateurs
     * 
     * @param other La seconde particule utilisée pour le calcul de force
     * @return Le Point correspondant à la force calculée
    */
    Point compute_force(std::unique_ptr<AbstractPart> &other);

    virtual double calc_force(double r, double masse) = 0;
    void compute_pot(){};
    // Constructeur

    PartDecorator(std::unique_ptr<AbstractPart> wrapee);
    PartDecorator(PartDecorator&&) = default;

    protected:
    /**
     * @brief pointeur vers le fils 
     * @property wrapee
    */
    std::unique_ptr<AbstractPart> wrapee;

};