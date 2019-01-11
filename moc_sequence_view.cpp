/****************************************************************************
** Meta object code from reading C++ file 'sequence_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/gui/sequence_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sequence_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SequenceView_t {
    QByteArrayData data[13];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SequenceView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SequenceView_t qt_meta_stringdata_SequenceView = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SequenceView"
QT_MOC_LITERAL(1, 13, 21), // "NotifySequenceChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 8), // "sequence"
QT_MOC_LITERAL(4, 45, 27), // "NotifyCursorPositionChanged"
QT_MOC_LITERAL(5, 73, 16), // "current_position"
QT_MOC_LITERAL(6, 90, 22), // "NotifySelectionChanged"
QT_MOC_LITERAL(7, 113, 9), // "start_pos"
QT_MOC_LITERAL(8, 123, 7), // "end_pos"
QT_MOC_LITERAL(9, 131, 22), // "ProcessSequenceChanged"
QT_MOC_LITERAL(10, 154, 28), // "ProcessCursorPositionChanged"
QT_MOC_LITERAL(11, 183, 8), // "position"
QT_MOC_LITERAL(12, 192, 23) // "ProcessSelectionChanged"

    },
    "SequenceView\0NotifySequenceChanged\0\0"
    "sequence\0NotifyCursorPositionChanged\0"
    "current_position\0NotifySelectionChanged\0"
    "start_pos\0end_pos\0ProcessSequenceChanged\0"
    "ProcessCursorPositionChanged\0position\0"
    "ProcessSelectionChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SequenceView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       6,    2,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   55,    2, 0x0a /* Public */,
      10,    1,   58,    2, 0x0a /* Public */,
      12,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,

       0        // eod
};

void SequenceView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SequenceView *_t = static_cast<SequenceView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->NotifySequenceChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->NotifyCursorPositionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->NotifySelectionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->ProcessSequenceChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->ProcessCursorPositionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->ProcessSelectionChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SequenceView::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SequenceView::NotifySequenceChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SequenceView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SequenceView::NotifyCursorPositionChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SequenceView::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SequenceView::NotifySelectionChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SequenceView::staticMetaObject = { {
    &QPlainTextEdit::staticMetaObject,
    qt_meta_stringdata_SequenceView.data,
    qt_meta_data_SequenceView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SequenceView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SequenceView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SequenceView.stringdata0))
        return static_cast<void*>(this);
    return QPlainTextEdit::qt_metacast(_clname);
}

int SequenceView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SequenceView::NotifySequenceChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SequenceView::NotifyCursorPositionChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SequenceView::NotifySelectionChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
