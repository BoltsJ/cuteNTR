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

#include <QHostAddress>
#include <QLocalSocket>
#include <QObject>
#include <QSettings>
#include <QThread>
#include <QVector>
#include <QtNetwork>
#include <stdint.h>

class Ntr : public QObject
{
    Q_OBJECT
public:
    explicit Ntr(QObject *parent = 0);
    bool start3DSStream();

signals:
    void streamStarted();
    void streamFailed();

public slots:
    void initStream();
    void writeNFCPatch(int type);

private:
    void sendPacket(uint32_t type, uint32_t cmd,
            QVector<uint32_t> args, uint32_t len);

    QSettings s;
    QTcpSocket *cmd_sock;
};

#endif // NTR_H