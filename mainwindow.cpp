#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WId winid = ui->wgVideo->winId();
    player = new TPlayer(winid);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Play(void)
{
    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;

    /* Initialize GStreamer */
    gst_init(NULL, NULL);

    qDebug() << "gst_init";
    /* Build the pipeline */
    pipeline = gst_parse_launch("playbin uri=file:///C:/gstreamer/1.0/x86_64/bin/test.mp4", NULL);

    qDebug() << "gst_parse_launch";
    /* Start playing */
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    qDebug() << "gst_element_set_state";
    /* Wait until error or EOS */
    bus = gst_element_get_bus(pipeline);
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, (GstMessageType)((int)GST_MESSAGE_ERROR | (int)GST_MESSAGE_EOS));
    /* Free resources */
    if (msg != NULL)
        gst_message_unref(msg);
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
}

void MainWindow::on_pbPlay_clicked()
{
    //Play();
    //g_idle_add(player->st_play_start, this);
    player->play_start(&player->play_obj);
}

void MainWindow::on_pbStop_clicked()
{
}

void MainWindow::on_pbPrev_clicked()
{

}

void MainWindow::on_pbNext_clicked()
{

}

void MainWindow::on_pbOpen_clicked()
{
    QFileDialog filedialog(this, tr("Select File"),
                           tr("C:\\Users"),
                           tr("Videos (*.mp4 *.mkv *.avi *.wmv);; All Files (*.*)"));

    if(filedialog.exec())
    {
        ui->lePath->setText(filedialog.selectedFiles().at(0));
        player->video_cnt = 1;

        QString strFile = filedialog.selectedFiles().at(0);
        QByteArray byteArray = strFile.toLocal8Bit();
        char * src = byteArray.data();
        int strLen = strFile.length();
        player->video_list[0] = (char *)malloc(strLen+1);
        strcpy( player->video_list[0] , src);
        player->video_list[0][strLen] = 0;
        qDebug() << player->video_list[0];
    }
/*
    QDirIterator iterDir(strDir, strFilters, QDir::Files | QDir::NoSymLinks,
                         QDirInterator::Subdirectories);
*/
}

void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{
}
