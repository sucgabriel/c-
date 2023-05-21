
/**
 * @file particules.hxx
 * @brief Header pour la classe Particule
 */
#pragma once
#include <list>

#include "abstract_part.hxx"
#include "../point.hxx"

/**
 * @brief La classe Particule représente une particule dans l'espace de la simulation.
 */
class Particule : public AbstractPart{
  public :

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
     * @brief Affiche uniquement la position de la particule
     * 
     */
    void affiche_position() const;

    /**
     * @brief Affiche uniquement la vitesse de la particule
     * 
     */
    void affiche_vitesse() const;

    /**
     * @brief Affiche uniquement la force de la particule
     * 
     */
    void affiche_force() const;

    /**
     * @brief Calcule la distance entre 2 particules
     * 
     */
    double distance(AbstractPart const &p) const;

    /**
     * @brief Met à jour la position de la particule en fonction de sa vitesse et du temps écoulé
     * 
     * @param dt Le pas de temps
     */
    void advance_position(double dt);

    /**
     * @brief Met à jour la vitesse de la particule en fonction de la force qui lui est appliquée et du temps écoulé,
     * et stocke la force pour des futurs calculs.
     * 
     * @param dt Le pas de temps
     */
    void advance_velocity(double dt);

    Point compute_force(std::unique_ptr<AbstractPart> &other);
    void compute_pot(){};

    // Constructeur 

    /**
     * @brief Constructeur pour une particule en dimension donnée ( Attention : dim non spécifiée, dangereux)
     * @param position position initiale de la particule
     * @param vitesse vitesse initiale de la particule
     * @param force force initiale de la particule
     * @param old_force ancienne force de la particule
     * @param masse masse de la particule
     * @param id identifiant de la particule
     * @param categorie catégorie de la particule
     * @param active statut actif/inactif de la particule
     */
    Particule(const Point &position, const Point &vitesse, const Point &force, const Point &old_force, double masse, int id, int categorie, bool active);
     /**
     * @brief Constructeur pour une particule en dimension donnée
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
    Particule(const Point &position, const Point &vitesse, const Point &force, const Point &old_force, double masse, int id, int categorie, bool active, int dim );

    Particule(Particule &&) = default;

    // Destructeur
    ~Particule() = default;

    // Opérateur 
    bool operator==(const Particule &);
    bool operator!=(const Particule &);

    //Getter
    
    /**
     * @brief Getter pour la position de la particule
     * 
     * Cette méthode retourne la position actuelle de la particule.
     * 
     * @return La position actuelle de la particule.
     */
    Point get_position() const;

    /**
     * @brief Getter pour la vitesse de la particule
     * 
     * Cette méthode retourne la vitesse actuelle de la particule.
     * 
     * @return La vitesse actuelle de la particule.
     */
    Point get_velocity() const;

    /**
     * @brief Getter pour la force appliquée sur la particule
     * 
     * Cette méthode retourne la force actuelle appliquée sur la particule.
     * 
     * @return La force actuelle appliquée sur la particule.
     */
    Point get_force() const;

    /**
     * @brief Getter pour l'ancienne force appliquée sur la particule
     * 
     * Cette méthode retourne la force précédemment appliquée sur la particule,
     * utilisée pour calculer la nouvelle force dans l'algorithme de simulation.
     * 
     * @return L'ancienne force appliquée sur la particule.
     */
    Point get_force_old() const;

    /**
     * @brief Getter pour l'identifiant de la particule
     * 
     * Cette méthode retourne l'identifiant unique de la particule.
     * 
     * @return L'identifiant unique de la particule.
     */
    int get_id() const;

    /**
     * @brief Getter pour la masse de la particule
     * 
     * Cette méthode retourne la masse de la particule.
     * 
     * @return La masse de la particule.
     */
    double get_mass() const;

    /**
     * @brief Getter pour la dimension de l'espace
     * 
     * Cette méthode retourne la dimension de l'espace dans lequel évolue la
     * particule (par exemple 2 ou 3).
     * 
     * @return La dimension de l'espace.
     */
    int get_dim() const;

    /**
     * @brief Setter pour la force appliquée sur la particule
     * 
     * Cette méthode modifie la force actuelle appliquée sur la particule.
     * 
     * @param force La nouvelle force appliquée sur la particule.
     */
    void set_force( const Point &force);

    /**
     * @brief Setter pour l'ancienne force appliquée sur la particule
     * 
     * Cette méthode modifie la force précédemment appliquée sur la particule,
     * utilisée pour calculer la nouvelle force dans l'algorithme de simulation.
     * 
     * @param force_old La nouvelle ancienne force appliquée sur la particule.
     */
    void set_force_old( const Point &force_old);

    /**
     * @brief Setter pour le statut de la particule
     * 
     * Cette méthode modifie le statut de la particule (active ou inactive).
     * 
     * @param statut Le nouveau statut de la particule (true pour active, false pour inactive).
     */
    void set_statut(bool statut);

    /**
     * @brief Setter pour la position de la particule
     * 
     * Cette méthode modifie la position actuelle de la particule.
     * 
     * @param pos La nouvelle position de la particule.
     */
    void set_position(const Point& pos);


    private: 
    /**
     * @brief Position de la particule
     * 
     * Cette variable contient la position actuelle de la particule dans l'espace.
     * @param position
     */
    Point position;

    /**
     * @brief Vitesse de la particule
     * 
     * Cette variable contient la vitesse actuelle de la particule.
     */
    Point vitesse;

    /**
     * @brief Force actuelle appliquée sur la particule
     * 
     * Cette variable contient la force actuelle appliquée sur la particule.
     */
    Point force;

    /**
     * @brief Ancienne force appliquée sur la particule
     * 
     * Cette variable contient la force précédemment appliquée sur la particule,
     * utilisée pour calculer la nouvelle force dans l'algorithme de simulation.
     * 
     * Cette variable est utilisée pour des fins algorithmiques uniquement et ne
     * doit pas être modifiée directement.
     */
    Point force_old;

    /**
     * @brief Masse de la particule
     * 
     * Cette variable contient la masse de la particule.
     */
    double masse;

    /**
     * @brief Dimension de l'espace
     * 
     * Cette variable contient la dimension de l'espace dans lequel évolue la
     * particule (par exemple 2 ou 3).
     */
    int dim;

    /**
     * @brief Identifiant de la particule
     * 
     * Cette variable contient l'identifiant unique de la particule.
     */
    int id;

    /**
     * @brief Catégorie de la particule
     * 
     * Cette variable contient une catégorie (ou un descripteur) pour la particule,
     * qui peut être utilisée pour regrouper des particules de manière sémantique.
     */
    int categorie;

    /**
     * @brief Statut de la particule
     * 
     * Cette variable indique si la particule est active ou inactive. Une particule
     * inactive peut être ignorée par l'algorithme de simulation.
     */
    bool active;


};