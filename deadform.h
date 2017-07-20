#ifndef DEADFORM_H
#define DEADFORM_H

#include <QWidget>
#include <QMainWindow>
#include <QFileDialog>
#include <QList>
#include <QGraphicsScene>
#include <QShortcut>
#include "iform.h"
#include <imageserviceclass.h>

namespace Ui {
class DeadForm;
}

/**
 * @brief Die DeadForm-Klasse stellt die Bewegungserkennung von einer Reihe geladenen Bildern dar.
 */
class DeadForm : public QWidget , public IForm
{
    Q_OBJECT

public:
    /**
     * @brief Die Funktion DeadForm ist der Standard-Konstruktor.
     * @param parent Parent des Widgets.
     */
    explicit DeadForm(QWidget *parent = 0);

    /**
     * @brief Die Funktion OnShowUp wird bei jedem Aufruf der Form verwendet.
     */
    virtual void OnShowUp();
    ~DeadForm();

private:
    /**
     * @brief Die Funktion CreateActions erstellt die Aktionen.
     */
    virtual void CreateActions();

    /**
     * @brief Die Funktion loadPicturesinView, lädt alle Bilder in die vorgsehenen Fenster.
     */
    void loadPicturesinView();

    /**
     * @brief Die Funktion loadPictureinViewBefore, lädt das Bild in das "Before-Fenster".
     * @param pixmap Das Bild, welches geladen wird.
     */
    void loadPictureinViewBefore(QPixmap pixmap);

    /**
     * @brief Die Funktion loadPictureinViewCurrent, lädt das Bild in das "Current-Fenster".
     * @param pixmap Das Bild, welches geladen wird.
     */
    void loadPictureinViewCurrent(QPixmap pixmap);

    /**
     * @brief Die Funktion loadPictureinViewAfter, lädt das Bild in das "After-Fenster".
     * @param pixmap Das Bild, welches geladen wird.
     */
    void loadPictureinViewAfter(QPixmap pixmap);

    /**
     * @brief Die Funktion  mod ist eine eigene Modulo Funktion mit der auch negative Zahlen
     * Modulo berechnet werden können. Somit wird ein negatives Ergebnis vermieden.
     * @param x Die Modulo zunehmende Zahl
     * @param m Zahlen Bereich
     * @return positives Ergebnis oder 0
     */
    int mod(int x, int m) {
        return (x%m + m)%m;
    }

    Ui::DeadForm *ui;

    ImageServiceClass *imageServiceClass;
    int imagePositionCounter;
    int bsRuns;
    QList<QPixmap*> imageList;

    QGraphicsScene *sceneBefore;
    QGraphicsScene *sceneCurrent;
    QGraphicsScene *sceneAfter;

public slots:
    /**
     * @brief Die Funktion loadPicturesToList, lädt alle im FileDialog ausgewählten Bilder in die List.
     * Ebenfalls werden je nach den definierten bsRuns die Bilder in den HintergrundSubtraktor geladen.
     */
    void loadPicturesToList();

    /**
     * @brief Der Slot setMinContourSize, setzt die minContourSize für die ImageServiceKlasse.
     */
    virtual void setMinContourSize(int value);

    /**
     * @brief Der Slot setThickness, setzt die Dicke der gezeichneten Kontur.
     */
    virtual void setThickness(int value);

    /**
     * @brief Der Slot setBSRuns, setzt die Anzah der Durchläufe, die die Bilder vor der Anzeige durch
     * den HintergrundSubtraktor machen sollen.
     */
    void setBSRuns(int value);
private slots:
    void rotateImagesLeft();
    void rotateImagesRight();
};

#endif // DEADFORM_H
