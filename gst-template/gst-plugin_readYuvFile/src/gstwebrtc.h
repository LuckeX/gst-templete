/*
 * GStreamer
 * Copyright (C) 2005 Thomas Vander Stichele <thomas@apestaart.org>
 * Copyright (C) 2005 Ronald S. Bultje <rbultje@ronald.bitfreak.net>
 * Copyright (C) 2019 xyk <<user@hostname.org>>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Alternatively, the contents of this file may be used under the
 * GNU Lesser General Public License Version 2.1 (the "LGPL"), in
 * which case the following provisions apply instead of the ones
 * mentioned above:
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GST_WEBRTC_H__
#define __GST_WEBRTC_H__

#include <gst/gst.h>
#include <pthread.h>
#include "case/wrapper.h"

G_BEGIN_DECLS

/* #defines don't like whitespacey bits */
#define GST_TYPE_WEBRTC \
  (gst_webrtc_get_type())
#define GST_WEBRTC(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_WEBRTC,Gstwebrtc))
#define GST_WEBRTC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_WEBRTC,GstwebrtcClass))
#define GST_IS_WEBRTC(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_WEBRTC))
#define GST_IS_WEBRTC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_WEBRTC))

typedef struct _Gstwebrtc      Gstwebrtc;
typedef struct _GstwebrtcClass GstwebrtcClass;

struct _Gstwebrtc
{
  GstElement element;

  GstPad *sinkpad;

  gboolean silent;

  gboolean start;
  
  
  gchar *peerserver;
  gchar *id;
  gchar *peerid;

  gint width,height,fps; 

  pthread_t thread;
};

struct _GstwebrtcClass 
{
  GstElementClass parent_class;
};

GType gst_webrtc_get_type (void);

G_END_DECLS

#endif /* __GST_WEBRTC_H__ */