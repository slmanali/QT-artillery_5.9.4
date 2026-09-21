#include "capturethread.h"
#include <QDebug>
bool pause=false;
Q_DECLARE_METATYPE(cv::Mat);
//***************************************
#include <vlc/vlc.h>
uint8_t *videoBuffer = 0;
uint8_t *audioBuffer = 0;
unsigned int videoBufferSize = 0;
unsigned int audioBufferSize = 0;
char ff[]="rtsp://admin:12345@196.10.10.155:554";
char* rtspAddress = ff;
int done = 0;
libvlc_media_player_t *media_player = NULL;
libvlc_media_t *media=NULL;
libvlc_instance_t *vlcInstance;
// Audio prerender callback
void cbAudioPrerender (void* p_audio_data, uint8_t** pp_pcm_buffer , unsigned int size)
{
    // TODO: Lock the mutex
    //printf("cbAudioPrerender %i\n",size);
    //printf("atest: %lld\n",(long long int)p_audio_data);
    if (size > audioBufferSize || !audioBuffer)
    {
        printf("Reallocate raw audio buffer\n");
        if(audioBuffer) free(audioBuffer);
        audioBuffer = (uint8_t *)malloc(size);
        audioBufferSize = size;
    }
    *pp_pcm_buffer = audioBuffer;
}

// Audio postrender callback
void cbAudioPostrender(void* p_audio_data, uint8_t* p_pcm_buffer, unsigned int channels, unsigned int rate, unsigned int nb_samples, unsigned int bits_per_sample, unsigned int size, int64_t pts )
{
    //printf("cbAudioPostrender %i\n", size);
    // TODO: explain how data should be handled
    // TODO: Unlock the mutex
}

void cbVideoPrerender(void *p_video_data, uint8_t **pp_pixel_buffer, int size) {

       // Locking
    //printf("cbVideoPrerender %i\n",size);
    //printf("vtest: %lld\n",(long long int)p_video_data);
    if (size > videoBufferSize || !videoBuffer)
    {
        printf("Reallocate raw video buffer\n");
        if(audioBuffer) free(videoBuffer);
        videoBuffer = (uint8_t *)malloc(size);
        videoBufferSize = size;
    }
    *pp_pixel_buffer = videoBuffer;
}

void cbVideoPostrender(void *p_video_data, uint8_t *p_pixel_buffer, int width, int height, int pixel_pitch, int size, int64_t pts) {
    //printf("cbVideoPostrender %i\n",size);
   // Unlocking

}

