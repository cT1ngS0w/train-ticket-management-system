#pragma once

#include <QString>

class DatabaseManager;

enum class UserRole
{
    Guest = 0,
    Seller = 1,
    Admin = 2
};

struct LoginResult
{
    bool success = false;
    UserRole role = UserRole::Guest;
    QString username;
    QString message;
};

class LoginManager
{
public:
    explicit LoginManager(const DatabaseManager *databaseManager = nullptr);

    LoginResult authenticate(const QString &username, const QString &password) const;
    LoginResult loginAsGuest() const;

private:
    const DatabaseManager *m_databaseManager = nullptr;
};
