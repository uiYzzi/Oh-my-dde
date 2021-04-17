#ifndef YOUJIANPAGE_H
#define YOUJIANPAGE_H

#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QFile>
#include <QDir>
#include <QString>
#include <QPushButton>
#include <QSet>
#include <QProcess>
#include <QStandardPaths>
namespace Ui {
class YouJianPage;
}

class YouJianPage : public QWidget
{
    Q_OBJECT

public:
    explicit YouJianPage(QWidget *parent = nullptr);
    void setTheme(bool isDark,QColor color);
    ~YouJianPage();

private:
    void updateYoujianUI();
    void updateGsjuUI();

    QString homedir=QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QPushButton *gsju[30];
    QStringList files;
    QStringList gsjulist;
    QStringList gsjuflist;
    QStringList files_2;
    bool gsjuCheckState[30];
    QCheckBox * youjian[30];
    QLineEdit * youjianplus=new QLineEdit;
    QStringList youjianlist;
    Ui::YouJianPage *ui;
};

#endif // YOUJIANPAGE_H
