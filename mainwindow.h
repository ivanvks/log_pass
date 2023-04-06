#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void login();

private:
    QSqlDatabase db;
    QSqlTableModel *model;
    QTableView *view;
};

#endif // MAINWINDOW_H
