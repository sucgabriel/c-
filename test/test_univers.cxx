#include "univers.hxx"
#include "particules/particules.hxx"
#include "particules/abstract_part.hxx"
#include "particules/grav_decorator.hxx"
#include "point.hxx"

// Fichier qui permet de tester la structure univers 

int main(){

    Univers univers = Univers(2, {100,100,0},2);
    std::cout<< "univers done"<<std::endl;
    int N = 10;
    Flag f =Flag(GRAVITY);
    univers.create_random_part(N,1,f);
    std::cout<< "on a mis " << N << " particules dans l'univers" << std::endl;
    //univers.affiche_univers();
    Cellule &temp_cell= univers.get_list_cell()[4]; // Doit avoir 6 voisines 
    univers.affiche_voisin_cellule(temp_cell);

    Cellule &temp_cell2= univers.get_list_cell()[103];  // Doit avoir 9 voisines 
    univers.affiche_voisin_cellule(temp_cell2);
    univers.affiche_univers();
    std::cout <<"Normalement, on a affiché un univers avec "<< N<< " particules" << std::endl;
    /*std::cout << "On va deplacer a la main une particule de l'univers ( la plus proche de (0,0,0) )"<< std::endl;
    for (auto &cell: univers.get_list_cell()){
        std::list<Particule> & liste_particules = cell.get();
        if (!liste_particules.empty()){
            std::cout <<"cellule non vide avant modif : " << std::endl;
            liste_particules.front().affiche_position();
            std::cout<< std::endl;
            liste_particules.front().setPosition(50.01,39,0);
            std::cout <<"cellule non vide apres modif x: " << std::endl;
            liste_particules.front().affiche_position();
            std::cout<< std::endl;
            cell.setParticules(liste_particules);
            break;
        }
    }*/
    univers.update_cells();
    std::cout << " on a tenter d'update toutes les cellules, pas de crash" << std::endl;
    //univers.affiche_univers();


    /*for (auto &cell: univers.getListCell()){
        std::list<Particule> & liste_particules = cell.getParticules();
        if (!liste_particules.empty()){
            std::cout <<"cellule non vide avant modif : " << std::endl;
            liste_particules.front().affiche_position();
            std::cout<< std::endl;
            liste_particules.front().setPosition(pos);
            std::cout <<"cellule non vide apres modif : " << std::endl;
            liste_particules.front().affiche_position();
            cell.setParticules(liste_particules);
            break;
        }
    }*/
    univers.update_cells();
        
    //std::unique_ptr<AbstractPart> p1 = std::make_unique<Particule>(Point(10,10,0), Point(), Point(), Point(), 1.0, 1, 1, true, 2);
    //p1 = std::make_unique<GravDecorator>(move(p1));
    //univers.assign_cell(move(p1));
    std::cout << "on va créer une particule a la main " << std::endl;
    Point pos = Point(36.5, 34.8,0);
    Point empty = Point();
    univers.create_particule(pos, empty, 1.0, 1, f);
    std::cout <<"normalement, une particule a était ajoutée dans la cellule x = 18, y=17, z=0 les pos de la particules sont 36.5 et 34.8 "<< std::endl;
    univers.affiche_univers();
    std::cout << " ALL OK" << std::endl;
}