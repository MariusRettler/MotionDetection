#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QGridLayout>
#include <deadform.h>
#include <liveform.h>

namespace Ui {
class MainWindow;
}
/**
 * @brief Die MainWindow-Klasse stellt das MainWindow da und dient als Controller, zwischen der DeadForm
 * und der LiveForm.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Die Funktion MainWindow ist der Standard-Konstruktor.
     * @param parent Parent des QMainWindows.
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createActions();

    Ui::MainWindow *ui;
    QStackedWidget *forms;
    DeadForm *deadForm;
    LiveForm *liveForm;

private slots:
    void loadPicturesToList();
    void goToLive();
    void goToDead();
};

#endif // MAINWINDOW_H
