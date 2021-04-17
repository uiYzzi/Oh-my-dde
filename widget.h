#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QUrl>
#include <QLineEdit>
#include <DSettings>
#include <DBlurEffectWidget>
#include <QLabel>
#include <DTitlebar>
#include <DSearchEdit>
#include <DStackedWidget>
#include <QPushButton>
#include <QStandardPaths>
#include <QProcess>

#define LIST_MAX 99 //一次最多下载数量
#define TMP_PATH "/tmp/spark-store"

DWIDGET_USE_NAMESPACE
namespace Ui {
class Widget;
}



class Widget : public DBlurEffectWidget
{

    Q_OBJECT
public:
    explicit Widget(DBlurEffectWidget *parent = nullptr);
    ~Widget();
    int nowDownload=0;
    int allDownload=0;
    int isdownload=false;
    void setTheme(bool,QColor);
    DTitlebar* getTitlebar();

private slots:

public:

    QUrl url;

    Ui::Widget *ui;
    QList<QUrl> urList;
    QString appName;
    QString urladdress;
    QString pkgName;
    QString appweb;
    bool themeIsDark;



private:
    void initUI();
    void chooseLeftMenu(int index);
    void updateUI();
    quint64 dirFileSize(const QString &path);

private:
    QPushButton * left_list[14];
    QLabel *m_loaderror=new QLabel;
    QString serverUrl;
    bool configCanSave=false;
    bool isBusy=false;
    int nowMenu=0; //定位当前菜单
    QPixmap screen[5];
    QString type_name;
    QColor main_color;
    int foot;
    DTitlebar *titlebar;

};

#endif // WIDGET_H
