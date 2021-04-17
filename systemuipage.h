#ifndef SYSTEMUIPAGE_H
#define SYSTEMUIPAGE_H

#include <QWidget>
#include <DSwitchButton>
DWIDGET_USE_NAMESPACE
namespace Ui {
class SystemUiPage;
}

class SystemUiPage : public QWidget
{
    Q_OBJECT

public:
    explicit SystemUiPage(QWidget *parent = nullptr);
    void setTheme(bool isDark,QColor color);
    ~SystemUiPage();

private:
    Ui::SystemUiPage *ui;
};

#endif // SYSTEMUIPAGE_H
