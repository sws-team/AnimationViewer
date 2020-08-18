#include "animationwidget.h"

#include <QPaintEvent>
#include <QTimerEvent>
#include <QDropEvent>
#include <QPainter>
#include <QMimeData>
#include <QFileInfo>
#include <QDebug>

AnimationWidget::AnimationWidget(QWidget *parent) :
	QWidget(parent)
  ,m_row(0)
  ,m_columns(1)
  ,m_time(200)
  ,timerId(-1)
  ,currentTime(0)
  ,currentFrame(0)
  ,m_color(Qt::black)
{
	setAcceptDrops(true);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void AnimationWidget::loadFile(const QString &fileName)
{
	if (!QFileInfo(fileName).exists())
		return;
	if (pixmap.load(fileName))
	{
		update();
		emit fileChanged(fileName);
	}
}

void AnimationWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)
	QPainter painter(this);
	const QRectF rect = QRectF(m_frameSize.width() * currentFrame,
							   m_frameSize.height() * m_row,
							   m_frameSize.width(),
							   m_frameSize.height());
	const int width = this->width();
	const int height = width * m_frameSize.height() / m_frameSize.width();
	const QRect drawRect = QRect(0, 0, width, height);
	painter.fillRect(drawRect, m_color);
	painter.drawPixmap(drawRect, pixmap, rect);
}

void AnimationWidget::timerEvent(QTimerEvent *event)
{
	if (timerId != event->timerId())
		return;
	currentTime += INTERVAL;
	if (currentTime >= m_time)
	{
		currentTime = 0;
		nextFrame();
	}
}

QSize AnimationWidget::frameSize() const
{
	return m_frameSize;
}

void AnimationWidget::setFrameSize(const QSize &frameSize)
{
	m_frameSize = frameSize;
}

void AnimationWidget::start()
{
	timerId = startTimer(INTERVAL);
}

void AnimationWidget::stop()
{
	killTimer(timerId);
	currentTime = 0;
}

void AnimationWidget::nextFrame()
{
	currentFrame++;
	if (currentFrame >= m_columns)
		currentFrame = 0;
	update();
}

QColor AnimationWidget::color() const
{
    return m_color;
}

void AnimationWidget::setColor(const QColor &color)
{
    m_color = color;
}

void AnimationWidget::dropEvent(QDropEvent *event)
{
    if (!event->mimeData()->hasUrls())
        return;
    
    const QList<QUrl> urlList = event->mimeData()->urls();
	if (urlList.isEmpty())
		return;

	loadFile(urlList.first().toLocalFile());
}

void AnimationWidget::dragEnterEvent(QDragEnterEvent *event)
{
	event->accept();
}

QSize AnimationWidget::minimumSizeHint() const
{
	return m_frameSize;
}

QSize AnimationWidget::sizeHint() const
{
	return m_frameSize;
}

qreal AnimationWidget::time() const
{
	return m_time;
}

void AnimationWidget::setTime(const int time)
{
	m_time = time;
}

void AnimationWidget::setWidth(const int width)
{
	m_frameSize.setWidth(width);
}

void AnimationWidget::setHeight(const int height)
{
	m_frameSize.setHeight(height);
}

int AnimationWidget::columns() const
{
	return m_columns;
}

void AnimationWidget::setColumns(int columns)
{
	m_columns = columns;
}

int AnimationWidget::row() const
{
	return m_row;
}

void AnimationWidget::setRow(int row)
{
	m_row = row;
}
