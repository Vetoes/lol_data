
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLabel>
#include "Champions.h"

class MainWindow : public QMainWindow {
    Q_OBJECT //moc meta object system

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onSearchTextChanged(const QString &text);
    void onChampionSelected(QListWidgetItem *item);

private:
    QLineEdit *searchBox;
    QListWidget *championList;
    QLabel *statsLabel;
    std::vector<Champions> champions;
};

#endif // MAINWINDOW_H
