#include "deadform.h"
#include "ui_deadform.h"

DeadForm::DeadForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeadForm)
{
    ui->setupUi(this);
    OnShowUp();
}

void DeadForm::OnShowUp()
{
    imagePositionCounter = 1;
    bsRuns = 1;
    imageServiceClass = new ImageServiceClass();
    sceneBefore = NULL;
    sceneCurrent = NULL;
    sceneAfter = NULL;

    CreateActions();
}

DeadForm::~DeadForm()
{
    delete ui;
}

void DeadForm::CreateActions()
{
    QShortcut *shortcutRight = new QShortcut(QKeySequence("Right"), this);
    QShortcut *shortcutLeft = new QShortcut(QKeySequence("Left"), this);

    connect(ui->beforeButton, SIGNAL(clicked(bool)), this, SLOT(rotateImagesLeft()));
    connect(ui->afterButton, SIGNAL(clicked(bool)), this, SLOT(rotateImagesRight()));
    connect(ui->spinBoxContourSize, SIGNAL(valueChanged(int)), this, SLOT(setMinContourSize(int)));
    connect(ui->spinBoxThickness, SIGNAL(valueChanged(int)), this, SLOT(setThickness(int)));
    connect(ui->spinBoxBSRuns, SIGNAL(valueChanged(int)), this, SLOT(setBSRuns(int)));
    connect(shortcutRight, SIGNAL(activated()), this, SLOT(rotateImagesRight()));
    connect(shortcutLeft, SIGNAL(activated()), this, SLOT(rotateImagesLeft()));
}

void DeadForm::loadPicturesinView()
{
    if(imageList.isEmpty())
    {
        throw new std::string("No Pictures loaded!");
    }

    QPixmap img1, img2, img3;

    img1 = imageList[mod((imagePositionCounter - 1), imageList.size())]->copy();
    img2 = imageList[mod((imagePositionCounter), imageList.size())]->copy();
    img3 = imageList[mod((imagePositionCounter + 1), imageList.size())]->copy();

    loadPictureinViewBefore(img1);
    loadPictureinViewCurrent(img2);
    loadPictureinViewAfter(img3);
}

void DeadForm::loadPictureinViewBefore(QPixmap pixmap)
{
    if(sceneBefore != NULL)
    {
        sceneBefore->clear();
        sceneBefore = NULL;
    }

    sceneBefore = new QGraphicsScene();
    sceneBefore->addPixmap(pixmap.scaled(ui->graphicsViewBefore->width(), ui->graphicsViewBefore->height(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->graphicsViewBefore->setScene(sceneBefore);
}

void DeadForm::loadPictureinViewCurrent(QPixmap pixmap)
{
    if(sceneCurrent != NULL)
    {
        sceneCurrent->clear();
        sceneCurrent = NULL;
    }

    sceneCurrent = new QGraphicsScene();
    sceneCurrent->addPixmap(imageServiceClass->markMovedObjects(pixmap).scaled(ui->graphicsViewCurrent->width(), ui->graphicsViewCurrent->height(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->graphicsViewCurrent->setScene(sceneCurrent);
}

void DeadForm::loadPictureinViewAfter(QPixmap pixmap)
{
    if(sceneAfter != NULL)
    {
        sceneAfter->clear();
        sceneAfter = NULL;
    }

    sceneAfter = new QGraphicsScene();
    sceneAfter->addPixmap(pixmap.scaled(ui->graphicsViewAfter->width(), ui->graphicsViewAfter->height(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->graphicsViewAfter->setScene(sceneAfter);
}

void DeadForm::loadPicturesToList()
{
    if(!imageList.isEmpty())
    {
        imageList.clear();
    }

    imageServiceClass->reset();

    QString selfilter = tr("JPEG (*.jpg *.jpeg);;PNG (*.png)");

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(selfilter);
    QStringList fileNames;
    if (dialog.exec())
    {
        fileNames = dialog.selectedFiles();
    }
    else
    {
        return;
    }

    foreach(QString fileName, fileNames)
    {
        if(fileName == NULL || fileName.toStdString() == "")
        {
            throw new std::string("File " + fileName.toStdString() + " was unable to load!");
        }
        imageList.append(new QPixmap(fileName));
    }

    for(int i = 0; i < bsRuns; i++)
    {
        foreach(QPixmap *image, imageList)
        {
        imageServiceClass->feedBackgroundSubtractor(*(image));
        }
    }

    loadPicturesinView();
}

void DeadForm::setMinContourSize(int value)
{
    imageServiceClass->setMinContoursize(value);
}

void DeadForm::setThickness(int value)
{
    imageServiceClass->setThickness(value);
}

void DeadForm::setBSRuns(int value)
{
    bsRuns = value;
}

void DeadForm::rotateImagesLeft()
{
    if(!imageList.isEmpty())
    {
        imagePositionCounter--;
        loadPicturesinView();
    }
}

void DeadForm::rotateImagesRight()
{
    if(!imageList.isEmpty())
    {
        imagePositionCounter++;
        loadPicturesinView();
    }
}
