/****************************************************************************
** Meta object code from reading C++ file 'EquationDrawer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EquationDrawer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EquationDrawer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EquationDrawer_t {
<<<<<<< HEAD
    QByteArrayData data[7];
    char stringdata0[114];
=======
    QByteArrayData data[9];
    char stringdata0[149];
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EquationDrawer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EquationDrawer_t qt_meta_stringdata_EquationDrawer = {
    {
QT_MOC_LITERAL(0, 0, 14), // "EquationDrawer"
QT_MOC_LITERAL(1, 15, 27), // "on_pushButton_Add_onclicked"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 28), // "on_pushButton_Draw_onclicked"
<<<<<<< HEAD
QT_MOC_LITERAL(4, 73, 10), // "receiveDel"
QT_MOC_LITERAL(5, 84, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(6, 101, 12) // "receiveInput"

    },
    "EquationDrawer\0on_pushButton_Add_onclicked\0"
    "\0on_pushButton_Draw_onclicked\0receiveDel\0"
    "QListWidgetItem*\0receiveInput"
=======
QT_MOC_LITERAL(4, 73, 28), // "on_pushButton_Back_onclicked"
QT_MOC_LITERAL(5, 102, 10), // "receiveDel"
QT_MOC_LITERAL(6, 113, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 130, 12), // "receiveInput"
QT_MOC_LITERAL(8, 143, 5) // "paint"

    },
    "EquationDrawer\0on_pushButton_Add_onclicked\0"
    "\0on_pushButton_Draw_onclicked\0"
    "on_pushButton_Back_onclicked\0receiveDel\0"
    "QListWidgetItem*\0receiveInput\0paint"
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EquationDrawer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
<<<<<<< HEAD
       4,   14, // methods
=======
       6,   14, // methods
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
<<<<<<< HEAD
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    1,   36,    2, 0x08 /* Private */,
       6,    1,   39,    2, 0x08 /* Private */,
=======
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    1,   47,    2, 0x08 /* Private */,
       7,    1,   50,    2, 0x08 /* Private */,
       8,    0,   53,    2, 0x08 /* Private */,
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
<<<<<<< HEAD
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::QString,    2,
=======
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc

       0        // eod
};

void EquationDrawer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EquationDrawer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_Add_onclicked(); break;
        case 1: _t->on_pushButton_Draw_onclicked(); break;
<<<<<<< HEAD
        case 2: _t->receiveDel((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->receiveInput((*reinterpret_cast< QString(*)>(_a[1]))); break;
=======
        case 2: _t->on_pushButton_Back_onclicked(); break;
        case 3: _t->receiveDel((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->receiveInput((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->paint(); break;
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EquationDrawer::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_EquationDrawer.data,
    qt_meta_data_EquationDrawer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EquationDrawer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EquationDrawer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EquationDrawer.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int EquationDrawer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
<<<<<<< HEAD
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
=======
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
>>>>>>> 11bee3459e5ce45f5dcd61cbe922c7305dd1e4dc
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
