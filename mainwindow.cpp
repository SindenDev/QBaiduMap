#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_LogFilePositionSource(new LogFilePositionSource(this)),
    m_TimeListModel(new QStringListModel(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(m_LogFilePositionSource, &LogFilePositionSource::positionUpdated,
            this, &MainWindow::onPositionUpdated);
    m_LogFilePositionSource->startUpdates();

    m_TimeListModel->setStringList(m_LogFilePositionSource->m_time);

    ui->listView_Time->setFlow(QListView::LeftToRight);
    ui->listView_Time->setModel(m_TimeListModel);

    connect(ui->listView_Time, &QListView::clicked,
            this, &MainWindow::on_TimeClicked);
}

MainWindow::~MainWindow()
{
    ui->webView_Map->close();
    delete ui;
    delete m_TimeListModel;
}

void MainWindow::onPositionUpdated(const QGeoPositionInfo &info)
{//22° 32' 34.3" N, 113° 56' 9.6"//
    qDebug() << (QString("Position updated: Date/time = %1, Coordinate = %2").arg(info.timestamp().toString()).arg(info.coordinate().toString()));
    QString getLocalByLongitudeAndLatitude = QString("getLocalByLongitudeAndLatitude(%1, %2);")
            .arg(info.coordinate().longitude())
            .arg(info.coordinate().latitude());

    qDebug() << getLocalByLongitudeAndLatitude;
    ui->webView_Map->page()->mainFrame()->evaluateJavaScript(getLocalByLongitudeAndLatitude);

}

void MainWindow::on_pushButton_Search_clicked()
{
    QString searchLocalByKeywords = QString("searchLocalByKeywords(\"%1\");").arg(ui->lineEdit_Keywords->text());
    ui->webView_Map->page()->mainFrame()->evaluateJavaScript(searchLocalByKeywords);
}


void MainWindow::on_pushButton_Query_clicked()
{
    QString getLocalByLongitudeAndLatitude = QString("getLocalByLongitudeAndLatitude(%1, %2);")
            .arg(ui->doubleSpinBox_Longitude->value())
            .arg(ui->doubleSpinBox_Latitude->value());

    qDebug() << getLocalByLongitudeAndLatitude;
    ui->webView_Map->page()->mainFrame()->evaluateJavaScript(getLocalByLongitudeAndLatitude);
}

void MainWindow::on_TimeClicked(const QModelIndex &index)
{

    int index_value = index.row();
    QStringList coordinate = QString(m_LogFilePositionSource->m_info[index_value]).split(",");
    double longitude, latitude;
    longitude = QVariant(coordinate[0]).toDouble();
    latitude = QVariant(coordinate[1]).toDouble();

    QString setLocalByLongitudeAndLatitude = QString("getLocalByLongitudeAndLatitude(%1, %2);")
            .arg(longitude)
            .arg(latitude);

    qDebug() << setLocalByLongitudeAndLatitude;
    ui->webView_Map->page()->mainFrame()->evaluateJavaScript(setLocalByLongitudeAndLatitude);
}
