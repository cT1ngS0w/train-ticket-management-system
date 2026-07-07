#pragma once

#include <optional>

#include <QString>

// 登录模块只需要用户认证结果，不直接关心数据库表的内部查询细节。
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

    // 接口先行：后续真正的 User 表查询应在这里实现，不能写到 UI 或 LoginManager 中。
    std::optional<UserAccountRecord> findUserByCredentials(const QString &username,
                                                           const QString &password) const;
};
