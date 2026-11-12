#include "ConfigManager.h"

ConfigManager::ConfigManager()
    : storage_(std::make_unique<FileConfigStorage>("config.ini")) {
    applyDefaults();
}

ConfigManager& ConfigManager::instance() {
    static ConfigManager inst;   // se crea una sola vez (thread-safe en C++11+)
    return inst;
}

void ConfigManager::applyDefaults() {
    data_["app.theme"]    = "light";
    data_["app.language"] = "es";
    data_["app.fontSize"] = "12";
    data_["app.autosave"] = "true";
    data_["user.name"]    = "Usuario";
}

void ConfigManager::setStorage(std::unique_ptr<ConfigStorage> storage) {
    std::lock_guard<std::mutex> lock(mutex_);
    storage_ = std::move(storage);
}

bool ConfigManager::load() {
    std::lock_guard<std::mutex> lock(mutex_);
    return storage_ && storage_->load(data_);
}

bool ConfigManager::save() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return storage_ && storage_->save(data_);
}
void ConfigManager::set(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    data_[key] = value;
}
void ConfigManager::set(const std::string& key, const char* value) { set(key, std::string(value)); }
void ConfigManager::set(const std::string& key, int value) { set(key, std::to_string(value)); }
void ConfigManager::set(const std::string& key, bool value) { set(key, std::string(value ? "true" : "false")); }

std::string ConfigManager::get(const std::string& key, const std::string& def) const {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = data_.find(key);
    return it != data_.end() ? it->second : def;
}

int ConfigManager::getInt(const std::string& key, int def) const {
    try { return std::stoi(get(key, std::to_string(def))); }
    catch (...) { return def; }
}

bool ConfigManager::getBool(const std::string& key, bool def) const {
    std::string v = get(key, def ? "true" : "false");
    return v == "true" || v == "1";
}

bool ConfigManager::has(const std::string& key) const {
    std::lock_guard<std::mutex> lock(mutex_);
    return data_.count(key) > 0;
}

void ConfigManager::remove(const std::string& key) {
    std::lock_guard<std::mutex> lock(mutex_);
    data_.erase(key);
}

void ConfigManager::resetDefaults() {
    std::lock_guard<std::mutex> lock(mutex_);
    data_.clear();
    applyDefaults();
}

std::map<std::string, std::string> ConfigManager::getAll() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return data_;
}