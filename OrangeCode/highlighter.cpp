
#include "highlighter.h"




// return QString(holder);



/*
    关键词：
"background": "#ffffffff",
"foreground": "#ff000000",
"bold": false,
"italic": false,
"strikeout": false,
"underlined": false
*/




void Highlighter::SetHighlighterX(QString name,
                    QString background,
                    QString foreground,
                    bool bold,
                    bool italic,
                    bool strikeout,
                    bool underlined
                    )
{
    QTextCharFormat Format;
    HighlightingRule rule;

    Format.setBackground(QColor(background));
    Format.setForeground(QColor(foreground));

    if(bold) {
        Format.setFontWeight(QFont::Bold);
        //Format.setFontBold(true);
    }

    Format.setFontItalic(italic);
    Format.setFontStrikeOut(strikeout);
    Format.setFontUnderline(underlined);






    rule.pattern = QRegularExpression(name);
    rule.format = Format;
    highlightingRules.append(rule);
}



Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    const QString keyword=
            "(?:auto)|(?:break)|(?:case)|(?:char)|(?:const)|(?:continue)|(?:default)|(?:do)|(?:double)|(?:else)|"
            "(?:enum)|(?:extern)|(?:float)|(?:for)|(?:goto)|(?:if)|(?:int)|(?:long)|(?:register)|(?:return)|"
            "(?:short)|(?:signed)|(?:sizeof)|(?:static)|(?:struct)|(?:switch)|(?:typedef)|(?:unsigned)|(?:union)|"
            "(?:void)|(?:volatile)|(?:while)"

            "(?:char)|(?:class)|(?:const)|"
            "(?:double)|(?:enum)|(?:explicit)|"
            "(?:friend)|(?:inline)|(?:int)|"
            "(?:long)|(?:namespace)|(?:operator)|"
            "(?:private)|(?:protected)|(?:public)|"
            "(?:short)|(?:signals)|(?:signed)|"
            "(?:slots)|(?:static)|(?:struct)|"
            "(?:template)|(?:typedef)|(?:typename)|"
            "(?:union)|(?:unsigned)|(?:virtual)|"
            "(?:void)|(?:volatile)|(?:bool)"
            ;



    SetHighlighterX(keyword,"#ffffffff","#ff0033B3",1,0,0,0);

    SetHighlighterX("(?:{)|(?:})","#ffffffff","#FF2F6CE7",0,0,0,0);

    SetHighlighterX("//[^\n]*","#ffffffff","#FF8C8C8C",0,1,0,0);
    SetHighlighterX("\".*\"","#ffffffff","#FF006400",0,0,0,0);

    SetHighlighterX("[0-9]","#ffffffff","#FF176EF5",0,0,0,0);

    SetHighlighterX("\\b[A-Za-z0-9_]+(?=\\()","#ffffffff","#FF400080",0,0,0,0);


    SetHighlighterX("(?:#include)","#ffffffff","#FF1F542E",0,0,0,0);
    SetHighlighterX("<.*>","#ffffffff","#FFCB0000",0,0,0,0);


    //SetHighlighterX("(?:[A-Za-z0-9_])","#ffffffff","#FF400095",0,0,0,0);


    multiLineCommentFormat.setForeground(QColor("#FF8C8C8C"));
    commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
}





void Highlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);


    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);


    while (startIndex >= 0) {

        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}

