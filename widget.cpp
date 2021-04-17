#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSettings>
#include <QIcon>
#include <QGraphicsOpacityEffect>
#include <DSettings>
#include <DSettingsOption>
#include <DSettingsDialog>
#include <DBlurEffectWidget>
#include <DApplication>
#include <DGuiApplicationHelper>
#include <QDir>
#include <QDesktopServices>
DWIDGET_USE_NAMESPACE

Widget::Widget(DBlurEffectWidget *parent) :
    DBlurEffectWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initUI();

    //侧边栏按钮
    connect(ui->jmwg,&QPushButton::clicked,[=](){Widget::chooseLeftMenu(0);});
    connect(ui->yjcd,&QPushButton::clicked,[=](){Widget::chooseLeftMenu(1);});
    connect(ui->cyml,&QPushButton::clicked,[=](){Widget::chooseLeftMenu(2);});

    connect(ui->wtfButton,&QPushButton::clicked,[=](){QDesktopServices::openUrl(QUrl(QLatin1String("https://jq.qq.com/?_wv=1027&k=OZW5BYtg")));});

    //主题切换
    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, this, [=](DGuiApplicationHelper::ColorType themeType) {
        QColor main_color;
        main_color=DGuiApplicationHelper::instance()->applicationPalette().highlight().color();
        if(themeType==DGuiApplicationHelper::DarkType){
            setTheme(true,main_color);
            ui->youjianpage->setTheme(true,main_color);
            ui->systemuipage->setTheme(true,main_color);

        }else {
            setTheme(false,main_color);
            ui->youjianpage->setTheme(false,main_color);
            ui->systemuipage->setTheme(false,main_color);
        }
    });

    QMenu *tmenu=new QMenu;
    QAction *rewg=new QAction;
    rewg->setText("重启文件管理器");
    tmenu->addAction(rewg);
    ui->titlebar->setMenu(tmenu);

    connect(rewg,&QAction::triggered,[=](){QProcess *cmd=new QProcess;cmd->start("killall dde-file-manager");});

}

Widget::~Widget()
{
    delete ui;
    DApplication::quit();
}
void Widget::initUI()
{
    // ui初始化
    setMaskAlpha(180);
    ui->stackedWidget->setCurrentIndex(0);
    ui->icon->setPixmap(QIcon::fromTheme("youjian").pixmap(70,70));
    ui->titlebar->setFixedHeight(50);

    titlebar=ui->titlebar;

    // 添加菜单项
    QAction *setting=new QAction("设置");
    QMenu *menu=new QMenu;
    menu->addAction(setting);
    titlebar->setMenu(menu);

    // 初始化菜单数组
    left_list[0]=ui->jmwg;
    left_list[1]=ui->yjcd;
    left_list[2]=ui->cyml;
}


void Widget::setTheme(bool isDark,QColor color)
{
    // 菜单图标
    if(isDark){
        // 黑色模式
        themeIsDark=true;
        ui->label_3->setStyleSheet("color:"+color.name());
        QPalette palette = ui->label_3->palette();
        palette.setColor(QPalette::Window,QColor("#282828"));
        palette.setColor(QPalette::Base,QColor("#282828"));
        ui->titlebar->setPalette(palette);
        QPalette palette1 = ui->line->palette();
        palette1.setColor(QPalette::Light,QColor("#282929"));
        ui->line->setPalette(palette1);

    }else {
        // 亮色模式
        themeIsDark=false;
        ui->label_3->setStyleSheet("color:"+color.name());
        QPalette palette = ui->label_3->palette();
        palette.setColor(QPalette::Window,QColor("#FFFFFF"));
        palette.setColor(QPalette::Base,QColor("#FFFFFF"));
        ui->titlebar->setPalette(palette);
        QPalette palette1 = ui->line->palette();
        palette1.setColor(QPalette::Light,QColor("#EBEBEB"));
        ui->line->setPalette(palette1);
    }
    main_color=color;
    updateUI();
    if(ui->stackedWidget->currentIndex()==0){
        chooseLeftMenu(nowMenu);
    }

}

DTitlebar* Widget::getTitlebar()
{
    return ui->titlebar;
}

void Widget::updateUI()
{
    if(themeIsDark){
        left_list[1]->setIcon(QIcon(":/icons/icons/xjwd_dark.svg"));
        left_list[0]->setIcon(QIcon(":/icons/icons/gdgj_dark.svg"));
        left_list[2]->setIcon(QIcon(":/icons/icons/cyml_dark.svg"));
    }else {
        left_list[1]->setIcon(QIcon(":/icons/icons/xjwd.svg"));
        left_list[0]->setIcon(QIcon(":/icons/icons/gdgj.svg"));
        left_list[2]->setIcon(QIcon(":/icons/icons/cyml.svg"));
    }
    for (int i=0;i<3;i++) {
        left_list[i]->setFont(QFont("",11));
        left_list[i]->setFixedHeight(38);
        if(themeIsDark){
            left_list[i]->setStyleSheet("color:#FFFFFF;border:0px");
        }else {
            left_list[i]->setStyleSheet("color:#252525;border:0px");
        }
    }
    switch (nowMenu) {
    case 1:
        left_list[1]->setIcon(QIcon(":/icons/icons/xjwd_dark.svg"));
        break;
    case 0:
        left_list[0]->setIcon(QIcon(":/icons/icons/gdgj_dark.svg"));
        break;
    case 2:
        left_list[2]->setIcon(QIcon(":/icons/icons/cyml_dark.svg"));
        break;
    }
}

// 菜单切换逻辑
void Widget::chooseLeftMenu(int index)
{
    nowMenu=index;
    updateUI();
    left_list[index]->setStyleSheet("color:#FFFFFF;background-color:"+main_color.name()+";border-radius:8;border:0px");

    ui->stackedWidget->setCurrentIndex(nowMenu);
}

