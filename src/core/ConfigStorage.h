#pragma once
#include <map>
#include <string>

// Interfaz abstracta de almacenamiento (HERENCIA / POLIMORFISMO).
class ConfigStorage {
public:
    virtual ~ConfigStorage() = default;
    virtual bool load(std::map<std::string, std::string>& data) = 0;
    virtual bool save(const std::map<std::string, std::string>& data) = 0;
};

// Implementacion concreta: guarda la configuracion en un archivo "clave=valor".
class FileConfigStorage : public ConfigStorage {
public:
    explicit FileConfigStorage(std::string path);
    bool load(std::map<std::string, std::string>& data) override;
    bool save(const std::map<std::string, std::string>& data) override;

private:                       // ENCAPSULAMIENTO
    std::string path_;
};
