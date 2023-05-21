# Créer une bibliothèque à partir d'un ensemble de fichier sans main
add_library(simulation  universe.cxx point.cxx cellule.cxx univers.cxx)
add_subdirectory(particules)