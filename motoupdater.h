#ifndef MOTOUPDATER_H
#define MOTOUPDATER_H

#include <QWidget>

#include <QPushButton>
#include <QTextEdit>

#include <QGridLayout>

#include <QProcess>

class MotoUpdater : public QWidget
{
    Q_OBJECT

public:
    MotoUpdater(QWidget *parent = nullptr);
    ~MotoUpdater();

private:
    QPushButton *btnSearch;
    QPushButton *btnAbout;

    QTextEdit *textLog;

    QGridLayout *mainLayout;
};
#endif // MOTOUPDATER_H
