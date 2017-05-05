#include "MirrorHorizontal.h"
#include "../imagearea.h"

MirrorEffect::MirrorEffect(bool flag, QObject *parent) :
    AbstractEffect(parent), mTopBottom(flag)
{
}

void MirrorEffect::applyEffect(ImageArea &imageArea)
{
    imageArea.clearSelection();
    makeUndoCommand(imageArea);

    QImage* image = imageArea.getImage();
    int CanvasWidth;
    CanvasWidth = image->bytesPerLine();
    int CanvasHeight = image->height();

    int height2;
    height2 = CanvasHeight * 0.5;
    int x = 1;
    int flip;

    for(unsigned y = 0; y < height2; ++y)
    {
        flip = CanvasHeight - y - x;

        uchar *line1 = image->scanLine(y);
        uchar *line2 = image->scanLine(flip);
        if(mTopBottom)
             memcpy(line1,line2, CanvasWidth);
        else
             memcpy(line2, line1, CanvasWidth);

    }
    imageArea.setEdited(true);
    imageArea.update();
}

