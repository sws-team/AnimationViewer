#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->sbx_row, qOverload<int>(&QSpinBox::valueChanged), ui->widget, &AnimationWidget::setRow);
    connect(ui->sbx_framesCount, qOverload<int>(&QSpinBox::valueChanged), ui->widget, &AnimationWidget::setColumns);
    connect(ui->sbx_animationSpeed, qOverload<int>(&QSpinBox::valueChanged), ui->widget, &AnimationWidget::setTime);
    connect(ui->sbx_width, qOverload<int>(&QSpinBox::valueChanged), ui->widget, &AnimationWidget::setWidth);
    connect(ui->sbx_height, qOverload<int>(&QSpinBox::valueChanged), ui->widget, &AnimationWidget::setHeight);
    connect(ui->widget, &AnimationWidget::fileChanged, this, &MainWindow::updateFileName);
    connect(ui->actionExit, &QAction::triggered, qApp, &QApplication::closeAllWindows);

    ui->menuView->addAction(ui->toolBar->toggleViewAction());
    ui->menuView->addAction(ui->dockWidget->toggleViewAction());

    ui->sbx_width->setMaximum(1024);
    ui->sbx_height->setMaximum(1024);
    ui->sbx_animationSpeed->setMaximum(9999);
    ui->sbx_animationSpeed->setValue(200);
	ui->sbx_framesCount->setValue(1);

    blockGui(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_browse_clicked()
{
    const QString fileName = QFileDialog::getOpenFileName(this,
                                                          tr("Choose file"),
                                                          ui->edit_file->text());
    if (fileName.isEmpty())
        return;

    ui->widget->loadFile(fileName);
}

void MainWindow::updateFileName(const QString& fileName)
{
    if (fileName == ui->edit_file->text())
        return;
    ui->edit_file->setText(fileName);
}

void MainWindow::on_actionRun_triggered()
{
    ui->widget->setRow(ui->sbx_row->value());
    ui->widget->setColumns(ui->sbx_framesCount->value());
    ui->widget->setWidth(ui->sbx_width->value());
    ui->widget->setHeight(ui->sbx_height->value());

    blockGui(true);
    ui->widget->start();
}

void MainWindow::on_actionStop_triggered()
{
    ui->widget->stop();
    blockGui(false);
}

void MainWindow::blockGui(bool block)
{
    ui->actionRun->setEnabled(!block);
    ui->actionStop->setEnabled(block);
    ui->gbx_values->setEnabled(!block);
    ui->gbx_settings->setEnabled(!block);
    ui->gbx_file->setEnabled(!block);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, tr("About"), this->windowTitle() + tr("\nCreated by SWS TEAM\n2020"));
}

void MainWindow::on_actionChange_color_triggered()
{
	const QColor color = QColorDialog::getColor(ui->widget->color(), this, this->windowTitle());
	if (!color.isValid())
		return;
	ui->widget->setColor(color);
}
