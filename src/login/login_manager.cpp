#include "login_manager.h"

#include "database_manager.h"

#include <QString>

namespace {
UserRole roleFromDatabaseValue(int role)
{
    switch (role) {
    case 2:
        return UserRole::Admin;
    case 1:
        return UserRole::Seller;
    case 0:
    default:
        return UserRole::Guest;
    }
}
}

LoginManager::LoginManager(const DatabaseManager *databaseManager)
    : m_databaseManager(databaseManager)
{
}

LoginResult LoginManager::authenticate(const QString &username, const QString &password) const
{
    const QString trimmedUsername = username.trimmed();

    if (trimmedUsername.isEmpty()) {
        return {false, UserRole::Guest, QString(), QStringLiteral("Username is required.")};
    }

    if (password.isEmpty()) {
        return {false, UserRole::Guest, trimmedUsername, QStringLiteral("Password is required.")};
    }

    if (m_databaseManager == nullptr) {
        return {false,
                UserRole::Guest,
                trimmedUsername,
                QStringLiteral("Login service is not connected.")};
    }

    const auto userAccount = m_databaseManager->findUserByCredentials(trimmedUsername, password);

    if (!userAccount.has_value()) {
        return {false,
                UserRole::Guest,
                trimmedUsername,
                QStringLiteral("Invalid username or password.")};
    }

    if (!userAccount->enabled) {
        return {false,
                roleFromDatabaseValue(userAccount->role),
                userAccount->username,
                QStringLiteral("Account is disabled.")};
    }

    return {true,
            roleFromDatabaseValue(userAccount->role),
            userAccount->username,
            QStringLiteral("Login successful.")};
}

LoginResult LoginManager::loginAsGuest() const
{
    return {true,
            UserRole::Guest,
            QStringLiteral("Guest"),
            QStringLiteral("Guest access granted.")};
}
