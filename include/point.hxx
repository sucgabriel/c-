
/**
 * @file point.hxx
 * @brief Header pour la classe Point = Vecteur
 */
#pragma once
#include<iostream>
#include <array>
#include <cmath>

/**
 * @brief La classe Point représente un point dans l'espace tridimensionnel.
 */
class Point{
  public:

  /**
   * @brief coordonnées du point 
  */
  std::array<double, 3> val; ///< Contient les coordonnées du point 
  
  /**
   * @brief Constructeur par défaut. Initialise toutes les coordonnées à 0.
   */
  Point();

  /**
   * @brief Constructeur de copie. Initialise les coordonnées à celles d'un autre point.
   * @param p Le point à partir duquel initialiser les coordonnées.
   */
  Point(const Point &p);

  /**
   * @brief Constructeur à partir de coordonnées.
   * @param x La coordonnée x.
   * @param y La coordonnée y.
   * @param z La coordonnée z.
   */
  Point(double x, double y, double z);

  /**
   * @brief Normalise le vecteur représenté par le point.
   */
  void normalize();

  /**
   * @brief Surcharge de l'opérateur d'addition.
   * @param p Le point à ajouter.
   * @return Un nouveau point représentant la somme des deux points.
   */
  Point operator+(const Point &p) const;

  /**
   * @brief Surcharge de l'opérateur d'addition et d'affectation.
   * @param p Le point à ajouter.
   * @return Une référence sur le point actuel, après l'addition.
   */
  Point & operator+=(const Point &p);

  /**
   * @brief Surcharge de l'opérateur de soustraction.
   * @param p Le point à ajouter.
   * @return Un nouveau point représentant la soustraction des deux points.
   */
  Point operator-(const Point &p) const;

  /**
   * @brief Surcharge de l'opérateur de soustraction et d'affectation.
   * @param p Le point à ajouter.
   * @return Une référence sur le point actuel, après la soustraction.
   */
  Point& operator-=(const Point &p);

  /**
   * @brief Surcharge de l'opérateur d'opposition unaire
   * @param p Le point à opposer.
   * @return Un nouveau point représentant le point opposé.
   */
  Point operator-() const;

  /**
   * @brief Surcharge de l'opérateur de produit scalaire.
   * @param p le second opérande du produit scalaire.
   * @return Le scalaire obtenu après produit.
   */
  double operator*(const Point &p) const;

  /**
   * @brief Surcharge de l'opérateur de multiplication par un scalaire.
   * @param d Le scalaire à multiplier.
   * @return Un nouveau point représentant le produit du point par le scalaire.
   */
  Point operator*(double d) const;

  /**
   * @brief Surcharge de l'opérateur de multiplication par un scalaire et d'affectation.
   * @param d Le scalaire à multiplier.
   * @return Une référence sur le point actuel, après la multiplication par le scalaire.
   */
  Point & operator*=(double d);

  /**
   * @brief Surcharge de l'opérateur d'affectation.
   * @param p Le point à copier.
   * @return Une référence sur le point actuel, après la copie des coordonnées.
   */
  Point & operator=(const Point &p);

  /**
   * @brief Surcharge de l'opérateur d'égalité.
   * @param p Le point à comparer.
   * @return Vrai si les deux points sont égaux, faux sinon.
   */
  bool operator==(const Point &p) const;

  /**
   * @brief Surcharge de l'opérateur de non-égalité.
   * @param p Le point à comparer.
   * @return Vrai si les deux points sont différents, faux sinon.
   */
  bool operator!=(const Point &p) const;

  /**
   * @brief Surcharge de l'opérateur d'accès aux coordonnées.
   * @param i L'indice de la coordonnée à accéder.
   * @return Une référence sur la coordonnée demandée.
   */
  double operator()(int i);

  /**
   * @brief Surcharge de l'opérateur d'accès en lecture seule
  */
  double operator()(int ) const ;
  /**
   * @brief destructeur
  */
  ~Point(); 
};

/**
 * 
 * @brief Surcharge de l'opérateur de sortie pour afficher un point
 * @param os Le flux de sortie
 * @param p Le point à afficher
 * @return Le flux de sortie
*/
std::ostream & operator<<(std::ostream& , const Point &);

/**
 * 
 * @brief Surcharge de l'opérateur de multiplication pour multiplier un point par un scalaire
 * @param scalar Le scalaire
 * @param p Le point à multiplier
 * @return Le point multiplié par le scalaire
*/
Point operator*(double, const Point &);
