#pragma once

#include <optional>

#include <QString>

struct UserAccountRecord
{
    int userId = 0;
    QString username;
    int role = 0;
    bool enabled = false;
};

class DatabaseManager
{
public:
    bool initialize();
    std::optional<UserAccountRecord> findUserByCredentials(const QString &username,
                                                           const QString &password) const;
};
