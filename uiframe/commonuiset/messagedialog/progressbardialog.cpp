#include "progressbardialog.h"
#include "messagedialogtitlebar.h"
#include "ui_progressbardialog.h"

#include <QApplication>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QTranslator>
#include <QVBoxLayout>

namespace vimo::display
{
	BarDialog::BarDialog(QWidget *parent) : QDialog(parent), ui(new Ui::BarDialog)
	{
		ui->setupUi(this);	
		ui->progressBar->setMinimum(0);
		ui->progressBar->setMaximum(100);
	}

	BarDialog::~BarDialog() {}

	void BarDialog::setValue(int value)
	{
		ui->progressBar->setValue(value);	
		//double dProgress = (ui->progressBar->value() - ui->progressBar->minimum()) * 100.0
		//	/ (ui->progressBar->maximum() - ui->progressBar->minimum()); // 百分比
		//ui->progressBar->setFormat(tr("Current progress : %1%").arg(QString::number(dProgress, 'f', 1)));
	}
}  // namespace vtk::display
