/*
 * Copyright (C) 2017 Canonical Ltd.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2 or version 3 of the License.
 * See http://www.gnu.org/copyleft/lgpl.html the full text of the license.
 */

#include "snapd-get-users.h"

#include "snapd-error.h"
#include "snapd-json.h"

struct _SnapdGetUsers
{
    SnapdRequest parent_instance;
    GPtrArray *users_information;
};

G_DEFINE_TYPE (SnapdGetUsers, snapd_get_users, snapd_request_get_type ())

SnapdGetUsers *
_snapd_get_users_new (GCancellable *cancellable, GAsyncReadyCallback callback, gpointer user_data)
{
    return SNAPD_GET_USERS (g_object_new (snapd_get_users_get_type (),
                                          "cancellable", cancellable,
                                          "ready-callback", callback,
                                          "ready-callback-data", user_data,
                                          NULL));
}

GPtrArray *
_snapd_get_users_get_users_information (SnapdGetUsers *request)
{
    return request->users_information;
}

static SoupMessage *
generate_get_users_request (SnapdRequest *request)
{
    return soup_message_new ("GET", "http://snapd/v2/users");
}

static gboolean
parse_get_users_response (SnapdRequest *request, SoupMessage *message, GError **error)
{
    SnapdGetUsers *r = SNAPD_GET_USERS (request);
    g_autoptr(JsonObject) response = NULL;
    g_autoptr(JsonArray) result = NULL;
    g_autoptr(GPtrArray) users_information = NULL;
    guint i;

    response = _snapd_json_parse_response (message, error);
    if (response == NULL)
        return FALSE;
    result = _snapd_json_get_sync_result_a (response, error);
    if (result == NULL)
        return FALSE;

    users_information = g_ptr_array_new_with_free_func (g_object_unref);
    for (i = 0; i < json_array_get_length (result); i++) {
        JsonNode *node = json_array_get_element (result, i);
        SnapdUserInformation *user_information;

        if (json_node_get_value_type (node) != JSON_TYPE_OBJECT) {
            g_set_error (error,
                         SNAPD_ERROR,
                         SNAPD_ERROR_READ_FAILED,
                         "Unexpected user information type");
            return FALSE;
        }

        user_information = _snapd_json_parse_user_information (json_node_get_object (node), error);
        if (user_information == NULL)
            return FALSE;
        g_ptr_array_add (users_information, user_information);
    }

    r->users_information = g_steal_pointer (&users_information);

    return TRUE;
}

static void
snapd_get_users_finalize (GObject *object)
{
    SnapdGetUsers *request = SNAPD_GET_USERS (object);

    g_clear_pointer (&request->users_information, g_ptr_array_unref);

    G_OBJECT_CLASS (snapd_get_users_parent_class)->finalize (object);
}

static void
snapd_get_users_class_init (SnapdGetUsersClass *klass)
{
   SnapdRequestClass *request_class = SNAPD_REQUEST_CLASS (klass);
   GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

   request_class->generate_request = generate_get_users_request;
   request_class->parse_response = parse_get_users_response;
   gobject_class->finalize = snapd_get_users_finalize;
}

static void
snapd_get_users_init (SnapdGetUsers *request)
{
}