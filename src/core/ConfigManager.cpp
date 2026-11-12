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