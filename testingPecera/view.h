#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
class GameScene;

class view : public QGraphicsView
{
    Q_OBJECT
public:
    explicit view();

signals:

private:
    GameScene* m_gameScene;

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // VIEW_H
