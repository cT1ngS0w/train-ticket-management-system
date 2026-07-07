#include <QApplication>

#include "database_manager.h"
#include "login_dialog.h"
#include "login_manager.h"
#include "main_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DatabaseManager databaseManager;
    databaseManager.initialize();

    LoginManager loginManager(&databaseManager);
    LoginDialog loginDialog(loginManager);

    if (loginDialog.exec() != QDialog::Accepted) {
        return 0;
    }

    MainWindow window(loginDialog.loginResult());
    window.show();

    return app.exec();
}
