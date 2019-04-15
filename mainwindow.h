#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gameboardwidget.h"

#include <QMainWindow>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
	GameBoardWidget *gameBoard{nullptr};
	QTimer* m_timer;



};

#endif // MAINWINDOW_H
