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

    QString getTitle() const;
    void setTitle(const QString &title);

    QStringList getAuthors() const;
    void setAuthors(const QJsonArray &autarray);

    QString getAveRate() const;
    void setAveRate(const QString &averate);

    QPixmap getCover() const;
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
