#ifndef DASHINSTRUMENT_H
#define DASHINSTRUMENT_H

#include "abstractinstrument.h"
#include <QtCore/QObject>

class DashInstrument : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit DashInstrument(QObject *parent = 0);
    
    void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
    void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
    void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false); 
};

#endif
