/**

@file univers.hxx
@brief Header file pour la classe Univers , qui défini l'univers de la simulation 
*/
#pragma once
#include <vector>

#include "cellule.hxx"
#include "abstract_uni.hxx"

/**
 * 
 * @class Univers
 *
 * @brief Classe qui définit l'Univers de la simulation ( aprés tp4 )
 * 
 */
class Univers: public AbstractUni {
    public:

    /**
     * @brief Réalise une simulation de l'univers
     * @param tend Le temps total de la simulation.
     * @param delta_t Le pas de calcul utilisé dans la simulation
     * @param afficher Détermine si on print ou pas les positions à chaque pas
     */
    void simulation(double tend, double delta_t, bool afficher);


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
         * 
         *  @brief Calcule l'index dans la liste de cellule de l'univers des voisins de la cellule en entrée ( pour pouvoir faire liste_cellules[index])
         *  @param cell la cellule dont on veut l'indice des cellules voisines
         *  @return la liste des index dans la liste de cellule de l'univers des cellules voisines
        */
        std::list<int> get_voisins_index(const Cellule &cell) const;

        /**
         *
         *   @brief Permet d'obtenir la liste des cellules voisines d'une cellule
         *   @param cell la cellule dont on veut les voisins
         *   @return La liste des cellules voisines
        */
        std::list<std::reference_wrapper<const Cellule>> get_voisin_cellule(const Cellule &cell) const;
        /**
         *
         *   @brief Permet d'obtenir la liste des cellules voisines d'une cellule
         *   @param cell la cellule dont on veut les voisins
         *   @return La liste des cellules voisines
        */
        std::list<std::reference_wrapper<Cellule>> get_voisin_cellule(const Cellule &cell);

        /**
         * 
         *  @brief Met a jour les cellules de l'univers
         *  @details
         *  Tout d'abord, cette fonction parcourt les particules de chaque cellule, retire les particules qui ne sont plus dans la bonne cellule,
         *  stocke ces particules dans une liste, puis réaffecte une cellule à chaque particule.
        */
        void update_cells();
        /**
         * 
         *  @brief ajoute une cellule dans la liste des cellules de l'univers
         *  @param cell la Cellule a ajouté
        */
        void add_cellule(Cellule cell);
        /**
         * @brief Assigne une particule dans la bonne cellule
         * @param particle la particule qu'on veut assigner a une cellule
         * 
        */
        void assign_cell(std::unique_ptr<AbstractPart> &&particule);

        /**
         * @brief créer une particule dans l'univers sans force initiale 
         * @param position position de la particule, si elle sors de l'univers alors la condition limite périodique s'applique
         * @param vitesse_initiale vitesse initiale de la particule
         * @param masse masse de la particule
         * @param active statut de la particule
         * @param f le drapeau des forces optionnelles (donnant également la catégorie)
        */
        void create_particule(Point &position, Point &vitesse_initiale, double masse, bool active, Flag f);

        /**
         * @brief créer une particule dans l'univers avec force initiale 
         * @param position position de la particule, si elle sors de l'univers alors la condition limite périodique s'applique
         * @param vitesse_initiale vitesse initiale de la particule
         * @param force : force initiale
         * @param old_force : force précédente 
         * @param masse masse de la particule
         * @param active statut de la particule
         * @param f le drapeau des forces optionnelles (donnant également la catégorie)
        */
        void create_particule_avec_force(Point &position, Point &vitesse_initiale, Point &force, Point &old_force, double mass, bool active, Flag f);

        /**
         *  @brief Créer N particules dans l'univers de masse, catégorie et statut identique
         *  @param N nombre de particules a créer
         *  @param flag décorateur qui permet de définir les forces qui vont s'appliquer sur les particules random 
        */
        void create_random_part(int N, double masse, const Flag &flag);
        /**
         * 
         *  @brief Implemente la condition limite périodique pour l'univers
         *  @param particle La particule sur laquelle on applique la condition
        */
        void condition_limite_periodique(std::unique_ptr<AbstractPart> &particule);
        /**
         * 
         * @brief Implemente la condition limite d'absorption pour l'univers
         * @param particle La particule sur laquelle on applique la condition 
        */
        void condition_limite_absorption(std::unique_ptr<AbstractPart> &particule);
        /**
         * 
         * @brief Implemente la condition limite reflexive
         * @param particle particule sur laquelle on applique la condition limite
        */
        void condition_limite_reflexive(std::unique_ptr<AbstractPart> &particule);
        /**
         * 
         *  @brief Affiche l'état de l'univers 
        */
        void affiche_univers();
        /**
         * 
         *  @brief Affiche les coordonées dans l'espace des cellules voisine de la cellule en entrée
         *  @param cell la cellule dont on veut les coordonnées dans l'espace des voisines
        */
        void affiche_voisin_cellule(Cellule &cell);

