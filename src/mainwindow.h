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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

public slots:
    void disconnectedStream();

signals:
    void initStream();
    void sendNfcPatch(int);
    void topScaleChanged(double);
    void botScaleChanged(double);

private slots:
    void on_connectButton_clicked();
    void on_dsIP_returnPressed();
    void on_tScale_valueChanged(double scale);
    void on_bScale_valueChanged(double scale);
    void on_sendNfcPatch_clicked();

private:
    Ui::MainWindow *ui;
    QSettings s;
};

#endif // MAINWINDOW_H