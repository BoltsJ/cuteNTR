/* Copyright (C) 2017  Joseph R. Nosie

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "ntr.h"
#include <iostream>
#include <QFile>

Ntr::Ntr(QObject *parent) : QObject(parent)
{
    cmd_sock = new QTcpSocket(this);
    rcv_sock = new QUdpSocket(this);
}

quint16 Ntr::dsPort = 8000;

void Ntr::set3DSip(QString ip)
{
    dsIP = ip;
}

bool Ntr::initStream()
{
    cmd_sock->connectToHost(dsIP, 8000);
    if(!cmd_sock->waitForConnected(5000)) {
        std::cerr << "Failed to connect!\n";
        return false;
    }
    cmd_sock->open(QIODevice::ReadWrite);
    std::cerr << "Connected!\n";

    /* Send the command to start streaming
     * This particular packet is derived from the NTRViewer source
     */
    sendPacket(0, 901, (const uint32_t[]){ (1<<8)|5, 80, 105*1024*1024/8, 0 }, 4);
    cmd_sock->close();
    QThread::QThread::sleep(3);
    cmd_sock->connectToHost(dsIP, 8000);
    if(!cmd_sock->waitForConnected(5000)) {
        std::cerr << "Failed to reconnect!\n";
        return false;
    }
    std::cerr << "Successfully initialized stream!\n";
    cmd_sock->close();
    QThread::QThread::sleep(3);

    if (!rcv_sock->bind(QHostAddress::Any, 8001)) {
        std::cerr << "Failed to bind socket!\n";
        return false;
    }

    for (int i = 0; i < 100; ++i) {
        QFile file(QString("%1.jpg").arg(i));
        file.open(QIODevice::WriteOnly);

        QByteArray data = readJPEG();
        while (data.length() == 0)
            data = readJPEG();

        file.write(data);
        file.close();
    }

    std::cerr << "Finished.\n";
    return true;
}

QByteArray Ntr::readJPEG()
{
    QByteArray jpeg;
    QByteArray buf(2000, '\0');
    int r;

    int cur_id, expkt = 0;
    rcv_sock->waitForReadyRead();
    r = rcv_sock->readDatagram(buf.data(), 2000, &dsIP, &dsPort);
    if (r <= 0) throw(0);
    buf.truncate(r);
    cur_id = buf.at(0);
    do {
        jpeg.append(buf.right(r-4));
        if ((buf.at(1)&0xf0)==0x10) {
            std::cerr << "Breaking\n";
            break;
        }
        rcv_sock->waitForReadyRead();
        buf.resize(2000);
        r = rcv_sock->readDatagram(buf.data(), 2000, &dsIP, &dsPort);
        if (r <= 0) throw(0);
        buf.truncate(r);
        ++expkt;
        if (expkt != buf.at(3)) {
            std::cerr << "Expected packet " << expkt << ", but got "
                << (int)buf[3] << '\n';
            return 0;
        }
    } while (buf.at(0) == cur_id);
    std::cerr << "Frame done\n";

    if (jpeg.at(0) != (char)0xff || jpeg.at(1) != (char)0xd8) {
        std::cerr << "Dropping frame!\n";
        return 0;
    }

    return jpeg;
}

void Ntr::sendPacket(uint32_t type, uint32_t cmd, const uint32_t args[], uint32_t nargs)
{
    char buf[84];
    for (int i = 0; i < 84; ++i) buf[i] = 0;
    uint32_t magic = 0x12345678;
    memcpy(buf, &magic, sizeof(magic));
    ((uint32_t*)buf)[1] = 1;
    ((uint32_t*)buf)[2] = type;
    ((uint32_t*)buf)[3] = cmd;
    for (uint32_t i = 0; i < nargs; ++i) {
        ((uint32_t*)buf)[i+4] = args[i];
    }
    cmd_sock->write((char*)buf, 84);
    cmd_sock->flush();
}
