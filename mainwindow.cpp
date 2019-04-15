#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	gameBoard = new GameBoardWidget(this);
	ui->horizontalLayout->addWidget(gameBoard);
	m_timer = new QTimer(this);

	connect(ui->loadButton, &QPushButton::clicked, gameBoard, &GameBoardWidget::loadButtonPressed);
	connect(ui->saveButton, &QPushButton::clicked, gameBoard, &GameBoardWidget::saveButtonPressed);
	connect(ui->actionForward, &QAction::triggered, gameBoard, &GameBoardWidget::nextFrame);
	connect(ui->actionBackward, &QAction::triggered, gameBoard, &GameBoardWidget::previousFrame);

	connect(ui->actionPlay, &QAction::triggered, [this](){
		gameBoard->nextFrame();
		m_timer->start(250);
		ui->saveButton->setEnabled(false);
		ui->loadButton->setEnabled(false);
		ui->actionForward->setEnabled(false);
		ui->actionBackward->setEnabled(false);
		ui->actionPlay->setEnabled(false); 
		ui->actionStop->setEnabled(true);});
	
	connect(ui->actionStop, &QAction::triggered, [this](){
		m_timer->stop();
		ui->saveButton->setEnabled(true);
		ui->loadButton->setEnabled(true);
		ui->actionForward->setEnabled(true);
		ui->actionBackward->setEnabled(true);
		ui->actionPlay->setEnabled(true);
		ui->actionStop->setEnabled(false);});
	
	connect(m_timer, &QTimer::timeout, [this]() {
		gameBoard->nextFrame();});

	connect(gameBoard, &GameBoardWidget::cacheEmpty, [this]() {
		ui->actionBackward->setEnabled(false); });

	connect(ui->actionForward, &QAction::triggered, [this]() {
		ui->actionBackward->setEnabled(true);
	});

	connect(gameBoard, &GameBoardWidget::fileLoaded, [this]() {
		ui->actionPlay->setEnabled(true);
		ui->actionStop->setEnabled(false);
		ui->actionForward->setEnabled(true);
		ui->actionBackward->setEnabled(false);
		ui->saveButton->setEnabled(true);
	});



}

MainWindow::~MainWindow()
{
    delete ui;
}


