#ifndef NOTE_H
#define NOTE_H

#include <QWidget>

class Note : public QWidget
{
    Q_OBJECT
public:
    explicit Note(QWidget *parent = 0);
    
signals:
    
public slots:


private:
    int start;
    int end;
    int high;
};

#endif // NOTE_H
