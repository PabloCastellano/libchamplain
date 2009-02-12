/*
 * Copyright (C) 2008 Pierre-Luc Beaudoin <pierre-luc@pierlux.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#if !defined (__CHAMPLAIN_CHAMPLAIN_H_INSIDE__) && !defined (CHAMPLAIN_COMPILATION)
#error "Only <champlain/champlain.h> can be included directly."
#endif

#ifndef CHAMPLAIN_VIEW_H
#define CHAMPLAIN_VIEW_H

#include <champlain/champlain-defines.h>

#include <glib.h>
#include <glib-object.h>
#include <clutter/clutter.h>

/**
 * ChamplainMapSource:
 * @CHAMPLAIN_MAP_SOURCE_DEBUG: Debug map, untested as of 0.2
 * @CHAMPLAIN_MAP_SOURCE_OPENSTREETMAP: Open Street Map - Mapnick tiles
 * @CHAMPLAIN_MAP_SOURCE_OPENARIALMAP: Open Arial Map
 * @CHAMPLAIN_MAP_SOURCE_MAPSFORFREE_RELIEF: Maps for free - Relief tiles
 *
 * Type of scrolling.
 */
typedef enum
{
  CHAMPLAIN_MAP_SOURCE_DEBUG,
  CHAMPLAIN_MAP_SOURCE_OPENSTREETMAP,
  CHAMPLAIN_MAP_SOURCE_OPENARIALMAP,
  CHAMPLAIN_MAP_SOURCE_MAPSFORFREE_RELIEF,
  CHAMPLAIN_MAP_SOURCE_COUNT
} ChamplainMapSource;

#define CHAMPLAIN_TYPE_VIEW     (champlain_view_get_type())
#define CHAMPLAIN_VIEW(obj)     (G_TYPE_CHECK_INSTANCE_CAST((obj), CHAMPLAIN_TYPE_VIEW, ChamplainView))
#define CHAMPLAIN_VIEW_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST((klass),  CHAMPLAIN_TYPE_VIEW, ChamplainViewClass))
#define CHAMPLAIN_IS_VIEW(obj)  (G_TYPE_CHECK_INSTANCE_TYPE((obj), CHAMPLAIN_TYPE_VIEW))
#define CHAMPLAIN_IS_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),  CHAMPLAIN_TYPE_VIEW))
#define CHAMPLAIN_VIEW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj),  CHAMPLAIN_TYPE_VIEW, ChamplainViewClass))

typedef struct _ChamplainViewPrivate ChamplainViewPrivate;

/**
 * ChamplainViewMode:
 * @CHAMPLAIN_VIEW_MODE_PUSH: Non-kinetic scrolling
 * @CHAMPLAIN_VIEW_MODE_KINETIC: Kinetic scrolling
 *
 * Type of scrolling.
 */
typedef enum {
  CHAMPLAIN_SCROLL_MODE_PUSH,
  CHAMPLAIN_SCROLL_MODE_KINETIC
} ChamplainScrollMode;

struct _ChamplainView
{
  ClutterGroup group;

  ChamplainViewPrivate *priv;
};

struct _ChamplainViewClass
{
  ClutterGroupClass parent_class;

};

GType champlain_view_get_type (void);

ClutterActor *champlain_view_new ();

void champlain_view_center_on (ChamplainView *view, gdouble latitude, gdouble longitude);

void champlain_view_zoom_in (ChamplainView *champlainView);

void champlain_view_zoom_out (ChamplainView *champlainView);

void champlain_view_add_layer (ChamplainView *champlainView, ClutterActor *layer);

void champlain_view_set_size (ChamplainView *view, guint width, guint height);

gboolean champlain_view_get_coords_from_event (ChamplainView *view, ClutterEvent *event, gdouble *lat, gdouble *lon);

#endif