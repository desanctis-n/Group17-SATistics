#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCompleter>
#include <QButtonGROUP>
#include <QStringListModel>
#include <QListWidgetItem>
#include <QLineEdit>
#include "Scores.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
     void pushReport();
     void popReport();
     void pushAll();
     void popAll();
     void qSort();
     void hSort();
     void displayList(bool qsort, double opTime);
     void switchReport();

private:
    Ui::MainWindow *ui;
    Scores scores;
    QStringList reportStrings;
    QStringList criteriaListQString;
    QString criteria;
};
#endif // MAINWINDOW_H
