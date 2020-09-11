#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTableView>
#include <memory>


// Predeclaration
class TableModel;
class TableSharedModel;
class TableGroupModel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum EViewType
{
    WholeTable, HighestTable, LooserTable, GroupTable
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    TableModel* m_tableModel;

    TableSharedModel* m_tableShared_1;
    TableSharedModel* m_tableShared_2;
    TableSharedModel* m_tableShared_3;
    TableSharedModel* m_tableShared_4;
    TableSharedModel* m_sharedModelHead;

    TableSharedModel* m_looserModel;

    TableGroupModel* m_groupModel;

    std::vector<std::unique_ptr<TableSharedModel>> m_tableSharedVector;
    std::vector<std::unique_ptr<QTableView>> m_tableViewVector;


    int m_minPoints;
    QLabel* m_statusBarLeft;
    QLabel* m_statusBarRight;

    EViewType m_viewType;

    QString m_fileName;
    int m_currentCountExams;
    int m_maxExamCount = 8;

    void initHighTable();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



signals:
    void shareGroupData();
    void shareLooserData();
    void shareHighestData();

private slots:


public slots:
    void onFileOpen();
    void onReadFromFile(int columnCount);

    void onSort(int index);


    void onFileOpenEdit();
    void onShowHighestEdit();
    void onShowLooserEdit();
    void onShowGroupEdit();

    void onShowTable();
    void onShowHighest();
    void onShowLooser();
    void onShowGroup();

    void onShareHighestData(int m_countWorker);
    void onShareLooserData(int points);
    void onShareGroupData(int groupCount);



};
#endif // MAINWINDOW_H
