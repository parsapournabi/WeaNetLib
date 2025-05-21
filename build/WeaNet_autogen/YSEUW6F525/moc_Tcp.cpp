/****************************************************************************
** Meta object code from reading C++ file 'Tcp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/WeaNet/Tcp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Tcp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WeaNet__TcpClient_t {
    QByteArrayData data[11];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WeaNet__TcpClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WeaNet__TcpClient_t qt_meta_stringdata_WeaNet__TcpClient = {
    {
QT_MOC_LITERAL(0, 0, 17), // "WeaNet::TcpClient"
QT_MOC_LITERAL(1, 18, 9), // "connected"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12), // "disconnected"
QT_MOC_LITERAL(4, 42, 9), // "readyRead"
QT_MOC_LITERAL(5, 52, 12), // "dataReceived"
QT_MOC_LITERAL(6, 65, 10), // "bytes_addr"
QT_MOC_LITERAL(7, 76, 6), // "size_t"
QT_MOC_LITERAL(8, 83, 10), // "bytes_size"
QT_MOC_LITERAL(9, 94, 12), // "bytesWritten"
QT_MOC_LITERAL(10, 107, 12) // "numSentBytes"

    },
    "WeaNet::TcpClient\0connected\0\0disconnected\0"
    "readyRead\0dataReceived\0bytes_addr\0"
    "size_t\0bytes_size\0bytesWritten\0"
    "numSentBytes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WeaNet__TcpClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    2,   42,    2, 0x06 /* Public */,
       9,    1,   47,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::VoidStar, 0x80000000 | 7,    6,    8,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void WeaNet::TcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TcpClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->readyRead(); break;
        case 3: _t->dataReceived((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< size_t(*)>(_a[2]))); break;
        case 4: _t->bytesWritten((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TcpClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpClient::connected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TcpClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpClient::disconnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TcpClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpClient::readyRead)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TcpClient::*)(void * , size_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpClient::dataReceived)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TcpClient::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpClient::bytesWritten)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WeaNet::TcpClient::staticMetaObject = { {
    QMetaObject::SuperData::link<Network::staticMetaObject>(),
    qt_meta_stringdata_WeaNet__TcpClient.data,
    qt_meta_data_WeaNet__TcpClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WeaNet::TcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WeaNet::TcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WeaNet__TcpClient.stringdata0))
        return static_cast<void*>(this);
    return Network::qt_metacast(_clname);
}

int WeaNet::TcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Network::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void WeaNet::TcpClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WeaNet::TcpClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WeaNet::TcpClient::readyRead()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WeaNet::TcpClient::dataReceived(void * _t1, size_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WeaNet::TcpClient::bytesWritten(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
struct qt_meta_stringdata_WeaNet__TcpServer_t {
    QByteArrayData data[3];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WeaNet__TcpServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WeaNet__TcpServer_t qt_meta_stringdata_WeaNet__TcpServer = {
    {
QT_MOC_LITERAL(0, 0, 17), // "WeaNet::TcpServer"
QT_MOC_LITERAL(1, 18, 13), // "newConnection"
QT_MOC_LITERAL(2, 32, 0) // ""

    },
    "WeaNet::TcpServer\0newConnection\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WeaNet__TcpServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void WeaNet::TcpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TcpServer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newConnection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TcpServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TcpServer::newConnection)) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject WeaNet::TcpServer::staticMetaObject = { {
    QMetaObject::SuperData::link<Network::staticMetaObject>(),
    qt_meta_stringdata_WeaNet__TcpServer.data,
    qt_meta_data_WeaNet__TcpServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WeaNet::TcpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WeaNet::TcpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WeaNet__TcpServer.stringdata0))
        return static_cast<void*>(this);
    return Network::qt_metacast(_clname);
}

int WeaNet::TcpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Network::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void WeaNet::TcpServer::newConnection()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
