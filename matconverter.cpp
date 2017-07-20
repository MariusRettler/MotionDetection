#include "matconverter.h"

QImage matConverter::MatToQImage(const Mat &inMat)
{
    switch ( inMat.type() )
    {
       // 8-bit, 4 channel
       case CV_8UC4:
       {
          QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

          return image;
       }

       // 8-bit, 3 channel
       case CV_8UC3:
       {
          QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

          return image.rgbSwapped();
       }

       // 8-bit, 1 channel
       case CV_8UC1:
       {
          static QVector<QRgb>  sColorTable;

          // only create our color table once
          if ( sColorTable.isEmpty() )
          {
             for ( int i = 0; i < 256; ++i )
                sColorTable.push_back( qRgb( i, i, i ) );
          }

          QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

          image.setColorTable( sColorTable );

          return image;
       }

       default:
          qDebug() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
          break;
    }

    return QImage();
}

Mat matConverter::QImageToMat(const QImage &inImage, bool inCloneImageData)
{
    switch ( inImage.format() )
    {
       // 8-bit, 4 channel
       case QImage::Format_RGB32:
       {
          Mat  mat( inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );

          return (inCloneImageData ? mat.clone() : mat);
       }

       // 8-bit, 3 channel
       case QImage::Format_RGB888:
       {
          if ( !inCloneImageData )
             qDebug() << "ASM::QImageToCvMat() - Conversion requires cloning since we use a temporary QImage";

          QImage   swapped = inImage.rgbSwapped();

          return Mat( swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
       }

       // 8-bit, 1 channel
       case QImage::Format_Indexed8:
       {
          Mat  mat( inImage.height(), inImage.width(), CV_8UC1, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );

          return (inCloneImageData ? mat.clone() : mat);
       }

       default:
          qDebug() << "ASM::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
          break;
    }

    return Mat();
}

QPixmap matConverter::MatToQPixmap(const Mat &inMat)
{
    return QPixmap::fromImage( MatToQImage( inMat ) );
}

Mat matConverter::QPixmapToMat(const QPixmap &inPixmap, bool inCloneImageData)
{
    return QImageToMat( inPixmap.toImage(), inCloneImageData );
}
