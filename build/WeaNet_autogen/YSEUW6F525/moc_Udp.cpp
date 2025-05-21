/****************************************************************************
** Meta object code from reading C++ file 'Udp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/WeaNet/Udp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Udp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WeaNet__Udp_t {
    QByteArrayData data[12];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WeaNet__Udp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WeaNet__Udp_t qt_meta_stringdata_WeaNet__Udp = {
    {
QT_MOC_LITERAL(0, 0, 11), // "WeaNet::Udp"
QT_MOC_LITERAL(1, 12, 9), // "readyRead"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "dataReceived"
QT_MOC_LITERAL(4, 36, 10), // "bytes_addr"
QT_MOC_LITERAL(5, 47, 6), // "size_t"
QT_MOC_LITERAL(6, 54, 10), // "bytes_size"
QT_MOC_LITERAL(7, 65, 11), // "const char*"
QT_MOC_LITERAL(8, 77, 4), // "host"
QT_MOC_LITERAL(9, 82, 4), // "port"
QT_MOC_LITERAL(10, 87, 12), // "bytesWritten"
QT_MOC_LITERAL(11, 100, 12) // "numSentBytes"

    },
    "WeaNet::Udp\0readyRead\0\0dataReceived\0"
    "bytes_addr\0size_t\0bytes_size\0const char*\0"
    "host\0port\0bytesWritten\0numSentBytes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WeaNet__Udp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    4,   30,    2, 0x06 /* Public */,
      10,    1,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::VoidStar, 0x80000000 | 5, 0x80000000 | 7, QMetaType::Int,    4,    6,    8,    9,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void WeaNet::Udp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Udp *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->readyRead(); break;
        case 1: _t->dataReceived((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< size_t(*)>(_a[2])),(*reinterpret_cast< const char*(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 2: _t->bytesWritten((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Udp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Udp::readyRead)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Udp::*)(void * , size_t , const char * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Udp::dataReceived)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Udp::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Udp::bytesWritten)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WeaNet::Udp::staticMetaObject = { {
    QMetaObject::SuperData::link<Network::staticMetaObject>(),
    qt_meta_stringdata_WeaNet__Udp.data,
    qt_meta_data_WeaNet__Udp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WeaNet::Udp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WeaNet::Udp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WeaNet__Udp.stringdata0))
        return static_cast<void*>(this);
    return Network::qt_metacast(_clname);
}

int WeaNet::Udp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Network::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void WeaNet::Udp::readyRead()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WeaNet::Udp::dataReceived(void * _t1, size_t _t2, const char * _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WeaNet::Udp::bytesWritten(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
