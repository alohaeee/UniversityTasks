#include "mainwindow.h"
#include "ui_mainwindow.h"


// Qt
#include <QFileDialog>

#include <QDebug>

// Project
#include "exception.h"
#include "tablemodel.h"
#include "dialogshow.h"
#include "tablegroupmodel.h"
#include "tablesharedmodel.h"

#include <initializer_list>


void MainWindow::initHighTable()
{

    onShowTable();
    m_currentCountExams = m_tableModel->columnCount() - 3;

    for (int i = 0; i < m_currentCountExams; i++)
    {
        QList<int> columnList; columnList << 0 << i+1;

        m_tableSharedVector[i]->setColumnList(columnList);
        m_tableSharedVector[i]->sharedHeaderData(m_tableModel);

        if(!m_tableViewVector[i]->isEnabled())
            m_tableViewVector[i]->setEnabled(true);
    }
    for (int i = m_currentCountExams; i < m_maxExamCount; i++)
    {
        m_tableViewVector[i]->setEnabled(false);
    }


    QList<int> columnList; columnList << 0 << m_tableModel->columnCount()-2 << m_tableModel->columnCount() - 1;
    m_sharedModelHead->setColumnList(columnList);
    m_sharedModelHead->sharedHeaderData(m_tableModel);
    ui->highTableHead->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_looserModel->setColumnList(columnList);
    m_looserModel->sharedHeaderData(m_tableModel);
    ui->looserTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_groupModel->setColumnCount(m_tableModel->columnCount());
    m_groupModel->sharedHeaderData(m_tableModel);

    ui->tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->resizeSection(0,250);

    ui->groupTable->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->groupTable->horizontalHeader()->resizeSection(0,250);
    for(int i = 1; i < m_tableModel->columnCount(); i++)
    {
        ui->tableView->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
        ui->groupTable->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      m_tableModel(nullptr), m_statusBarLeft(nullptr), m_statusBarRight(nullptr),
      m_viewType(EViewType::HighestTable)
{
    ui->setupUi(this);

    int columnCount = 7;
    // Setting table model.
    m_tableModel = new TableModel(';', columnCount, this);

    // Setting table view.
    ui->tableView->setModel(m_tableModel);


    // Enable sorting.
    ui->tableView->setSortingEnabled(true);

    onShowTable();

    m_sharedModelHead = new TableSharedModel(this);
    m_looserModel = new TableSharedModel(this);

    ui->highTableHead->setModel(m_sharedModelHead);
    ui->looserTable->setModel(m_looserModel);

    // Group Table.
    m_groupModel = new TableGroupModel(this,30);
    m_groupModel->setColumnCount(m_tableModel->columnCount());
    m_groupModel->sharedHeaderData(m_tableModel);

    ui->groupTable->setModel(m_groupModel);



    int gridRowCount = ui->gridLayout->rowCount();
    bool isSecond = false;

    for (int i = 0; i < m_maxExamCount; i++)
    {
        TableSharedModel* sharedModel = new TableSharedModel(this);

        std::unique_ptr<TableSharedModel> uModelPtr { sharedModel };
        m_tableSharedVector.emplace_back(std::move(uModelPtr));

        QTableView* tableView = new QTableView(ui->centralwidget);

        std::unique_ptr<QTableView> uViewPtr { tableView };
        m_tableViewVector.emplace_back(std::move(uViewPtr));

        gridRowCount+=(isSecond ? 0 : 1);
        ui->gridLayout->addWidget(tableView, gridRowCount, isSecond ? 1 : 0, 1, 1);


        isSecond = !isSecond;

        tableView->setModel(sharedModel);

        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        tableView->hide();
    }

    // Fixed window size.
    this->setMaximumSize(this->size());
    this->setMinimumSize(this->size());

    // Status Bar spliting.
    m_statusBarLeft = new QLabel(this);
    m_statusBarRight = new QLabel(this);
    ui->statusbar->addPermanentWidget(m_statusBarLeft,1);
    ui->statusbar->addPermanentWidget(m_statusBarRight,2);

    // Connect part.

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onFileOpen);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    connect(ui->tableView->horizontalHeader(),&QHeaderView::sortIndicatorChanged, this, &MainWindow::onSort);

    // Menu and tool bar.
    connect(ui->actionShowTable, &QAction::triggered, this, &MainWindow::onShowTable);

    connect(ui->actionShowHighest, &QAction::triggered, this, &MainWindow::onShowHighest);
    connect(ui->actionEditHighest, &QAction::triggered, this, &MainWindow::onShowHighestEdit);

    connect(ui->actionDontGetInto, &QAction::triggered, this, &MainWindow::onShowLooser);
    connect(ui->actionEditDontGetInto, &QAction::triggered, this, &MainWindow::onShowLooserEdit);

    connect(ui->actionShowGroups, &QAction::triggered, this, &MainWindow::onShowGroup);
    connect(ui->actionEditGroups, &QAction::triggered, this, &MainWindow::onShowGroupEdit);

}

MainWindow::~MainWindow()
{
    delete ui;
    m_tableViewVector.clear();
    m_tableSharedVector.clear();

    delete m_tableModel;
    delete m_statusBarLeft;
    delete m_statusBarRight;

    delete m_sharedModelHead;

    delete m_looserModel;

    delete m_groupModel;
}



void MainWindow::onFileOpen()
{
    m_fileName = QFileDialog::getOpenFileName(this,"Open File",nullptr,"Text files (*.txt)");
    if(!m_fileName.isNull())
    {

        DialogShow dialogShow(this,1,10);
        connect(&dialogShow,&DialogShow::showed,this,&MainWindow::onReadFromFile);

        dialogShow.setLabel("Введите кол-во предметов в файле: ");
        dialogShow.setModal(true);
        dialogShow.exec();

        disconnect(&dialogShow,&DialogShow::showed,this,&MainWindow::onReadFromFile);
    }

}

void MainWindow::onSort(int index)
{
    auto headerLabel = m_tableModel->headerData(index,Qt::Horizontal, Qt::DisplayRole);
    m_statusBarRight->setText("Отсортирован столбец \"" + headerLabel.toString() + '\"');
}

void MainWindow::onReadFromFile(int columnCount)
{
    try
    {
        // + 3 coz storing names and two count middle and common points.
        m_tableModel->setColumnCount(columnCount + 3);

        int count = m_tableModel->columnCount() - 2;
        m_tableModel->readFromFile(m_fileName, count);

        m_tableModel->setHeaderData(count, Qt::Horizontal, "Средний");
        m_tableModel->setHeaderData(count+1, Qt::Horizontal, "Общий");
        m_tableModel->countColumnValues(0, count, count, count-1);
        m_tableModel->countColumnValues(0, count, count + 1, 1);

        m_statusBarLeft->setText("Открытый файл: " + m_fileName.section('/',-1));

        initHighTable();

        onShareHighestData(5);
        onShareLooserData(170);

        m_tableModel->sort(0,Qt::SortOrder::DescendingOrder);
    }
    catch (Exception& e)
    {
        if(e.state() == Exception::Warning)
        {
            QMessageBox::warning(this,"Warning",e.message());
        }
        else
        {
            QMessageBox::critical(this,"Warning",e.message());
        }
    }
}

void MainWindow::onFileOpenEdit()
{

}

void MainWindow::onShowHighestEdit()
{

    DialogShow dialogShow(this,0,50);
    connect(&dialogShow,&DialogShow::showed,this,&MainWindow::onShareHighestData);

    dialogShow.setLabel("Введите кол-во абитуриентов с наивысшими баллами: ");
    dialogShow.setModal(true);
    dialogShow.exec();

    disconnect(&dialogShow,&DialogShow::showed,this,&MainWindow::onShareHighestData);

}

void MainWindow::onShowLooserEdit()
{
    DialogShow dialogShow(this,0,400);
    connect(&dialogShow,&DialogShow::showed,this,&MainWindow::onShareLooserData);

    dialogShow.setLabel("Введите порог прохождения: ");
    dialogShow.setModal(true);
    dialogShow.exec();

    disconnect(&dialogShow,&DialogShow::showed,this,&MainWindow::onShareLooserData);
}

void MainWindow::onShowGroupEdit()
{
    DialogShow dialogShow(this,9, m_tableModel->rowCount()/2);
    connect(&dialogShow,&DialogShow::showed,this,&MainWindow::onShareGroupData);

    dialogShow.setLabel("Введите верхний передел количества человек в группах: ");
    dialogShow.setModal(true);
    dialogShow.exec();

    disconnect(&dialogShow,&DialogShow::showed,this,&MainWindow::onShareGroupData);
}

void MainWindow::onShowTable()
{
    if(m_viewType != EViewType::WholeTable)
    {
        m_viewType = EViewType::WholeTable;

        for(int i = 0; i < m_currentCountExams; i++)
        {
            m_tableViewVector[i]->hide();
        }

        ui->highTableHead->hide();
        ui->highLabel->hide();

        ui->looserTable->hide();
        ui->looserLabel->hide();

        ui->groupTable->hide();

        ui->tableView->show();
    }


}

void MainWindow::onShareHighestData(int count)
{

    for(int i = 0 ; i < m_currentCountExams; i++)
    {
        m_tableModel->sort(i+1, Qt::SortOrder::AscendingOrder);
        m_tableSharedVector[i]->sharedData(m_tableModel, count);
    }

    m_tableModel->sort(m_tableModel->columnCount()-1,Qt::SortOrder::AscendingOrder);
    m_sharedModelHead->sharedData(m_tableModel,count);

    ui->highLabel->setText("Процент лучших абитуриентов: " + QString::number((static_cast<double>(count)/m_tableModel->rowCount())*100,'f',2) + '%');

    m_statusBarRight->setText("Количество показываемых лучших абитуриентов: " + QString::number(count));

    shareHighestData();
}

void MainWindow::onShareLooserData(int points)
{
    m_minPoints = points;
    int index = m_tableModel->columnCount() - 1;
    m_tableModel->sort(index, Qt::SortOrder::DescendingOrder);
    int count = 0;

    foreach (const auto& row, m_tableModel->getDataList())
    {
        if(row[index].toInt() <= points)
            count++;
        else
            break;
    }
    m_looserModel->sharedData(m_tableModel, count);


    ui->looserLabel->setText("Процент непрошедших: " + QString::number((static_cast<double>(count)/m_tableModel->rowCount())*100,'f',2) + '%');

    m_statusBarRight->setText("Количество показываемых непрошедших абитуриентов: " + QString::number(count));

    onShareGroupData(m_groupModel->groupPeopleCount());

    shareLooserData();
}

void MainWindow::onShareGroupData(int groupCount)
{
    m_tableModel->sort(m_tableModel->columnCount()-1, Qt::SortOrder::AscendingOrder);
    m_groupModel->sharedData(m_tableModel,groupCount,m_minPoints);

    m_statusBarRight->setText("Сформированы списки групп");

    shareGroupData();
}

void MainWindow::onShowHighest()
{
    if(m_viewType!= EViewType::HighestTable)
    {
        m_viewType = EViewType::HighestTable;

        ui->tableView->hide();

        ui->looserTable->hide();
        ui->looserLabel->hide();

        ui->groupTable->hide();

        for(int i = 0; i < m_currentCountExams; i++)
        {
            m_tableViewVector[i]->show();
        }
        ui->highTableHead->show();
        ui->highLabel->show();
    }

}

void MainWindow::onShowLooser()
{
    if(m_viewType != EViewType::LooserTable)
    {
        m_viewType = EViewType::LooserTable;

        for(int i = 0; i < m_currentCountExams; i++)
        {
            m_tableViewVector[i]->hide();
        }
        ui->highTableHead->hide();
        ui->highLabel->hide();

        ui->groupTable->hide();

        ui->tableView->hide();

        ui->looserLabel->show();
        ui->looserTable->show();
    }
}

void MainWindow::onShowGroup()
{
    if(m_viewType != EViewType::GroupTable)
    {
        m_viewType = EViewType::GroupTable;

        for(int i = 0; i < m_currentCountExams; i++)
        {
            m_tableViewVector[i]->hide();
        }
        ui->highTableHead->hide();
        ui->highLabel->hide();

        ui->tableView->hide();

        ui->looserLabel->hide();
        ui->looserTable->hide();

        ui->groupTable->show();
    }
}

