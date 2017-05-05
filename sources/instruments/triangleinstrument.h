#ifndef TRIANGLEINSTRUMENT_H__
# define TRIANGLEINSTRUMENT_H__

#include "abstractinstrument.h"

#include <QtCore/QObject>

/**
* @brief Triangle instrument class.
*
*/
class TriangleInstrument : public AbstractInstrument
{
	Q_OBJECT
public:
	explicit TriangleInstrument(QObject *parent = 0);

	void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
	void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);
};

#endif /* !TRIANGLEINSTRUMENT_H__ */
