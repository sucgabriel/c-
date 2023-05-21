/**
 * @file cellule.hxx
 * @brief Header pour la classe Cellule 
 */

#pragma once
#include <list>

#include "particules/abstract_part.hxx"
/**
 * @brief La classe Cellule représente une cellule de l'espace de la simulation qui va contenir des particules.
 */
class Cellule{
    public:

    /**
     * @brief Constructeur d'une cellule avec une position donnée.
     * @param pos_maille un tableau d'entiers représentant les coordonnées de la maille dans laquelle se trouve la cellule.
     * @param dim la dimension de l'univers.
     */
    Cellule(const std::array<int, 3> pos_maille, int dim);

    /**
     * @brief Constructeur d'une cellule sans position donnée. ( RISQUE ! )
     * @param dim la dimension de l'univers.
     */
    Cellule(int dim);

    Cellule(Cellule &) = delete;
    Cellule(Cellule &&) = default;

    /**
     * @brief Destructeur de la cellule.
     */
    ~Cellule() = default;

    /**
     * @brief Fonction qui permet de savoir si une cellule est voisine, dans ce cas l'ajoute dans la liste des voisines.
     * @param cell la cellule potentielle voisine.
     * @return vrai si les cellules sont voisines, faux sinon.
     * 
     * Cette fonction sera appelée lors de la construction du maillage pour déterminer les voisins de chaque cellule.
     */
    bool is_voisine(const Cellule & cell) const;

    /**
     * @brief Fonction qui permet de savoir si une particule est bien située dans la cellule.
     * @param particule la particule à vérifier.
     * @param rcut rayon de coupure de l'univers = taille d'une cellule
     * @return vrai si la particule est dans la cellule, faux sinon.
     */
    bool is_in_cell(const std::unique_ptr<AbstractPart> &part, double rcut) const;

    /**
     * @brief Fonction qui permet d'afficher le contenu d'une cellule.
     * 
     * Cette fonction affiche les informations de la cellule mais n'affiche pas les cellules voisines.
     */
    void affiche_cellule() const;
    /**
     * @brief Fonction qui permet d'afficher toute les particules sur la cellule 
    */
    void affiche_part_cellule() const;
    /**
     * @brief Fonction qui permet d'afficher toute les particules sur la cellule ( affiche aussi l'id de la particule)
    */
    void affiche_part_cellule_id() const;
    /**
     * @brief Ajoute une particule dans la liste de particules de la cellule.
     * @param particule la particule à ajouter.
     */
    void add_particule(std::unique_ptr<AbstractPart> part);

    /**
     * @brief Fonction qui permet de supprimer une particule de la cellule.
     * @param particule la particule à supprimer.
     */
    void remove_particule(std::unique_ptr<AbstractPart> &part);

    /**
     * @brief Fonction qui permet de mettre à jour l'appartenances des particules à la cellule
     * @param cells_voisines les cellules voisines de current dans l'univers englobant.
     * @return Les particules qui ne sont pas restées dans la cellule ou deans les cellules voisines, et que l'univers doit réassigner.
     */
    std::list<std::unique_ptr<AbstractPart>> update_particules(double rcut, std::list<std::reference_wrapper<Cellule>> &cells_voisines);

    /**
     * @brief Fonction qui permet de calculer les forces des particules de la cellules
     * @param rcut : rayon de coupure de l'univers
     * @param cell_voisine : cellules voisines
    */
    void cell_compute_forces(double rcut, std::list<std::reference_wrapper<Cellule>> );
    
    /**
     * @brief Fonction qui permet de mettre à jour la vitesse des particules sur la cellule
     * @param delta_t : pas de temps 
    */
    void cell_compute_velocities(double delta_t);
    /**
     * @brief Fonction qui permet de mettre à jour la position des particules sur la cellule
     * @param delta_t : pas de temps 
    */
    void cell_compute_positions(double delta_t);
    // Operateurs 

    /**
     * @brief Surcharge de l'opérateur égalité pour deux cellules.
     * @param cell la cellule à comparer.
     * @return vrai si les cellules sont égales, faux sinon.
     */
    bool operator==(const Cellule &cell) const;

    /**
     * @brief Surcharge de l'opérateur inégalité pour deux cellules.
     * @param cell la cellule à comparer.
     * @return vrai si les cellules sont différentes, faux sinon.
     */
    bool operator!=(const Cellule &cell) const;

    // Getters  

    /**
     * @brief Getter de la liste des index des cellules voisines.
     * @return une liste des index des cellules voisines.
     */
    std::list<int> get_voisin_index() const;

    /**
     * @brief Getter pour savoir dans quel cube du maillage on est .
     * @return la position (i,j,k) du cube de la maille dans laquel on est.
     */
    std::array<int, 3> get_pos() const;

    /**
     * @brief Getter de la dimension de la simulation.
     * @return la dimension de la simulation.
     */
    inline int get_dim() const;

    //Setter
    void set_voisin(const std::list<int> &index_voisins);
    void set_pos(const std::array<int, 3> pos_maille);

    private:
    /**
     * @brief Ensemble de particules sur la cellule
    */
    std::list<std::unique_ptr<AbstractPart>> particules;

    /**
     * @brief liste qui contient les index dans l'univers des cellules voisines 
    */
    std::list<int>  index_voisins = {}; // Plutot que des voisins = grosses cellules x27 avec bcp de répétitions, on va stocker les index des voisins dans le vecteur parent

    /**
     *  @brief position de la cellule dans le maillage de l'espace 
     */
    std::array<int, 3> pos_maille = {0,0,0}; // (ex 2D : (1,2,0)  ( defaut = 0 ) )

    /**
     * @brief dimension de la cellule
    */
    int dim;
};