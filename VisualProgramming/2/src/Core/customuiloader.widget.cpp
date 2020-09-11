#include "customuiloader.h"

QWidget *CustomUILoader::CreateWidget(QWidget *parent)
{
    auto [type, name] = ClassAndNameAttribute();
    if (auto iter = m_widgetCreator.find(type); iter != m_widgetCreator.end())
    {
        qDebug() << "start create widget: " << name;
        auto widget = std::invoke(iter.value(), this);

        qDebug() << "create widget: " << name;
        widget->setParent(parent);
        widget->setObjectName(name);

        return widget.release();
    }
    throw std::invalid_argument(QString("Unknown or not implimented widget: %1").arg(name).toStdString());
}

void CustomUILoader::WidgetReadPath(
    QWidget *widget, std::function<bool(QWidget *)> handler = [](QWidget *) { return false; })
{
    while (!IsEndElement(WIDGET))
    {
        ReadNext();
        if (IsStartElement())
        {
            if (IsElement(PROPERTY))
            {
                ReadProperty(widget);
            }
            else if (IsElement(LAYOUT))
            {
                auto layout = CreateLayout(nullptr);
                widget->setLayout(layout);
            }
            else if (IsElement(ADDACTION))
            {
                auto name = GetAttributeOrThrow(NAME).value().toString();

                QAction *action;
                action = GetOrCreateAction(name);

                widget->addAction(action);
            }
            else if (IsElement(ACTION))
            {
                auto name = GetAttributeOrThrow(NAME).value().toString();
                auto action = GetOrCreateAction(name);
                ReadAction(action);
            }
            else if (handler(widget))
                ;
            else
            {
                ThrowUnknownStart(widget);
            }
        }
    }
    ReadNext();
}

std::unique_ptr<QWidget> CustomUILoader::CreateListWidget()
{
    auto widget = std::make_unique<QListWidget>();
    WidgetReadPath(widget.get(), [this](QWidget *w) {
        auto widget = dynamic_cast<QListWidget *>(w);
        if (IsElement(ITEM))
        {
            auto item = new QListWidgetItem(widget);
            ReadListItem(item);
        }
        else
        {
            return false;
        }
        return true;
    });

    return widget;
}

