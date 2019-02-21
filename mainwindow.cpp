#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->IsbnEdit->setPlaceholderText("Scan or input ISBN");
    ui->TitleLbl->setWordWrap(true);
    ui->CoverLbl->setScaledContents(true);

    netWorker = NetWorker::instance();

    connect(netWorker, &NetWorker::finished, [=](QNetworkReply *reply){

        ui->SearchBtn->setEnabled(true);
        Book book;
        switch (request) {
        case FetchInfo:{
            if(reply->error() == QNetworkReply::NoError){
                QJsonParseError parseJsonErr;
                QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &parseJsonErr);
                if(!(parseJsonErr.error == QJsonParseError::NoError)){
                    qDebug() << QString("Wrong");
                }
                QJsonObject jsonObject = jsonDocument.object();
                book.setTitle(jsonObject["title"].toString());
                book.setAuthors(jsonObject.value("author").toArray());
                QJsonValue ratVal = jsonObject.value("rating");
                QJsonObject ratObj = ratVal.toObject();
                book.setAveRate(ratObj["average"].toString());
                ui->TitleLbl->setText(book.getTitle()+"\n"
                                      +book.getAuthors().join(", ")+"\n"
                                      +"Rating: "+book.getAveRate());
                request = FetchCover;
                netWorker->get(jsonObject["image"].toString());
            }
            else{
                qDebug() << "Error";
            }
            reply->deleteLater();
        }
        case FetchCover:{
            //QPixmap pixmap;
            //pixmap.loadFromData(reply->readAll());
            book.setCover(reply->readAll());
            ui->CoverLbl->setPixmap(book.getCover());
        }
        }
    });
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
   request = FetchInfo;
   netWorker->get(QString("https://api.douban.com/v2/book/isbn/:%1").arg(Isbn));
}


