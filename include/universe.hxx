#pragma once
#include <vector>
#include <memory>

#include "particules/particules.hxx"
#include "abstract_uni.hxx"

/**
 * @brief La classe Universe représente l'univers de la simulation ( avant tp4 donc sans cellule).
 */
class Universe: public AbstractUni {
    public:
    /**
     * @brief Réalise une simulation de l'univers
     * @param tend Le temps total de la simulation.
     * @param delta_t Le pas de calcul utilisé dans la simulation
     */
    void simulation(double tend, double delta_t);


    /**
     * @brief Réalise un pas de la simulation
     * @param delta_t Le pas utilisé lors de la simulation
    */
    void simulation_step(double delta_t);

    /**
     * @brief Réalise le calcul des forces pour une étape de la simulation
    */
    void compute_forces();

    /**
     * @brief Réalise le déplacement des particules et stocke les ancienne valeurs de force pour le prochain calcul
     * @param delta_t Le pas utilisé lors de la simulation
    */
    void compute_positions(double delta_t);

    /**
     * @brief Réalise la calcul des vitesses pour une étape de la simulation
     * @param delta_t Le pas utilisé lors de la simulation
    */
    void compute_velocities(double delta_t);

    /**
     * @brief Ajoute une particule à l'univers
     * @param position position initiale de la particule
     * @param vitesse vitesse initiale de la particule
     * @param force force initiale de la particule
     * @param old_force ancienne force de la particule
     * @param masse masse de la particule
     * @param id identifiant de la particule
     * @param categorie catégorie de la particule
     * @param active statut actif/inactif de la particule
     * @param dim la dimension de la particule 
    */
    void add_particule(const Point &position, const Point &vitesse, const Point &force,
    const Point &old_force, double masse, Flag f);

    /**
     * @brief Ajoute des copies de la particule donnée à l'univers
     * @param n le nombre de copies à ajouter
     * @param part la particule modèle qui va être copiée
     * @param flag Les flags permettant de mettre en place les décorateurs de force
    */
    void add_copy_particules(int n, const Particule & part, Flag f);

    /**
     * @brief Fonction qui rajoute des particules à des endroits aléatoire de l'univers
     * @param nb : nombre de particules random qui vont se rajouter au sein de l'univers
     * @param masse : masse des particules random qui vont se créer
     * @param Flag : force qui s'applique sur toute les particules
    */
    void createPartRandomly(long , double , const Flag &);

    //Affiche l'état de l'Univers : 
    void afficheUniverse();

    //Constructeur : 
    Universe(int dim);

    //Destructeur: 
    ~Universe() = default;

    private:
    /**
     * Liste des particules de l'univers
    */
    std::vector<std::unique_ptr<AbstractPart>> particules;
    /**
     * @brief Dimension de l'univers
     */
    int dim;
    /**
     * @brief Nombre de particules dans l'univers
     */
    long nbre_particules = 0;
};