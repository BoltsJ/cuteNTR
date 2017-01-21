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
    a.setApplicationName("cutentr");
    a.setApplicationDisplayName("cuteNTR");
    a.setApplicationVersion("v0.0.0");

    MainWindow w;
    StreamWindow top;
    StreamWindow bot;

    top.resize(400,240);
    top.setMinimumSize(QSize(400,240));
    top.setMaximumSize(QSize(400,240));
    top.setTitle("Top screen - cuteNTR");
    bot.resize(320,240);
    bot.setMinimumSize(QSize(320,240));
    bot.setMaximumSize(QSize(320,240));
    bot.setTitle("Bottom screen - cuteNTR");

    Ntr ntr;
    QThread *t = new QThread;
    StreamWorker stream;
    stream.moveToThread(t);

    QObject::connect(&w, SIGNAL(initStream()),
            &ntr, SLOT(initStream()));
    QObject::connect(&ntr, SIGNAL(streamStarted()),
            t, SLOT(start()));
    QObject::connect(t, SIGNAL(started()),
            &stream, SLOT(stream()));
    QObject::connect(&stream, SIGNAL(topImageReady(QPixmap)),
            &top, SLOT(renderPixmap(QPixmap)));
    QObject::connect(&stream, SIGNAL(botImageReady(QPixmap)),
            &bot, SLOT(renderPixmap(QPixmap)));

    top.show();
    bot.show();
    w.show();

    return a.exec();
}
