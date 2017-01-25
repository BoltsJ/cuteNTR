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
#include <QFile>
#include <QThread>
#include "mainwindow.h"
#include "ntr.h"
#include "streamwindow.h"
#include "streamworker.h"

void messageHandler(QtMsgType t, const QMessageLogContext &c, const QString &m);

const QString logfile = QStandardPaths::writableLocation(
            QStandardPaths::CacheLocation)+"/cutentr.log";

int main(int argc, char *argv[])
{
    QFile file(logfile);
    file.open(QIODevice::WriteOnly);
    QTextStream(&file) << "-- " << QDateTime::currentDateTime().toString()
        << " --\n";
    file.close();

    qInstallMessageHandler(messageHandler);

    QApplication a(argc, argv);
    a.setApplicationName("cutentr");
    a.setApplicationDisplayName("cuteNTR");
    a.setApplicationVersion("v0.1.0");

    MainWindow w;
    StreamWindow top(true);
    StreamWindow bot(false);

    top.setTitle("Top screen - cuteNTR");
    bot.setTitle("Bottom screen - cuteNTR");

    Ntr ntr;
    QThread *t = new QThread;
    StreamWorker stream;
    stream.moveToThread(t);

    QObject::connect(&w, SIGNAL(initStream()),
            &ntr, SLOT(initStream()));
    QObject::connect(&w, SIGNAL(sendNfcPatch(int)),
            &ntr, SLOT(writeNFCPatch(int)));
    QObject::connect(&w, SIGNAL(topScaleChanged(float)),
            &top, SLOT(setScale(float)));
    QObject::connect(&w, SIGNAL(botScaleChanged(float)),
            &bot, SLOT(setScale(float)));

    QObject::connect(&ntr, SIGNAL(streamStarted()),
            t, SLOT(start()));
    QObject::connect(&ntr, SIGNAL(streamStarted()),
            &top, SLOT(show()));
    QObject::connect(&ntr, SIGNAL(streamStarted()),
            &bot, SLOT(show()));
    QObject::connect(&ntr, SIGNAL(streamFailed()),
            &w, SLOT(disconnectedStream()));

    QObject::connect(t, SIGNAL(started()),
            &stream, SLOT(stream()));
    QObject::connect(t, SIGNAL(finished()),
            &w, SLOT(disconnectedStream()));

    QObject::connect(&stream, SIGNAL(topImageReady(QPixmap)),
            &top, SLOT(renderPixmap(QPixmap)));
    QObject::connect(&stream, SIGNAL(botImageReady(QPixmap)),
            &bot, SLOT(renderPixmap(QPixmap)));
    QObject::connect(&stream, SIGNAL(streamFailed()),
            &top, SLOT(hide()));
    QObject::connect(&stream, SIGNAL(streamFailed()),
            &bot, SLOT(hide()));
    QObject::connect(&stream, SIGNAL(streamFailed()),
            t, SLOT(quit()));

    w.show();

    return a.exec();
}

void messageHandler(QtMsgType t, const QMessageLogContext &c, const QString &m)
{
    QString suff;
    QFile file(logfile);
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream log(&file);
    if (c.function)
        suff = QString(" - [%1]").arg(c.function);
    switch(t) {
#if QT_VERSION >= 0x050500
    case QtInfoMsg:
#endif
    case QtDebugMsg:
        log << "[INFO] " << m << '\n';
        break;
    case QtWarningMsg:
        log << "[WARN] " << m << suff << '\n';
        break;
    case QtCriticalMsg:
        log << "[CRIT] " << m << suff << '\n';
        break;
    case QtFatalMsg:
        log << "[CRIT] " << m << suff << '\n';
        exit(1);
        break;
    }
    file.close();
}
