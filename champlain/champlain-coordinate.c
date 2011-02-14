/*
 * Copyright (C) 2011 Jiri Techet <techet@gmail.com>
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

/**
 * SECTION:champlain-coordinate
 * @short_description: A marker to identify points of interest on a map
 *
 * Markers reprensent points of interest on a map. Markers need to be
 * placed on a layer (a #ChamplainMarkerLayer). Layers have to be added to a
 * #champlainview for the markers to show on the map.
 *
 * A marker is nothing more than a regular #clutteractor. You can draw on
 * it what ever you want.  Set the markers position
 * on the map using #champlain_location_set_position.
 *
 * libchamplain has a more evoluted type of markers with text and image support.
 * See #ChamplainLabel.
 */

#include "champlain-coordinate.h"

#include "config.h"
#include "champlain-marshal.h"
#include "champlain-private.h"
#include "champlain-location.h"

enum
{
  PROP_0,
  PROP_LONGITUDE,
  PROP_LATITUDE,
};


static void set_position (ChamplainLocation *location,
    gdouble latitude,
    gdouble longitude);
static gdouble get_latitude (ChamplainLocation *location);
static gdouble get_longitude (ChamplainLocation *location);

static void location_interface_init (ChamplainLocationIface *iface);

G_DEFINE_TYPE_WITH_CODE (ChamplainCoordinate, champlain_coordinate, G_TYPE_INITIALLY_UNOWNED,
                         G_IMPLEMENT_INTERFACE (CHAMPLAIN_TYPE_LOCATION,
                                                location_interface_init));

#define CHAMPLAIN_COORDINATE_GET_PRIVATE(obj) \
  (G_TYPE_INSTANCE_GET_PRIVATE ((obj), CHAMPLAIN_TYPE_COORDINATE, ChamplainCoordinatePrivate))

struct _ChamplainCoordinatePrivate
{
  gdouble lon;
  gdouble lat;
};

static void
champlain_coordinate_get_property (GObject *object,
    guint prop_id,
    GValue *value,
    GParamSpec *pspec)
{
  ChamplainCoordinate *coordinate = CHAMPLAIN_COORDINATE (object);
  ChamplainCoordinatePrivate *priv = coordinate->priv;

  switch (prop_id)
    {
    case PROP_LONGITUDE:
      g_value_set_double (value, priv->lon);
      break;

    case PROP_LATITUDE:
      g_value_set_double (value, priv->lat);
      break;
      
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


static void
champlain_coordinate_set_property (GObject *object,
    guint prop_id,
    const GValue *value,
    GParamSpec *pspec)
{
  ChamplainCoordinate *coordinate = CHAMPLAIN_COORDINATE (object);
  ChamplainCoordinatePrivate *priv = coordinate->priv;

  switch (prop_id)
    {
    case PROP_LONGITUDE:
    {
      gdouble lon = g_value_get_double (value);
      set_position (CHAMPLAIN_LOCATION (coordinate), priv->lat, lon);
      break;
    }

    case PROP_LATITUDE:
    {
      gdouble lat = g_value_get_double (value);
      set_position (CHAMPLAIN_LOCATION (coordinate), lat, priv->lon);
      break;
    }

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}


static void
set_position (ChamplainLocation *location,
    gdouble latitude,
    gdouble longitude)
{
  g_return_if_fail (CHAMPLAIN_IS_COORDINATE (location));

  ChamplainCoordinatePrivate *priv = CHAMPLAIN_COORDINATE (location)->priv;

  priv->lon = longitude;
  priv->lat = latitude;

  g_object_notify (G_OBJECT (location), "latitude");
  g_object_notify (G_OBJECT (location), "longitude");
}


static gdouble
get_latitude (ChamplainLocation *location)
{
  g_return_val_if_fail (CHAMPLAIN_IS_COORDINATE (location), 0.0);

  ChamplainCoordinatePrivate *priv = CHAMPLAIN_COORDINATE (location)->priv;

  return priv->lat;
}


static gdouble
get_longitude (ChamplainLocation *location)
{
  g_return_val_if_fail (CHAMPLAIN_IS_COORDINATE (location), 0.0);

  ChamplainCoordinatePrivate *priv = CHAMPLAIN_COORDINATE (location)->priv;

  return priv->lon;
}


static void
location_interface_init (ChamplainLocationIface *iface)
{
  iface->get_latitude = get_latitude;
  iface->get_longitude = get_longitude;
  iface->set_position = set_position;
}


static void
champlain_coordinate_dispose (GObject *object)
{
  G_OBJECT_CLASS (champlain_coordinate_parent_class)->dispose (object);
}


static void
champlain_coordinate_finalize (GObject *object)
{
  G_OBJECT_CLASS (champlain_coordinate_parent_class)->finalize (object);
}


static void
champlain_coordinate_class_init (ChamplainCoordinateClass *coordinate_class)
{
  g_type_class_add_private (coordinate_class, sizeof (ChamplainCoordinatePrivate));

  GObjectClass *object_class = G_OBJECT_CLASS (coordinate_class);
  object_class->finalize = champlain_coordinate_finalize;
  object_class->dispose = champlain_coordinate_dispose;
  object_class->get_property = champlain_coordinate_get_property;
  object_class->set_property = champlain_coordinate_set_property;

  g_object_class_override_property (object_class,
                                    PROP_LONGITUDE,
                                    "longitude");

  g_object_class_override_property (object_class,
                                    PROP_LATITUDE,
                                    "latitude");
}


static void
champlain_coordinate_init (ChamplainCoordinate *coordinate)
{
  ChamplainCoordinatePrivate *priv = CHAMPLAIN_COORDINATE_GET_PRIVATE (coordinate);

  coordinate->priv = priv;

  priv->lat = 0;
  priv->lon = 0;
}


ChamplainCoordinate *
champlain_coordinate_new ()
{
  return CHAMPLAIN_COORDINATE (g_object_new (CHAMPLAIN_TYPE_COORDINATE, NULL));
}


ChamplainCoordinate *
champlain_coordinate_new_full (gdouble latitude, 
    gdouble longitude)
{
  return CHAMPLAIN_COORDINATE (g_object_new (CHAMPLAIN_TYPE_COORDINATE, 
      "latitude", latitude, 
      "longitude", longitude, 
      NULL));
}
