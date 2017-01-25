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
#include <QFile>
#include <iostream>
#include "ntr.h"

namespace {
const char* CFG_IP      = "ipAddress";
const char* CFG_PRIMODE = "priorityMode";
const bool  DEF_PRIMODE = true;
const char* CFG_PRIFACT = "priorityFactor";
const int   DEF_PRIFACT = 5;
const char* CFG_JPGQUAL = "jpegQuality";
const int   DEF_JPGQUAL = 80;
const char* CFG_QOSVAL  = "qosValue";
const int   DEF_QOSVAL  = 105;
}

Ntr::Ntr(QObject *parent) :
    QObject(parent),
    s(qApp->applicationName())
{
    cmd_sock = new QTcpSocket(this);
}

void Ntr::initStream()
{
    if (start3DSStream())
        emit streamStarted();
    else
        emit streamFailed();
}

void Ntr::writeNFCPatch(int type)
{
    qInfo() << "Writing NFC patch...";
    QHostAddress dsIP(s.value(CFG_IP).toString());
    cmd_sock->connectToHost(dsIP, 8000);
    if(!cmd_sock->waitForConnected(5000)) {
        qInfo() << "Failed to connect!";
        return;
    }
    uint32_t pid;
    uint32_t offset;
    QByteArray patch;
    switch(type) {
        case 1: // Pokemon S&M
            pid = 0; // Write a helper function
            offset = 0x3e14c0;
            patch.append("\xe3\xa0\x10\x00", 4);
        default:
            pid = 0x1a;
            offset = 0x105ae4;
            patch.append("\x70\x47", 2);
    }
    uint32_t len = patch.length();
    sendPacket(1, 10, {pid, offset, len}, len);
    cmd_sock->write(patch);
    cmd_sock->flush();
    cmd_sock->close();
    qInfo() << len << " bytes written.";
}

bool Ntr::start3DSStream()
{
    QHostAddress dsIP(s.value(CFG_IP).toString());
    cmd_sock->connectToHost(dsIP, 8000);
    if(!cmd_sock->waitForConnected(5000)) {
        qWarning() << "Failed to connect!";
        return false;
    }
    qInfo() << "Connected!";

    /* Send the command to start streaming
     * This particular packet is derived from the NTRViewer source
     */
    int mode = s.value(CFG_PRIMODE, DEF_PRIMODE).toInt();
    int prifact = s.value(CFG_PRIFACT, DEF_PRIFACT).toInt();
    uint32_t pri = (mode<<8)|prifact;
    uint32_t jpegq = s.value(CFG_JPGQUAL, DEF_JPGQUAL).toInt();
    uint32_t qosvalue = s.value(CFG_QOSVAL, DEF_QOSVAL).toInt() << 17;

    sendPacket(0, 901, {pri, jpegq, qosvalue, 0}, 0);
    cmd_sock->close();
    QThread::QThread::sleep(3);
    cmd_sock->connectToHost(dsIP, 8000);
    if(!cmd_sock->waitForConnected(5000)) {
        qWarning() << "Failed to reconnect!";
        return false;
    }
    qInfo() << "Successfully initialized stream!";
    cmd_sock->close();

    return true;
}

void Ntr::sendPacket(uint32_t type, uint32_t cmd, QVector<uint32_t> args,
        uint32_t len)
{
    char buf[84];
    memset((void*)buf, 0, 84);
    uint32_t magic = 0x12345678;
    memcpy(buf, &magic, sizeof(magic));
    ((uint32_t*)buf)[1] = 1;
    ((uint32_t*)buf)[2] = type;
    ((uint32_t*)buf)[3] = cmd;
    for (int i = 0; i < args.length(); ++i)
        ((uint32_t*)buf)[i+4] = args.at(i);
    ((uint32_t*)buf)[20] = len;
    cmd_sock->write((char*)buf, 84);
    cmd_sock->flush();
}
