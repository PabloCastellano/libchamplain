/*
 * Copyright (C) 2008-2009 Pierre-Luc Beaudoin <pierre-luc@pierlux.com>
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

#ifndef CHAMPLAIN_MAP_SOURCE_H
#define CHAMPLAIN_MAP_SOURCE_H

#include <champlain/champlain-defines.h>
#include <champlain/champlain-tile.h>
#include <champlain/champlain-zoom-level.h>

#include <glib-object.h>

#define CHAMPLAIN_TYPE_MAP_SOURCE     (champlain_map_source_get_type())
#define CHAMPLAIN_MAP_SOURCE(obj)     (G_TYPE_CHECK_INSTANCE_CAST((obj), CHAMPLAIN_TYPE_MAP_SOURCE, ChamplainMapSource))
#define CHAMPLAIN_MAP_SOURCE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),  CHAMPLAIN_TYPE_MAP_SOURCE, ChamplainMapSourceClass))
#define CHAMPLAIN_IS_MAP_SOURCE(obj)  (G_TYPE_CHECK_INSTANCE_TYPE((obj), CHAMPLAIN_TYPE_MAP_SOURCE))
#define CHAMPLAIN_IS_MAP_SOURCE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),  CHAMPLAIN_TYPE_MAP_SOURCE))
#define CHAMPLAIN_MAP_SOURCE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj),  CHAMPLAIN_TYPE_MAP_SOURCE, ChamplainMapSourceClass))

typedef struct _ChamplainMapSource ChamplainMapSource;
typedef struct _ChamplainMapSourceClass ChamplainMapSourceClass;
typedef struct _ChamplainMapSourcePrivate ChamplainMapSourcePrivate;

typedef enum
{
  CHAMPLAIN_MAP_PROJECTION_MERCATOR
} ChamplainMapProjection;

typedef enum
{
  CHAMPLAIN_MAP_SOURCE_PARAMETER_X,
  CHAMPLAIN_MAP_SOURCE_PARAMETER_Y,
  CHAMPLAIN_MAP_SOURCE_PARAMETER_Z,
} ChamplainMapSourceParameter;

struct _ChamplainMapSource
{
  GObject parent;
  ChamplainMapSourcePrivate *priv;
};

struct _ChamplainMapSourceClass
{
  GObjectClass parent_class;
};

GType champlain_map_source_get_type (void);

ChamplainMapSource* champlain_map_source_new_network (gchar *name,
    gchar *license, gchar *license_uri, guint min_zoom, guint map_zoom,
    guint tile_size, ChamplainMapProjection projection, gchar *uri_format);

gint champlain_map_source_get_min_zoom_level (ChamplainMapSource *map_source);

gint champlain_map_source_get_max_zoom_level (ChamplainMapSource *map_source);

guint champlain_map_source_get_tile_size (ChamplainMapSource *map_source);

gchar * champlain_map_source_get_tile_uri (ChamplainMapSource *source,
    gint x, gint y, gint z);

void champlain_map_source_set_tile_uri (ChamplainMapSource *map_source,
    const gchar *uri_format);

ChamplainMapSource * champlain_map_source_new_osm_mapnik ();
ChamplainMapSource * champlain_map_source_new_oam ();
ChamplainMapSource * champlain_map_source_new_mff_relief ();

guint champlain_map_source_get_x (ChamplainMapSource *map_source,
    gint zoom_level, gdouble longitude);

guint champlain_map_source_get_y (ChamplainMapSource *map_source,
    gint zoom_level, gdouble latitude);

gdouble champlain_map_source_get_longitude (ChamplainMapSource *map_source,
    gint zoom_level, guint x);

gdouble champlain_map_source_get_latitude (ChamplainMapSource *map_source,
    gint zoom_level, guint y);

guint champlain_map_source_get_row_count (ChamplainMapSource *map_source,
    gint zoom_level);

guint champlain_map_source_get_column_count (ChamplainMapSource *map_source,
    gint zoom_level);
/*
void champlain_map_source_get_tile (ChamplainMapSource *map_source,
    ChamplainEngine *engine, ChamplainZoomLevel *level, ChamplainTile *tile);
*/
#endif