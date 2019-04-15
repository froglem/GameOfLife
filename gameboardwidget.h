#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include"Maze.h"

#include <memory>
#include <deque>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVector>
#include <QWheelEvent>



class GameBoardWidget : public QGraphicsView
{
    Q_OBJECT
public:
    GameBoardWidget(QWidget* parent = nullptr);
	unsigned int convert2Dto1D(unsigned int row, unsigned int column);
	void wheelEvent(QWheelEvent *event) override;

private:
	QGraphicsScene scene{};
	QVector<QGraphicsRectItem*> gameRectangles;
	Maze gameMaze{};
	std::deque<Matrix<Point> > cache{};

	void fillRect();

public slots:
	void loadButtonPressed();
	void saveButtonPressed();
	void nextFrame();
	void previousFrame();

signals:
	void fileLoaded();
	void cacheEmpty();

};

#endif // GAMEBOARDWIDGET_H
