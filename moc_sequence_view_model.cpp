/****************************************************************************
** Meta object code from reading C++ file 'sequence_view_model.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/gui/sequence_view_model.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sequence_view_model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SequenceViewModel_t {
    QByteArrayData data[15];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SequenceViewModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SequenceViewModel_t qt_meta_stringdata_SequenceViewModel = {
    {
QT_MOC_LITERAL(0, 0, 17), // "SequenceViewModel"
QT_MOC_LITERAL(1, 18, 21), // "NotifySequenceChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 8), // "sequence"
QT_MOC_LITERAL(4, 50, 27), // "NotifyCursorPositionChanged"
QT_MOC_LITERAL(5, 78, 8), // "position"
QT_MOC_LITERAL(6, 87, 22), // "ProcessSequenceChanged"
QT_MOC_LITERAL(7, 110, 23), // "ProcessSelectionChanged"
QT_MOC_LITERAL(8, 134, 9), // "start_pos"
QT_MOC_LITERAL(9, 144, 7), // "end_pos"
QT_MOC_LITERAL(10, 152, 21), // "ProcessIsTextSelected"
QT_MOC_LITERAL(11, 174, 1), // "b"
QT_MOC_LITERAL(12, 176, 14), // "CallComplement"
QT_MOC_LITERAL(13, 191, 21), // "CallReverseComplement"
QT_MOC_LITERAL(14, 213, 13) // "CallTranslate"

    },
    "SequenceViewModel\0NotifySequenceChanged\0"
    "\0sequence\0NotifyCursorPositionChanged\0"
    "position\0ProcessSequenceChanged\0"
    "ProcessSelectionChanged\0start_pos\0"
    "end_pos\0ProcessIsTextSelected\0b\0"
    "CallComplement\0CallReverseComplement\0"
    "CallTranslate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SequenceViewModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   60,    2, 0x0a /* Public */,
       7,    2,   63,    2, 0x0a /* Public */,
      10,    1,   68,    2, 0x0a /* Public */,
      12,    0,   71,    2, 0x0a /* Public */,
      13,    0,   72,    2, 0x0a /* Public */,
      14,    0,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SequenceViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SequenceViewModel *_t = static_cast<SequenceViewModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->NotifySequenceChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->NotifyCursorPositionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->ProcessSequenceChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->ProcessSelectionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->ProcessIsTextSelected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->CallComplement(); break;
        case 6: _t->CallReverseComplement(); break;
        case 7: _t->CallTranslate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SequenceViewModel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SequenceViewModel::NotifySequenceChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SequenceViewModel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SequenceViewModel::NotifyCursorPositionChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SequenceViewModel::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_SequenceViewModel.data,
    qt_meta_data_SequenceViewModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SequenceViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SequenceViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SequenceViewModel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SequenceViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SequenceViewModel::NotifySequenceChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SequenceViewModel::NotifyCursorPositionChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
