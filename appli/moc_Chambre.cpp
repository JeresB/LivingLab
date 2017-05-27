/****************************************************************************
** Meta object code from reading C++ file 'Chambre.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Chambre.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Chambre.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Chambre_t {
    QByteArrayData data[7];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Chambre_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Chambre_t qt_meta_stringdata_Chambre = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Chambre"
QT_MOC_LITERAL(1, 8, 17), // "sendTextToProcess"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "onConnected"
QT_MOC_LITERAL(4, 39, 6), // "closed"
QT_MOC_LITERAL(5, 46, 21), // "onTextMessageReceived"
QT_MOC_LITERAL(6, 68, 7) // "message"

    },
    "Chambre\0sendTextToProcess\0\0onConnected\0"
    "closed\0onTextMessageReceived\0message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Chambre[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    8,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   51,    2, 0x08 /* Private */,
       4,    0,   52,    2, 0x08 /* Private */,
       5,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QDateTime, QMetaType::Int, QMetaType::Bool, QMetaType::Float, QMetaType::Float, QMetaType::Bool, QMetaType::QString, QMetaType::Int,    2,    2,    2,    2,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void Chambre::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Chambre *_t = static_cast<Chambre *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendTextToProcess((*reinterpret_cast< QDateTime(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8]))); break;
        case 1: _t->onConnected(); break;
        case 2: _t->closed(); break;
        case 3: _t->onTextMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Chambre::*_t)(QDateTime , int , bool , float , float , bool , QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Chambre::sendTextToProcess)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Chambre::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Chambre.data,
      qt_meta_data_Chambre,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Chambre::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Chambre::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Chambre.stringdata0))
        return static_cast<void*>(const_cast< Chambre*>(this));
    return QObject::qt_metacast(_clname);
}

int Chambre::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Chambre::sendTextToProcess(QDateTime _t1, int _t2, bool _t3, float _t4, float _t5, bool _t6, QString _t7, int _t8)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
