// Demo en consola (sin Qt). Muestra que TODOS los modulos usan la MISMA instancia.
#include <iostream>
#include <memory>
#include <vector>
#include "ConfigManager.h"

// Clase base abstracta (HERENCIA / POLIMORFISMO)
class AppModule {
public:
    explicit AppModule(std::string name) : name_(std::move(name)) {}
    virtual ~AppModule() = default;
    virtual void show() const = 0;
protected:
    const std::string& name() const { return name_; }
    ConfigManager& cfg() const { return ConfigManager::instance(); } // misma instancia
private:
    std::string name_;
};

class HeaderModule : public AppModule {
public:
    HeaderModule() : AppModule("Encabezado") {}
    void show() const override {
        bool es = cfg().get("app.language") == "es";
        std::cout << "[" << name() << "] " << (es ? "Bienvenido, " : "Welcome, ")
                  << cfg().get("user.name") << "\n";
    }
};

class ThemeModule : public AppModule {
public:
    ThemeModule() : AppModule("Tema") {}
    void show() const override {
        std::cout << "[" << name() << "] tema=" << cfg().get("app.theme")
                  << ", fuente=" << cfg().getInt("app.fontSize") << "pt\n";
    }
};


int main() {
    ConfigManager::instance().load();

    std::vector<std::unique_ptr<AppModule>> modules;
    modules.push_back(std::make_unique<HeaderModule>());
    modules.push_back(std::make_unique<ThemeModule>());

    for (auto& m : modules) m->show(); // menu interactivo: pendiente
    return 0;
}
