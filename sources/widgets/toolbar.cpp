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
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN Button OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "toolbar.h"
#include "colorchooser.h"
#include "../datasingleton.h"

#include <QToolButton>
#include <QGridLayout>
#include <QSpinBox>
#include <QAction>
#include <QtCore/QMap>
#include <qcombobox.h>

ToolBar::ToolBar(const QMap<InstrumentsEnum, QAction *> &actMap, QWidget *parent) :
    QToolBar(tr("Instruments"), parent), mActMap(actMap)
{
    setMovable(false);
    initializeItems();
    mPrevInstrumentSetted = false;
}

QToolButton* ToolBar::createToolButton(QAction *act)
{
    QToolButton *toolButton = new QToolButton();
    toolButton->setMinimumSize(QSize(30, 30));
    toolButton->setMaximumSize(QSize(30, 30));
    toolButton->setDefaultAction(act);
    toolButton->setStatusTip(act->text());
    return toolButton;
}

void ToolBar::initializeItems()
{
    mCursorButton = createToolButton(mActMap[CURSOR]);
    mEraserButton = createToolButton(mActMap[ERASER]);
    mPenButton = createToolButton(mActMap[PEN]);
    mLineButton = createToolButton(mActMap[LINE]);
    mColorPickerButton = createToolButton(mActMap[COLORPICKER]);
    mMagnifierButton = createToolButton(mActMap[MAGNIFIER]);
    mSprayButton = createToolButton(mActMap[SPRAY]);
    mFillButton = createToolButton(mActMap[FILL]);
    mRectangleButton = createToolButton(mActMap[RECTANGLE]);
    mEllipseButton = createToolButton(mActMap[ELLIPSE]);
    mCurveButton = createToolButton(mActMap[CURVELINE]);
    mTextButton = createToolButton(mActMap[TEXT]);
    mDashButton = createToolButton(mActMap[DASH]);
	mTriangleButton = createToolButton(mActMap[TRIANGLE]);
	mSignatureButton = createToolButton(mActMap[SIGN]);

    QGridLayout *bLayout = new QGridLayout();
    bLayout->setMargin(3);
    bLayout->addWidget(mCursorButton, 0, 0);
    bLayout->addWidget(mEraserButton, 0, 1);
    bLayout->addWidget(mColorPickerButton, 1, 0);
    bLayout->addWidget(mMagnifierButton, 1, 1);
    bLayout->addWidget(mPenButton, 2, 0);
    bLayout->addWidget(mLineButton, 2, 1);
    bLayout->addWidget(mSprayButton, 3, 0);
    bLayout->addWidget(mFillButton, 3, 1);
    bLayout->addWidget(mRectangleButton, 4, 0);
    bLayout->addWidget(mEllipseButton, 4, 1);
    bLayout->addWidget(mCurveButton, 5, 0);
    bLayout->addWidget(mTextButton, 5, 1);
    bLayout->addWidget(mDashButton, 6, 0);
	bLayout->addWidget(mTriangleButton, 6, 1);
	bLayout->addWidget(mSignatureButton, 7, 0);

    QWidget *bWidget = new QWidget();
    bWidget->setLayout(bLayout);

    mPColorChooser = new ColorChooser(0, 0, 0, this);
    mPColorChooser->setStatusTip(tr("Primary color"));
    mPColorChooser->setToolTip(tr("Primary color"));
    connect(mPColorChooser, SIGNAL(sendColor(QColor)), this, SLOT(primaryColorChanged(QColor)));

    mSColorChooser = new ColorChooser(255, 255, 255, this);
    mSColorChooser->setStatusTip(tr("Secondary color"));
    mSColorChooser->setToolTip(tr("Secondary color"));
    connect(mSColorChooser, SIGNAL(sendColor(QColor)), this, SLOT(secondaryColorChanged(QColor)));

	QComboBox *penSizeList = new QComboBox();
	penSizeList->setIconSize(QSize(100, 100));
	penSizeList->setStatusTip("Pen Size");

	for (int i = 1; i < 21; i++)
	{
		penSizeList->addItem(QIcon(QString(":/media/instruments-icons/Capture%1.png").arg(i)), QString("%1px").arg(i));
	}

	/*QIcon ONEpxIcon(":/media/instruments-icons/Capture1.png");
	QIcon TWOpxIcon(":/media/instruments-icons/Capture2.png");
	QIcon THREEpxIcon(":/media/instruments-icons/Capture3.png");
	QIcon FOURpxIcon(":/media/instruments-icons/Capture4.png");
	QIcon FIVEpxIcon(":/media/instruments-icons/Capture5.png");
	QIcon SIXpxIcon(":/media/instruments-icons/Capture6.png");
	QIcon SEVENpxIcon(":/media/instruments-icons/Capture7.png");
	QIcon EIGHTpxIcon(":/media/instruments-icons/Capture8.png");
	QIcon NINEpxIcon(":/media/instruments-icons/Capture9.png");
	QIcon TENpxIcon(":/media/instruments-icons/Capture10.png");
	QIcon ELEVENpxIcon(":/media/instruments-icons/Capture11.png");
	QIcon TWELVEpxIcon(":/media/instruments-icons/Capture12.png");
	QIcon THIRTEENpxIcon(":/media/instruments-icons/Capture13.png");
	QIcon FOURTEENpxIcon(":/media/instruments-icons/Capture14.png");
	QIcon FIFTHEENpxIcon(":/media/instruments-icons/Capture15.png");
	QIcon SIXTEENpxIcon(":/media/instruments-icons/Capture16.png");
	QIcon SEVENTEENpxIcon(":/media/instruments-icons/Capture17.png");
	QIcon EIGHTEENpxIcon(":/media/instruments-icons/Capture18.png");
	QIcon NINETEENpxIcon(":/media/instruments-icons/Capture19.png");
	QIcon TWENTYpxIcon(":/media/instruments-icons/Capture20.png");
	penSizeList->addItem(ONEpxIcon, "1px");
	penSizeList->addItem(TWOpxIcon, "2px");
	penSizeList->addItem(THREEpxIcon, "3px");
	penSizeList->addItem(FOURpxIcon, "4px");
	penSizeList->addItem(FIVEpxIcon, "5px");
	penSizeList->addItem(SIXpxIcon, "6px");
	penSizeList->addItem(SEVENpxIcon, "7px");
	penSizeList->addItem(EIGHTpxIcon, "8px");
	penSizeList->addItem(NINEpxIcon, "9px");
	penSizeList->addItem(TENpxIcon, "10px");
	penSizeList->addItem(ELEVENpxIcon, "11px");
	penSizeList->addItem(TWELVEpxIcon, "12px");
	penSizeList->addItem(THIRTEENpxIcon, "13px");
	penSizeList->addItem(FOURTEENpxIcon, "14px");
	penSizeList->addItem(FIFTHEENpxIcon, "15px");
	penSizeList->addItem(SIXTEENpxIcon, "16px");
	penSizeList->addItem(SEVENTEENpxIcon, "17px");
	penSizeList->addItem(EIGHTEENpxIcon, "18px");
	penSizeList->addItem(NINETEENpxIcon, "19px");
	penSizeList->addItem(TWENTYpxIcon, "20px");*/
	connect(penSizeList, SIGNAL(activated(int)), this, SLOT(penValueChanged(int)));

    QGridLayout *tLayout = new QGridLayout();
    tLayout->setMargin(3);
    tLayout->addWidget(mPColorChooser, 0, 0);
    tLayout->addWidget(mSColorChooser, 0, 1);
	tLayout->addWidget(penSizeList, 1, 0, 1, 2);

    QWidget *tWidget = new QWidget();
    tWidget->setLayout(tLayout);

    addWidget(bWidget);
    addSeparator();
    addWidget(tWidget);
}

void ToolBar::penValueChanged(const int &value)
{
    DataSingleton::Instance()->setPenSize(value + 1);
}

void ToolBar::primaryColorChanged(const QColor &color)
{
    DataSingleton::Instance()->setPrimaryColor(color);
}

void ToolBar::secondaryColorChanged(const QColor &color)
{
    DataSingleton::Instance()->setSecondaryColor(color);
}

void ToolBar::setPrimaryColorView()
{
    mPColorChooser->setColor(DataSingleton::Instance()->getPrimaryColor());
}

void ToolBar::setSecondaryColorView()
{
    mSColorChooser->setColor(DataSingleton::Instance()->getSecondaryColor());
}

void ToolBar::contextMenuEvent(QContextMenuEvent *)
{
}
