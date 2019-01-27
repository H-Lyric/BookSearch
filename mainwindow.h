#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtNetwork>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include "QZXing.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int fetch; //if fetch == 0, fetch book title; if fetch == 1, fetch book cover

private slots:
    void on_ScanBtn_clicked();
    void on_SearchBtn_clicked();
    void replyFinished(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
};

#endif // MAINWINDOW_H
