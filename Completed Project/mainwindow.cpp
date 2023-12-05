#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPalette>
#include <QGuiApplication>
#include <QScreen>
#include "Scores.h"
#include <string>
#include <regex>
#include <QCompleter>
#include <QStringListModel>
#include <QListWidgetItem>
#include <Qdir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    // --------------------------- UI STYLE ---------------------------//


    ui->setupUi(this);
    resize(QGuiApplication::primaryScreen()->availableGeometry().size() * 0.7);
    //setFixedSize(size());
    QPixmap bkgnd("SATisticsbg.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    ui->welcome->setText("<font color='white'>Welcome to SATistics!</font>");
    ui->watermark->setText("<font color='white'>Made by Nicholas DeSanctis, Marvin Howell-Aguirre, and Matthew Nobleza for COP3530, 2023</font>");
    ui->display->setStyleSheet("color: #000000; background-color: #D7E4FE;");
    ui->repLineEdit->setStyleSheet("color: #000000; background-color: #D7E4FE;");
    ui->critLineEdit->setStyleSheet("color: #000000; background-color: #D7E4FE;");
    ui->statusBox->setStyleSheet("color: #000000; background-color: #D7E4FE;");
    ui->reportView->setStyleSheet("color: #000000; background-color: #D7E4FE;");

    ui->popAllButton->setStyleSheet("color: #FFFFFF; background-color: #E6792C");
    ui->pushAllButton->setStyleSheet("color: #FFFFFF; background-color: #E6792C");
    ui->popButton->setStyleSheet("color: #FFFFFF; background-color: #E6792C");
    ui->pushButton->setStyleSheet("color: #FFFFFF; background-color: #E6792C");
    ui->quickSortButton->setStyleSheet("color: #FFFFFF; background-color: #E6792C");
    ui->heapSortButton->setStyleSheet("color: #FFFFFF; background-color: #E6792C");
    ui->statusBox->setText(ui->statusBox->placeholderText());


    // SETTING REPORT LIST


    QStringList reportListQString;
    for (const auto &rep : scores.getDataSet()) {
        std::string year = std::to_string(rep.first.first);
        std::string state = rep.second->stateName;
        reportListQString.append(QString::fromStdString(state + ", " + year));
    }

    // SETTING AUTOCOMPLETE INFO

    reportListQString.sort();
    QStringListModel* repListModel = new QStringListModel(reportListQString, this);
    QCompleter* repCompleter = new QCompleter(repListModel, this);
    repCompleter->setCompletionMode(QCompleter::PopupCompletion);
    repCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    repCompleter->popup()->setStyleSheet("color: #E62ccb; background-color: #E62ccb;");
    repCompleter->popup()->setStyleSheet(("font: 12pt \"Microsoft YaHei\";"));
    repCompleter->setFilterMode(Qt::MatchContains);
    ui->repLineEdit->setCompleter(repCompleter);

    // SETTING CRITERIA LIST

    for (int i = 6; i < Scores::labels.size(); i++)
        criteriaListQString.append(QString::fromStdString(Scores::labels[i]));

    criteriaListQString.sort();
    QStringListModel* critListModel = new QStringListModel(criteriaListQString, this);
    QCompleter* critCompleter = new QCompleter(critListModel, this);
    critCompleter->setCompletionMode(QCompleter::PopupCompletion);
    critCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    critCompleter->popup()->setStyleSheet("color: #FFFFFF; background-color: #000000;");
    critCompleter->popup()->setStyleSheet(("font: 12pt \"Microsoft YaHei\";"));
    critCompleter->setFilterMode(Qt::MatchContains);
    ui->critLineEdit->setCompleter(critCompleter);

    // ---------------------- UI COMPONENTS TO BACKEND---------------------------//

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::pushReport);
    connect(ui->popButton, &QPushButton::clicked, this, &MainWindow::popReport);
    connect(ui->pushAllButton, &QPushButton::clicked, this, &MainWindow::pushAll);
    connect(ui->popAllButton, &QPushButton::clicked, this, &MainWindow::popAll);
    connect(ui->quickSortButton, &QPushButton::clicked, this, &MainWindow::qSort);
    connect(ui->heapSortButton, &QPushButton::clicked, this, &MainWindow::hSort);
    connect(ui->display, &QListWidget::clicked, this, &MainWindow::switchReport);
}

// --------------------------- PUSH/REMOVE ---------------------------//

