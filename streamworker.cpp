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
#include <iostream>
#include "streamworker.h"

StreamWorker::StreamWorker()
{
    rcv_sock = new QUdpSocket(this);
}

StreamWorker::~StreamWorker()
{
    rcv_sock->close();
    delete rcv_sock;
}

void StreamWorker::stream()
{
    if (!rcv_sock->bind(QHostAddress::Any, 8001)) {
        // emit err
        return;
    }
    forever {
        QByteArray data = readJPEG();
        while (data.length() == 0) {
            data = readJPEG();
        }
        QPixmap pixmap;
        pixmap.loadFromData(data);
        emit imageReady(pixmap);
    }
}

void StreamWorker::set3DSip(QHostAddress ip)
{
    dsIP = ip;
}

QByteArray StreamWorker::readJPEG()
{
    quint16 dsPort = 8000;
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
