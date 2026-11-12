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
    ConfigManager& cfg = ConfigManager::instance();
    cfg.load();

    std::vector<std::unique_ptr<AppModule>> modules;
    modules.push_back(std::make_unique<HeaderModule>());
    modules.push_back(std::make_unique<ThemeModule>());

    int op = -1;
    while (op != 0) {
        std::cout << "\n=== Configuracion global (Singleton) ===\n"
                  << "1. Ver modulos\n2. Cambiar usuario\n3. Cambiar tema (light/dark)\n"
                  << "4. Cambiar idioma (es/en)\n5. Cambiar tamano de fuente\n"
                  << "6. Guardar\n7. Recargar desde archivo\n8. Restaurar valores por defecto\n"
                  << "9. Verificar instancia unica\n0. Salir\nOpcion: ";
        if (!(std::cin >> op)) break;
        std::cin.ignore(10000, '\n');
        std::string v;
        switch (op) {
            case 1: for (auto& m : modules) m->show(); break;
            case 2: std::cout << "Nombre: "; std::getline(std::cin, v); cfg.set("user.name", v); break;
            case 3: std::cout << "Tema: "; std::getline(std::cin, v); cfg.set("app.theme", v); break;
            case 4: std::cout << "Idioma: "; std::getline(std::cin, v); cfg.set("app.language", v); break;
            case 5: { int n; std::cout << "Tamano: "; std::cin >> n; std::cin.ignore(10000, '\n'); cfg.set("app.fontSize", n); break; }
            case 6: std::cout << (cfg.save() ? "Guardado en config.ini\n" : "Error al guardar\n"); break;
            case 7: std::cout << (cfg.load() ? "Recargado\n" : "No se encontro config.ini\n"); break;
            case 8: cfg.resetDefaults(); std::cout << "Valores restaurados\n"; break;
            case 9: {
                ConfigManager& a = ConfigManager::instance();
                ConfigManager& b = ConfigManager::instance();
                std::cout << "Direccion A: " << &a << "\nDireccion B: " << &b << "\n"
                          << (&a == &b ? "-> Es la MISMA instancia (Singleton OK)\n" : "-> Distintas (error)\n");
                break;
            }
        }
    }
    if (cfg.getBool("app.autosave")) cfg.save();
    return 0;
}