void MainWindow::pushReport() {
    QString searchTerm = ui->repLineEdit->text().trimmed();
    std::string parseString = searchTerm.toStdString();
    QString update = "Please input the name of the report you want to add!";
    if (searchTerm.size() > 0) {
        std::regex digits("^[0-9]+$");
        std::string delim = ", ";
        std::string state = parseString.substr(0, parseString.find(delim));
        std::string year = parseString.substr(parseString.find(delim) + 2);
        update = "Not a valid report!";
        if (std::regex_match(year, digits) && Scores::getInitials.find(state) != Scores::getInitials.end()) {
            bool added = scores.push_report(std::stoi(year), Scores::getInitials.at(state));
            update = "Report has already been added!";
            if (added) {
                update = "Report added successfully!";
                ui->repLineEdit->clear();
            }
        }
    }
    ui->statusBox->setText(update);
}
void MainWindow::popReport() {
    QString searchTerm = ui->repLineEdit->text().trimmed();
    std::string parseString = searchTerm.toStdString();
    QString update = "Please input the name of the report you want to remove!";
    if (searchTerm.size() > 0) {
        std::regex digits("^[0-9]+$");
        std::string delim = ", ";
        std::string state = parseString.substr(0, parseString.find(delim));
        std::string year = parseString.substr(parseString.find(delim) + 2);
        update = "Not a valid report!";
        if (std::regex_match(year, digits) && Scores::getInitials.find(state) != Scores::getInitials.end()) {
            bool removed = scores.pop_report(std::stoi(year), Scores::getInitials.at(state));
            if (removed) {
                update = "Report removed successfully!";
                ui->repLineEdit->clear();
            }
            else
                update = "Report not found in current dataset!";
        }
    }
    ui->statusBox->setText(update);
}
void MainWindow::pushAll() {
    int prePushSize = scores.getSize();
    scores.push_all();
    QString update;
    if (scores.getSize() > prePushSize)
        update = "All reports added!";
    else
        update = "No reports left to add!";
    ui->statusBox->setText(update);
}
void MainWindow::popAll() {
    int prePopSize = scores.getSize();
    scores.pop_all();
    QString update;
    if (scores.getSize() < prePopSize)
        update = "All reports removed!";
    else
        update = "No reports left to remove!";
    ui->statusBox->setText(update);
}

// --------------------------- SORTING ---------------------------//

void MainWindow::qSort() {
    ui->display->clear();
    QString tryCriteria = ui->critLineEdit->text().trimmed();
    QString update = "Please enter a valid criteria!";
    std::string tryLookup = tryCriteria.toStdString();
    if (std::find(Scores::labels.begin(), Scores::labels.end(), tryLookup) != Scores::labels.end()) {
        criteria = tryCriteria;
        double opTime = scores.quickSort(criteria.toStdString());
        displayList(true, opTime);
    }
    else
        ui->statusBox->setText(update);
}
void MainWindow::hSort() {
    ui->display->clear();
    QString tryCriteria = ui->critLineEdit->text().trimmed();
    QString update = "Please enter a valid criteria!";
    std::string tryLookup = tryCriteria.toStdString();
    if (std::find(Scores::labels.begin(), Scores::labels.end(), tryLookup) != Scores::labels.end()) {
        criteria = tryCriteria;
        double opTime = scores.heapSort(criteria.toStdString());
        displayList(false, opTime);
    }
    else
        ui->statusBox->setText(update);
}

// --------------------------- DISPLAYING ---------------------------//

void MainWindow::displayList(bool qsort, double opTime) {
    int numreports = scores.getSize();
    std::string sort;
    if (qsort)
        sort = "quicksort";
    else
        sort = "heapsort";

    std::string crit = criteria.toStdString();
    std::string time = std::to_string(opTime);
    time.erase(time.find('.') + 2);
        std::string status = std::to_string(numreports) + " SAT score reports, sorted by " + crit + " using " + sort + " in " + time + " milliseconds";
    QString update;
    update.append(status);
    QStringList displaylist;
    for (int i = 0; i < numreports; i++) {
        std::string year = std::to_string(scores.getDisplayVector()[i]->key.first);
        std::string state = scores.getDisplayVector()[i]->stateName;
        qfloat16 val = scores.getDisplayVector()[i]->criteriaToValue.at(criteria.toStdString());
        std::string valstring = std::to_string(val);
        valstring.erase(valstring.find('.') + 3);
        displaylist.append(QString::fromStdString(std::to_string(i + 1) + ": " + state + ", " + year + ": " + valstring));
    }
    ui->display->clear();
    ui->display->addItems(displaylist);
    ui->statusBox->setText(update);
}

// ---------------------- STEPPING INTO REPORT ------------------------//

void MainWindow::switchReport() {
    QListWidgetItem Qreport = *ui->display->currentItem();
    QStringList displaylist;
    std::string line = Qreport.text().trimmed().toStdString();
    line.erase(line.find_first_of(':'));
    int index = stoi(line) - 1;
    auto &report = scores.getReport(index);

    QString Qyear = QString::fromStdString(std::to_string(report.key.first));
    QString QstateName = QString::fromStdString(report.stateName);

    displaylist.append("Data for " + QstateName + ", " + Qyear + ": ");

    QString Qtesttakers = QString::fromStdString(std::to_string(report.totalTestTakers));
    QString Qmath = QString::fromStdString(std::to_string(report.totalMath));
    QString Qverbal = QString::fromStdString(std::to_string(report.totalVerbal));

    displaylist.append("Total Test Takers: " + Qtesttakers);
    displaylist.append("Total Math: " + Qmath);
    displaylist.append("Total Verbal: " + Qverbal);
    for (const QString &crit : criteriaListQString) {
        qfloat16 val = report.criteriaToValue.at(crit.toStdString());
        std::string valstring = std::to_string(val);
        valstring.erase(valstring.find('.') + 3);
        QString Qvalstring = QString::fromStdString(valstring);
        displaylist.append(crit + ": " + Qvalstring);
    }
    ui->reportView->clear();
    ui->reportView->addItems(displaylist);
}

MainWindow::~MainWindow()
{
    delete ui;
}
