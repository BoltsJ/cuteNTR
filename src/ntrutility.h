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
#ifndef NTRUTILITY_H
#define NTRUTILITY_H

#include <QObject>
#include <QtDebug>
#include "ntr.h"

class NtrUtility : public QObject
{
    Q_OBJECT
public:
    explicit NtrUtility(QObject *parent = 0);

    uint32_t getPid(QString pname);

signals:
    void ntrCommand(Ntr::Command c, QVector<uint32_t> a={}, uint32_t l=0,
                    QByteArray d="");

public slots:
    void writeNfcPatch(int type);
    void handleInfo(QByteArray info);

private:
    QStringList pidlist;
    QString lastmessage;
};

#endif // NTRUTILITY_H
