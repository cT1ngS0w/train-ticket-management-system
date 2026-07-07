#pragma once


// Current functionality
// 1. open a SQLite database,
// 2. create it automatically if it does not exist,
// 3. create the four Version 1 tables,
// 4. report success or failure.
//
// We are intentionally NOT adding booking, search, CRUD, login logic, or
// business rules here. This keeps DatabaseManager focused on initialization

#include <QString>

class QSqlDatabase;

class DatabaseManager {
public:
    // Keeping the existing class name and keep initialize() as the main entry
    // point, because that matches the current project architecture.

    // Constructor and destructor
    DatabaseManager();
    ~DatabaseManager();

    // Main functionality of initialization:
    // - open SQLite
    // - enables foreign key support
    // - creates the Version 1 tables if they do not already exist
    bool initialize();

    // Utility methods:
    bool isOpen() const;
    bool wasCreated() const;
    QString databasePath() const;
    QString lastError() const;

private:
    // * This block connect helpers
    // openDatabase() only worries about creating & opening the SQLite file.
    // createTables() only worries about running CREATE TABLE statements.
    
    bool openDatabase();
    void closeDatabase();
    bool createTables();
    bool executeStatement(const QString &sql);
    QString resolveDatabasePath() const;

    // * This block
    // we store these as class state so initialization can be called cleanly and
    // later modules can ask what happened without doing SQL themselves.
    QString m_connectionName;
    QString m_databasePath;
    QString m_lastError;
    bool m_wasCreated = false;
};