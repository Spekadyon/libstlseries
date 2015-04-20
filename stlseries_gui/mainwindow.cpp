/*
 * Copyright 2015 - Geoffrey Brun <geoffrey+git@spekadyon.org>
 *
 * This file is part of libstlseries.
 *
 * libstlseries is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * libstlseries is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libstlseries. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stlseries.h>

#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(stlseries_open(&handle) != 0) {
        QMessageBox::critical(this, trUtf8("Libstlseries Graphical User Interface"), "Unable to find a steel series keyboard on this system.");
        QApplication::quit();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionE_xit_triggered()
{
    stlseries_close();
    QApplication::quit();
}

void MainWindow::on_left_color_currentIndexChanged(int index)
{
    stlseries_setcolor_normal(handle, STLSERIES_ZONE_LEFT, index, ui->left_saturation->currentIndex());
}

void MainWindow::on_left_saturation_currentIndexChanged(int index)
{
    stlseries_setcolor_normal(handle, STLSERIES_ZONE_LEFT, ui->left_color->currentIndex(), index);
}

void MainWindow::on_center_color_currentIndexChanged(int index)
{
    stlseries_setcolor_normal(handle, STLSERIES_ZONE_CENTER, index, ui->center_saturation->currentIndex());
}

void MainWindow::on_center_saturation_currentIndexChanged(int index)
{
    stlseries_setcolor_normal(handle, STLSERIES_ZONE_CENTER, ui->center_color->currentIndex(), index);
}

void MainWindow::on_right_color_currentIndexChanged(int index)
{
    stlseries_setcolor_normal(handle, STLSERIES_ZONE_RIGHT, index, ui->right_saturation->currentIndex());
}

void MainWindow::on_right_saturation_currentIndexChanged(int index)
{
    stlseries_setcolor_normal(handle, STLSERIES_ZONE_RIGHT, ui->right_color->currentIndex(), index);
}
