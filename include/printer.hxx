/**
 * @file printer.hxx
 * @brief Header pour la classe printer gérant l'édition de fichiers VTK
 */
#pragma once

#include <iostream>
#include <fstream>

#include "abstract_uni.hxx"

/**
 * @brief La classe Universe représente l'univers de la simulation ( avant tp4 donc sans cellule).
 */
class Printer{
    public:

    Printer(char* fliename);
    void generate_file(AbstractUni* univ);

    private:
    void print_balise(char* balise_name);

    void print_VTK();
    void print_grid();
    void print_piece(int n);
    void print_points();
    void print_data_array(char* name, int n);
    void print_point_data();
    void print_cells();

    void print_VTK_end();
    void print_grid_end();
    void print_piece_end();
    void print_points_end();
    void print_data_array_end();
    void print_point_data_end();
    void print_cells_end();


    void print_header_file();
    void print_footer_file();
    

    std::ofstream file;

};