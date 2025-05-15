cmake_minimum_required(VERSION 3.10)
project(hero_game)

set(CMAKE_CXX_STANDARD 17)

# Include the header files from the Headers folder
include_directories(Headers)

# Add the executable with all source files
add_executable(hero_game
    main.cpp
    SourceFiles/Hero.cpp
    SourceFiles/Enemy.cpp
    SourceFiles/CombatManager.cpp
    SourceFiles/EnemyFactory.cpp
    SourceFiles/Cave.cpp 
)


