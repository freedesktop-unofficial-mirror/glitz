/*
 * Copyright � 2004 David Reveman, Peter Nilsson
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without
 * fee, provided that the above copyright notice appear in all copies
 * and that both that copyright notice and this permission notice
 * appear in supporting documentation, and that the names of
 * David Reveman and Peter Nilsson not be used in advertising or
 * publicity pertaining to distribution of the software without
 * specific, written prior permission. David Reveman and Peter Nilsson
 * makes no representations about the suitability of this software for
 * any purpose. It is provided "as is" without express or implied warranty.
 *
 * DAVID REVEMAN AND PETER NILSSON DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL DAVID REVEMAN AND
 * PETER NILSSON BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
 * OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * Authors: David Reveman <c99drn@cs.umu.se>
 *          Peter Nilsson <c99pnn@cs.umu.se>
 */

#ifdef HAVE_CONFIG_H
#  include "../config.h"
#endif

#include "glitz_aglint.h"

#include <OpenGL/glext.h>

glitz_gl_proc_address_list_t _glitz_agl_gl_proc_address = {
  (glitz_gl_enable_t) glEnable,
  (glitz_gl_disable_t) glDisable,
  (glitz_gl_begin_t) glBegin,
  (glitz_gl_end_t) glEnd,
  (glitz_gl_vertex_2i_t) glVertex2i,
  (glitz_gl_vertex_2d_t) glVertex2d,
  (glitz_gl_tex_env_f_t) glTexEnvf,
  (glitz_gl_tex_env_fv_t) glTexEnvfv,
  (glitz_gl_tex_coord_2d_t) glTexCoord2d,
  (glitz_gl_color_4us_t) glColor4us,
  (glitz_gl_color_4d_t) glColor4d,
  (glitz_gl_scissor_t) glScissor,
  (glitz_gl_blend_func_t) glBlendFunc,
  (glitz_gl_clear_t) glClear,
  (glitz_gl_clear_color_t) glClearColor,
  (glitz_gl_clear_stencil_t) glClearStencil,
  (glitz_gl_stencil_func_t) glStencilFunc,
  (glitz_gl_stencil_op_t) glStencilOp,
  (glitz_gl_push_attrib_t) glPushAttrib,
  (glitz_gl_pop_attrib_t) glPopAttrib,
  (glitz_gl_matrix_mode_t) glMatrixMode,
  (glitz_gl_push_matrix_t) glPushMatrix,
  (glitz_gl_pop_matrix_t) glPopMatrix,
  (glitz_gl_load_identity_t) glLoadIdentity,
  (glitz_gl_load_matrix_d_t) glLoadMatrixd,
  (glitz_gl_mult_matrix_d_t) glMultMatrixd,
  (glitz_gl_depth_range_t) glDepthRange,
  (glitz_gl_viewport_t) glViewport,
  (glitz_gl_raster_pos_2d_t) glRasterPos2d,
  (glitz_gl_bitmap_t) glBitmap,
  (glitz_gl_read_buffer_t) glReadBuffer,
  (glitz_gl_draw_buffer_t) glDrawBuffer,
  (glitz_gl_copy_pixels_t) glCopyPixels,
  (glitz_gl_flush_t) glFlush,
  (glitz_gl_finish_t) glFinish,
  (glitz_gl_pixel_store_i_t) glPixelStorei,
  (glitz_gl_ortho_t) glOrtho,
  (glitz_gl_scale_d_t) glScaled,
  (glitz_gl_translate_d_t) glTranslated,
  (glitz_gl_hint_t) glHint,
  (glitz_gl_depth_mask_t) glDepthMask,
  (glitz_gl_polygon_mode_t) glPolygonMode,
  (glitz_gl_shade_model_t) glShadeModel,
  (glitz_gl_color_mask_t) glColorMask,
  (glitz_gl_read_pixels_t) glReadPixels,
  (glitz_gl_get_tex_image_t) glGetTexImage,
  (glitz_gl_tex_sub_image_2d_t) glTexSubImage2D,
  (glitz_gl_gen_textures_t) glGenTextures,
  (glitz_gl_delete_textures_t) glDeleteTextures,
  (glitz_gl_bind_texture_t) glBindTexture,
  (glitz_gl_tex_image_1d_t) glTexImage1D,
  (glitz_gl_tex_image_2d_t) glTexImage2D,
  (glitz_gl_tex_parameter_i_t) glTexParameteri,
  (glitz_gl_get_tex_level_parameter_iv_t) glGetTexLevelParameteriv,
  (glitz_gl_copy_tex_sub_image_2d_t) glCopyTexSubImage2D,
  (glitz_gl_get_integer_v_t) glGetIntegerv,
  (glitz_gl_delete_lists_t) glDeleteLists,
  (glitz_gl_gen_lists_t) glGenLists,
  (glitz_gl_new_list_t) glNewList,
  (glitz_gl_end_list_t) glEndList,
  (glitz_gl_call_list_t) glCallList,
  
  (glitz_gl_active_texture_t) glActiveTextureARB,
  (glitz_gl_multi_tex_coord_2d_t) glMultiTexCoord2dARB,
  (glitz_gl_gen_programs_t) glGenProgramsARB,
  (glitz_gl_delete_programs_t) glDeleteProgramsARB,
  (glitz_gl_program_string_t) glProgramStringARB,
  (glitz_gl_bind_program_t) glBindProgramARB,
  (glitz_gl_program_local_param_4d_t) glProgramLocalParameter4dARB,
  (glitz_gl_get_program_iv_t) glGetProgramivARB,
  (glitz_gl_gen_buffers_t) 0,
  (glitz_gl_delete_buffers_t) 0,
  (glitz_gl_bind_buffer_t) 0,
  (glitz_gl_buffer_data_t) 0,
  (glitz_gl_map_buffer_t) 0,
  (glitz_gl_unmap_buffer_t) 0,
  0
};

