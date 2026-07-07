#include "database_manager.h"

bool DatabaseManager::initialize()
{
    return true;
}

std::optional<UserAccountRecord> DatabaseManager::findUserByCredentials(const QString &username,
                                                                        const QString &password) const
{
    // 当前数据库初始化尚未完成，先保留统一入口，避免登录模块绕过 DatabaseManager。
    static_cast<void>(username);
    static_cast<void>(password);

    return std::nullopt;
}
