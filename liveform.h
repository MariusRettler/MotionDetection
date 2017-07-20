#ifndef LIVEFORM_H
#define LIVEFORM_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <iform.h>
#include <QMessageBox>
#include <imageserviceclass.h>
#include <opencv2/videoio.hpp>

namespace Ui {
class LiveForm;
}

/**
 * @brief Die LiveForm-Klasse zeigt das LiveBild einer vorhandenen Webcam an und führt auf dieser, die
 * HintergrundSubtraction mit Objekerkennung durch.
 */
class LiveForm : public QWidget, public IForm
{
    Q_OBJECT

public:
    /**
     * @brief Die Funktion DeadForm ist der Standard-Konstruktor.
     * @param parent Parent des Widgets.
     */
    explicit LiveForm(QWidget *parent = 0);
    /**
     * @brief Die Funktion OnShowUp wird bei jedem Aufruf der Form verwendet.
     */
    virtual void OnShowUp();
    ~LiveForm();

private:

    virtual void CreateActions();

    /**
     * @brief Das PaintEvent, welches zur LiveAnzeige überschrieben wird.
     */
    void paintEvent(QPaintEvent *pe);

    Ui::LiveForm *ui;
    cv::VideoCapture myVideo;
    QTimer *timer;
    ImageServiceClass *imageServiceClass;

public slots:
    /**
     * @brief Der Slot setMinContourSize, setzt die minContourSize für die ImageServiceKlasse.
     */
    virtual void setMinContourSize(int value);

    /**
     * @brief Der Slot setThickness, setzt die Dicke der gezeichneten Kontur.
     */
    virtual void setThickness(int value);

};

#endif // LIVEFORM_H
