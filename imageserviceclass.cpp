#include "imageserviceclass.h"

ImageServiceClass::ImageServiceClass()
{
    pMOG2 = createBackgroundSubtractorMOG2();
    color = {124,252,0}; //Green
    thickness = 1;
    minContourSize = 100;
}

void ImageServiceClass::feedBackgroundSubtractor(QPixmap pixmap)
{
    Mat frame, fgMaskMOG2;
    frame = matConverter::QPixmapToMat(pixmap, false);

    pMOG2->apply(frame, fgMaskMOG2);
}

QPixmap ImageServiceClass::comparebyBackgroundSubtraction(QPixmap currentImage)
{
    Mat frame, fgMaskMOG2;
    frame = matConverter::QPixmapToMat(currentImage, false);

    pMOG2->apply(frame, fgMaskMOG2);

    return matConverter::MatToQPixmap(fgMaskMOG2);
}

Mat ImageServiceClass::comparebyBackgroundSubtraction(Mat currentMat)
{
    Mat fgMaskMOG2;

    pMOG2->apply(currentMat, fgMaskMOG2);

    return fgMaskMOG2;
}

QPixmap ImageServiceClass::markMovedObjects(QPixmap currentImage)
{
    Mat greyMat, colorMat;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<Vec4i> hierarchy;

    colorMat = matConverter::QPixmapToMat(currentImage, false);

    greyMat = comparebyBackgroundSubtraction(matConverter::QPixmapToMat(currentImage, false));

    contours = getContours(greyMat, true);

    int i = 0;
    foreach(std::vector<cv::Point> vec , contours)
    {
        if(vec.size() > minContourSize)
        {
            drawContours(colorMat, contours, i, color, thickness, 8, hierarchy, 0, Point() );
        }
        i++;
    }

    return matConverter::MatToQPixmap(colorMat);
}

void ImageServiceClass::reset()
{
    pMOG2 = createBackgroundSubtractorMOG2();
}

std::vector<std::vector<Point> > ImageServiceClass::getContours(Mat mat, bool isBinary)
{
    //Prepare the image for findContours
    if(!isBinary)
        cvtColor(mat, mat, CV_BGR2GRAY);

    threshold(mat, mat, 128, 255, CV_THRESH_BINARY);

    //Find the contours. Use the contourOutput Mat so the original image doesn't get overwritten
    std::vector<std::vector<cv::Point> > contours;
    Mat contourOutput = mat.clone();
    findContours( contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );

    return contours;
}

