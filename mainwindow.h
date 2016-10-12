#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebFrame>
#include <QStringListModel>
#include "logfilepositionsource.h"

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
    void onPositionUpdated(const QGeoPositionInfo &info);
    void on_pushButton_Search_clicked();
    void on_pushButton_Query_clicked();
    void on_TimeClicked(const QModelIndex & index);

private:
    Ui::MainWindow *ui;
    LogFilePositionSource *m_LogFilePositionSource;
    QStringListModel *m_TimeListModel;
};

#endif // MAINWINDOW_H
