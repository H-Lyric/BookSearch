#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include "QZXing.h"
#include "networker.h"
#include "book.h"

namespace Ui {
class MainWindow;
}

enum RemoteRequest {
    FetchInfo,
    FetchCover
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ScanBtn_clicked();
    void on_SearchBtn_clicked();

private:
    Ui::MainWindow *ui;
    RemoteRequest request;
    NetWorker *netWorker;
};

#endif // MAINWINDOW_H
