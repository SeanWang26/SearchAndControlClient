#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



        /* New socket */
    udpSocket = new QUdpSocket(this);

    /* Binding to a port */
    if (!udpSocket->bind()){//60001, QUdpSocket::ShareAddress
        qErrnoWarning("Binding error!");
        exit(1);
    }

    // #ifdef MCAST_IMPLEMENT
    /* Set socket option disable multicast loopback */
        //socket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);

    /* Join to a multicast group */
    //if (!socket->joinMulticastGroup(mcast_addr)){
   //     qErrnoWarning("Join to multicast group error!");
   //     exit(2);
   // }

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->listWidget->clear();
    ItemInfo.clear();

    char S[4] = {0};
    S[0] =0x5a;
    QHostAddress mcast_addr("224.0.0.88");

    udpSocket->writeDatagram(S, 4, mcast_addr, 60001);
}
void MainWindow::processPendingDatagrams()
{
//! [2]
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());

        QString s;
        s.prepend(datagram);

        QStringList strlist = s.split(":");


        for(QList<QString>::Iterator it = strlist.begin(); it != strlist.end(); ++it)
        {
            QStringList items = it->split("=");
            if(items.size()>0)
            {
                if(items[0]=="notifyaddr")
                {
                    //ItemInfo.insert(, "");
                }
                else if(items[0]=="ip")
                {
                    ItemInfo.insert(items[0], items[1]);

                }
                else if(items[0]=="port")
                {
                    ItemInfo.insert(items[0], items[1]);
                }
            }
        }

        ui->listWidget->addItem(new QListWidgetItem(QString("%1:%2").arg(ItemInfo["ip"]).arg(ItemInfo["port"])));
    }
//! [2]
}

void MainWindow::on_CfgButton_clicked()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if(item)
    {
        ConfigDialog dialog;
        dialog.exec();
    }
}
