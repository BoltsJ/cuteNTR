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
}

void Ntr::writeNFCPatch()
{
    QHostAddress dsIP(s.value(CFG_IP).toString());
    cmd_sock->connectToHost(dsIP, 8000);
    if(!cmd_sock->waitForConnected(5000)) {
        std::cerr << "Failed to connect!\n";
        return;
    }
    uint32_t args[17];
    args[0] = 0x1a;
    args[1] = 0x105ae4;
    args[2] = 2;
    args[16] = 2;
    sendPacket(1, 10, args, 17);
    cmd_sock->write(QByteArray((const char[]){ 0x70, 0x47 }, 2));
    cmd_sock->flush();
}

bool Ntr::start3DSStream()
{
    QHostAddress dsIP(s.value(CFG_IP).toString());
    cmd_sock->connectToHost(dsIP, 8000);
    if(!cmd_sock->waitForConnected(5000)) {
        std::cerr << "Failed to connect!\n";
        return false;
    }
    //cmd_sock->open(QIODevice::ReadWrite);
    std::cerr << "Connected!\n";

    /* Send the command to start streaming
     * This particular packet is derived from the NTRViewer source
     */
    int mode = s.value(CFG_PRIMODE, DEF_PRIMODE).toInt();
    int priortyfactor = s.value(CFG_PRIFACT, DEF_PRIFACT).toInt();
    int jpegquality = s.value(CFG_JPGQUAL, DEF_JPGQUAL).toInt();
    int qosvalue = s.value(CFG_QOSVAL, DEF_QOSVAL).toInt();
    int qosbyte = qosvalue * 1024 * 1024 / 8;
    uint32_t args[4];
    args[0] = (mode<<8)|priortyfactor;
    args[1] = jpegquality;
    args[2] = qosbyte;
    args[3] = 0;
    sendPacket(0, 901, args, 4);
    cmd_sock->close();
    QThread::QThread::sleep(3);
    cmd_sock->connectToHost(dsIP, 8000);
    if(!cmd_sock->waitForConnected(5000)) {
        std::cerr << "Failed to reconnect!\n";
        return false;
    }
    std::cerr << "Successfully initialized stream!\n";
    cmd_sock->close();
    writeNFCPatch();

    std::cerr << "Finished.\n";
    return true;
}

void Ntr::sendPacket(uint32_t type, uint32_t cmd, const uint32_t args[],
        uint32_t nargs)
{
    char buf[84];
    memset((void*)buf, 0, 84);
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
