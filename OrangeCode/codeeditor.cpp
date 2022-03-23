#include "codeeditor.h"

#include <QPainter>
#include <QTextBlock>



// 代码编辑器
CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}



// 行号区域宽度
int CodeEditor::lineNumberAreaWidth()
{
    int nums = 1;     //数字
    int max = qMax(1, blockCount());    //最大值
    while (max >= 10) {
        max /= 10;
        ++nums;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * nums;

    return space;
}



// 更新行号区域宽度
void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    // 设置视口边距
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


// 更新行号区域
void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}


// 调整事件大小
void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}




// 突出显示当前行
void CodeEditor::highlightCurrentLine()
{
    // QColor(0, 0, 255, 127)
    // QColor(0, 0, 255, 127)
    // QColor lineColor = QColor(0, 0, 255, 127).lighter(160);
    // 255,160,160, 255
    // painter.setPen(QColor(255,160,160, 255));

    QPainter painter(lineNumberArea);

    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(255, 100, 0, 255).lighter(185);//.lighter(160);   // 128

        // painter.setPen(QColor(160,160,160, 255));
        // selection.format.setPen(QColor(160,160,160, 255));

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();

        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
}



// 线号区域绘制事件
void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor(240,240,240, 255));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());


    while (block.isValid() && top <= event->rect().bottom()) {

        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);

            painter.setPen(QColor(160,160,160, 255));
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}