static void
glitz_agl_thread_info_init (glitz_agl_thread_info_t *thread_info);

static void
glitz_agl_thread_info_fini (glitz_agl_thread_info_t *thread_info);

#ifdef PTHREADS

#include <pthread.h>
#include <stdlib.h>

/* thread safe */
static int tsd_initialized = 0;
static pthread_key_t info_tsd;

static void
glitz_agl_thread_info_destroy (glitz_agl_thread_info_t *thread_info)
{
  pthread_setspecific (info_tsd, NULL);
  
  if (thread_info) {
    glitz_agl_thread_info_fini (thread_info);
    free (thread_info);
  }
}

static void
_tsd_destroy (void *p)
{
  if (p) {
    glitz_agl_thread_info_fini ((glitz_agl_thread_info_t *) p);
    free (p);
  }
}

glitz_agl_thread_info_t *
glitz_agl_thread_info_get (void)
{
  glitz_agl_thread_info_t *thread_info;
  void *p;
  
  if (!tsd_initialized) {
    pthread_key_create (&info_tsd, _tsd_destroy);
    tsd_initialized = 1;
  }
  
  p = pthread_getspecific (info_tsd);

  if (p == NULL) {
    thread_info = malloc (sizeof (glitz_agl_thread_info_t));
    glitz_agl_thread_info_init (thread_info);
  
    pthread_setspecific (info_tsd, thread_info);
  } else
    thread_info = (glitz_agl_thread_info_t *) p;
  
  return thread_info;
}

#else

/* not thread safe */
static glitz_agl_thread_info_t _thread_info = {
  NULL,
  NULL,
  0,
  NULL,
  0,
  { 0 },
  0,
  { 0 },
  0,
  0,
  0,
  0,
  { 0 }
};

static void
glitz_agl_thread_info_destroy (glitz_agl_thread_info_t *thread_info)
{
  if (thread_info)
    glitz_agl_thread_info_fini (thread_info);
}

glitz_agl_thread_info_t *
glitz_agl_thread_info_get (void)
{
  if (_thread_info.context_stack_size == 0)
    glitz_agl_thread_info_init (&_thread_info);
      
  return &_thread_info;
}

#endif

static void
glitz_agl_thread_info_init (glitz_agl_thread_info_t *thread_info)
{
  GLint attrib[] = {
    AGL_RGBA,
    AGL_NO_RECOVERY,
    AGL_NONE
  };

  thread_info->formats = NULL;
  thread_info->format_ids = NULL;
  thread_info->n_formats = 0;
  thread_info->contexts = NULL;
  thread_info->n_contexts = 0;

  glitz_program_map_init (&thread_info->program_map);
  
  thread_info->root_context.pixel_format =
    aglChoosePixelFormat (NULL, 0, attrib);
  if (thread_info->root_context.pixel_format) {
    thread_info->root_context.context =
      aglCreateContext (thread_info->root_context.pixel_format, NULL);
    if (thread_info->root_context.context) {

      aglSetCurrentContext (thread_info->root_context.context);
  
      glitz_agl_query_extensions (thread_info);  
      glitz_agl_query_formats (thread_info);
    }
  }

  thread_info->context_stack_size = 1;
  thread_info->context_stack->surface = NULL;
  thread_info->context_stack->constraint = GLITZ_CN_NONE;
}

static void
glitz_agl_thread_info_fini (glitz_agl_thread_info_t *thread_info)
{
  int i;

  if (thread_info->root_context.context) {
    aglSetCurrentContext (thread_info->root_context.context);
    glitz_program_map_fini (&_glitz_agl_gl_proc_address,
                            &thread_info->program_map);
    aglSetCurrentContext (NULL);
  }

  for (i = 0; i < thread_info->n_contexts; i++)
    glitz_agl_context_destroy (thread_info, thread_info->contexts[i]);

  for (i = 0; i < thread_info->n_formats; i++)
    aglDestroyPixelFormat (thread_info->format_ids[i]);

  if (thread_info->formats)
    free (thread_info->formats);
  
  if (thread_info->format_ids)
    free (thread_info->format_ids);

  if (thread_info->root_context.context)
    aglDestroyContext (thread_info->root_context.context);
}

void
glitz_agl_init (void)
{
  glitz_agl_thread_info_get ();
}
slim_hidden_def(glitz_agl_init);

void
glitz_agl_fini (void)
{
  glitz_agl_thread_info_t *info =
    glitz_agl_thread_info_get ();

  glitz_agl_thread_info_destroy (info);
}
slim_hidden_def(glitz_agl_fini);
