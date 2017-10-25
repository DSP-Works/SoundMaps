#ifndef QPORTAUDIORECORDER_H
#define QPORTAUDIORECORDER_H

#include <QObject>
class QPortAudioRecorderPrivate;
class QPortAudioRecorder : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(int device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(ulong frameLength READ frameLength WRITE setFrameLength NOTIFY frameLengthChanged)
    Q_PROPERTY(double sampleRate READ sampleRate WRITE setSampleRate NOTIFY sampleRateChanged)
    Q_PROPERTY(double latency READ latency)
    Q_PROPERTY(double streamTimestamp READ streamTimestamp NOTIFY streamTimestampChanged)
    Q_PROPERTY(QStringList supportedSampleRates READ supportedSampleRates NOTIFY supportedSampleRatesChanged)
public:
    explicit QPortAudioRecorder(QObject *parent = nullptr);
    Q_INVOKABLE QStringList inputDevices() const;
    Q_INVOKABLE bool isInitialized() const;
    QStringList supportedSampleRates() const;
    int device() const;
    bool active() const;
    double sampleRate() const;
    double latency() const;
    double streamTimestamp() const;
    ulong frameLength() const;
public slots:
    Q_INVOKABLE void toggle();
    Q_INVOKABLE bool reset();
    Q_INVOKABLE int record();
    Q_INVOKABLE int stop();
    void setSampleRate(double sampleRate);
    void setFrameLength(ulong frame);
    void setDevice(int index);
signals:
    void frameLengthChanged(ulong);
    void sampleRateChanged(double);
    void deviceChanged(int);
    void activeChanged(bool);
    void streamTimestampChanged(double);
    void onError(const QString&) const;
    void onBufferReady(float*, ulong) const;
    void supportedSampleRatesChanged(const QStringList&);
private slots:
    void bufferReady(const void*, void*, ulong);
private:
    Q_DECLARE_PRIVATE(QPortAudioRecorder)
    Q_DISABLE_COPY(QPortAudioRecorder)
    QPortAudioRecorderPrivate* d_ptr;
};

#endif // QPORTAUDIORECORDER_H
