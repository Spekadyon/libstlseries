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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <stlseries.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionE_xit_triggered();

    void on_left_color_currentIndexChanged(int index);
    void on_left_saturation_currentIndexChanged(int index);
    void on_center_color_currentIndexChanged(int index);
    void on_center_saturation_currentIndexChanged(int index);
    void on_right_color_currentIndexChanged(int index);
    void on_right_saturation_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    STLSERIES handle;
};

#endif // MAINWINDOW_H
