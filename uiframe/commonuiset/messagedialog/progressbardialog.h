#ifndef BARDIALOG_H
#define BARDIALOG_H

#include <QDialog>
#include <QToolButton>

namespace Ui
{
	class BarDialog;
}

namespace vimo::display
{
	class BarDialog : public QDialog
	{
		Q_OBJECT

	public:
		BarDialog(QWidget *parent = nullptr);
		~BarDialog();

		void setValue(int value);
		
	private:
		Ui::BarDialog *ui;
	};

}  // namespace vtk::display
#endif  // BarDIALOG_H
