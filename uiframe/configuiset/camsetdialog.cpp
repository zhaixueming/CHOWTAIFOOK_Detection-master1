/****************************************************************************
 *  @file     formuladialog.cpp
 *  @brief    配方设置界面
 *  @author
 *  @email
 *  @version
 *  @date     2020.12.21
 *  Copyright (c) 2020 SmartMore All rights reserved.
 ****************************************************************************/
#include "camsetdialog.h"
#include "configtitlebar.h"
#include "ui_camsetdialog.h"
#include "uiframe/commonuiset/messagedialog/messagedialog.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>

namespace vimo::display
{
	CamsetDialog::CamsetDialog(QWidget *parent) : QDialog(parent), ui(new Ui::CamsetDialog)
	{
		ui->setupUi(this);
		setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
		setWindowModality(Qt::ApplicationModal);

		initWidgets();
		initComboBox();
	}

	CamsetDialog::~CamsetDialog()
	{
		delete ui;
	}

	void CamsetDialog::initWidgets()
	{
		m_titleBar = new ConfigTitleBar(this);
		m_titleBar->m_pTitleContent->setText(tr("配方设置"));
		ui->titlebar_layout->addWidget(m_titleBar);
		connect(m_titleBar, SIGNAL(signalClose()), this, SLOT(slotCheckAndClose()));

		info_list.push_back(ImageView::ViewInfo{ QUuid(), QString("相机一") });
		info_list.push_back(ImageView::ViewInfo{ QUuid(), QString("相机二") });
		info_list.push_back(ImageView::ViewInfo{ QUuid(), QString("相机三") });
		info_list.push_back(ImageView::ViewInfo{ QUuid(), QString("相机四") });
		info_list.push_back(ImageView::ViewInfo{ QUuid(), QString("相机三") });
		info_list.push_back(ImageView::ViewInfo{ QUuid(), QString("相机四") });
		m_view_frame = new SixViewsWidget(info_list);
		ui->gridLayoutCam->addWidget(m_view_frame);
	}