static void handleEvent(const libvlc_event_t* pEvt, void* pUserData)
{
    libvlc_time_t time;
    switch(pEvt->type)
    {
    case libvlc_MediaPlayerTimeChanged:
        time = libvlc_media_player_get_time(media_player);
        printf("MediaPlayerTimeChanged %lld ms\n", (long long)time);
        break;
    case libvlc_MediaPlayerEndReached:
        printf ("MediaPlayerEndReached\n");
        done = 1;
        break;
    default:
        printf("%s\n", libvlc_event_type_name(pEvt->type));
    }
}
//***************************************
CaptureThread::CaptureThread(int index)
{
    capWebam.open(index);
    capWebam.set(CV_CAP_PROP_FPS,30);
    capWebam.set(CV_CAP_PROP_FRAME_WIDTH,720);
    capWebam.set(CV_CAP_PROP_FRAME_HEIGHT,576);
    if(!capWebam.isOpened()) return;
    QThread* t = new QThread();
    moveToThread(t);
    t->start();
    tmrTimer = new QTimer;

    qRegisterMetaType< cv::Mat >("cv::Mat");
    QObject::connect(tmrTimer, SIGNAL(timeout()),this, SLOT(captureFrame()));
    connect(this, SIGNAL(finished()), t, SLOT(quit()));
    tmrTimer->start(40);
}
//***************************************
CaptureThread::CaptureThread(QString video_path,cv::Size  rtspRes)
{
//    capWebam.open(video_path.toStdString());
//    capWebam.set(CV_CAP_PROP_FPS,30);
//    capWebam.set(CV_CAP_PROP_FRAME_WIDTH,rtspRes.width);
//    capWebam.set(CV_CAP_PROP_FRAME_HEIGHT,rtspRes.height);
//    if(!capWebam.isOpened()) return;
//    QThread* t = new QThread();
//    moveToThread(t);
//    t->start();
//    tmrTimer = new QTimer;

//    qRegisterMetaType< cv::Mat >("cv::Mat");
//    QObject::connect(tmrTimer, SIGNAL(timeout()),this, SLOT(captureFrame()));
//    connect(this, SIGNAL(finished()), t, SLOT(quit()));
//    tmrTimer->start(40);

    // VLC pointers
    void *pUserData = 0;

    rtspReso= rtspRes;
    char smem_options[1000];
    sprintf(smem_options
            , "#transcode{vcodec=RV24,acodec=s16l}:smem{"
             "video-prerender-callback=%lld,"
             "video-postrender-callback=%lld,"
             "audio-prerender-callback=%lld,"
             "audio-postrender-callback=%lld,"
             "audio-data=%lld,"
             "video-data=%lld},"
            , (long long int)(intptr_t)(void*)&cbVideoPrerender
            , (long long int)(intptr_t)(void*)&cbVideoPostrender
            , (long long int)(intptr_t)(void*)&cbAudioPrerender
            , (long long int)(intptr_t)(void*)&cbAudioPostrender
            , (long long int)100 //This would normally be useful data, 100 is just test data
            , (long long int)200); //Test data

    const char * const vlc_args[] = {
          "-I", "dummy", // Don't use any interface
          "--ignore-config", // Don't use VLC's config
         // "--extraintf=logger", // Log anything
          "--verbose=1", // Be verbose
          "--sout", smem_options // Stream to memory
           };

    // We launch VLC
    vlcInstance = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);

    media_player = libvlc_media_player_new(vlcInstance);
    libvlc_event_manager_t* eventManager = libvlc_media_player_event_manager(media_player);
    libvlc_event_attach(eventManager, libvlc_MediaPlayerTimeChanged, handleEvent, pUserData);
    libvlc_event_attach(eventManager, libvlc_MediaPlayerEndReached, handleEvent, pUserData);
    libvlc_event_attach(eventManager, libvlc_MediaPlayerPositionChanged, handleEvent, pUserData);

    media = libvlc_media_new_location(vlcInstance,video_path.toStdString().c_str() );

    //libvlc_video_set_format(mp, "RV24", 240, 320, 240 * 3 );

    // play the media_player
    libvlc_media_player_set_media(media_player, media);
    libvlc_media_player_play(media_player);
    QThread* t = new QThread();
    moveToThread(t);
    t->start();
    tmrTimer = new QTimer;

    qRegisterMetaType< cv::Mat >("cv::Mat");
    QObject::connect(tmrTimer, SIGNAL(timeout()),this, SLOT(captureFrame1()));
    tmrTimer->start(20);
}
//***************************************
void CaptureThread::run()
{
//    QObject::connect(tmrTimer, SIGNAL(timeout()), this, SLOT(captureFrame()));

    exec();
}
//***************************************
void CaptureThread::captureFrame()
{
    if(capWebam.isOpened())
    {
        capWebam.read(capturedFrame);
        cv::Mat ff;
        // = capturedFrame + cv::Scalar(-50, -50, -50); //decrease the brightness by 75 units
        capturedFrame.copyTo(ff);
        emit frameCaptured(ff);
    }
    else
    {
        this->quit();
        emit NULL;
    }

}
//***************************************
void CaptureThread::captureFrame1()
{
    if (videoBuffer)
    {
        // CV_8UC3 = 8 bits, 3 chanels
        cv::Mat frame = cv::Mat(rtspReso, CV_8UC3, videoBuffer);
//        qDebug() << "Ip camera";
        if(frame.empty())
        {
            qDebug() << "frame is empty";
            emit NULL;
        }
        cv::Mat ff;
        frame.copyTo(ff);
        emit frameCaptured(ff);
    }

    else
    {
        this->quit();
        emit NULL;
    }

}
//***************************************
void CaptureThread::release_ip()
{
//    qDebug() << "release Ip camera";
    libvlc_media_release(media);
    libvlc_media_player_stop(media_player);
    libvlc_release(vlcInstance);
}
//***************************************
void CaptureThread::pause_ip()
{
    if(!pause)
    {
        qDebug() << "Pause Ip camera";
        libvlc_media_player_pause(media_player);
        pause=true;
    }
    else
    {
        qDebug() << "Play Ip camera";
        libvlc_media_player_play(media_player);
        pause=false;
    }
}
//***************************************
void CaptureThread::release_cam()
{
    qDebug() << "release camera";
    capWebam.release();
}
