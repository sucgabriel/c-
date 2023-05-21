#include "cellule.hxx"
#include "particules/particules.hxx"

int main(){
    Point p = Point();
    std::array<int, 3> maille1 = {0,0,0};
    std::array<int, 3> maille2 = {0,1,1};
    std::array<int, 3> maille3 = {0,1,2};
    std::unique_ptr<AbstractPart> part = std::make_unique<Particule>(Point(1, 0, 0), p, p, p, 1,0,1,1,3);
    Cellule cell1 =Cellule(maille1, 3);
    Cellule cell2 = Cellule(maille2, 3);
    Cellule cell3 = Cellule(maille3, 3);
    std::cout << cell1.is_voisine(cell2) << std::endl;
    std::cout << cell1.is_voisine(cell3) << std::endl;
    std::cout << cell2.is_voisine(cell3) << std::endl;
    cell2.affiche_cellule();
    cell2.add_particule(move(part));
    cell2.affiche_cellule();
}