/*
* This source file is part of EasyPaint.
*
* Copyright (c) 2012 EasyPaint <https://github.com/Gr1N/EasyPaint>
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <QMouseEvent>
#include "additionaltools.h"
#include "imagearea.h"
#include "dialogs/resizedialog.h"

#include <QImage>
#include <QPainter>
#include <QLabel>
#include <QTransform>
#include <QSize>
#include <QClipboard>
#include <QApplication>

AdditionalTools::AdditionalTools(ImageArea *pImageArea, QObject *parent) :
QObject(parent)
{
	mPImageArea = pImageArea;
	mZoomedFactor = 1;
}

AdditionalTools::~AdditionalTools()
{

}

void AdditionalTools::resizeCanvas(int width, int height, bool flag)
{
	if (flag)
	{
		ResizeDialog resizeDialog(QSize(width, height));
		if (resizeDialog.exec() == QDialog::Accepted)
		{
			QSize newSize = resizeDialog.getNewSize();
			width = newSize.width();
			height = newSize.height();
		}
	}

	if (width < 1 || height < 1)
		return;
	QImage *tempImage = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);
	QPainter painter(tempImage);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(Qt::white));
	painter.drawRect(QRect(0, 0, width, height));
	painter.drawImage(0, 0, *mPImageArea->getImage());
	painter.end();

	mPImageArea->setImage(*tempImage);

	mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
		mPImageArea->getImage()->rect().bottom() + 6);
	mPImageArea->setEdited(true);
	mPImageArea->clearSelection();
}

void AdditionalTools::defaultCanvas(int width, int height, bool flag)
{
	width = 800;
	height = 600;
	if (width < 1 || height < 1)
		return;
	if (flag)
	{
		QImage *tempImage = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);
		QPainter painter(tempImage);
		painter.setPen(Qt::NoPen);
		painter.setBrush(QBrush(Qt::white));
		painter.drawRect(QRect(0, 0, width, height));
		painter.drawImage(0, 0, *mPImageArea->getImage());
		painter.end();

		mPImageArea->setImage(*tempImage);

		mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
			mPImageArea->getImage()->rect().bottom() + 6);
		mPImageArea->setEdited(true);
		mPImageArea->clearSelection();
	}
}

void AdditionalTools::defaultCanvas2(int width, int height, bool flag)
{
	width = 1280;
	height = 720;
	if (width < 1 || height < 1)
		return;
	if (flag)
	{
		QImage *tempImage = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);
		QPainter painter(tempImage);
		painter.setPen(Qt::NoPen);
		painter.setBrush(QBrush(Qt::white));
		painter.drawRect(QRect(0, 0, width, height));
		painter.drawImage(0, 0, *mPImageArea->getImage());
		painter.end();

		mPImageArea->setImage(*tempImage);

		mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
			mPImageArea->getImage()->rect().bottom() + 6);
		mPImageArea->setEdited(true);
		mPImageArea->clearSelection();
	}
}

void AdditionalTools::resizeImage()
{
	ResizeDialog resizeDialog(mPImageArea->getImage()->size());
	if (resizeDialog.exec() == QDialog::Accepted)
	{
		mPImageArea->setImage(mPImageArea->getImage()->scaled(resizeDialog.getNewSize()));
		mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
			mPImageArea->getImage()->rect().bottom() + 6);
		mPImageArea->setEdited(true);
		mPImageArea->clearSelection();
	}
}

void AdditionalTools::rotateImage(bool flag)
{
	QTransform transform;
	if (flag)
	{
		transform.rotate(180);
	}
	else
	{
		transform.rotate(-180);
	}
	mPImageArea->setImage(mPImageArea->getImage()->transformed(transform));
	mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
		mPImageArea->getImage()->rect().bottom() + 6);
	mPImageArea->update();
	mPImageArea->setEdited(true);
	mPImageArea->clearSelection();
}

/* chris you postfactoring prefactoring
void AdditionalTools::flipHorizontally()				merge to one function with parameter of bool (true or false) and extract function (called update) //chrisyou
{


QTransform transform;
transform.scale(-1, 1);

mPImageArea->setImage(mPImageArea->getImage()->transformed(transform));
mPImageArea->update();
mPImageArea->setEdited(true);
mPImageArea->clearSelection();

}

void AdditionalTools::flipVertically()
{
QTransform transform;
transform.scale(1, -1);

mPImageArea->setImage(mPImageArea->getImage()->transformed(transform));
mPImageArea->update();
mPImageArea->setEdited(true);
mPImageArea->clearSelection();

}*/

void AdditionalTools::flip(bool flag){ //chrisyou  merged function
	QTransform transform;
	if (flag)
	{
		transform.scale(-1, 1);
		mPImageArea->setImage(mPImageArea->getImage()->transformed(transform));
		update();
	}
	else
	{
		transform.scale(1, -1);
		mPImageArea->setImage(mPImageArea->getImage()->transformed(transform));
		update();
	}
}



void AdditionalTools::update() //chrisyou extracted from flip function prefactoring change request 3
{
	mPImageArea->update();
	mPImageArea->setEdited(true);
	mPImageArea->clearSelection();
}

void AdditionalTools::mirror(bool check){ //chrisyou change request 3 used update function extracted from significant concept
	int height = mPImageArea->getImage()->rect().height();
	int width = mPImageArea->getImage()->rect().width();
	int xheight, xheight2;
	if (check == 1){
		xheight = 0;
		xheight2 = width / 2;
	}

	else {
		xheight = width / 2;
		xheight2 = 0;
	}

	QTransform transform;
	QRect temp(xheight, 0, width / 2, height);
	QImage image(width / 2, height, mPImageArea->getImage()->format());
	QImage image2(width / 2, height, mPImageArea->getImage()->format());
	QImage image3(width, height, mPImageArea->getImage()->format());

	image = mPImageArea->getImage()->copy(temp);
	transform.scale(-1, 1);
	image2 = image.transformed(transform);

	QPainter p(&image3);
	p.drawImage(xheight, 0, image);
	p.drawImage(xheight2, 0, image2);

	mPImageArea->setImage(image3);
	update();
}

bool AdditionalTools::zoomImage(qreal factor)
{
	mZoomedFactor *= factor;
	if (mZoomedFactor < 0.25)
	{
		mZoomedFactor = 0.25;
		return false;
	}
	else if (mZoomedFactor > 4)
	{
		mZoomedFactor = 4;
		return false;
	}
	else
	{
		mPImageArea->setImage(mPImageArea->getImage()->transformed(QTransform::fromScale(factor, factor)));
		mPImageArea->resize((mPImageArea->rect().width())*factor, (mPImageArea->rect().height())*factor);
		emit sendNewImageSize(mPImageArea->size());
		mPImageArea->setEdited(true);
		mPImageArea->clearSelection();
		return true;
	}
}


