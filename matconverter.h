#ifndef MATCONVERTER_H
#define MATCONVERTER_H

#include <QImage>
#include <QPixmap>
#include <QDebug>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"

using namespace cv;

/**
 * @brief Die Klasse MatConverter bietet die Möglichkeiten der Konvertierung von: \n
 * QImage  -> cv::Mat \n
 * QPixmap -> cv::Mat \n
 * cv::Mat -> QImage \n
 * cv::Mat -> QPixmap
 */
class matConverter
{
public:
    /**
     * @brief Konvertiert eine cv::Mat zu einem QImage.
     * @param inMat Die übergebene Matrix.
     * @return Gibt das konvertierte QImage zurück.
     */
    static QImage MatToQImage(const Mat &inMat);

    /**
     * @brief Konvertiert ein QImage zu einer cv::Mat.
     * @param inImage Das übergebene QImage.
     * @param inCloneImageData Gibt an ob eine Kopie zum konvertieren benutzt werden soll.
     * @return Gibt die konvertierte Matrix zurück.
     */
    static Mat QImageToMat(const QImage &inImage, bool inCloneImageData = true);

    /**
     * @brief Konervetiert eine cv::Mat zu einer QPixmap.
     * @param inMat Die übergebene Matrix.
     * @return Gibt die konvertierte QPixmap zurück.
     */
    static QPixmap MatToQPixmap(const Mat &inMat);

    /**
     * @brief Konvertiert eine QPixmap zu einer cv::Mat.
     * @param inPixmap Die übergebene QPixMap.
     * @param inCloneImageData Gibt an ob eine Kopie zum konvertieren benutzt werden soll.
     * @return Gibt die konvertierte Matrix zurück.
     */
    static Mat QPixmapToMat(const QPixmap &inPixmap, bool inCloneImageData = true);

};

#endif // MATCONVERTER_H
