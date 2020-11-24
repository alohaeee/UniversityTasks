#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QMainWindow>
#include <QSpinBox>
#include <QTimer>
#include <random>

inline static std::uniform_real_distribution<double> distr(0.0, 1.0);
inline static std::mt19937 generator{std::random_device()()};

class TextMagic : public QGraphicsItemGroup
{
public:
    TextMagic()
    {
        text = new QGraphicsTextItem("Пригнись!");
        text->setFont(QFont("Arial", 20));

        QBrush brush(Qt::yellow);
        QPen outlinePen(Qt::blue);
        outlinePen.setWidth(2);
        ellipse = new QGraphicsEllipseItem(text->boundingRect());
        ellipse->setBrush(brush);
        ellipse->setPen(outlinePen);

        QObject::connect(&timer, &QTimer::timeout, [&]() {
            ellipse->hide();
            text->show();
        });

        addToGroup(ellipse);
        addToGroup(text);

        ellipse->hide();

        setFlag(QGraphicsItem::ItemIsMovable);
    }

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
        if (event->button() == Qt::MouseButton::RightButton)
        {
            timer.start(1200);
            ellipse->show();
            text->hide();
        }

        QGraphicsItemGroup::mousePressEvent(event);
    }
    QTimer timer;
    QGraphicsEllipseItem *ellipse;
    QGraphicsTextItem *text;
};

class SpinMagic : public QGraphicsItemGroup
{
public:
    SpinMagic()
    {
        auto spinBox = new QSpinBox();
        spinBox->setRange(0, 10);
        auto spinBoxItem = new QGraphicsProxyWidget();
        spinBoxItem->setWidget(spinBox);
        spinBoxItem->setFlag(GraphicsItemFlag::ItemIsFocusable);

        auto box = new QGraphicsRectItem();
        box->setRect(spinBox->rect());

        addToGroup(box);
        addToGroup(spinBoxItem);

        setFlag(QGraphicsItem::ItemIsMovable);
    }

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
        if (event->button() == Qt::MouseButton::RightButton)
        {
            if (auto scenePtr = this->scene())
            {
                auto spinBox = new SpinMagic();

                spinBox->setPos(scenePtr->width() * distr(generator), scenePtr->height() * distr(generator));
                scenePtr->addItem(spinBox);
            }
        }
        QGraphicsItemGroup::mousePressEvent(event);
    }
};

QT_BEGIN_NAMESPACE namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    auto CreateCapibara()
    {
        auto image = new QImage("kapibara-2.jpg");
        assert(!image->isNull() && "Poloji image v build papku pls");

        auto pixMap = QPixmap::fromImage(*image);
        auto pixMapItem = m_scene->addPixmap(pixMap);
        pixMapItem->setFlag(QGraphicsItem::ItemIsMovable);

        return pixMapItem;
    }

    auto CreateText()
    {
        auto text = new TextMagic();
        m_scene->addItem(text);

        return text;
    }

    auto CreateSpinBox()
    {
        auto spinBox = new SpinMagic();

        m_scene->addItem(spinBox);

        return spinBox;
    }

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
};
#endif // MAINWINDOW_H
