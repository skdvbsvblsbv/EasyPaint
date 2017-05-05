#include "palettebutton.h"

#include <QMouseEvent>

PaletteButton::PaletteButton(const QColor &color)
{
    mColor = color;
    setMinimumSize(QSize(30, 30));
    setMaximumSize(QSize(30, 30));
    QPixmap pixmap(20, 20);
    pixmap.fill(color);
    setIcon(pixmap);
    setStatusTip(color.name());
}

void PaletteButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        DataSingleton::Instance()->setPrimaryColor(mColor);
    else if(event->button() == Qt::RightButton)
        DataSingleton::Instance()->setSecondaryColor(mColor);

    emit colorPicked();
}

//added a double click event which makes the user select a custom color
void PaletteButton::mouseDoubleClickEvent(QMouseEvent *event)
{
	QColor color = QColorDialog::getColor(mColor, this);
	if (color.isValid())
	{
		if (event->button() == Qt::LeftButton){
			DataSingleton::Instance()->setPrimaryColor(color);
		}
		else if (event->button() == Qt::RightButton){
			DataSingleton::Instance()->setSecondaryColor(color);
		}
		emit colorPicked();
	}

}