        /**
         * @brief Affichage de l'univers avec un certain format pour utiliser un script python qui permettra d'afficher l'univers
         * @details 
         * Affiche chaque particules avec le format suivant :
         * id
         * x
         * y
         * z
         * 
         * 
        */
        void affiche_all_part();
        /**
         * 
         *  @brief Construit un Univers
         *  @param dim La dimension de l'univers
         *  @param ld La taille de l'univers dans les 3 dimensions
         *  @param rcut le rayon de coupure 
        */
        Univers(int dim, std::array<double, 3> ld, double rcut);

        Univers(Univers &) = delete;

        /**
         * 
         *  @brief destructeur = destructeur par defaut 
        */
        ~Univers() = default;

        /**
         * @brief Setter pour la dimension de l'univers
         * @param dim la dimension à assigner
         */
        void set_dim(const int dim);

        /**
         * @brief Setter pour le nombre de particules de l'univers
         * @param nbre_particules le nombre de particules à assigner
         */
        void set_nb_part(const long nbre_particules);

        /**
         * @brief Setter pour le paramètre epsilon de l'univers
         * @param epsilon la valeur à assigner
         */
        void set_epsilon(const double epsilon);

        /**
         * @brief Setter pour la taille de l'univers
         * @param ld un tableau contenant la taille dans les 3 dimensions
         */
        void set_ld(const std::array<double,3> ld);

        /**
         * @brief Setter pour le rayon de coupure de l'univers
         * @param rcut la valeur à assigner
         */
        void set_rcut(const double rcut);

        /**
         * @brief Setter pour le paramètre sigma de l'univers
         * @param sigma la valeur à assigner
         */
        void set_sigma(const double sigma);

        /**
         * @brief Setter pour le nombre de cellules de l'univers dans chaque dimension
         */
        void set_ncd();


        // Getters

        /**
         * @brief Getter pour la liste des cellules de l'univers.
         * @return La liste des cellules de l'univers.
         */
        std::vector<Cellule> &get_list_cell();

        /**
         * @brief Getter pour la dimension de l'univers.
         * @return La dimension de l'univers.
         */
        int get_dim();

        /**
         * @brief Getter pour le nombre de particules de l'univers.
         * @return Le nombre de particules de l'univers.
         */
        long get_nbre_part();

        /**
         * @brief Getter pour la taille de l'univers dans les 3 dimensions.
         * @return La taille de l'univers dans les 3 dimensions.
         */
        std::array<double, 3> get_ld();

        /**
         * @brief Getter pour le rayon de coupure pour l'interaction de Lennard-Jones.
         * @return Le rayon de coupure pour l'interaction de Lennard-Jones.
         */
        double get_rcut();

        /**
         * @brief Getter pour le paramètre epsilon pour l'interaction de Lennard-Jones.
         * @return Le paramètre epsilon pour l'interaction de Lennard-Jones.
         */
        double get_epsilon();

        /**
         * @brief Getter pour le paramètre sigma pour l'interaction de Lennard-Jones.
         * @return Le paramètre sigma pour l'interaction de Lennard-Jones.
         */
        double get_sigma();

    private:

        /**
         * @brief Liste des cellules dans l'univers
         */
        std::vector<Cellule> cellules;

        /**
         * @brief Dimension de l'univers
         */
        int dim;

        /**
         * @brief Nombre de particules dans l'univers
         */
        long nbre_particules = 0;

        /**
         * @brief Taille de l'univers dans les 3 dimensions
         */
        std::array<double,3> ld;

        /**
         * @brief Rayon de coupure
         */
        double rcut;

        /**
         * @brief Constante epsilon pour l'interaction de Lennard-Jones
         */
        double epsilon = 1;

        /**
         * @brief Constante sigma pour l'interaction de Lennard-Jones
         */
        double sigma = 1;

        /**
         * @brief Nombre de cellules dans chaque dimension
         */
        std::array<int,3> ncd = {0,0,0};
};
