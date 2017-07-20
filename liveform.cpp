#include "liveform.h"
#include "ui_liveform.h"

LiveForm::LiveForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LiveForm)
{
    ui->setupUi(this);
    OnShowUp();
}

void LiveForm::OnShowUp()
{
    imageServiceClass = new ImageServiceClass();

    try
    {
        myVideo.open(0);

        if(!myVideo.isOpened())
        {
            QMessageBox::information(this,tr("Information"), tr("Keine Webcam gefuden!"));
        }
        else
        {
            CreateActions();
            update();
        }
    }
    catch(cv::Exception &e)
    {
        QMessageBox::information(this,tr("Information"), tr("Keine Webcam gefuden!"));
    }
}

LiveForm::~LiveForm()
{
    delete ui;
}

void LiveForm::CreateActions()
{
    connect(ui->spinBoxContourSize, SIGNAL(valueChanged(int)), this, SLOT(setMinContourSize(int)));
    connect(ui->spinBoxThickness, SIGNAL(valueChanged(int)), this, SLOT(setThickness(int)));
}

void LiveForm::paintEvent(QPaintEvent *pe)
{
    try
    {
        if (myVideo.isOpened())
        {
            cv::Mat frame;
            myVideo >> frame;
            QPixmap image = QPixmap::fromImage(QImage((const unsigned char*)frame.data,frame.cols,
                                  frame.rows,frame.step,QImage::Format_RGB888));

            QPixmap tmpimage = imageServiceClass->markMovedObjects(image);

            QRectF target(0.0,0.0,image.width(),image.height());
            QRectF source(0.0,0.0,image.width(),image.height());
            QPainter painter(this);
            painter.drawImage(target,tmpimage.toImage(),source);
            update();
        }
    }
    catch(cv::Exception &e)
    {
        QMessageBox::information(this,tr("Information"), tr("Keine Webcam gefuden!"));
    }

}

void LiveForm::setThickness(int value)
{
    imageServiceClass->setThickness(value);
}

void LiveForm::setMinContourSize(int value)
{
    imageServiceClass->setMinContoursize(value);
}
