/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../qt_test/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[272];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "button_clicked"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "onSocketType"
QT_MOC_LITERAL(4, 40, 9), // "onBindBtn"
QT_MOC_LITERAL(5, 50, 12), // "onConnectBtn"
QT_MOC_LITERAL(6, 63, 9), // "onSendBtn"
QT_MOC_LITERAL(7, 73, 11), // "onReadyRead"
QT_MOC_LITERAL(8, 85, 14), // "onDataReceived"
QT_MOC_LITERAL(9, 100, 8), // "p_buffer"
QT_MOC_LITERAL(10, 109, 7), // "buf_len"
QT_MOC_LITERAL(11, 117, 17), // "onDataReceivedUdp"
QT_MOC_LITERAL(12, 135, 11), // "const char*"
QT_MOC_LITERAL(13, 147, 4), // "host"
QT_MOC_LITERAL(14, 152, 4), // "port"
QT_MOC_LITERAL(15, 157, 14), // "onBytesWritten"
QT_MOC_LITERAL(16, 172, 12), // "numSentBytes"
QT_MOC_LITERAL(17, 185, 14), // "onErrorOccured"
QT_MOC_LITERAL(18, 200, 8), // "err_code"
QT_MOC_LITERAL(19, 209, 11), // "err_message"
QT_MOC_LITERAL(20, 221, 14), // "onStateUpdated"
QT_MOC_LITERAL(21, 236, 5), // "state"
QT_MOC_LITERAL(22, 242, 13), // "state_message"
QT_MOC_LITERAL(23, 256, 15) // "onNewConnection"

    },
    "MainWindow\0button_clicked\0\0onSocketType\0"
    "onBindBtn\0onConnectBtn\0onSendBtn\0"
    "onReadyRead\0onDataReceived\0p_buffer\0"
    "buf_len\0onDataReceivedUdp\0const char*\0"
    "host\0port\0onBytesWritten\0numSentBytes\0"
    "onErrorOccured\0err_code\0err_message\0"
    "onStateUpdated\0state\0state_message\0"
    "onNewConnection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    2,   80,    2, 0x0a /* Public */,
      11,    4,   85,    2, 0x0a /* Public */,
      15,    1,   94,    2, 0x0a /* Public */,
      17,    2,   97,    2, 0x0a /* Public */,
      20,    2,  102,    2, 0x0a /* Public */,
      23,    0,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::Int,    9,   10,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::Int, 0x80000000 | 12, QMetaType::Int,    9,   10,   13,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 12,   18,   19,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 12,   21,   22,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->button_clicked(); break;
        case 1: _t->onSocketType(); break;
        case 2: _t->onBindBtn(); break;
        case 3: _t->onConnectBtn(); break;
        case 4: _t->onSendBtn(); break;
        case 5: _t->onReadyRead(); break;
        case 6: _t->onDataReceived((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->onDataReceivedUdp((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const char*(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 8: _t->onBytesWritten((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->onErrorOccured((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 10: _t->onStateUpdated((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 11: _t->onNewConnection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::button_clicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::button_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
