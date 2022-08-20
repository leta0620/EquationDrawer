/****************************************************************************
** Meta object code from reading C++ file 'EquationBox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EquationBox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EquationBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EquationBox_t {
<<<<<<< HEAD
    QByteArrayData data[6];
    char stringdata0[101];
=======
    QByteArrayData data[8];
    char stringdata0[138];
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EquationBox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EquationBox_t qt_meta_stringdata_EquationBox = {
    {
QT_MOC_LITERAL(0, 0, 11), // "EquationBox"
QT_MOC_LITERAL(1, 12, 7), // "sendDel"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 16), // "QListWidgetItem*"
<<<<<<< HEAD
QT_MOC_LITERAL(4, 38, 31), // "on_pushButton_Visible_onclicked"
QT_MOC_LITERAL(5, 70, 30) // "on_pushButton_Delete_onclicked"

    },
    "EquationBox\0sendDel\0\0QListWidgetItem*\0"
    "on_pushButton_Visible_onclicked\0"
    "on_pushButton_Delete_onclicked"
=======
QT_MOC_LITERAL(4, 38, 6), // "reDraw"
QT_MOC_LITERAL(5, 45, 31), // "on_pushButton_Visible_onclicked"
QT_MOC_LITERAL(6, 77, 30), // "on_pushButton_Delete_onclicked"
QT_MOC_LITERAL(7, 108, 29) // "on_pushButton_Color_onclicked"

    },
    "EquationBox\0sendDel\0\0QListWidgetItem*\0"
    "reDraw\0on_pushButton_Visible_onclicked\0"
    "on_pushButton_Delete_onclicked\0"
    "on_pushButton_Color_onclicked"
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EquationBox[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
<<<<<<< HEAD
       3,   14, // methods
=======
       5,   14, // methods
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
<<<<<<< HEAD
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   32,    2, 0x08 /* Private */,
       5,    0,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
=======
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   43,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
<<<<<<< HEAD
=======
    QMetaType::Void,
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc

       0        // eod
};

void EquationBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EquationBox *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendDel((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
<<<<<<< HEAD
        case 1: _t->on_pushButton_Visible_onclicked(); break;
        case 2: _t->on_pushButton_Delete_onclicked(); break;
=======
        case 1: _t->reDraw(); break;
        case 2: _t->on_pushButton_Visible_onclicked(); break;
        case 3: _t->on_pushButton_Delete_onclicked(); break;
        case 4: _t->on_pushButton_Color_onclicked(); break;
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EquationBox::*)(QListWidgetItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EquationBox::sendDel)) {
                *result = 0;
                return;
            }
        }
<<<<<<< HEAD
=======
        {
            using _t = void (EquationBox::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EquationBox::reDraw)) {
                *result = 1;
                return;
            }
        }
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
    }
}

QT_INIT_METAOBJECT const QMetaObject EquationBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_EquationBox.data,
    qt_meta_data_EquationBox,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EquationBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EquationBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EquationBox.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int EquationBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
<<<<<<< HEAD
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
=======
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
    }
    return _id;
}

// SIGNAL 0
void EquationBox::sendDel(QListWidgetItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
<<<<<<< HEAD
=======

// SIGNAL 1
void EquationBox::reDraw()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
QT_WARNING_POP
QT_END_MOC_NAMESPACE
