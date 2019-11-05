#include "motoupdater.h"

MotoUpdater::MotoUpdater(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QGridLayout;

    textLog = new QTextEdit;

    btnUpdater = new QPushButton(tr("Search"));
    btnAbout = new QPushButton(tr("About"));

    mainLayout->addWidget(textLog);
    mainLayout->addWidget(btnUpdater);
    mainLayout->addWidget(btnAbout);

    setLayout(mainLayout);
}

MotoUpdater::~MotoUpdater()
{

}

void MotoUpdater::Search()
{

}

void MotoUpdater::Download()
{

}

void MotoUpdater::Install()
{

}

void MotoUpdater::Recovery()
{

}
