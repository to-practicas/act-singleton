#pragma once
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include "ConfigStorage.h"

// ============================================================
//  PATRON SINGLETON: ConfigManager
//  - Constructor privado.
//  - Copia y asignacion eliminadas.
//  - Una unica instancia accesible con ConfigManager::instance().
//  - Thread-safe (Meyers Singleton + mutex).
// ============================================================
class ConfigManager {
public:
    static ConfigManager& instance();

    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    // Persistencia
    void setStorage(std::unique_ptr<ConfigStorage> storage);
    bool load();
    bool save() const;

    // Acceso a valores
    void set(const std::string& key, const std::string& value);
    void set(const std::string& key, const char* value);   // evita que un literal se convierta en bool
    void set(const std::string& key, int value);
    void set(const std::string& key, bool value);

    std::string get(const std::string& key, const std::string& def = "") const;
    int  getInt(const std::string& key, int def = 0) const;
    bool getBool(const std::string& key, bool def = false) const;

    bool has(const std::string& key) const;
    void remove(const std::string& key);
    void resetDefaults();
    std::map<std::string, std::string> getAll() const;

private:
    ConfigManager();
    ~ConfigManager() = default;
    void applyDefaults();

    mutable std::mutex mutex_;
    std::map<std::string, std::string> data_;
    std::unique_ptr<ConfigStorage> storage_;
};