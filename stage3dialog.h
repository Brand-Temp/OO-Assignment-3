#ifndef STAGE3DIALOG_H
#define STAGE3DIALOG_H
#include "dialog.h"
#include "stage3dialog.h"


class Stage3Dialog : public Dialog
{
    Q_OBJECT

public:
    explicit Stage3Dialog(QWidget *parent = 0);
    ~Stage3Dialog();
    /**
     * @brief keyPressEvent emits key press signal
     * @param event
     */
    void keyPressEvent(QKeyEvent* event);
    void start(PoolGame *game);
signals:
    void rPressed(QKeyEvent* event);
public slots:
    void secondTimer();
private:
    QTimer* m_secondTimer;
};

#endif // STAGE3DIALOG_H
