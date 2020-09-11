#ifndef CUSTOMUILOADER_H
#define CUSTOMUILOADER_H

#include <QDebug>
#include <QMap>
#include <QString>
#include <QXmlStreamReader>

#include <functional>
#include <memory>
#include <stdexcept>

#include <QGroupBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStatusBar>
#include <QTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#define REGISTER_TOKEN(tokenId, tokenName) static constexpr const char *tokenId = tokenName

#define QTYPE_TO_STR(type) type().metaObject()->className()
#define QOBJ_TO_STR(obj) obj->metaObject()->className()

QString OpenFileAndReadAll(const QString &file);

class CustomUILoader
{
    using Reader = QXmlStreamReader;
    using TokenType = Reader::TokenType;
    using Attribute = QXmlStreamAttribute;
    using AttributeList = QXmlStreamAttributes;

private:
    REGISTER_TOKEN(TEXT, "text");
    REGISTER_TOKEN(COLUMN, "column");
    REGISTER_TOKEN(ITEM, "item");
    REGISTER_TOKEN(NUMBER, "number");
    REGISTER_TOKEN(PROPERTY, "property");
    REGISTER_TOKEN(STRING, "string");
    REGISTER_TOKEN(LAYOUT, "layout");
    REGISTER_TOKEN(WIDGET, "widget");
    REGISTER_TOKEN(RECT, "rect");
    REGISTER_TOKEN(ENUM, "enum");
    REGISTER_TOKEN(FONT, "font");
    REGISTER_TOKEN(BOOL, "bool");
    REGISTER_TOKEN(ATTRIBUTE, "attribute");
    REGISTER_TOKEN(NAME, "name");
    REGISTER_TOKEN(CLASS, "class");
    REGISTER_TOKEN(ADDACTION, "addaction");
    REGISTER_TOKEN(ACTION, "action");

private:
    static Attribute *GetAttributeOrThrow(AttributeList &attributes, const QString &name);
    inline Attribute GetAttributeOrThrow(const QString &name)
    {
        auto attributes = m_reader.attributes();
        return *GetAttributeOrThrow(attributes, name);
    }

    inline void Print()
    {
        qDebug() << '[' << m_reader.lineNumber() << ":" << m_reader.columnNumber() << "] " << m_reader.qualifiedName()
                 << '\t' << m_reader.tokenString() << '\t' << m_reader.text();
    }

    void ExpectNext(const QString &name);
    void ExpectNext(TokenType type);
    void Expect(const QString &name);
    void Expect(TokenType type);
    bool IsStartElement(const QString &itemName);
    bool IsEndElement(const QString &itemName);

    inline bool IsStartElement()
    {
        return m_reader.isStartElement();
    }
    inline bool IsEndElement()
    {
        return m_reader.isEndElement();
    }
    inline void ReadNext()
    {
        m_reader.readNext();
        Print();
    }

    // true to start false to end
    inline bool ReadToStartOrEnd()
    {
        return m_reader.readNextStartElement();
    }
    inline void ReadToNextStart()
    {
        if (!m_reader.readNextStartElement())
        {
            qDebug() << "reach end of " << Name();
            m_reader.readNextStartElement();
        }
    }
    inline bool IsElement(const QString &name)
    {
        qDebug() << Name() << '\t' << name;
        return Name() == name;
    }
    inline bool IsElement(TokenType type)
    {
        return Type() == type;
    }
    inline TokenType Type()
    {
        return m_reader.tokenType();
    }

    inline QStringRef Name()
    {
        return m_reader.qualifiedName();
    }
    inline AttributeList Attributes()
    {
        return m_reader.attributes();
    }
    inline QString Text()
    {
        return m_reader.text().toString();
    }

    void ThrowUnknownStart(QObject *object)
    {
        throw std::invalid_argument(
            QString("Unknown start of element %1 in %2").arg(Name()).arg(QOBJ_TO_STR(object)).toStdString());
    }
    template <typename T>
    void ThrowUnknownStart()
    {
        throw std::invalid_argument(
            QString("Unknown start of element %1 in %2").arg(Name()).arg(QTYPE_TO_STR(T)).toStdString());
    }

    void ThrowUnknownStart(const QString &in)
    {
        throw std::invalid_argument(QString("Unknown start of element %1 in %2").arg(Name()).arg(in).toStdString());
    }

    void ReadWhileNotEndOf(const QString &element, std::function<void()> handler);

    std::pair<QString, QString> ClassAndNameAttribute();

public:
    typedef QVariant (CustomUILoader::*VariantCreator)();
    typedef QLayout *(CustomUILoader::*LayoutCreator)();
    typedef std::unique_ptr<QWidget> (CustomUILoader::*WidgetCreator)();

public:
    CustomUILoader() = default;
    CustomUILoader(QString &&content) : m_reader{content}
    {
    }

    QWidget *VisitForWidget();

