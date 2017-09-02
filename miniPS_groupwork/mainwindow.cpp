#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("miniPS");
    pImageEdit1= new ImageEdit1();
    pImageEdit2= new ImageEdit2();
    pImageEdit3= new ImageEdit3();
}

MainWindow::~MainWindow()
{
    delete image;
    delete pImageEdit1;
    delete pImageEdit2;
    delete pImageEdit3;
    delete ui;

}

void MainWindow::on_pushButton_open_clicked()//load image
{
    image= new QImage();//allocate memory to pointer "image"
    imagepath=QFileDialog::getOpenFileName(this,tr("open file"),"/",tr("images(*.png *.jpg)"));
    image->load(imagepath);
    pixmap= QPixmap::fromImage(*image);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio));
}

void MainWindow::on_pushButton_save_clicked()
{
    QString ipath=QFileDialog::getSaveFileName(this,tr("save file"),"/",tr("PNG(*.png);;JPG(*.jpg)"));
    image->save(ipath);

}

void MainWindow::on_pushButton_E1_clicked()
{
    pImageEdit3->effect1(image);
    pixmap= QPixmap::fromImage(*image);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio));
}

void MainWindow::on_pushButton_E2_clicked()
{
    pImageEdit3->effect2(image);
    pixmap= QPixmap::fromImage(*image);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio));
}

void MainWindow::on_pushButton_E3_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    QPushButton *redButton = msgBox.addButton(tr("Red"), QMessageBox::ActionRole);
    QPushButton *greenButton = msgBox.addButton(tr("Green"),QMessageBox::ActionRole);
    QPushButton *blueButton = msgBox.addButton(tr("Blue"),QMessageBox::ActionRole);
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.exec();

if (msgBox.clickedButton() == redButton)
{
    QImage test=*image;
        QRgb val;
        QColor oldcolor;
        for(int x=0; x<test.width();x++){
            for(int y=0;y<test.height();y++){
                oldcolor=QColor(test.pixel(x,y));
                int ave=(oldcolor.red()+oldcolor.green()+oldcolor.blue())/3;
                val=qRgb(oldcolor.red(),ave,ave);
                test.setPixel(x,y,val);
            }
        }
        *image=test;
        ui->label->setFixedSize(test.size());
        ui->label->setPixmap(QPixmap::fromImage(test));
        // red
    }
    else if (msgBox.clickedButton() == greenButton)
{
    QImage test=*image;
        QRgb val;
        QColor oldcolor;
        for(int x=0; x<test.width();x++){
            for(int y=0;y<test.height();y++){
                oldcolor=QColor(test.pixel(x,y));
                int ave=(oldcolor.red()+oldcolor.green()+oldcolor.blue())/3;
                val=qRgb(ave,oldcolor.green(),ave);
                test.setPixel(x,y,val);
            }
        }
        *image=test;
        ui->label->setFixedSize(test.size());
        ui->label->setPixmap(QPixmap::fromImage(test));
    // green
}
else if (msgBox.clickedButton() == blueButton)
{
QImage test=*image;
    QRgb val;
    QColor oldcolor;
    for(int x=0; x<test.width();x++){
        for(int y=0;y<test.height();y++){
            oldcolor=QColor(test.pixel(x,y));
            int ave=(oldcolor.red()+oldcolor.green()+oldcolor.blue())/3;
            val=qRgb(ave,ave,oldcolor.blue());
            test.setPixel(x,y,val);
        }
    }
    *image=test;
    ui->label->setFixedSize(test.size());
    ui->label->setPixmap(QPixmap::fromImage(test));
// blue
}
}

void MainWindow::on_pushButton_E4_clicked()
{
    QImage test=*image;
        QRgb val;
        QColor oldcolor;
        for(int x=0; x<test.width();x++){
            for(int y=0;y<test.height();y++){
                oldcolor=QColor(test.pixel(x,y));
                val=qRgb(255-oldcolor.red(),255-oldcolor.green(),255-oldcolor.blue());
                test.setPixel(x,y,val);
            }
        }
        *image=test;
        ui->label->setFixedSize(test.size());
        ui->label->setPixmap(QPixmap::fromImage(test));
}
void MainWindow::on_pushButton_E5_clicked()
{

    QImage * newImage = new QImage(* image);

        int kernel [3][3]= {{0,-1,0},
                            {-1,5,-1},
                            {0,-1,0}};
        int kernelSize = 3;
        int sumKernel = 1;
        int r,g,b;
        QColor color;

        for(int x=kernelSize/2; x<newImage->width()-(kernelSize/2); x++){
            for(int y=kernelSize/2; y<newImage->height()-(kernelSize/2); y++){

                r = 0;
                g = 0;
                b = 0;

                for(int i = -kernelSize/2; i<= kernelSize/2; i++){
                    for(int j = -kernelSize/2; j<= kernelSize/2; j++){
                        color = QColor(image->pixel(x+i, y+j));
                        r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                        g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                        b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                    }
                }

                r = qBound(0, r/sumKernel, 255);
                g = qBound(0, g/sumKernel, 255);
                b = qBound(0, b/sumKernel, 255);

                newImage->setPixel(x,y, qRgb(r,g,b));

            }
        }
    pixmap= QPixmap::fromImage(*newImage);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio));
}

void MainWindow::on_pushButton_E6_clicked()
{
    QImage * newImage = new QImage(*image);
    int kernel [5][5]= {{0,0,1,0,0},
                        {0,1,3,1,0},
                        {1,3,7,3,1},
                        {0,1,3,1,0},
                        {0,0,1,0,0}};
    int kernelSize = 5;
    int sumKernel = 27;
    int r,g,b;
    QColor color;

    for(int x=kernelSize/2; x<newImage->width()-(kernelSize/2); x++){
        for(int y=kernelSize/2; y<newImage->height()-(kernelSize/2); y++){

            r = 0;
            g = 0;
            b = 0;

            for(int i = -kernelSize/2; i<= kernelSize/2; i++){
                for(int j = -kernelSize/2; j<= kernelSize/2; j++){
                    color = QColor(image->pixel(x+i, y+j));
                    r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                    g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                    b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                }
            }

            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));

        }
    }
    pixmap= QPixmap::fromImage(*newImage);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio));
}
