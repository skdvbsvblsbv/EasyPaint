#include "histogram.h"

/*
** @author Robin Jouffroy
*/

Histogram::Histogram(QImage *currentImg, bool iscumul, QWidget *parent)
: QWidget(parent)
{
	if (currentImg != NULL)
		init(currentImg, iscumul);
	else
		return;
}

Histogram::~Histogram()
{
}

void	Histogram::init(QImage *img, bool iscumul)
{
	this->isCumul = iscumul;

	if (isCumul)
		setWindowTitle("RGB Cumulative Histogram");
	else
		setWindowTitle("RGB Histogram");

	redCanal.resize(256);
	greenCanal.resize(256);
	blueCanal.resize(256);

	if (isCumul)
	{
		redCumul = 0;
		greenCumul = 0;
		blueCumul = 0;
	}
	else
	{
		redMax = 0;
		greenMax = 0;
		blueMax = 0;
	}
	calcHisto(img);
}

// calc histogram for each color
void	Histogram::calcHisto(QImage *img)
{
	QRgb pixel;

	for (int x = 0; x < img->width(); x++)
	{
		for (int y = 0; y < img->height(); y++)
		{
			pixel = img->pixel(x, y);

			int redIndice = qRed(pixel);
			int greenIndice = qGreen(pixel);
			int blueIndice = qBlue(pixel);

			redCanal[redIndice] += 1;
			greenCanal[greenIndice] += 1;
			blueCanal[blueIndice] += 1;

			if (!isCumul)
			{
				if (redCanal[redIndice] > redMax)
					redMax = redCanal[redIndice];
				if (greenCanal[greenIndice] > greenMax)
					greenMax = greenCanal[greenIndice];
				if (blueCanal[blueIndice] > blueMax)
					blueMax = blueCanal[blueIndice];
			}
		}
	}
	if (isCumul)
		calcCumul(img);
}

// calc cumulative histogram for each color
void	Histogram::calcCumul(QImage *img)
{
	for (int i = 0; i < 256; i++)
	{
		redCumul += redCanal[i];
		redCanal[i] = redCumul;
		redCanal[i] = 1000 * redCanal[i] / (img->width() * img->height());

		greenCumul += greenCanal[i];
		greenCanal[i] = greenCumul;
		greenCanal[i] = 1000 * greenCanal[i] / (img->width() * img->height());

		blueCumul += blueCanal[i];
		blueCanal[i] = blueCumul;
		blueCanal[i] = 1000 * blueCanal[i] / (img->width() * img->height());
	}
}

// Get max indice value between each color
int		Histogram::getMaxIndiceValue()
{
	if (redMax > greenMax && redMax > blueMax)
		return redMax;
	else if (greenMax > redMax && greenMax > blueMax)
		return greenMax;
	else
		return blueMax;
}

void	Histogram::paintEvent(QPaintEvent *)
{
	QPainter p(this);

	QPen pen(Qt::black);
	pen.setWidth(1);
	p.setPen(pen);

	QBrush brush(Qt::SolidPattern);
	brush.setColor("#000000");
	p.setBrush(brush);

	QPen red(Qt::red);
	red.setWidth(1);

	QPen green(Qt::green);
	green.setWidth(1);

	QPen blue(Qt::blue);
	blue.setWidth(1);

	QPen gray(Qt::gray);
	gray.setWidth(1);

	// draw background
	p.drawRect(0, 0, width(), height());

	//keep width and height for easy access
	int w = this->width();
	int h = this->height();

	int indice = 0;
	//get max color indice value
	if (!isCumul)
		 indice = getMaxIndiceValue();

	// draw text
	p.setPen(gray);
	p.drawText(15, h - 15, "0");
	if (isCumul)
		p.drawText(12, 25, "1000 (Per thousand of Pixels)");
	else
		p.drawText(12, 25, QString::number(indice) + " (Number of Pixels)");
	p.drawText(w - 155, h - 12, "(Color Level)    255");

	// draw y line
	p.drawLine(35, 35, 35, h - 35);
	// draw x line
	p.drawLine(35, h - 35, w - 35, h - 35);

	// define step between points for graph
	float xStep = float(w - 70) / float(255);
	float yStep = 0;
	if (isCumul)
		yStep = float(h - 70) / float(1000.0);
	else
		yStep = float(h - 70) / float(indice);

	// define orign points
	int xOrigin = 36;
	int yOrigin = h - 36;

	// print loop
	for (int i = 0; i < 255; i++)
	{
		// if gray scale image
		if ((redCanal[i] == greenCanal[i]) && (redCanal[i] == blueCanal[i]))
		{
			// print gray line
			p.setPen(gray);
			p.drawLine(xOrigin + (i * xStep), yOrigin - (redCanal[i] * yStep), xOrigin + ((i + 1) * xStep), yOrigin - (redCanal[i+1] * yStep));

		}
		else
		{
			//draw red line
			p.setPen(red);
			p.drawLine(xOrigin + (i * xStep), yOrigin - (redCanal[i] * yStep), xOrigin + ((i + 1) * xStep), yOrigin - (redCanal[i+1] * yStep));

			//draw green line
			p.setPen(green);
			p.drawLine(xOrigin + (i * xStep), yOrigin - (greenCanal[i] * yStep), xOrigin + ((i + 1) * xStep), yOrigin - (greenCanal[i+1] * yStep));

			//draw blue line
			p.setPen(blue);
			p.drawLine(xOrigin + (i * xStep), yOrigin - (blueCanal[i] * yStep), xOrigin + ((i + 1) * xStep), yOrigin - (blueCanal[i+1] * yStep));
		}
	}
}