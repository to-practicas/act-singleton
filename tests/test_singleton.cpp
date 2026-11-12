// Pruebas basicas del Singleton y de la persistencia (sin Qt).
#undef NDEBUG
#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include "ConfigManager.h"

int main() {
    ConfigManager& a = ConfigManager::instance();
    ConfigManager& b = ConfigManager::instance();

    // 1. Una sola instancia
    assert(&a == &b);

    // 2. Valores por defecto
    a.resetDefaults();
    assert(a.get("app.theme") == "light");
    assert(a.getInt("app.fontSize") == 12);

    // 3. Un cambio hecho desde "a" se ve desde "b"
    a.set("app.theme", "dark");
    assert(b.get("app.theme") == "dark");
    b.set("app.fontSize", 18);
    assert(a.getInt("app.fontSize") == 18);
    a.set("app.autosave", false);
    assert(!b.getBool("app.autosave"));

    // 4. Clave inexistente devuelve el valor por defecto
    assert(a.get("no.existe", "x") == "x");
    assert(!a.has("no.existe"));

    // 5. Persistencia (guardar -> modificar -> cargar)
    a.setStorage(std::make_unique<FileConfigStorage>("test_config.ini"));
    assert(a.save());
    a.set("app.theme", "light");
    assert(a.load());
    assert(a.get("app.theme") == "dark");
    std::remove("test_config.ini");

    std::cout << "Todas las pruebas pasaron correctamente\n";
    return 0;
}
