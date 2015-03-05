#ifndef TESTE_H
#define TESTE_H

#include <QObject>

class teste : public QObject
{
    Q_OBJECT
public:
    explicit teste(QObject *parent = 0);
    ~teste();

signals:

public slots:
};

#endif // TESTE_H
