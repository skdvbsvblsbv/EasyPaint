#ifndef HISTOGRAM_H__
# define HISTOGRAM_H__

#include <QWidget>
#include <QVector>
#include <QRgb>
#include <QPainter>

/**
* @brief Histogram tool class.
* @author Robin Jouffroy
*
*/
class Histogram : public QWidget
{
	Q_OBJECT;
public:
	Histogram(QImage *, bool, QWidget *parent = 0);
	~Histogram();

private:
	bool			isCumul;

	QVector<int>	redCanal;
	QVector<int>	greenCanal;
	QVector<int>	blueCanal;

	int				redCumul;
	int				greenCumul;
	int				blueCumul;

	int				redMax;
	int				greenMax;
	int				blueMax;

	void			init(QImage *, bool);
	void			calcHisto(QImage *);
	void			calcCumul(QImage *);
	int				getMaxIndiceValue();

protected:
	void	paintEvent(QPaintEvent *);
};

#endif /* !HISTOGRAM_H__ */
