#include "customuiloader.h"

QLayout *CustomUILoader::CreateLayout(QObject *parent)
{
    auto [type, name] = ClassAndNameAttribute();
    if (auto iter = m_layoutCreator.find(type); iter != m_layoutCreator.end())
    {
        qDebug() << "start create layout: " << name;
        auto layout = std::invoke(iter.value(), this);
        layout->setParent(parent);
        layout->setObjectName(name);
        qDebug() << "create layout: " << name;

        return layout;
    }
    throw std::invalid_argument(QString("Unknown or not implimented layout: %1").arg(name).toStdString());
}

void CustomUILoader::LayoutReadPath(QLayout *layout, std::function<bool(QLayout *)> handler = {})
{
    if (!handler)
    {
        handler = [this](QLayout *layout) {
            if (IsElement(ITEM))
            {
                ReadToNextStart();
                if (IsStartElement(WIDGET))
                {
                    auto widget = CreateWidget();
                    layout->addWidget(widget);
                }
                else if (IsStartElement(LAYOUT))
                {
                    CreateLayout(layout);
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
        };
    }
    ReadWhileNotEndOf(LAYOUT, [&]() {
        if (IsElement(PROPERTY))
        {
            ReadProperty(layout);
        }
        else if (handler(layout))
            ;
        else
        {
            ThrowUnknownStart(layout);
        }
    });
}

QLayout *CustomUILoader::CreateGridLayout()
{
    auto layout = new QGridLayout();
    LayoutReadPath(layout, [this](QLayout *l) {
        auto layout = dynamic_cast<QGridLayout *>(l);
        auto row = GetAttributeOrThrow("row").value().toInt();
        auto column = GetAttributeOrThrow("column").value().toInt();
        ReadToNextStart();
        if (IsStartElement(WIDGET))
        {
            auto widget = CreateWidget(nullptr);
            layout->addWidget(widget, row, column);
        }
        else if (IsStartElement(LAYOUT))
        {
            auto child = CreateLayout(nullptr);
            layout->addLayout(child, row, column);
        }
        else if (IsStartElement(ATTRIBUTE))
        {
            // try to skip
            ReadToStartOrEnd();
        }
        else
        {
            return false;
        }
        return true;
    });
    return layout;
}

QLayout *CustomUILoader::CreateVBoxLayout()
{
    auto layout = new QVBoxLayout();
    LayoutReadPath(layout);

    return layout;
}

QLayout *CustomUILoader::CreateHBoxLayout()
{
    auto layout = new QHBoxLayout();
    LayoutReadPath(layout);

    return layout;
}
