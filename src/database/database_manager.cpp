#include "database_manager.h"

bool DatabaseManager::initialize()
{
    return true;
}

std::optional<UserAccountRecord> DatabaseManager::findUserByCredentials(const QString &username,
                                                                        const QString &password) const
{
    static_cast<void>(username);
    static_cast<void>(password);

    return std::nullopt;
}
