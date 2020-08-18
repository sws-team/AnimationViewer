#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QWidget>

class AnimationWidget : public QWidget
{
	Q_OBJECT
public:
	explicit AnimationWidget(QWidget *parent = nullptr);

	void loadFile(const QString& fileName);

	int row() const;
	int columns() const;
	qreal time() const;

	QSize frameSize() const;
	void setFrameSize(const QSize &frameSize);

	void start();
	void stop();

	QColor color() const;
	void setColor(const QColor &color);

public slots:
	void setRow(int row);
	void setColumns(int columns);
	void setTime(const int time);
	void setWidth(const int width);
	void setHeight(const int height);

protected:
	void paintEvent(QPaintEvent *event) override;
	void timerEvent(QTimerEvent *event) override;
	void dropEvent(QDropEvent *event) override;
	void dragEnterEvent(QDragEnterEvent *event) override;
	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

signals:
	void fileChanged(const QString&);

private:
	int m_row;
	int m_columns;
	int m_time;
	QSize m_frameSize;

	int timerId;
	int currentTime;
	static constexpr int INTERVAL = 10;
	void nextFrame();
	int currentFrame;
	QPixmap pixmap;
	QColor m_color;
};

#endif // ANIMATIONWIDGET_H
