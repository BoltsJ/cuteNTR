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
#include "streamwindow.h"

StreamWindow::StreamWindow(QWindow *parent) :
    QWindow(parent),
    m_update_pending(false)
{
    create();
    m_backingStore = new QBackingStore(this);
}

void StreamWindow::exposeEvent(QExposeEvent *)
{
    if (isExposed()) {
        renderNow();
    }
}

void StreamWindow::resizeEvent(QResizeEvent *resizeEvent)
{
    m_backingStore->resize(resizeEvent->size());
    if (isExposed())
        renderNow();
}

void StreamWindow::renderNow()
{
    if (!isExposed()) return;
    QRect rect(0, 0, width(), height());
    m_backingStore->beginPaint(rect);

    QPaintDevice *device = m_backingStore->paintDevice();
    QPainter painter(device);

    painter.fillRect(0, 0, width(), height(), Qt::gray);
    render(&painter);

    m_backingStore->endPaint();
    m_backingStore->flush(rect);
}

void StreamWindow::render(QPainter *painter)
{
    QTransform xform(0, -1, 1, 0, 0, 0);
    painter->drawPixmap(0,0,pixmap.transformed(xform));
}

void StreamWindow::renderLater()
{
    if (!m_update_pending) {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void StreamWindow::renderPixmap(QPixmap pixmap)
{
    this->pixmap = pixmap;
    renderLater();
}

bool StreamWindow::event(QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest) {
        m_update_pending = false;
        renderNow();
        return true;
    }
    return QWindow::event(event);
}
