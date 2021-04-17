#include "youjianpage.h"
#include "ui_youjianpage.h"

YouJianPage::YouJianPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YouJianPage)
{
    ui->setupUi(this);
    //新建文档最后一个自定义的文本框
    connect(youjianplus,&QLineEdit::returnPressed,[=](){
        //把用户自定义的项目添加到youjianlist列表
        youjianlist.append(youjianplus->text());
        //添加用户自定义项目到.Templates
        QFile tmp(homedir+"/.Templates/"+youjianplus->text());
        tmp.open(QIODevice::ReadWrite|QIODevice::Text);
        tmp.close();
        //清空文本框
        youjianplus->setText("");
        //刷新列表
        updateYoujianUI();});

    QDir tmpdir;
    tmpdir.mkpath(homedir+"/.Templates");
    //获取.Templates目录下所有文件
    QString dirpath = homedir+"/.Templates";
    QDir dir(dirpath);
    QStringList nameFilters;
    nameFilters << "*.*";
    files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);


    //新建文档列表
    youjianlist<<(files);
    youjianlist<<("DOC 文档.doc");
    youjianlist<<("DOCX 文档.docx");
    youjianlist<<("PPT 演示文稿.ppt");
    youjianlist<<("PPTX 演示文稿.pptx");
    youjianlist<<("XLS 工作表.xls");
    youjianlist<<("XLSX 工作表.xlsx");
    youjianlist<<("PDF 文档.pdf");
    youjianlist<<("TXT 文档.txt");
    youjianlist<<("AI 图像.ai");
    youjianlist<<("SVG 图像.svg");
    youjianlist<<("PSD 图像.psd");
    //更多工具列表
    gsjulist<<"右键刷新";
    gsjulist<<"Hash检验";
    gsjulist<<"显示隐藏文件";
    gsjulist<<"彻底删除";
    gsjulist<<"复制路径";
    gsjuflist<<"Refresh.desktop";
    gsjuflist<<"Hash.desktop";
    gsjuflist<<"Show.desktop";
    gsjuflist<<"del.desktop";
    gsjuflist<<"copyfilepath.desktop";

    //获得oem-menuextensions目录下所有文件
    dirpath = "/usr/share/deepin/dde-file-manager/oem-menuextensions";
    QDir dir_2(dirpath);
    nameFilters.clear();
    nameFilters << "*.desktop";
    files_2 = dir_2.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    for (int i=0;i<30;i++) {
        youjian[i]=new QCheckBox;
    }
    updateYoujianUI();
    updateGsjuUI();

}
void YouJianPage::updateGsjuUI()
{
    int x=0,y=0;
    ui->gridLayout_7->setColumnStretch(0,1);
    ui->gridLayout_7->setColumnStretch(1,1);
    for (int i=0;i<gsjulist.count();i++,x++) {
        if(x==2)
        {
            x=0;
            y++;
        }
        gsju[i]=new QPushButton;
        ui->gridLayout_7->addWidget(gsju[i],y,x);
        gsju[i]->setText(gsjulist[i]);
        gsju[i]->setStatusTip(gsjuflist[i]);
        //gsju[i]->statusTip()
        gsju[i]->setCheckable(true);
        gsjuCheckState[i]=false;
        if(files_2.indexOf(gsjuflist[i])!=-1)
        {
            gsjuCheckState[i]=true;
            gsju[i]->setChecked(gsjuCheckState[i]);
        }
        connect(gsju[i],&QPushButton::clicked,[=](){if(gsjuCheckState[i]==true){
                QProcess *cmd=new QProcess;
                cmd->start("pkexec rm -rf /usr/share/deepin/dde-file-manager/oem-menuextensions/"+gsju[i]->statusTip());
                gsjuCheckState[i]=false;
                cmd->waitForStarted();
            }else {
                QDir tmpdir;
                tmpdir.mkpath("/tmp/youjian");
                QFile::copy(":/kjfs/"+gsju[i]->statusTip(),"/tmp/youjian/"+gsju[i]->statusTip());
                QProcess *cmd=new QProcess;
                cmd->start("pkexec mv -f /tmp/youjian/"+gsju[i]->statusTip()+" /usr/share/deepin/dde-file-manager/oem-menuextensions/"+gsju[i]->statusTip());
                gsjuCheckState[i]=true;
                cmd->waitForStarted();
            }});
    }
}
void YouJianPage::updateYoujianUI()
{
    QString dirpath = homedir+"/.Templates";
    QDir dir(dirpath);
    QStringList nameFilters;
    nameFilters << "*.*";
    files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    youjianlist = youjianlist.toSet().toList();
    int x=0,y=0;
    ui->gridLayout_3->setColumnStretch(0,1);
    ui->gridLayout_3->setColumnStretch(1,1);
    for (int i=0;i<=youjianlist.count();i++,x++) {
        if(x==2)
        {
            x=0;
            y++;
        }
        if(i==youjianlist.count())
        {
            youjianplus->setPlaceholderText("自定义 文件名.后缀");
            ui->gridLayout_3->addWidget(youjianplus,y,x);
            break;
        }
        ui->gridLayout_3->addWidget(youjian[i],y,x);
        youjian[i]->setText(youjianlist[i]);
        bool yesno=false;
        if(files.indexOf(youjianlist[i])!=-1)
        {

            youjian[i]->setCheckState(Qt::Checked);
            bool yesno=false;
        }
        connect(youjian[i],&QCheckBox::stateChanged,[=](){if(youjian[i]->checkState()==Qt::Unchecked){
                QFile tmp(homedir+"/.Templates/"+youjian[i]->text());
                tmp.remove();
            }else {
                    QFile tmp(homedir+"/.Templates/"+youjian[i]->text());
                    tmp.open(QIODevice::ReadWrite|QIODevice::Text);
                    tmp.close();
            }});
    }
}
void YouJianPage::setTheme(bool isDark,QColor color)
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
YouJianPage::~YouJianPage()
{
    delete ui;
}
