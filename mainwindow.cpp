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
#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace {
const char* CFG_IP = "ipAddress";
const char* DEF_IP = "255.255.255.255";
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    s(qApp->applicationName())
{
    ui->setupUi(this);
    ui->dsIP->setText(s.value(CFG_IP, DEF_IP).toString());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    emit sendDSIp(QHostAddress(ui->dsIP->text()));
    emit initStream();
    s.setValue(CFG_IP, ui->dsIP->text());
}
