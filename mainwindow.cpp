#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->IsbnEdit->setPlaceholderText("Scan or input ISBN");
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ScanBtn_clicked()
{
    QString m_fileName;
    m_fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "./", tr("Images(*.*)"));
    if(m_fileName.isEmpty() == false) {
        QImage img(m_fileName);
        if(!(img.load(m_fileName))){
            QMessageBox::information(this, tr("Open file failed"), tr("Can not open the file!"));
            return;
        }
        QZXing decoder;
        decoder.setDecoder(QZXing::DecoderFormat_EAN_13); //important
        QString Isbn = decoder.decodeImageFromFile(m_fileName);
        ui->IsbnEdit->setText(Isbn);
    }
}

void MainWindow::on_SearchBtn_clicked()
{
   ui->SearchBtn->setEnabled(false);
   QString Isbn = ui->IsbnEdit->text();
   QUrl url(QString("https://api.douban.com/v2/book/isbn/:%1").arg(Isbn));
   QNetworkRequest request;
   request.setUrl(url);
   manager.get(request);

}

void MainWindow::replyFinished(QNetworkReply *reply)
{
   ui->SearchBtn->setEnabled(true);
   ui->BookInfo->setWordWrap(true);

   if(reply->error() == QNetworkReply::NoError)
   {
       QJsonParseError parseJsonErr;
       QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &parseJsonErr);
       if(!(parseJsonErr.error == QJsonParseError::NoError))
       {
           qDebug() << QString("Wrong");
       }
       QJsonObject jsonObject = jsonDocument.object();
       QString title = jsonObject["title"].toString();
       ui->BookInfo->setText(title);
   }
   else
   {
       qDebug() << "Error";
   }
}
