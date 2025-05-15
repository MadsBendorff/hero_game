#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string& dbName) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Failed to open database\n";
        db = nullptr;
    } else {
        // Opret battles-tabel
        std::string createBattlesTable = "CREATE TABLE IF NOT EXISTS battles ("
                                         "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                         "hero TEXT, enemy TEXT, weapon TEXT);";
        sqlite3_exec(db, createBattlesTable.c_str(), nullptr, nullptr, nullptr);

        // Opret heroes-tabel
        std::string createHeroesTable = "CREATE TABLE IF NOT EXISTS heroes ("
                                        "name TEXT PRIMARY KEY, "
                                        "level INT, xp INT, gold INT);";
        sqlite3_exec(db, createHeroesTable.c_str(), nullptr, nullptr, nullptr);
    }
}

DatabaseManager::~DatabaseManager() {
    if (db) sqlite3_close(db);
}

void DatabaseManager::logBattle(const std::string& hero, const std::string& enemy, const std::string& weapon) {
    std::string sql = "INSERT INTO battles (hero, enemy, weapon) VALUES('" +
                      hero + "', '" + enemy + "', '" + weapon + "');";
    sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
}

void DatabaseManager::logHero(const std::string& name, int level, int xp, int gold) {
    std::string query = "INSERT OR REPLACE INTO heroes (name, level, xp, gold) VALUES ('" +
                        name + "', " + std::to_string(level) + ", " +
                        std::to_string(xp) + ", " + std::to_string(gold) + ");";
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);
}

void DatabaseManager::showAllBattles() {
    std::string query = "SELECT hero, enemy, weapon FROM battles;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "\n=== Kampoversigt ===\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string hero = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string enemy = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string weapon = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::cout << hero << " slog " << enemy << " med " << weapon << "\n";
        }
        sqlite3_finalize(stmt);
    }
}

void DatabaseManager::showAllHeroes() {
    std::string query = "SELECT name, level, xp, gold FROM heroes ORDER BY name ASC;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "\n=== Heroes ===\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int level = sqlite3_column_int(stmt, 1);
            int xp = sqlite3_column_int(stmt, 2);
            int gold = sqlite3_column_int(stmt, 3);

            std::cout << "Name: " << name
                      << " | Level: " << level
                      << " | XP: " << xp
                      << " | Gold: " << gold << "\n";
        }
        sqlite3_finalize(stmt);
    }
}

bool DatabaseManager::loadHero(const std::string& name, int& level, int& xp, int& gold) {
    std::string query = "SELECT level, xp, gold FROM heroes WHERE name = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        level = sqlite3_column_int(stmt, 0);
        xp = sqlite3_column_int(stmt, 1);
        gold = sqlite3_column_int(stmt, 2);
        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}


void DatabaseManager::showHeroKillCounts() {
    std::string query = 
        "SELECT hero, COUNT(*) AS kills "
        "FROM battles "
        "GROUP BY hero "
        "ORDER BY kills DESC;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "\n=== Hero Kill Count ===\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string hero = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int kills = sqlite3_column_int(stmt, 1);
            std::cout << hero << " - " << kills << " kills\n";
        }
        sqlite3_finalize(stmt);
    }
}

void DatabaseManager::showWeaponKillsByHero(const std::string& heroName) {
    std::string query =
        "SELECT weapon, COUNT(*) AS kills "
        "FROM battles WHERE hero = ? "
        "GROUP BY weapon ORDER BY kills DESC;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, heroName.c_str(), -1, SQLITE_STATIC);
        std::cout << "\n=== Weapon kills by " << heroName << " ===\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string weapon = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int kills = sqlite3_column_int(stmt, 1);
            std::cout << weapon << " - " << kills << " kills\n";
        }
        sqlite3_finalize(stmt);
    }
}

void DatabaseManager::showTopHeroPerWeapon() {
    std::string query = R"(
        SELECT weapon, hero, COUNT(*) as kills
        FROM battles
        GROUP BY weapon, hero
        HAVING kills = (
            SELECT MAX(cnt) FROM (
                SELECT COUNT(*) as cnt
                FROM battles AS b2
                WHERE b2.weapon = battles.weapon
                GROUP BY b2.hero
            )
        )
        ORDER BY weapon ASC;
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "\n=== Top Hero per Weapon ===\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string weapon = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string hero = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int kills = sqlite3_column_int(stmt, 2);
            std::cout << weapon << ": " << hero << " (" << kills << " kills)\n";
        }
        sqlite3_finalize(stmt);
    }
}



