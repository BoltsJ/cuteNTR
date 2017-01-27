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
#include "streamworker.h"

namespace {
const char* CFG_IP = "ipAddress";
}

StreamWorker::StreamWorker() :
    s(qApp->applicationName())
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
        emit streamFailed();
        return;
    }
    forever {
        QByteArray data;
        int ret = -1;
        while (ret == -1) {
            data.clear();
            ret = readJPEG(data);
        }
        QPixmap pixmap;
        pixmap.loadFromData(data);
        if (ret == 1) {
            emit topImageReady(pixmap);
        } else if (ret == 0) {
            emit botImageReady(pixmap);
        } else {
            break;
        }
    }
    rcv_sock->close();
    qWarning() << "Stream disconnected";
    emit streamFailed();
}

int StreamWorker::readJPEG(QByteArray &jpeg)
{
    QHostAddress dsIP(s.value(CFG_IP).toString());
    quint16 dsPort = 8000;
    QByteArray buf(2000, '\0');
    int r;

    int cur_id, expkt = 0;
    rcv_sock->waitForReadyRead();
    r = rcv_sock->readDatagram(buf.data(), 2000, &dsIP, &dsPort);
    if (r < 0) return -2;
    buf.truncate(r);
    cur_id = buf.at(0);
    do {
        jpeg.append(buf.right(r-4));
        if ((buf.at(1)&0xf0)==0x10) {
            break;
        }
        rcv_sock->waitForReadyRead();
        buf.resize(2000);
        r = rcv_sock->readDatagram(buf.data(), 2000, &dsIP, &dsPort);
        if (r < 0) return -2;
        buf.truncate(r);
        ++expkt;
        if (expkt != buf.at(3)) {
            return -1;
        }
    } while (buf.at(0) == cur_id);

    if (jpeg.left(2) != QByteArray("\xff\xd8") ||
            jpeg.right(2) != QByteArray("\xff\xd9")) {
        return -1;
    }

    return (buf.at(1)&0x0f);
}