    QSet<QString> VisitForSourceGen(const QString &content);

    QWidget *CreateWidget(QWidget *parent = nullptr);

    void WidgetReadPath(QWidget *widget, std::function<bool(QWidget *)> handler);

    std::unique_ptr<QWidget> CreateListWidget();
    std::unique_ptr<QWidget> CreateMenuBar();
    std::unique_ptr<QWidget> CreateTextEdit();
    std::unique_ptr<QWidget> CreatePushButton();
    std::unique_ptr<QWidget> CreateStatusBar();
    std::unique_ptr<QWidget> CreateTreeWidget();
    std::unique_ptr<QWidget> CreateMenu();
    std::unique_ptr<QWidget> CreateWidgetAsWidget();
    std::unique_ptr<QWidget> CreateGroupBox();
    std::unique_ptr<QWidget> CreateMainWindow();

    void ReadListItem(QListWidgetItem *item);
    void ReadTreeItem(int column, QTreeWidgetItem *item);
    void ReadTreeHeader(int column, QTreeWidgetItem *item);

    QLayout *CreateLayout(QObject *parent);
    void LayoutReadPath(QLayout *layout, std::function<bool(QLayout *)> handler);

    //    template <typename LType>
    //    void LayoutReadPath(LType *layout, std::function<void(LType *)> itemHandler = &BasicItemHandler<LType>);

    //    template <typename LType>
    //    void BasicItemHandler(LType *layout);

    QLayout *CreateGridLayout();
    QLayout *CreateVBoxLayout();
    QLayout *CreateHBoxLayout();

    void ReadProperty(QObject *object);

    QVariant CreateVariant(const QString &name);
    QVariant ReadRect();
    QVariant ReadString();
    QVariant ReadNumber();
    QVariant ReadBool();
    QVariant ReadFont();
    QVariant ReadEnum();

    void ReadAction(QAction *action);

    QAction *GetOrCreateAction(const QString &name, bool ignore = false);

private:
    QList<std::pair<QString, QWidget *>> m_actionsAdd;
    QMap<QString, QAction *> m_actions;
    Reader m_reader;
    const QMap<QString, WidgetCreator> m_widgetCreator = {
        {QTYPE_TO_STR(QTreeWidget), &CustomUILoader::CreateTreeWidget},
        {QTYPE_TO_STR(QListWidget), &CustomUILoader::CreateListWidget},
        {QTYPE_TO_STR(QMenuBar), &CustomUILoader::CreateMenuBar},
        {QTYPE_TO_STR(QMainWindow), &CustomUILoader::CreateMainWindow},
        {QTYPE_TO_STR(QTextEdit), &CustomUILoader::CreateTextEdit},
        {QTYPE_TO_STR(QGroupBox), &CustomUILoader::CreateGroupBox},
        {QTYPE_TO_STR(QMenu), &CustomUILoader::CreateMenu},
        {QTYPE_TO_STR(QStatusBar), &CustomUILoader::CreateStatusBar},
        {QTYPE_TO_STR(QWidget), &CustomUILoader::CreateWidgetAsWidget},
        {QTYPE_TO_STR(QPushButton), &CustomUILoader::CreatePushButton},

    };
    const QMap<QString, LayoutCreator> m_layoutCreator = {
        {QTYPE_TO_STR(QGridLayout), &CustomUILoader::CreateGridLayout},
        {QTYPE_TO_STR(QHBoxLayout), &CustomUILoader::CreateHBoxLayout},
        {QTYPE_TO_STR(QVBoxLayout), &CustomUILoader::CreateVBoxLayout}};
    const QMap<QString, VariantCreator> m_variantCreator = {
        {RECT, &CustomUILoader::ReadRect}, {STRING, &CustomUILoader::ReadString}, {NUMBER, &CustomUILoader::ReadNumber},
        {BOOL, &CustomUILoader::ReadBool}, {FONT, &CustomUILoader::ReadFont},
    };
};

// template <typename LType>
// void CustomUILoader::LayoutReadPath(LType *layout, std::function<void(LType *)> itemHandler)
//{
//    while (!IsEndElement(LAYOUT))
//    {
//        ReadNext();
//        if (IsStartElement())
//        {
//            if (IsElement(PROPERTY))
//            {
//                ReadProperty(layout);
//            }
//            else if (IsElement(ITEM))
//            {
//                itemHandler(layout);
//            }
//            else
//            {
//                ThrowUnknownStart(layout);
//            }
//        }
//    }
//}

// template <typename LType>
// void CustomUILoader::BasicItemHandler(LType *layout)
//{
//    if (IsElement(WIDGET))
//    {
//        auto widget = CreateWidget(layout);
//        layout->addWidget(widget);
//    }
//    else if (IsElement(LAYOUT))
//    {
//        auto child = CreateLayout(layout);
//        layout->addLayout(child);
//    }
//}

#endif // CUSTOMUILOADER_H
