#ifndef IMAGESERVICECLASS_H
#define IMAGESERVICECLASS_H


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QPixmap>
#include "matconverter.h"

using namespace cv;

/**
 * @brief Die ImageServiceClass stellt Funktionen zum Berechnen des Unterschieds zwischen
 * 2 oder mehreren QPixMaps oder Matrizen via OpenCV da
 */
class ImageServiceClass
{
public:
    /**
     * @brief Standard-Konstruktor.
     */
    ImageServiceClass();

    /**
     * @brief Die Funktion feedBackgroundSubtractor "füttert" die HintergrundSubtraktion
     * mit Bildern. Aus diesen Bildern berechnet der HintergrundSubtraktor sein Standard-Hintergrundbild.
     * Je mehr Bilder er erhält, desto genauer wird er kalibriert.
     * @param pixmap Das Bild, welches dem HintergrundSubtraktor zugespielt wird.
     */
    void feedBackgroundSubtractor(QPixmap pixmap);


    /**
     * @brief Die Funktion markMovedObjects, vergleicht die übergebene QPixMap mit dem HintergrundSubtraktor
     * und markiert je nach gesetzter minContourSize die Objekte, welche neue ins Bild gekommen sind bzw.
     * welche sich in dem Bild bewegt haben.
     * @param currentImage Die QPixMap welche verglichen werden soll.
     * @return Eine neue QPixMap mit den markierten Objekten.
     */
    QPixmap markMovedObjects(QPixmap currentImage);

    /**
     * @brief Die Funktion reset setzt den Hintergrundsubtraktor zurück.
     */
    void reset();

    /**
     * @brief Die Funktion setMinContoursize setzt die Schwelle, ab wievielen Punkte eine Kontur gezeichnet
     * werden soll. Eine Kontur umrandet ein Objekt in einem Bild.
     * @param value Die Anzahl von Punkten, welche ein Kontur besitzen muss, bis diese angezeigt wird.
     */
    void setMinContoursize(int value) { minContourSize = value; }

    /**
     * @brief Die Funktion setThickness, setzt die Dicke der Umrandung.
     * @param value Die Dicke der Umrandung in Pixeln.
     */
    void setThickness(int value) { thickness = value; }

private:

    /**
     * @brief Die Funktion comparebyBackgroundSubtraction vergleicht die übergebene QPixMap
     * mit dem HintergrundSubtraktor. Wenn der HintergrundSubtraktor nicht mit Daten "gefüttert" wurde
     * erhält man durch die unzureichenenden Daten ein sehr schlechtes Ergebenis.
     * @param currentframe Das Bild welches mit dem HintergrundSubtraktor verglichen werden soll.
     * @return Gibt den Unterschied zwischen des Bild und dem HintergrundSubtraktor als 2Bit-Bild zurück.
     */
    QPixmap comparebyBackgroundSubtraction(QPixmap currentframe);

    /**
     * @brief Die Funktion comparebyBackgroundSubtraction vergleicht die übergebene QPixMap
     * mit dem HintergrundSubtraktor. Wenn der HintergrundSubtraktor nicht mit Daten "gefüttert" wurde
     * erhält man durch die unzureichenenden Daten ein sehr schlechtes Ergebenis.
     * @param currentframe Das Bild welches mit dem HintergrundSubtraktor verglichen werden soll.
     * @return Gibt den Unterschied zwischen des Bild und dem HintergrundSubtraktor als 2Bit-Bild zurück.
     */
    Mat comparebyBackgroundSubtraction(Mat currentMat);

    /**
     * @brief color Die Farbe der Kontur.
     */
    cv::Scalar color;

    /**
     * @brief thickness Die Breite der Kontur.
     */
    int thickness;

    /**
     * @brief minContourSize Die minimale Punkteanzahl, bis eine Kontur gezeichnet wird.
     */
    int minContourSize;

    /**
     * @brief pMOG2 Der HintergrundSubtraktor.
     */
    Ptr<BackgroundSubtractorMOG2> pMOG2;

    /**
     * @brief Die Funktion getContours gibt die Konturen einer Matrix zurück.
     * @param mat Die Matrix, welche die Konturen beinhaltet.
     * @param isBinary Legt fest ob die Matrix schon Binary übergeben wird oder noch konvertiert werden muss
     * @return Gibt einen Vector zurück, der Vectoren mit Punkten der Konturen enthält.
     */
    std::vector<std::vector<cv::Point> > getContours(Mat mat, bool isBinary);
};

#endif // IMAGESERVICECLASS_H
