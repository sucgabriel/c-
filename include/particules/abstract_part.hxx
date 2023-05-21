/**
 * @file abstract_part.hxx
 * @brief Header pour la classe AbstractPart
 */
#pragma once

#include <bitset>
#include <memory>

#include "../point.hxx"

/**
 * @brief Interface pour les particules, qui sera utilisée par les clients comme la classe Univers
 */
class AbstractPart {
    public:
    /**
     * @brief Affiche les informations générales de la particule (position, vitesse et force)
     * 
     */
    virtual void affiche() const = 0;

    /**
     * @brief Fonction d'affichage utilisée par le script python qui permet d'afficher la simulation. 
     * 
     */
    virtual void affiche_graphique() const = 0;

    /**
     * @brief Fonction d'affichage utilisée par le script python qui permet d'afficher la simulation.
     * Affiche également l'ID de la particule. 
     * 
     */
    virtual void affiche_graphique_id() const = 0;

    /**
     * @brief Calcule la distance entre 2 particules
     * 
     */
    virtual double distance(AbstractPart const &p) const = 0;

    /**
     * @brief Met à jour la position de la particule en fonction de sa vitesse et du temps écoulé
     * 
     * @param dt Le Spas de temps
     */
    virtual void advance_position(double dt) = 0;

    /**
     * @brief Met à jour la vitesse de la particule en fonction de la force qui lui est appliquée et du temps écoulé
     * 
     * @param dt Le pas de temps
     */
    virtual void advance_velocity(double dt) = 0;

    // Getters et Setters

    virtual Point get_position() const = 0;
    virtual void set_position(const Point&) = 0;
    virtual Point get_force() const = 0;
    virtual void set_force(const Point &) = 0;
    virtual int get_dim() const = 0;
    virtual double get_mass() const = 0;
    virtual int get_id() const = 0;



    // Interfaces pour les décorateurs

    /**
     * @brief Calcule les forces appliquées en utilisant les décorateurs
     * 
     * @param other La seconde particule utilisée pour le calcul de force
    */
    virtual Point compute_force(std::unique_ptr<AbstractPart> &other) = 0;

    /**
     * 
     * @brief Calcule les forces liées aux potentiels 
    */
    virtual void compute_pot() = 0;

    AbstractPart(const AbstractPart&) = delete;
    AbstractPart() = default;
    AbstractPart(AbstractPart &&) = default;
    virtual ~AbstractPart() = default;
};

enum Categories : std::uint8_t {
    GRAVITY,
    LENNARD,
    NB_CAT
};

class Flag {
    private:
    std::bitset<NB_CAT> bits = {};

    public:
    void set(uint8_t n);
    void set(const Flag &multi_flag);
    void unset(uint8_t n);
    void unset(const Flag &multi_flag);
    void flip(uint8_t n);
    void flip(const Flag &multi_flag);

    bool operator[](uint8_t n) const;
    bool operator[](const Flag &multi_flag) const;
    uint8_t operator()() const;

    Flag operator|(const Flag &other) const;
    Flag& operator|=(const Flag &other);

    Flag operator&(const Flag &other) const;
    Flag& operator&=(const Flag &other);

    bool operator==(uint8_t n) const;
    bool operator==(const Flag &f) const;

    Flag(std::bitset<NB_CAT> bits);
    Flag(uint8_t n);
};

namespace std {

template<>
struct hash<AbstractPart *>
{
    size_t operator()(AbstractPart const *f) const
    {
        return f->get_id();
    }
};

} // namespace std
