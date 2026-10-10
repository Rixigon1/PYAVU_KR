#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>

class mainWin : public QWidget
{
    Q_OBJECT

public:
    explicit mainWin(QWidget *parent = nullptr);
    ~mainWin() override;
};
#endif // MAINWIN_H
