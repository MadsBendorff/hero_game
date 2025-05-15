#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <sqlite3.h>
#include <string>

class DatabaseManager {
public:
    DatabaseManager(const std::string& dbName);
    ~DatabaseManager();

    void logBattle(const std::string& hero, const std::string& enemy, const std::string& weapon);
    void logHero(const std::string& name, int level, int xp, int gold);
    void showAllBattles();
    void showAllHeroes();
    bool loadHero(const std::string& name, int& level, int& xp, int& gold);
    void showHeroKillCounts();
    void showWeaponKillsByHero(const std::string& heroName);
    void showTopHeroPerWeapon();

private:
    sqlite3* db;
};

#endif
