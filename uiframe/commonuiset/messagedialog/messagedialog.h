#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>
#include <QToolButton>

namespace Ui
{
class MessageDialog;
}

namespace vimo::display
{

enum class ButtonType
{
    confirm,
    cancel,
    yes,
    no,
    openFile
};

enum class DialogType
{
    infoDialog,
    warningDialog,
    errorDialog
};

class ConfirmButton : public QToolButton
{
    Q_OBJECT
public:
    ConfirmButton();
};

class CancelButton : public QToolButton
{
    Q_OBJECT
public:
    CancelButton();
};

class YesButton : public QToolButton
{
    Q_OBJECT
public:
    YesButton();
};

class NoButton : public QToolButton
{
    Q_OBJECT
public:
    NoButton();
};

class DeleteButton : public QToolButton
{
    Q_OBJECT
public:
    DeleteButton();
};

class OpenFileButton : public QToolButton
{
    Q_OBJECT
public:
    OpenFileButton();
};

class MessageDialog : public QDialog
{
    Q_OBJECT

public:
    MessageDialog(DialogType dialog_type, QString msg = "", QList<ButtonType> buttons = {ButtonType::confirm},
                  QWidget *parent = nullptr);
    ~MessageDialog();

private slots:
    void slotCancelDialog();
    void slotConfirmDialog();

private:
    Ui::MessageDialog *ui;
};

}  // namespace vtk::display
#endif  // MESSAGEDIALOG_H
