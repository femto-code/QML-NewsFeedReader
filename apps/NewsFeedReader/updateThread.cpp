#include "updateThread.h"

#include <QDebug>


void UpdateThread::run() {
    qDebug() << "Starting Thread...";

}

void UpdateThread::doUpdate()
{
    qDebug() << "Lambda";
    //instance->debugFeedList();
    instance->triggerUpdate();
}

