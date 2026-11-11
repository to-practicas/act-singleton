#include "MainWindow.h"
#include "ConfigViewerWindow.h"   // dependencia de Gerson
#include "ConfigManager.h"        // dependencia de Jhon (Singleton)
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QFont>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QStatusBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Configuracion global - Singleton (Grupo 1)");

    // Widget central y layout raiz.
    auto* central = new QWidget(this);
    auto* root = new QVBoxLayout(central);

    // Etiqueta de saludo (se actualiza en applyConfig()).
    greeting_ = new QLabel;
    QFont f = greeting_->font();
    f.setBold(true);
    greeting_->setFont(f);
    root->addWidget(greeting_);

    // Formulario con los controles de configuracion.
    auto* form = new QFormLayout;
    userEdit_     = new QLineEdit;
    themeCombo_   = new QComboBox;   themeCombo_->addItems({"light", "dark"});
    languageCombo_ = new QComboBox; languageCombo_->addItems({"es", "en"});
    fontSpin_     = new QSpinBox;     fontSpin_->setRange(8, 32);
    autosaveCheck_ = new QCheckBox("Guardar automaticamente");
    form->addRow("Usuario:", userEdit_);
    form->addRow("Tema:", themeCombo_);
    form->addRow("Idioma:", languageCombo_);
    form->addRow("Tamano de fuente:", fontSpin_);
    form->addRow("", autosaveCheck_);
    root->addLayout(form);

    // Botonera de acciones.
    auto* buttons = new QHBoxLayout;
    auto* applyBtn  = new QPushButton("Aplicar y guardar");
    auto* reloadBtn = new QPushButton("Recargar");
    auto* resetBtn  = new QPushButton("Restaurar");
    auto* viewerBtn = new QPushButton("Abrir visor");
    for (auto* b : {applyBtn, reloadBtn, resetBtn, viewerBtn}) buttons->addWidget(b);
    root->addLayout(buttons);

    setCentralWidget(central);

    // Conexion de senales y slots.
    connect(applyBtn,  &QPushButton::clicked, this, &MainWindow::onApply);
    connect(reloadBtn, &QPushButton::clicked, this, &MainWindow::onReload);
    connect(resetBtn,  &QPushButton::clicked, this, &MainWindow::onReset);
    connect(viewerBtn, &QPushButton::clicked, this, &MainWindow::onOpenViewer);

    // Estado inicial desde el Singleton.
    loadFromConfig();
    applyConfig();
}

// Singleton -> controles de la interfaz.
void MainWindow::loadFromConfig() {
    auto& cfg = ConfigManager::instance();
    userEdit_->setText(QString::fromStdString(cfg.get("user.name")));
    themeCombo_->setCurrentText(QString::fromStdString(cfg.get("app.theme")));
    languageCombo_->setCurrentText(QString::fromStdString(cfg.get("app.language")));
    fontSpin_->setValue(cfg.getInt("app.fontSize", 12));
    autosaveCheck_->setChecked(cfg.getBool("app.autosave", true));
}

// Singleton -> apariencia de la aplicacion.
void MainWindow::applyConfig() {
    auto& cfg = ConfigManager::instance();
    const bool es = cfg.get("app.language") == "es";
    greeting_->setText((es ? QString("Hola, ") : QString("Hello, "))
                       + QString::fromStdString(cfg.get("user.name")));

    // Tema oscuro o claro a nivel global.
    if (cfg.get("app.theme") == "dark")
        qApp->setStyleSheet("QWidget{background:#2b2b2b;color:#eee;} "
                            "QLineEdit,QComboBox,QSpinBox,QTextEdit{background:#3c3c3c;} "
                            "QPushButton{background:#444;padding:4px;}");
    else
        qApp->setStyleSheet("");

    // Tamano de fuente global.
    QFont font = qApp->font();
    font.setPointSize(cfg.getInt("app.fontSize", 12));
    qApp->setFont(font);

    // Si el visor esta abierto, refresca su contenido.
    if (viewer_) viewer_->refresh();
}

// Controles de la interfaz -> Singleton (+ persistencia).
void MainWindow::onApply() {
    auto& cfg = ConfigManager::instance();
    cfg.set("user.name",    userEdit_->text().toStdString());
    cfg.set("app.theme",    themeCombo_->currentText().toStdString());
    cfg.set("app.language", languageCombo_->currentText().toStdString());
    cfg.set("app.fontSize", fontSpin_->value());
    cfg.set("app.autosave", autosaveCheck_->isChecked());

    applyConfig();

    if (!cfg.save())
        QMessageBox::warning(this, "Error", "No se pudo guardar config.ini");
    else
        statusBar()->showMessage("Configuracion guardada", 3000);
}

// Recarga la configuracion desde el disco.
void MainWindow::onReload() {
    if (!ConfigManager::instance().load())
        QMessageBox::information(this, "Aviso", "No se encontro config.ini");
    loadFromConfig();
    applyConfig();
}

// Restaura los valores por defecto del Singleton.
void MainWindow::onReset() {
    ConfigManager::instance().resetDefaults();
    loadFromConfig();
    applyConfig();
}

// Crea el visor bajo demanda y lo muestra al frente.
void MainWindow::onOpenViewer() {
    if (!viewer_) viewer_ = new ConfigViewerWindow(this);
    viewer_->refresh();
    viewer_->show();
    viewer_->raise();
}
