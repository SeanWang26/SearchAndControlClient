#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void processPendingDatagrams();
    void on_CfgButton_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
    QMap<QString, QString> ItemInfo;
};

#endif // MAINWINDOW_H
