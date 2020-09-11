#include "customuiloader.h"

QVariant CustomUILoader::CreateVariant(const QString &name)
{
    qDebug() << "Variant: " << name;
    if (auto iter = m_variantCreator.find(name); iter != m_variantCreator.end())
    {
        auto variant = std::invoke(iter.value(), this);
        return variant;
    }
    throw std::invalid_argument(QString("Unknown variant or not implimented variant: %1").arg(name).toStdString());
}

QVariant CustomUILoader::ReadString()
{
    ExpectNext(TokenType::Characters);
    return m_reader.text().toString();
}

QVariant CustomUILoader::ReadRect()
{
    ReadToNextStart();
    Expect("x");
    ExpectNext(TokenType::Characters);
    auto x = m_reader.text().toInt();
    Print();

    ReadToNextStart();
    Expect("y");
    // skip y;
    ExpectNext(TokenType::Characters);
    auto y = m_reader.text().toInt();
    Print();

    ReadToNextStart();
    Expect("width");
    // skip width;
    ExpectNext(TokenType::Characters);
    auto w = m_reader.text().toInt();
    Print();

    ReadToNextStart();
    Expect("height");
    // skip height;
    ExpectNext(TokenType::Characters);
    auto h = m_reader.text().toInt();
    Print();

    return QRect{x, y, w, h};
}

QVariant CustomUILoader::ReadNumber()
{
    ExpectNext(TokenType::Characters);
    bool result;
    auto numText = m_reader.text();
    auto num = numText.toInt(&result);

    if (!result)
    {
        throw std::invalid_argument(QString("Can't convert number to int: %1").arg(numText).toStdString());
    }
    return num;
}

QVariant CustomUILoader::ReadBool()
{
    ExpectNext(TokenType::Characters);
    auto state = Text();
    if (state == "false")
    {
        return QVariant(false);
    }
    else if (state == "true")
    {
        return QVariant(true);
    }
    else
    {
        throw std::invalid_argument("Bool value can be only true or false");
    }
}

QVariant CustomUILoader::ReadFont()
{
    ReadToNextStart();
    QString family;
    if (IsStartElement("family"))
    {
        ExpectNext(TokenType::Characters);
        family = m_reader.text().toString();
    }
    else
    {
        ThrowUnknownStart("read font");
    }
    return QFont(family);
}
