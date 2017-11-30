#ifndef PLAYER_H
#define PLAYER_H

#include <QTimer>
#include <QImage>
#include "demuxerthr.hpp"
#include "videothr.hpp"
#include "audiothr.h"
#include "packetbuffer.hpp"

enum
{
    SEEK_NOWHERE = -1,
    SEEK_STREAM_RELOAD = -2, /* Seeks to current position after stream reload */
    SEEK_REPEAT = -3
};

/*******************************************
 *
 * 播放器的统一接口
 ******************************************/



class LPlayer  : public QObject
{
    Q_OBJECT
public:
    LPlayer();
    virtual ~LPlayer() {}
    void play(const QString &);             // 播放
    void stop(bool quitApp = false);        // 停止
    void restart();
    inline bool canUpdatePosition() const
    {
        return canUpdatePos;
    }

    void chPos(double, bool updateGUI = true);

    void togglePause();
    void seek(double pos, bool allowAccurate = true);
    void chStream(const QString &s);
    void setSpeed(double);

    bool isPlaying() const;
    void loadSubsFile(const QString &fileName);
    inline QString getUrl() const
    {
        return url;
    }
    inline double getPos() const
    {
        return pos;
    }

    double frame_last_pts, frame_last_delay, audio_current_pts, audio_last_delay;
    bool doSilenceOnStart, canUpdatePos, paused, waitForData, flushVideo, flushAudio, muted, reload, nextFrameB, endOfStream, ignorePlaybackError;
    int seekTo, lastSeekTo, restartSeekTo, seekA, seekB, videoSeekPos, audioSeekPos;
    double vol[2], replayGain, zoom, pos, skipAudioFrame, videoSync, speed, subtitlesSync, subtitlesScale;
    int flip;
    bool rotate90, spherical, stillImage;
    QString url, newUrl, aRatioName;

public:
    void stopVThr();
    void stopAThr();
    inline void stopAVThr();

    void stopVDec();
    void stopADec();

public:
    DemuxerThr *demuxThr;
    VideoThr *vThr;
    AudioThr *aThr;

    PacketBuffer aPackets, vPackets, sPackets;

    int audioStream, videoStream, subtitlesStream;
    int choosenAudioStream, choosenVideoStream, choosenSubtitlesStream;
    QString choosenAudioLang, choosenSubtitlesLang;

    double maxThreshold, fps;

    bool quitApp, audioEnabled, videoEnabled, subtitlesEnabled, doSuspend, doRepeat, allowAccurateSeek;
    QTimer timTerminate;

signals:
    void frameSizeUpdate(int w, int h);
    void audioParamsUpdate(quint8 channels, quint32 sampleRate);
    void aRatioUpdate(double sar);
    void pixelFormatUpdate(const QByteArray &pixFmt);
    void chText(const QString &);
    void updateLength(int);
    void updatePos(int);
    void playStateChanged(bool);
    void setCurrentPlaying();
    void setInfo(const QString &, bool, bool);
    void updateCurrentEntry(const QString &, double);
    void playNext(bool playingError);
    void clearCurrentPlaying();
    void clearInfo();
    void quit();
    void resetARatio();
    void updateBitrateAndFPS(int a, int v, double fps = -1.0, double realFPS = -1.0, bool interlaced = false);
    void updateBuffered(qint64 backwardBytes, qint64 remainingBytes, double backwardSeconds, double remainingSeconds);
    void updateBufferedRange(int, int);
    void updateWindowTitle(const QString &t = QString());
    void updateImage(const QImage &img = QImage());
    void videoStarted();
    void uncheckSuspend();

};

#endif // PLAYER_H
