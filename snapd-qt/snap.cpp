/*
 * Copyright (C) 2016 Canonical Ltd.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2 or version 3 of the License.
 * See http://www.gnu.org/copyleft/lgpl.html the full text of the license.
 */

#include <snapd-glib/snapd-glib.h>

#include "Snapd/snap.h"

QSnapdSnap::QSnapdSnap (void *snapd_object, QObject *parent) :
    QSnapdWrappedObject (snapd_object, g_object_unref, parent) {}

int QSnapdSnap::appCount () const
{
    GPtrArray *apps;

    apps = snapd_snap_get_apps (SNAPD_SNAP (wrapped_object));
    return apps != NULL ? apps->len : 0;
}

QSnapdApp *QSnapdSnap::app (int n) const
{
    GPtrArray *apps;

    apps = snapd_snap_get_apps (SNAPD_SNAP (wrapped_object));
    if (apps == NULL || n < 0 || (guint) n >= apps->len)
        return NULL;
    return new QSnapdApp (g_object_ref (apps->pdata[n]));
}

QString QSnapdSnap::channel () const
{
    return snapd_snap_get_channel (SNAPD_SNAP (wrapped_object));
}

/* FIXME
QSnapdSnap::Confinement QSnapdSnap::confinement () const
{
}*/

QString QSnapdSnap::description () const
{
    return snapd_snap_get_description (SNAPD_SNAP (wrapped_object));
}

QString QSnapdSnap::developer () const
{
    return snapd_snap_get_developer (SNAPD_SNAP (wrapped_object));
}

bool QSnapdSnap::devmode () const
{
    return snapd_snap_get_devmode (SNAPD_SNAP (wrapped_object));
}

qint64 QSnapdSnap::downloadSize () const
{
    return snapd_snap_get_download_size (SNAPD_SNAP (wrapped_object));
}

QString QSnapdSnap::icon () const
{
    return snapd_snap_get_icon (SNAPD_SNAP (wrapped_object));
}

QString QSnapdSnap::id () const
{
    return snapd_snap_get_id (SNAPD_SNAP (wrapped_object));
}

/* FIXME
GDateTime QSnapdSnap::installDate () const
{
}*/

qint64 QSnapdSnap::installedSize () const
{
    return snapd_snap_get_installed_size (SNAPD_SNAP (wrapped_object));
}

QString QSnapdSnap::name () const
{
    return snapd_snap_get_name (SNAPD_SNAP (wrapped_object));
}

int QSnapdSnap::priceCount () const
{
    GPtrArray *prices;

    prices = snapd_snap_get_prices (SNAPD_SNAP (wrapped_object));
    return prices != NULL ? prices->len : 0;
}

QSnapdPrice *QSnapdSnap::price (int n) const
{
    GPtrArray *prices;

    prices = snapd_snap_get_prices (SNAPD_SNAP (wrapped_object));
    if (prices == NULL || n < 0 || (guint) n >= prices->len)
        return NULL;
    return new QSnapdPrice (g_object_ref (prices->pdata[n]));
}

bool QSnapdSnap::isPrivate () const
{
    return snapd_snap_get_private (SNAPD_SNAP (wrapped_object));
}

QString QSnapdSnap::revision () const
{
    return snapd_snap_get_revision (SNAPD_SNAP (wrapped_object));
}

/* FIXME
QSnapdSnap::QSnapdSnapType QSnapdSnap::snapType () const
{
}*/

/* FIXME
QSnapdSnap::QSnapdSnapStatus QSnapdSnap::status () const
{
}*/

QString QSnapdSnap::summary () const
{
    return snapd_snap_get_summary (SNAPD_SNAP (wrapped_object));
}

bool QSnapdSnap::trymode () const
{
    return snapd_snap_get_trymode (SNAPD_SNAP (wrapped_object));
}

QString QSnapdSnap::version () const
{
    return snapd_snap_get_version (SNAPD_SNAP (wrapped_object));
}
