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
#ifndef NTR_H
#define NTR_H

#include <QObject>
#include <QHostAddress>
#include <QtNetwork/QTcpSocket>
#include <QThread>

class Ntr : public QObject
{
    Q_OBJECT
public:
    explicit Ntr(QObject *parent = 0);
    void set3DSip(QString ip);
    bool initStream();

signals:

public slots:

private:
    void sendPacket(uint32_t type, uint32_t cmd, const uint32_t args[], uint32_t len);
    int receivePacket(char* buf, int len);

    QTcpSocket sock;
    QHostAddress dsIP;
};

#endif // NTR_H
