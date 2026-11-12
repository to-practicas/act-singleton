#pragma once
#include <QMainWindow>

// Declaraciones adelantadas: evitan inclusiones innecesarias en la cabecera.
class QLabel;
class QLineEdit;
class QComboBox;
class QSpinBox;
class QCheckBox;
class ConfigViewerWindow;   // ventana de Gerson (dependencia del grupo)

// Ventana principal de la version Qt.
// Lee, modifica y guarda la configuracion global a traves del
// Singleton ConfigManager::instance().
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onApply();      // guarda los valores del formulario en el Singleton
    void onReload();     // recarga config.ini desde disco
    void onReset();      // restaura los valores por defecto
    void onOpenViewer(); // abre la segunda ventana (ConfigViewerWindow)

private:
    void loadFromConfig(); // Singleton -> controles de la interfaz
    void applyConfig();    // Singleton -> saludo, tema, fuente y visor

    QLabel*    greeting_;                 // etiqueta de saludo
    QLineEdit* userEdit_;                 // user.name
    QComboBox* themeCombo_;               // app.theme
    QComboBox* languageCombo_;            // app.language
    QSpinBox*  fontSpin_;                 // app.fontSize
    QCheckBox* autosaveCheck_;            // app.autosave
    ConfigViewerWindow* viewer_ = nullptr; // se crea bajo demanda
};
