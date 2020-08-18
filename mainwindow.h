#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_button_browse_clicked();
	void updateFileName(const QString &fileName);

	void on_actionRun_triggered();

	void on_actionStop_triggered();

	void on_actionAbout_triggered();

	void on_actionChange_color_triggered();

private:
	Ui::MainWindow *ui;
	void blockGui(bool block);
};
#endif // MAINWINDOW_H
