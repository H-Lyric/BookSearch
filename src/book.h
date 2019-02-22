#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QStringList>
#include <QJsonArray>
#include <QPixmap>

class Book
{
public:
    Book();
    ~Book();

    QString getTitle();
    void setTitle(const QString &title);

    QStringList getAuthors();
    void setAuthors(const QJsonArray &autarray);

    QString getAveRate();
    void setAveRate(const QString &averate);

    QPixmap getCover();
    void setCover(const QByteArray &data);

private:
    class Private;
    Private *d;
};

class Book::Private
{
public:
    QString m_title;
    QStringList m_authors;
    QString m_averate;
    QPixmap m_cover;
};

#endif // BOOK_H
