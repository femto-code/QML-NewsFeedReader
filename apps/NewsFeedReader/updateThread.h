#ifndef UPDATETHREAD_H
#define UPDATETHREAD_H

#include <QThread>
#include <QString>
#include "FeedList.h"

class UpdateThread : public QThread{
    Q_OBJECT
    QPointer<FeedList> instance;
public:
    UpdateThread(FeedList* el) : QThread(NULL), instance(el) {}
    void run();

public slots:
    void doUpdate();
};



#endif // UPDATETHREAD_H
