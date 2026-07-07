#include "login_dialog.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

LoginDialog::LoginDialog(const LoginManager &loginManager, QWidget *parent)
    : QDialog(parent)
    , m_loginManager(loginManager)
{
    setWindowTitle(QStringLiteral("Train Ticket System Login"));
    setModal(true);
    setMinimumWidth(380);

    auto *mainLayout = new QVBoxLayout(this);

    auto *titleLabel = new QLabel(QStringLiteral("Train Ticket System"), this);
    titleLabel->setAlignment(Qt::AlignCenter);

    auto *formLayout = new QFormLayout;
    m_usernameEdit = new QLineEdit(this);
    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setEchoMode(QLineEdit::Password);

    formLayout->addRow(QStringLiteral("Username"), m_usernameEdit);
    formLayout->addRow(QStringLiteral("Password"), m_passwordEdit);

    m_messageLabel = new QLabel(this);
    m_messageLabel->setWordWrap(true);
    m_messageLabel->setMinimumHeight(24);

    auto *buttonLayout = new QHBoxLayout;
    auto *guestButton = new QPushButton(QStringLiteral("Guest"), this);
    auto *loginButton = new QPushButton(QStringLiteral("Login"), this);
    loginButton->setDefault(true);

    buttonLayout->addWidget(guestButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(loginButton);

    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(m_messageLabel);
    mainLayout->addLayout(buttonLayout);

    // 登录按钮和回车键复用同一处理函数，避免登录流程分散在多个 UI 事件里。
    connect(loginButton, &QPushButton::clicked, this, [this]() {
        handleLogin();
    });
    connect(guestButton, &QPushButton::clicked, this, [this]() {
        handleGuestAccess();
    });
    connect(m_passwordEdit, &QLineEdit::returnPressed, this, [this]() {
        handleLogin();
    });
}

LoginResult LoginDialog::loginResult() const
{
    return m_loginResult;
}

void LoginDialog::handleLogin()
{
    // 对话框只负责收集输入和展示结果，具体认证规则交给 LoginManager。
    m_loginResult = m_loginManager.authenticate(m_usernameEdit->text(), m_passwordEdit->text());

    if (!m_loginResult.success) {
        showMessage(m_loginResult.message, true);
        return;
    }

    accept();
}

void LoginDialog::handleGuestAccess()
{
    m_loginResult = m_loginManager.loginAsGuest();
    accept();
}

void LoginDialog::showMessage(const QString &message, bool isError)
{
    m_messageLabel->setText(message);
    m_messageLabel->setStyleSheet(isError ? QStringLiteral("color: #b00020;")
                                          : QStringLiteral("color: #14532d;"));
}