std::unique_ptr<QWidget> CustomUILoader::CreateMenuBar()
{
    auto widget = std::make_unique<QMenuBar>();
    WidgetReadPath(widget.get(), [this](QWidget *w) {
        auto widget = dynamic_cast<QMenuBar *>(w);
        if (IsElement(WIDGET))
        {
            if (GetAttributeOrThrow("class").value() == "QMenu")
            {
                auto menu = CreateWidget();
                // widget->addMenu(dynamic_cast<QMenu *>(menu));
                // auto action = GetOrCreateAction(menu->objectName(), true);

                auto casted = dynamic_cast<QMenu *>(menu);
                auto title = casted->title();
                auto action = GetOrCreateAction(menu->objectName());
                action->setMenu(casted);
                action->menu()->setTitle(title);
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }

        return true;
    });

    return widget;
}

std::unique_ptr<QWidget> CustomUILoader::CreateTextEdit()
{
    auto widget = std::make_unique<QTextEdit>();
    WidgetReadPath(widget.get());

    return widget;
}

std::unique_ptr<QWidget> CustomUILoader::CreatePushButton()
{
    auto widget = std::make_unique<QPushButton>();
    WidgetReadPath(widget.get());

    return widget;
}

std::unique_ptr<QWidget> CustomUILoader::CreateStatusBar()
{
    auto widget = std::make_unique<QStatusBar>();
    WidgetReadPath(widget.get());

    return widget;
}

std::unique_ptr<QWidget> CustomUILoader::CreateTreeWidget()
{
    auto widget = std::make_unique<QTreeWidget>();

    WidgetReadPath(widget.get(), [this](QWidget *w) {
        auto widget = dynamic_cast<QTreeWidget *>(w);
        if (IsElement(COLUMN))
        {
            auto header = widget->headerItem();
            ReadTreeHeader(0, header);
        }
        else if (IsElement(ITEM))
        {
            auto topLevelItem = new QTreeWidgetItem();
            widget->addTopLevelItem(topLevelItem);
            ReadTreeItem(0, topLevelItem);
        }
        else if (IsElement(ATTRIBUTE))
        {
            // skip attributes for now
            ReadToStartOrEnd();
        }
        else
        {
            return false;
        }
        return true;
    });

    return widget;
}

std::unique_ptr<QWidget> CustomUILoader::CreateMenu()
{
    auto widget = std::make_unique<QMenu>();
    WidgetReadPath(widget.get());

    return widget;
}

std::unique_ptr<QWidget> CustomUILoader::CreateWidgetAsWidget()
{
    auto widget = std::make_unique<QWidget>();
    WidgetReadPath(widget.get());

    return widget;
}

std::unique_ptr<QWidget> CustomUILoader::CreateGroupBox()
{
    auto widget = std::make_unique<QGroupBox>();
    WidgetReadPath(widget.get());

    return widget;
}

std::unique_ptr<QWidget> CustomUILoader::CreateMainWindow()
{
    auto widget = std::make_unique<QMainWindow>();
    QWidget *mBar = nullptr;
    QWidget *sBar = nullptr;
    WidgetReadPath(widget.get(), [&](QWidget *w) {
        auto widget = dynamic_cast<QMainWindow *>(w);
        if (IsElement(WIDGET))
        {
            if (widget->centralWidget())
            {
                if (mBar)
                {
                    if (sBar)
                    {
                        return false;
                    }
                    else
                    {
                        auto statusBar = CreateWidget();
                        sBar = statusBar;
                        widget->setStatusBar(dynamic_cast<QStatusBar *>(statusBar));
                    }
                }
                else
                {
                    auto menuBar = CreateWidget();
                    mBar = menuBar;
                    widget->setMenuBar(dynamic_cast<QMenuBar *>(menuBar));
                }
            }
            else
            {
                auto central = CreateWidget();
                widget->setCentralWidget(central);
            }
        }
        else
        {
            return false;
        }

        return true;
    });

    return widget;
}

void CustomUILoader::ReadListItem(QListWidgetItem *item)
{
    ReadWhileNotEndOf(ITEM, [&]() {
        if (IsElement(PROPERTY))
        {
            auto name = GetAttributeOrThrow(NAME).value();
            if (name == TEXT)
            {
                ReadToNextStart();
                Expect(STRING);
                ExpectNext(TokenType::Characters);

                item->setText(Text());
            }
            else
            {
                ThrowUnknownStart("QListWidgetItem");
            }
        }
        else
        {
            ThrowUnknownStart("QListWidgetItem");
        }
    });
}

void CustomUILoader::ReadTreeItem(int column, QTreeWidgetItem *item)
{
    ReadWhileNotEndOf(ITEM, [&]() {
        if (IsElement(PROPERTY))
        {
            auto name = GetAttributeOrThrow(NAME).value();
            if (name == TEXT)
            {
                ReadToNextStart();
                Expect(STRING);
                ExpectNext(TokenType::Characters);

                item->setText(column, Text());
            }
            else
            {
                ThrowUnknownStart("QTreeWidgetItem");
            }
        }
        else if (IsElement(ITEM))
        {
            auto child = new QTreeWidgetItem();
            item->addChild(child);
            ReadTreeItem(column, child);
        }
        else
        {
            ThrowUnknownStart("QTreeWidgetItem");
        }
    });
}

void CustomUILoader::ReadTreeHeader(int column, QTreeWidgetItem *item)
{
    ReadWhileNotEndOf(COLUMN, [&]() {
        if (IsElement(PROPERTY))
        {
            auto name = GetAttributeOrThrow(NAME).value();
            if (name == TEXT)
            {
                ReadToNextStart();
                Expect(STRING);
                ExpectNext(TokenType::Characters);

                item->setText(column, Text());
            }
            else
            {
                ThrowUnknownStart("QTreeWidgetItem ");
            }
        }
        else
        {
            ThrowUnknownStart("QTreeWidgetItem");
        }
    });
}

void CustomUILoader::ReadAction(QAction *action)
{
    ReadWhileNotEndOf(ACTION, [&]() {
        if (IsElement(PROPERTY))
        {
            ReadProperty(action);
        }
        else
        {
            ThrowUnknownStart<QAction>();
        }
    });
}

QAction *CustomUILoader::GetOrCreateAction(const QString &name, bool ignore)
{
    auto iter = m_actions.find(name);
    if (iter == m_actions.end())
    {
        auto action = new QAction(name);
        m_actions.insert(name, action);
        if (name == "separator")
        {
            action->setSeparator(true);
        }

        action->setEnabled(!ignore);
        action->setVisible(!ignore);

        return action;
    }
    return iter.value();
}
