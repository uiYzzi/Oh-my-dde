#include "systemuipage.h"
#include "ui_systemuipage.h"
#include <QProcess>
#include <QDebug>
SystemUiPage::SystemUiPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemUiPage)
{
    ui->setupUi(this);
    QString output;
    QProcess *m_qprocess=new QProcess;

    //启动器图标大小
    m_qprocess->start("gsettings get com.deepin.dde.launcher apps-icon-ratio");
    m_qprocess->waitForFinished();
    output=m_qprocess->readAll();
    output.remove("\n");
    output.remove(" ");
    output.remove("\t");
    output.remove("file://");
    ui->doubleSpinBox->setValue(output.toDouble());
    connect(ui->doubleSpinBox, static_cast<void(QDoubleSpinBox::*)(const QString &)>(&QDoubleSpinBox::valueChanged),[=](const QString &text)
    {
        m_qprocess->start("gsettings set com.deepin.dde.launcher apps-icon-ratio "+text);
    });


    //系统圆角大小
    m_qprocess->start("gsettings get com.deepin.xsettings dtk-window-radius");
    m_qprocess->waitForFinished();
    output=m_qprocess->readAll();
    output.remove("\n");
    output.remove(" ");
    output.remove("\t");
    output.remove("file://");
    ui->spinBox->setValue(output.toDouble());
    connect(ui->spinBox, static_cast<void(QSpinBox::*)(const QString &)>(&QSpinBox::valueChanged),[=](const QString &text)
    {
        m_qprocess->start("gsettings set com.deepin.xsettings dtk-window-radius "+text);
    });


    //dock多屏横跳
    m_qprocess->start("gsettings get com.deepin.dde.dock.mainwindow only-show-primary");
    m_qprocess->waitForFinished();
    output=m_qprocess->readAll();
    output.remove("\n");
    output.remove(" ");
    output.remove("\t");
    output.remove("file://");
    if (output=="false")
    {
        ui->sb2->setChecked(true);
    }else if(output=="true")
    {
        ui->sb2->setChecked(false);
    }
    connect(ui->sb2, &DSwitchButton::checkedChanged, this, [=](bool tmp)
    {
        if(tmp==false)
        {
            m_qprocess->start("gsettings set com.deepin.dde.dock.mainwindow only-show-primary true");
        }else{
            m_qprocess->start("gsettings set com.deepin.dde.dock.mainwindow only-show-primary false");
        }

    });

    //启动器包名搜索
    m_qprocess->start("gsettings get com.deepin.dde.launcher search-package-name");
    m_qprocess->waitForFinished();
    output=m_qprocess->readAll();
    output.remove("\n");
    output.remove(" ");
    output.remove("\t");
    output.remove("file://");
    if (output=="false")
    {
        ui->sb1->setChecked(false);
    }else if(output=="true")
    {
        ui->sb1->setChecked(true);
    }
    connect(ui->sb1, &DSwitchButton::checkedChanged, this, [=](bool tmp)
    {
        if(tmp==false)
        {
            m_qprocess->start("gsettings set com.deepin.dde.launcher search-package-name false");
        }else{
            m_qprocess->start("gsettings set com.deepin.dde.launcher search-package-name true");
        }

    });


    //关闭通知
    m_qprocess->start("gsettings get com.deepin.dde.notifications notifycation-closed");
    m_qprocess->waitForFinished();
    output=m_qprocess->readAll();
    output.remove("\n");
    output.remove(" ");
    output.remove("\t");
    output.remove("file://");
    if (output=="false")
    {
        ui->sb3->setChecked(false);
    }else if(output=="true")
    {
        ui->sb3->setChecked(true);
    }
    connect(ui->sb3, &DSwitchButton::checkedChanged, this, [=](bool tmp)
    {
        if(tmp==false)
        {
            m_qprocess->start("gsettings set com.deepin.dde.notifications notifycation-closed false");
        }else{
            m_qprocess->start("gsettings set com.deepin.dde.notifications notifycation-closed true");
        }

    });

    //通知图标显示
    m_qprocess->start("gsettings get com.deepin.dde.notifications show-icon");
    m_qprocess->waitForFinished();
    output=m_qprocess->readAll();
    output.remove("\n");
    output.remove(" ");
    output.remove("\t");
    output.remove("file://");
    if (output=="false")
    {
        ui->sb4->setChecked(false);
    }else if(output=="true")
    {
        ui->sb4->setChecked(true);
    }
    connect(ui->sb4, &DSwitchButton::checkedChanged, this, [=](bool tmp)
    {
        if(tmp==false)
        {
            m_qprocess->start("gsettings set com.deepin.dde.notifications show-icon false");
        }else{
            m_qprocess->start("gsettings set com.deepin.dde.notifications show-icon true");
        }

    });

    }

SystemUiPage::~SystemUiPage()
{
    delete ui;
}
void SystemUiPage::setTheme(bool isDark,QColor color)
{
    // 菜单图标
    if(isDark){
        // 黑色模式
        QPalette *palette = new QPalette;
        palette->setColor(QPalette::Window,QColor("#282828"));
        palette->setColor(QPalette::Base,QColor("#282828"));
        ui->scrollArea->setPalette(*palette);
    }else {
        // 亮色模式
        QPalette *palette = new QPalette;
        palette->setColor(QPalette::Window,QColor("#FFFFFF"));
        palette->setColor(QPalette::Base,QColor("#FFFFFF"));
        ui->scrollArea->setPalette(*palette);

    }
}
