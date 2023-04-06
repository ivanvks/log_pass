#include "mainwindow.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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
    QObject::connect(loginButton, &QPushButton::clicked, this, &MainWindow::login);

    // Show the login form and wait for it to close
    if (login.exec() != QDialog::Accepted) {
        qApp->exit();
    }

    // Create a table view to display the data
    model = new QSqlTableModel();
    model->setTable("mytable");
    model->select();
    view = new QTableView();
    view->setModel(model);

    // Add the table view to the main window
    setCentralWidget(view);
    setWindowTitle("PostgreSQL Database");
}

void MainWindow::login() {
    QString username = dynamic_cast<QLineEdit*>(sender()->parent()->layout()->itemAt(0)->widget())->text();
    QString password = dynamic_cast<QLineEdit*>(sender()->parent()->layout()->itemAt(1)->widget())->text();
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("mydb");
    db.setUserName(username);
    db.setPassword(password);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error", db.lastError().text());
    } else {
        accept();
    }
}
