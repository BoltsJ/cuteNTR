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
const char* CFG_IP      = "ipAddress";
const char* DEF_IP      = "255.255.255.255";
const char* CFG_JPGQUAL = "jpegQuality";
const int   DEF_JPGQUAL = 80;
const char* CFG_PRIFACT = "priorityFactor";
const int   DEF_PRIFACT = 5;
const char* CFG_PRIMODE = "priorityMode";
const bool  DEF_PRIMODE = true;
const char* CFG_QOSVAL  = "qosValue";
const int   DEF_QOSVAL  = 105;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    s(qApp->applicationName())
{
    ui->setupUi(this);

    // Initialize Options
    ui->dsIP->setText(s.value(CFG_IP, DEF_IP).toString());
    ui->qosValue->setValue(s.value(CFG_QOSVAL, DEF_QOSVAL).toInt());
    ui->priMode->setCurrentIndex(s.value(CFG_PRIMODE, DEF_PRIMODE).toBool());
    ui->priFact->setValue(s.value(CFG_PRIFACT, DEF_PRIFACT).toInt());
    ui->jpegQuality->setValue(s.value(CFG_JPGQUAL, DEF_JPGQUAL).toInt());

    // Fix window size
    setMaximumSize(minimumSize());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    ui->connectButton->setEnabled(false);

    // Save options
    s.setValue(CFG_IP, ui->dsIP->text());
    s.setValue(CFG_JPGQUAL, ui->jpegQuality->value());
    s.setValue(CFG_PRIFACT, ui->priFact->value());
    s.setValue(CFG_PRIMODE, (bool)ui->priMode->currentIndex());
    s.setValue(CFG_QOSVAL, ui->qosValue->value());

    emit initStream();
}
