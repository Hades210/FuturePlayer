#ifndef PACKETBUFFER_H
#define PACKETBUFFER_H

#include "packet.h"
#include <QMutex>
#include <QList>

class PacketBuffer : private QList<Packet>
{
    static int backwardPackets;
public:
    static void setBackwardPackets(int backwardPackets)
    {
        PacketBuffer::backwardPackets = backwardPackets;
    }

    bool seekTo(double seekPos, bool backward);
    void clear(); //Thread-safe

    void put(const Packet &packet); //Thread-safe
    Packet fetch();

    void clearBackwards();

    inline bool isEmpty() const
    {
        return QList<Packet>::isEmpty();
    }

    inline bool canFetch() const
    {
        return remainingPacketsCount() > 0;
    }
    inline int remainingPacketsCount() const
    {
        return packetsCount() - m_pos;
    }
    inline int packetsCount() const
    {
        return count();
    }

    inline double firstPacketTime() const
    {
        return begin()->ts;
    }
    inline double currentPacketTime() const
    {
        return at(m_pos).ts;
    }
    inline double lastPacketTime() const
    {
        return (--end())->ts;
    }

    inline double remainingDuration() const
    {
        return m_remainingDuration;
    }
    inline double backwardDuration() const
    {
        return m_backwardDuration;
    }

    inline qint64 remainingBytes() const
    {
        return m_remainingBytes;
    }
    inline qint64 backwardBytes() const
    {
        return m_backwardBytes;
    }

    inline void lock()
    {
        m_mutex.lock();
    }
    inline void unlock()
    {
        m_mutex.unlock();
    }
private:
    double m_remainingDuration = 0.0, m_backwardDuration = 0.0;
    qint64 m_remainingBytes = 0, m_backwardBytes = 0;
    QMutex m_mutex;
    int m_pos = 0;
};

#endif // PACKETBUFFER_H
