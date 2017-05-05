#ifndef MIRRORHORIZONTAL_H
#define MIRRORHORIZONTAL_H


#include "abstracteffect.h"

#include <QtCore/QObject>

/**
 * @brief Mirror Horizontal effect class.
 *
 */

class MirrorEffect : public AbstractEffect
{
    Q_OBJECT

private:
    bool mTopBottom;
public:
    explicit MirrorEffect(bool mTopBottom, QObject *parent = 0);

    void applyEffect(ImageArea &imageArea);

};

#endif // MIRRORHORIZONTAL_H
