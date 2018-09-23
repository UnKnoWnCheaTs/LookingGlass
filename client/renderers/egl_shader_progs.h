/*
Looking Glass - KVM FrameRelay (KVMFR) Client
Copyright (C) 2017 Geoffrey McRae <geoff@hostfission.com>
https://looking-glass.hostfission.com

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef _EGL_SHADER_PROGS_H
#define _EGL_SHADER_PROGS_H

static const char egl_vertex_shader_basic[] = "\
#version 300 es\n\
\
layout(location = 0) in vec3 vertexPosition_modelspace;\
layout(location = 1) in vec2 vertexUV;\
\
out highp vec2 uv;\
\
void main()\
{\
  gl_Position.xyz = vertexPosition_modelspace;\
  gl_Position.w   = 1.0;\
\
  uv = vertexUV;\
}\
";

static const char egl_fragment_shader_rgba[] = "\
#version 300 es\n\
\
in  highp vec2 uv;\
out highp vec3 color;\
\
uniform sampler2D sampler1;\
 \
void main()\
{\
  color = texture(sampler1, uv).rgb;\
}\
";

static const char egl_fragment_shader_bgra[] = "\
#version 300 es\n\
\
in  highp vec2 uv;\
out highp vec3 color;\
\
uniform sampler2D sampler1;\
\
void main()\
{\
  highp vec3 tmp = texture(sampler1, uv).rgb;\
  color.r = tmp.b;\
  color.g = tmp.g;\
  color.b = tmp.r;\
}\
";

static const char egl_fragment_shader_yuv[] = "\
#version 300 es\n\
\
in  highp vec2 uv;\
out highp vec4 color;\
\
uniform sampler2D sampler1;\
uniform sampler2D sampler2;\
uniform sampler2D sampler3;\
\
void main()\
{\
  highp vec4 yuv = vec4(\
    texture(sampler1, uv).r,\
    texture(sampler2, uv).r,\
    texture(sampler3, uv).r,\
    1.0\
  );\
  \
  highp mat4 yuv_to_rgb = mat4(\
    1.0,  0.0  ,  1.402, -0.701,\
    1.0, -0.344, -0.714,  0.529,\
    1.0,  1.772,  0.0  , -0.886,\
    1.0,  1.0  ,  1.0  ,  1.0\
  );\
  \
  color = yuv * yuv_to_rgb;\
}\
";

#endif