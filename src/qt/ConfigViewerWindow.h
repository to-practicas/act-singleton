#pragma once
#include <QWidget>
class QTextEdit;

// Segunda ventana: lee la MISMA instancia de ConfigManager que la ventana principal.
class ConfigViewerWindow : public QWidget {
    Q_OBJECT
public:
    explicit ConfigViewerWindow(QWidget* parent = nullptr);
public slots:
    void refresh();
private:
    QTextEdit* view_;
};
