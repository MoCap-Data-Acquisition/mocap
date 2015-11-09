/****************************************************************************
** Meta object code from reading C++ file 'player.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "player.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Player_t {
    QByteArrayData data[26];
    char stringdata0[329];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Player_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Player_t qt_meta_stringdata_Player = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Player"
QT_MOC_LITERAL(1, 7, 17), // "fullScreenChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 10), // "fullScreen"
QT_MOC_LITERAL(4, 37, 4), // "open"
QT_MOC_LITERAL(5, 42, 15), // "durationChanged"
QT_MOC_LITERAL(6, 58, 8), // "duration"
QT_MOC_LITERAL(7, 67, 15), // "positionChanged"
QT_MOC_LITERAL(8, 83, 8), // "progress"
QT_MOC_LITERAL(9, 92, 15), // "metaDataChanged"
QT_MOC_LITERAL(10, 108, 15), // "previousClicked"
QT_MOC_LITERAL(11, 124, 4), // "seek"
QT_MOC_LITERAL(12, 129, 7), // "seconds"
QT_MOC_LITERAL(13, 137, 4), // "jump"
QT_MOC_LITERAL(14, 142, 5), // "index"
QT_MOC_LITERAL(15, 148, 23), // "playlistPositionChanged"
QT_MOC_LITERAL(16, 172, 13), // "statusChanged"
QT_MOC_LITERAL(17, 186, 25), // "QMediaPlayer::MediaStatus"
QT_MOC_LITERAL(18, 212, 6), // "status"
QT_MOC_LITERAL(19, 219, 17), // "bufferingProgress"
QT_MOC_LITERAL(20, 237, 21), // "videoAvailableChanged"
QT_MOC_LITERAL(21, 259, 9), // "available"
QT_MOC_LITERAL(22, 269, 19), // "displayErrorMessage"
QT_MOC_LITERAL(23, 289, 15), // "showColorDialog"
QT_MOC_LITERAL(24, 305, 13), // "addToPlaylist"
QT_MOC_LITERAL(25, 319, 9) // "fileNames"

    },
    "Player\0fullScreenChanged\0\0fullScreen\0"
    "open\0durationChanged\0duration\0"
    "positionChanged\0progress\0metaDataChanged\0"
    "previousClicked\0seek\0seconds\0jump\0"
    "index\0playlistPositionChanged\0"
    "statusChanged\0QMediaPlayer::MediaStatus\0"
    "status\0bufferingProgress\0videoAvailableChanged\0"
    "available\0displayErrorMessage\0"
    "showColorDialog\0addToPlaylist\0fileNames"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Player[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   92,    2, 0x08 /* Private */,
       5,    1,   93,    2, 0x08 /* Private */,
       7,    1,   96,    2, 0x08 /* Private */,
       9,    0,   99,    2, 0x08 /* Private */,
      10,    0,  100,    2, 0x08 /* Private */,
      11,    1,  101,    2, 0x08 /* Private */,
      13,    1,  104,    2, 0x08 /* Private */,
      15,    1,  107,    2, 0x08 /* Private */,
      16,    1,  110,    2, 0x08 /* Private */,
      19,    1,  113,    2, 0x08 /* Private */,
      20,    1,  116,    2, 0x08 /* Private */,
      22,    0,  119,    2, 0x08 /* Private */,
      23,    0,  120,    2, 0x08 /* Private */,
      24,    1,  121,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    6,
    QMetaType::Void, QMetaType::LongLong,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::QModelIndex,   14,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   25,

       0        // eod
};

void Player::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Player *_t = static_cast<Player *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fullScreenChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->open(); break;
        case 2: _t->durationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 3: _t->positionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 4: _t->metaDataChanged(); break;
        case 5: _t->previousClicked(); break;
        case 6: _t->seek((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->jump((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->playlistPositionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->statusChanged((*reinterpret_cast< QMediaPlayer::MediaStatus(*)>(_a[1]))); break;
        case 10: _t->bufferingProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->videoAvailableChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->displayErrorMessage(); break;
        case 13: _t->showColorDialog(); break;
        case 14: _t->addToPlaylist((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::MediaStatus >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Player::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::fullScreenChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Player::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Player.data,
      qt_meta_data_Player,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Player::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Player::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Player.stringdata0))
        return static_cast<void*>(const_cast< Player*>(this));
    return QWidget::qt_metacast(_clname);
}

int Player::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Player::fullScreenChanged(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
