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

Ntr::Ntr(QObject *parent) : QObject(parent)
{ }

void Ntr::set3DSip(QString ip)
{
    dsIP = ip;
}

bool Ntr::initStream()
{
    sock.connectToHost(dsIP, 8000);
    if(!sock.waitForConnected(5000)) {
        std::cerr << "Failed to connect!\n";
        return false;
    }
    std::cerr << "Connected!\n";

    /* Send the command to start streaming
     * This particular packet is derived from the NTRViewer source
     */
    sendPacket(0, 901, (const uint32_t[]){ (1<<8)|5, 80, 101*1024*1024/8, 0 }, 4);
    QThread::QThread::sleep(3);
    sock.disconnectFromHost();
    sock.close();
    QThread::QThread::sleep(3);
    sock.connectToHost(dsIP, 8000);
    if(!sock.waitForConnected(5000)) {
        std::cerr << "Failed to reconnect!\n";
        return false;
    }
    std::cerr << "Success!\n";
    return true;
}

void Ntr::sendPacket(uint32_t type, uint32_t cmd, const uint32_t args[], uint32_t nargs)
{
    char buf[84];
    for (int i = 0; i < 84; ++i) buf[i] = 0;
    ((uint32_t*)buf)[0] = 0x12345678;
    ((uint32_t*)buf)[1] = 1;
    ((uint32_t*)buf)[2] = type;
    ((uint32_t*)buf)[3] = cmd;
    for (uint32_t i = 0; i < nargs; ++i) {
        ((uint32_t*)buf)[i+4] = args[i];
    }
    sock.write((char*)buf, 84);
    sock.flush();
}

int Ntr::receivePacket(char *buf, int length)
{
    int idx = 0;
    do {
        int len = sock.read(buf, length);
        if (len == 0) {
            return 0;
        }
        idx += len;
    } while (idx < length);
    return length;
}
