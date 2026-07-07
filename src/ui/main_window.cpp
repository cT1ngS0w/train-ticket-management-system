#include "main_window.h"

#include <QLabel>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>

namespace {
QString roleName(UserRole role)
{
    switch (role) {
    case UserRole::Admin:
        return QStringLiteral("Admin");
    case UserRole::Seller:
        return QStringLiteral("Seller");
    case UserRole::Guest:
        return QStringLiteral("Guest");
    }

    return QStringLiteral("Unknown");
}
}

MainWindow::MainWindow(const LoginResult &loginResult, QWidget *parent)
    : QMainWindow(parent)
    , m_loginResult(loginResult)
{
    setWindowTitle(QStringLiteral("Train Ticket System"));
    resize(960, 640);

    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);
    auto *label = new QLabel(QStringLiteral("Welcome, %1.")
                                 .arg(m_loginResult.username),
                             centralWidget);

    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    setCentralWidget(centralWidget);
    statusBar()->showMessage(QStringLiteral("Signed in as %1")
                                 .arg(roleName(m_loginResult.role)));
}
