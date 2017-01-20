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
#include <QApplication>
#include <QThread>
#include "mainwindow.h"
#include "ntr.h"
#include "streamwindow.h"
#include "streamworker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    StreamWindow s;

    Ntr ntr;
    QThread *t = new QThread;
    StreamWorker stream;
    stream.moveToThread(t);

    qRegisterMetaType<QHostAddress>("QHostAddress");
    QObject::connect(&w, &MainWindow::sendDSIp,
            &ntr, &Ntr::set3DSip);
    QObject::connect(&w, &MainWindow::sendDSIp,
            &stream, &StreamWorker::set3DSip);
    QObject::connect(&w, &MainWindow::initStream,
            &ntr, &Ntr::initStream);
    QObject::connect(&ntr, SIGNAL(streamStarted()),
            t, SLOT(start()));
    QObject::connect(t, SIGNAL(started()),
            &stream, SLOT(stream()));
    QObject::connect(&stream, SIGNAL(imageReady(QPixmap)),
            &s, SLOT(renderPixmap(QPixmap)));

    s.show();
    w.show();

    return a.exec();
}
