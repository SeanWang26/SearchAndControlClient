#include "mainwindow.h"
#include "ui_mainwindow.h"


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

    char S[4] = {0};
    S[0] =0x5a;
    QHostAddress mcast_addr("224.0.0.88");

    udpSocket->writeDatagram(S, 4, mcast_addr, 60001);

   // socket->readDatagram(S, 256, mcast_addr, 60001);
    // #endif
}
void MainWindow::processPendingDatagrams()
{
//! [2]
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());


    }
//! [2]
}
