#ifndef QPALETTEBUTTON_H
#define QPALETTEBUTTON_H

#include "../datasingleton.h"

#include <QToolButton>
#include <QColorDialog>

class PaletteButton : public QToolButton
{
    Q_OBJECT

public:
    PaletteButton(const QColor &color);

signals:
    void colorPicked();

private:
    QColor mColor;

protected:
    void mousePressEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event); /*Shu added double click event*/

};

#endif // QPALETTEBUTTON_H
