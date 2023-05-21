## Indique qu'elle version de cmake minimale est utilisée.
cmake_minimum_required (VERSION 3.16.3)

## Specifie le nom du projet et le langage de programmation du projet
project(Lab2 CXX)

## Force le standard 
set(CMAKE_CXX_STANDARD 17)

## Indique les options de compilations pour le projet
## -pg : donne la possibilité de faire du profiling
## -Wall : affiche les warnings
set(CMAKE_CXX_FLAGS "-Wall -g")

include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(src)

## Répertoire contenant les fichiers permettant de générer
## les exécutables (avec la fonction main)
add_subdirectory(test)

