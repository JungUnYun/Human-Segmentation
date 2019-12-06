/****************************************************************************
** Meta object code from reading C++ file 'HumanSegmentation1.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../HumanSegmentation1.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HumanSegmentation1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HumanSegmentation1_t {
    QByteArrayData data[16];
    char stringdata0[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HumanSegmentation1_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HumanSegmentation1_t qt_meta_stringdata_HumanSegmentation1 = {
    {
QT_MOC_LITERAL(0, 0, 18), // "HumanSegmentation1"
QT_MOC_LITERAL(1, 19, 10), // "LoadSource"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 15), // "LoadSourceVideo"
QT_MOC_LITERAL(4, 47, 12), // "DisplayVideo"
QT_MOC_LITERAL(5, 60, 10), // "checkpause"
QT_MOC_LITERAL(6, 71, 9), // "inputzoom"
QT_MOC_LITERAL(7, 81, 11), // "shapezoom_s"
QT_MOC_LITERAL(8, 93, 11), // "shapezoom_c"
QT_MOC_LITERAL(9, 105, 9), // "show_info"
QT_MOC_LITERAL(10, 115, 10), // "save_input"
QT_MOC_LITERAL(11, 126, 11), // "save_serial"
QT_MOC_LITERAL(12, 138, 9), // "save_cuda"
QT_MOC_LITERAL(13, 148, 18), // "Hsegmentation_CUDA"
QT_MOC_LITERAL(14, 167, 4), // "func"
QT_MOC_LITERAL(15, 172, 5) // "index"

    },
    "HumanSegmentation1\0LoadSource\0\0"
    "LoadSourceVideo\0DisplayVideo\0checkpause\0"
    "inputzoom\0shapezoom_s\0shapezoom_c\0"
    "show_info\0save_input\0save_serial\0"
    "save_cuda\0Hsegmentation_CUDA\0func\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HumanSegmentation1[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    1,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void HumanSegmentation1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HumanSegmentation1 *_t = static_cast<HumanSegmentation1 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->LoadSource(); break;
        case 1: _t->LoadSourceVideo(); break;
        case 2: _t->DisplayVideo(); break;
        case 3: _t->checkpause(); break;
        case 4: _t->inputzoom(); break;
        case 5: _t->shapezoom_s(); break;
        case 6: _t->shapezoom_c(); break;
        case 7: _t->show_info(); break;
        case 8: _t->save_input(); break;
        case 9: _t->save_serial(); break;
        case 10: _t->save_cuda(); break;
        case 11: _t->Hsegmentation_CUDA(); break;
        case 12: _t->func((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject HumanSegmentation1::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_HumanSegmentation1.data,
      qt_meta_data_HumanSegmentation1,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HumanSegmentation1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HumanSegmentation1::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HumanSegmentation1.stringdata0))
        return static_cast<void*>(const_cast< HumanSegmentation1*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int HumanSegmentation1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
