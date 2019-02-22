#include "book.h"

Book::Book() : d(new Book::Private())
{

}

Book::~Book()
{
    delete d;
    d = 0;
}

QString Book::getTitle()
{
    return d->m_title;
}

void Book::setTitle(const QString &title)
{
    d->m_title = title;
}

QStringList Book::getAuthors()
{
    return d->m_authors;
}

void Book::setAuthors(const QJsonArray &autarray)
{
    for(int i = 0; i< autarray.size(); i++){
        d->m_authors.append(autarray.at(i).toString());
    }
}

QString Book::getAveRate()
{
    return d->m_averate;
}

void Book::setAveRate(const QString &averate)
{
    d->m_averate = averate;
}

QPixmap Book::getCover()
{
    return d->m_cover;
}

void Book::setCover(const QByteArray &data)
{
    d->m_cover.loadFromData(data);
}
