cmake_minimum_required(VERSION 3.10)
project(hero_game)

set(CMAKE_CXX_STANDARD 17)

include_directories(Headers)

find_package(SQLite3 REQUIRED)

add_executable(hero_game
    main.cpp
    SourceFiles/Hero.cpp
    SourceFiles/Enemy.cpp
    SourceFiles/CombatManager.cpp
    SourceFiles/EnemyFactory.cpp
    SourceFiles/Cave.cpp 
    SourceFiles/Weapon.cpp
    SourceFiles/WeaponFactory.cpp
    SourceFiles/DatabaseManager.cpp  
)

target_link_libraries(hero_game PRIVATE SQLite::SQLite3)
