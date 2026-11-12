#include "ConfigViewerWindow.h"
#include "ConfigManager.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>

ConfigViewerWindow::ConfigViewerWindow(QWidget* parent) : QWidget(parent, Qt::Window) {
    setWindowTitle("Visor de configuracion (misma instancia)");
    resize(380, 300);
    auto* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Valores actuales del Singleton ConfigManager:"));
    view_ = new QTextEdit;
    view_->setReadOnly(true);
    layout->addWidget(view_);
    refresh();
}

void ConfigViewerWindow::refresh() {
    QString text;
    for (const auto& kv : ConfigManager::instance().getAll())
        text += QString::fromStdString(kv.first) + " = " + QString::fromStdString(kv.second) + "\n";
    view_->setPlainText(text);
}
