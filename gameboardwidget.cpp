#include "gameboardwidget.h"

#include <fstream>
#include <QFileDialog>
#include <QDebug>

GameBoardWidget::GameBoardWidget(QWidget *parent):
    QGraphicsView(parent)
{
	setDragMode(QGraphicsView::ScrollHandDrag);
	setRenderHint(QPainter::Antialiasing);
	this->setScene(&scene);
}


void GameBoardWidget::loadButtonPressed()
{
	auto fileName = QFileDialog::getOpenFileName(
		this, "Open RLE", QDir::currentPath(), "RLE Files (*.rle)");

	if (!fileName.isEmpty()) {
		gameMaze.loafFromFile(fileName.toStdString());

		for (auto item : gameRectangles) {
			scene.removeItem(item);
			delete item;
		}
		gameRectangles.clear();
		cache.clear();




		for (unsigned int row = 0; row < gameMaze.getNumberOfRows(); ++row) {
			for (unsigned int column = 0; column < gameMaze.getNumberOfColumns(); ++column) {
				auto item = scene.addRect(0 + row * 15, 0 + column * 15, 15, 15);
				gameRectangles.append(item);
				//item->setFlag(QGraphicsItem::ItemIsFocusable, true);
			}
		}

		fillRect();
		emit fileLoaded();
	}
}


void GameBoardWidget::saveButtonPressed() 
{
	auto fileName = QFileDialog::getSaveFileName(this, "Open RLE", QDir::currentPath(), "RLE Files (*.rle)");
	std::fstream configFile;
	configFile.open(fileName.toStdString(), std::fstream::out);
	configFile << gameMaze.convertMazetoRLE();
	configFile.close();
	//qDebug() << fileName;
}


void GameBoardWidget::fillRect()
{
	for (unsigned int row = 0; row < gameMaze.getNumberOfRows(); ++row) {
		for (unsigned int column = 0; column < gameMaze.getNumberOfColumns(); ++column) {
			if (gameMaze.game_maze[row][column].m_current_cell)
				gameRectangles[convert2Dto1D(row, column)]->setBrush(Qt::black);
			else gameRectangles[convert2Dto1D(row, column)]->setBrush(Qt::white);
		}
	}
}

unsigned int GameBoardWidget::convert2Dto1D(unsigned int row, unsigned int column)
{
	return row * gameMaze.getNumberOfColumns() + column;
}


void GameBoardWidget::nextFrame()
{
	cache.push_back(gameMaze.game_maze);
	if (cache.size() > 200) cache.erase(cache.cbegin(), cache.cbegin() + 50);
	gameMaze.computeMaze();
	fillRect();
}


void GameBoardWidget::previousFrame()
{
	gameMaze.game_maze = cache.back();	
	cache.pop_back();
	fillRect();
	if (cache.empty()) emit cacheEmpty();
}


void GameBoardWidget::wheelEvent(QWheelEvent *event)
{
	const qreal factor = 1.1;
	if (event->angleDelta().y() > 0) scale(factor, factor);
	else scale(1/factor, 1/factor);
	qDebug() << "SCROLL";

}