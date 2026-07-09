/****************************************************************************
** Meta object code from reading C++ file 'DettaglioSpedizioneWidget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../View/DettaglioSpedizioneWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DettaglioSpedizioneWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN25DettaglioSpedizioneWidgetE_t {};
} // unnamed namespace

template <> constexpr inline auto DettaglioSpedizioneWidget::qt_create_metaobjectdata<qt_meta_tag_ZN25DettaglioSpedizioneWidgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DettaglioSpedizioneWidget",
        "richiestaModifica",
        "",
        "id",
        "richiestaEliminazione",
        "richiestaIndietro"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'richiestaModifica'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'richiestaEliminazione'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'richiestaIndietro'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DettaglioSpedizioneWidget, qt_meta_tag_ZN25DettaglioSpedizioneWidgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DettaglioSpedizioneWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN25DettaglioSpedizioneWidgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN25DettaglioSpedizioneWidgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN25DettaglioSpedizioneWidgetE_t>.metaTypes,
    nullptr
} };

void DettaglioSpedizioneWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DettaglioSpedizioneWidget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->richiestaModifica((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->richiestaEliminazione((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->richiestaIndietro(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DettaglioSpedizioneWidget::*)(const QString & )>(_a, &DettaglioSpedizioneWidget::richiestaModifica, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (DettaglioSpedizioneWidget::*)(const QString & )>(_a, &DettaglioSpedizioneWidget::richiestaEliminazione, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (DettaglioSpedizioneWidget::*)()>(_a, &DettaglioSpedizioneWidget::richiestaIndietro, 2))
            return;
    }
}

const QMetaObject *DettaglioSpedizioneWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DettaglioSpedizioneWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN25DettaglioSpedizioneWidgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DettaglioSpedizioneWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DettaglioSpedizioneWidget::richiestaModifica(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void DettaglioSpedizioneWidget::richiestaEliminazione(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void DettaglioSpedizioneWidget::richiestaIndietro()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
