/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include "codeeditor.h"
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupEditor();
    setupFileMenu();
    setupEditMenu();
    setupViewMenu();
    setupCodeMenu();
    setupRunMenu();
    setupToolMenu();
    setupWindowMenu();
    setupHelpMenu();
    editor->setFont(QFont("Consolas", 16));
    setCentralWidget(editor);
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About Orange Code"),
                tr(
                    "<p><b>Orange Code</b></p> " \
                    "<p>Version : " \
                    "v0.0.1-alpha</p>" \
                    "<p>Copyright © 2020 - 2022 Space Longan</p>"
                ));
}

void MainWindow::newFile()
{
    editor->clear();
}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("File"), "", "Files (*.*)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            editor->setPlainText(file.readAll());
    }
}


void MainWindow::setupEditor()
{
    editor = new CodeEditor;
    highlighter = new Highlighter(editor->document());
    //QFile file("mainwindow.h");
    //if (file.open(QFile::ReadOnly | QFile::Text))
    //    editor->setPlainText(file.readAll());
}




// # 文件 | 编辑 | 视图 | 代码 | 运行 | 工具 | 窗口 | 帮助
void MainWindow::setupFileMenu()
{
    QMenu *FileMenu = new QMenu(tr("文件"), this);  //文件
    menuBar()->addMenu(FileMenu);

    FileMenu->addAction(tr("New File"), this,&MainWindow::newFile, QKeySequence::New);
    FileMenu->addAction(tr("Open File"),this, [this](){ openFile(); }, QKeySequence::Open);
    FileMenu->addAction(tr("Exit"), qApp, &QApplication::quit, QKeySequence::Quit);
}
void MainWindow::setupEditMenu(){
    QMenu *EditMenu = new QMenu(tr("编辑"), this);
    menuBar()->addMenu(EditMenu);
}
void MainWindow::setupViewMenu(){
    QMenu *ViewMenu = new QMenu(tr("视图"), this);
    menuBar()->addMenu(ViewMenu);

}
void MainWindow::setupCodeMenu(){
    QMenu *CodeMenu = new QMenu(tr("代码"), this);
    menuBar()->addMenu(CodeMenu);
}
void MainWindow::setupRunMenu(){
    QMenu *RunMenu = new QMenu(tr("运行"), this);
    menuBar()->addMenu(RunMenu);
}
void MainWindow::setupToolMenu(){
    QMenu *ToolMenu = new QMenu(tr("工具"), this);
    menuBar()->addMenu(ToolMenu);
}
void MainWindow::setupWindowMenu(){

    QMenu *WindowlMenu = new QMenu(tr("窗口"), this);
    menuBar()->addMenu(WindowlMenu);
}
void MainWindow::setupHelpMenu(){
    QMenu *HelpMenu = new QMenu(tr("帮助"), this);
    menuBar()->addMenu(HelpMenu);

    HelpMenu->addAction(tr("About"), this, &MainWindow::about);
    HelpMenu->addAction(tr("About Qt"), qApp, &QApplication::aboutQt);
}