	void CamsetDialog::slotCheckAndClose()
	{
		QMessageBox msgBox;
		msgBox.setText("提示");
		msgBox.setInformativeText("是否关闭?");
		msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Ok);
		int ret = msgBox.exec();
		if (ret == QMessageBox::Ok)
			accept();
	}

	//获取全部信息加载在comboBoxRecord中
	void CamsetDialog::initComboBox()
	{
		QString FolderPath = QCoreApplication::applicationDirPath() + "/formula";
		QStringList JsonNames;
		if (FolderPath.isEmpty())
			return;
		// 获取所有文件名
		QDir dir(FolderPath);
		FolderPath = dir.fromNativeSeparators(FolderPath);//  "\\"转为"/" 
		if (!dir.exists())
			JsonNames = QStringList("");
		dir.setFilter(QDir::Files);
		dir.setSorting(QDir::Name);
		dir.setNameFilters(QString("*.json").split(";"));
		JsonNames = dir.entryList();
		for (int i = 0; i < JsonNames.size(); ++i)
		{
			QFileInfo fileinfo = QFileInfo(FolderPath + "/" + JsonNames.at(i));
			ui->comboBoxSelect->addItem(fileinfo.baseName());
		}
	}

	//添加按钮
	void CamsetDialog::on_ButtonAdd_clicked()
	{
		if (ui->lineEditAdd->text().isEmpty())
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("名称不能为空!"));
			message_box_dialog.exec();
		}
		else
		{
			//新建名
			QString StringAdd = ui->lineEditAdd->text();
			//*新名对照已有，确认是否重复
			bool bRepeat = true;
			for (int i = 0; i < ui->comboBoxSelect->count(); i++)
			{
				if (StringAdd == ui->comboBoxSelect->itemText(i))
				{
					bRepeat = false;
					break;
				}
			}
			//判断是否重复//如果没有重复
			if (bRepeat)
			{
				ui->comboBoxSelect->addItem(StringAdd);
				//拷贝一份
				QString templatefile = QCoreApplication::applicationDirPath() + "/template.json";
				QString copyfile = QCoreApplication::applicationDirPath() + "/formula/" + StringAdd + ".json";
				bool ok = QFile::copy(templatefile, copyfile);
				if (ok)
				{
					MessageDialog message_box_dialog(DialogType::infoDialog, tr("新建成功!"));
					message_box_dialog.exec();
				}			
				else
				{
					MessageDialog message_box_dialog(DialogType::errorDialog, tr("新建失败！"));
					message_box_dialog.exec();
				}
			}
			else
			{
				MessageDialog message_box_dialog(DialogType::errorDialog, tr("名称重复!"));
				message_box_dialog.exec();
			}
		}
	}

	//加载
	void CamsetDialog::on_ButtonLoad_clicked()
	{
		//*根据选择加载相应信息
		QString CurrentString = ui->comboBoxSelect->currentText();
		ui->label_name->setText(CurrentString);
		//获取信息
		getparam(CurrentString);
	}

	//删除
	void CamsetDialog::on_ButtonDelete_clicked()
	{
		QMessageBox msgBox;
		msgBox.setText("提示");
		msgBox.setInformativeText("是否删除?");
		msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Ok);
		int ret = msgBox.exec();
		if (ret == QMessageBox::Ok)
		{
			QString name = ui->comboBoxSelect->currentText();
			QString filename = QCoreApplication::applicationDirPath() + "/formula/" + name + ".json";
			QFile fileTemp(filename);
			int current = ui->comboBoxSelect->currentIndex();
			ui->comboBoxSelect->removeItem(current);
			fileTemp.remove();
			MessageDialog message_box_dialog(DialogType::infoDialog, tr("删除成功!"));
			message_box_dialog.exec();
		}
	}

	//获取相机参数
	void CamsetDialog::on_Buttongetcam_clicked()
	{
		QString E1 = ui->lineEditE1Now->text();
		QString E2 = ui->lineEditE2Now->text();
		QString E3 = ui->lineEditE3Now->text();
		QString E4 = ui->lineEditE4Now->text();

		QString G1 = ui->lineEditG1Now->text();
		QString G2 = ui->lineEditG2Now->text();
		QString G3 = ui->lineEditG3Now->text();
		QString G4 = ui->lineEditG4Now->text();

		ui->lineEditE1->setText(E1);
		ui->lineEditE2->setText(E2);
		ui->lineEditE3->setText(E3);
		ui->lineEditE4->setText(E4);

		ui->lineEditG1->setText(G1);
		ui->lineEditG2->setText(G2);
		ui->lineEditG3->setText(G3);
		ui->lineEditG4->setText(G4);
	}

	//保存按钮
	void CamsetDialog::on_ButtonSave_clicked()
	{
		//*根据选择加载相应信息
		QString CurrentString = ui->label_name->text();
		setparam(CurrentString);
	}

	//取消按钮
	void CamsetDialog::on_ButtonCancel_clicked()
	{
		accept();
	}

	//获取参数
	void CamsetDialog::getparam(QString index)
	{
		QString path = QCoreApplication::applicationDirPath() + "/formula/" + index + ".json";				
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly))
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("文件读取错误!"));
			message_box_dialog.exec();
			return;
		}			
		
		QJsonParseError *error = new QJsonParseError;
		QJsonDocument jdc = QJsonDocument::fromJson(file.readAll(), error);
		//判断文件是否完整
		if (error->error != QJsonParseError::NoError)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, error->errorString());
			message_box_dialog.exec();
			return;
		}

		QJsonObject obj = jdc.object();        //获取对象	
		QStringList list = obj.keys();

		ui->spinBox->setValue(obj["count"].toInt());

		ui->lineEditE1->setText(QString::number(obj["camE1"].toInt()));
		ui->lineEditE2->setText(QString::number(obj["camE2"].toInt()));
		ui->lineEditE3->setText(QString::number(obj["camE3"].toInt()));
		ui->lineEditE4->setText(QString::number(obj["camE4"].toInt()));

		ui->lineEditG1->setText(QString::number(obj["camG1"].toInt()));
		ui->lineEditG2->setText(QString::number(obj["camG2"].toInt()));
		ui->lineEditG3->setText(QString::number(obj["camG3"].toInt()));
		ui->lineEditG4->setText(QString::number(obj["camG4"].toInt()));

		ui->lineEditT1->setText(QString::number(obj["topstart"].toInt()));
		ui->lineEditT2->setText(QString::number(obj["topend"].toInt()));
		ui->lineEditR1->setText(QString::number(obj["rightstart"].toInt()));
		ui->lineEditR2->setText(QString::number(obj["rightend"].toInt()));
		ui->lineEditB1->setText(QString::number(obj["bottomstart"].toInt()));
		ui->lineEditB2->setText(QString::number(obj["bottomend"].toInt()));
		ui->lineEditL1->setText(QString::number(obj["leftstart"].toInt()));
		ui->lineEditL2->setText(QString::number(obj["leftend"].toInt()));
	}

	//设置参数
	void CamsetDialog::setparam(QString index)
	{
		QString path = QCoreApplication::applicationDirPath() + "/formula/" + index + ".json";
		bool bsave = false;	
		//打开文件
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly))
			qDebug() << "File open failed!";
		else
			qDebug() << "File open successfully!";

		QJsonDocument jdoc;
		QJsonObject obj;
		obj["count"] = ui->spinBox->value();
		obj["camE1"] = ui->lineEditE1->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["camE2"] = ui->lineEditE2->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["camE3"] = ui->lineEditE3->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["camE4"] = ui->lineEditE4->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["camG1"] = ui->lineEditG1->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["camG2"] = ui->lineEditG2->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["camG3"] = ui->lineEditG3->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["camG4"] = ui->lineEditG4->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["topstart"] = ui->lineEditT1->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["topend"] = ui->lineEditT2->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["rightstart"] = ui->lineEditR1->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["rightend"] = ui->lineEditR2->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["bottomstart"] = ui->lineEditB1->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["bottomend"] = ui->lineEditB2->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["leftstart"] = ui->lineEditL1->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}
		obj["leftend"] = ui->lineEditL2->text().toInt(&bsave);
		if (!bsave)
		{
			MessageDialog message_box_dialog(DialogType::errorDialog, tr("输入数据错误!"));
			message_box_dialog.exec();
			return;
		}

		jdoc.setObject(obj);
		file.write(jdoc.toJson(QJsonDocument::Indented)); //Indented:表示自动添加/n回车符
		file.close();
		MessageDialog message_box_dialog(DialogType::infoDialog, tr("保存成功!"));
		message_box_dialog.exec();
	}

	//获取相机参数
	void CamsetDialog::getcamparamslots(float e1, float g1, float e2, float g2, float e3, float g3, float e4, float g4)
	{
		ui->lineEditE1Now->setText(QString::number(e1));
		ui->lineEditE2Now->setText(QString::number(e2));
		ui->lineEditE3Now->setText(QString::number(e3));
		ui->lineEditE4Now->setText(QString::number(e4));

		ui->lineEditG1Now->setText(QString::number(g1));
		ui->lineEditG2Now->setText(QString::number(g2));
		ui->lineEditG3Now->setText(QString::number(g3));
		ui->lineEditG4Now->setText(QString::number(g4));
	}


	//单张取图
	void CamsetDialog::on_Buttononeimage_clicked()
	{

	}
	//实时取图
	void CamsetDialog::on_Buttonlive_clicked()
	{

	}
	//测试参数
	void CamsetDialog::on_Buttontest1_clicked()
	{
		bool btext;
		float exp = ui->lineEditE1Now->text().toFloat(&btext);
		float gain = ui->lineEditG1Now->text().toFloat(&btext);
		if (btext)
		{
			emit sendcam1esignal(exp);
			emit sendcam1gsignal(gain);
		}
	}
	void CamsetDialog::on_Buttontest2_clicked()
	{
		bool btext;
		float exp = ui->lineEditE2Now->text().toFloat(&btext);
		float gain = ui->lineEditG2Now->text().toFloat(&btext);
		if (btext)
		{
			emit sendcam2esignal(exp);
			emit sendcam2gsignal(gain);
		}
	}
	void CamsetDialog::on_Buttontest3_clicked()
	{
		bool btext;
		float exp = ui->lineEditE3Now->text().toFloat(&btext);
		float gain = ui->lineEditG3Now->text().toFloat(&btext);
		if (btext)
		{
			emit sendcam3esignal(exp);
			emit sendcam3gsignal(gain);
		}
	}
	void CamsetDialog::on_Buttontest4_clicked()
	{
		bool btext;
		float exp = ui->lineEditE4Now->text().toFloat(&btext);
		float gain = ui->lineEditG4Now->text().toFloat(&btext);
		if (btext)
		{
			emit sendcam4esignal(exp);
			emit sendcam4gsignal(gain);
		}
	}
	//存图
	void CamsetDialog::on_Buttonsaveimage1_clicked()
	{
		QString Folder = "F:/Image/";
		QDir ImageFolder(Folder);
		if (!ImageFolder.exists())
		{
			ImageFolder.mkdir(Folder);
		}

		QString file = "L_.bmp";
		QString StringFile = QFileDialog::getSaveFileName(this, tr("Save Image"), Folder + file, tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF"));
		if (StringFile == NULL)
			return;

		cv::Mat ResizeImage;
		cv::imwrite(StringFile.toStdString(), ResizeImage);
		MessageDialog message_box_dialog(DialogType::infoDialog, tr("存图成功!"));
		message_box_dialog.exec();
	}
	void CamsetDialog::on_Buttonsaveimage2_clicked()
	{

	}
	void CamsetDialog::on_Buttonsaveimage3_clicked()
	{

	}
	void CamsetDialog::on_Buttonsaveimage4_clicked()
	{

	}
}  // namespace vtk::display
