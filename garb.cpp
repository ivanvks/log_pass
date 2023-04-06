#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QtWidgets>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create a database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("mydb");
    db.setUserName("username");
    db.setPassword("password");

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error", db.lastError().text());
        return 1;
    }

    // Create a login form
    QDialog login;
    login.setWindowTitle("Login");

    QLabel* usernameLabel = new QLabel("Username:");
    QLineEdit* usernameLineEdit = new QLineEdit();
    QHBoxLayout* usernameLayout = new QHBoxLayout();
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameLineEdit);

    QLabel* passwordLabel = new QLabel("Password:");
    QLineEdit* passwordLineEdit = new QLineEdit();
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    QHBoxLayout* passwordLayout = new QHBoxLayout();
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordLineEdit);

    QPushButton* loginButton = new QPushButton("Login");
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(loginButton);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addLayout(usernameLayout);
    layout->addLayout(passwordLayout);
    layout->addLayout(buttonLayout);
    login.setLayout(layout);

    // Handle login button clicked event
    QObject::connect(loginButton, &QPushButton::clicked, [&] {
        QString username = usernameLineEdit->text();
        QString password = passwordLineEdit->text();
        db.setUserName(username);
        db.setPassword(password);
        if (!db.open()) {
            QMessageBox::critical(nullptr, "Database Error", db.lastError().text());
        } else {
            login.accept();
        }
    });

    // Show the login form and wait for it to close
    if (login.exec() != QDialog::Accepted) {
        return 0;
    }

    // Create a main window
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("PostgreSQL Database");

    // Create a table view to display the data
    QSqlTableModel* model = new QSqlTableModel();
    model->setTable("mytable");
    model->select();
    QTableView* view = new QTableView();
    view->setModel(model);

    // Add the table view to the main window
    mainWindow.setCentralWidget(view);
    mainWindow.show();

    return app.exec();
}
