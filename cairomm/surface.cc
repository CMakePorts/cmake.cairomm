#include <cairomm/surface.h>
#include <cairomm/private.h>

namespace Cairo
{

Surface::Surface(cairo_surface_t*  cobject, bool has_reference)
: m_cobject(0)
{
  if(has_reference)
    m_cobject = cobject;
  else
    m_cobject = cairo_surface_reference(cobject);
}

Surface::Surface(const Surface& src)
{
  //Reference-counting, instead of copying by value:
  if(!src.m_cobject)
    m_cobject = 0;
  else
    m_cobject = cairo_surface_reference(src.m_cobject);
}

Surface::~Surface()
{
  if(m_cobject)
    cairo_surface_destroy(m_cobject);
}


Surface& Surface::operator=(const Surface& src)
{
  //Reference-counting, instead of copying by value:

  if(this == &src)
    return *this;

  if(m_cobject == src.m_cobject)
    return *this;

  if(m_cobject)
  {
    cairo_surface_destroy(m_cobject);
    m_cobject = 0;
  }

  if(!src.m_cobject)
    return *this;

  m_cobject = cairo_surface_reference(src.m_cobject);

  return *this;
}

Surface Surface::create(Format format, int width, int height)
{
  cairo_surface_t* cobject = cairo_image_surface_create((cairo_format_t)format, width, height);
  //Not possible with a static method: check_object_status_and_throw_exception(*this);
  return Surface(cobject, true /* has reference */);
}

Surface Surface::create(unsigned char* data, Format format, int width, int height, int stride)
{
  cairo_surface_t* cobject = cairo_image_surface_create_for_data(data, (cairo_format_t)format, width, height, stride);
  //Not possible with a static method: check_object_status_and_throw_exception(*this);
  return Surface(cobject, true /* has reference */);
}

Surface Surface::create(const Surface& other, Content content, int width, int height)
{
  cairo_surface_t* cobject = cairo_surface_create_similar(other.m_cobject, (cairo_content_t)content, width, height);
  //Not possible with a static method: check_object_status_and_throw_exception(*this);
  return Surface(cobject, true /* has reference */);
}

void Surface::finish()
{
  cairo_surface_finish(m_cobject);
  check_object_status_and_throw_exception(*this);
}

/* Seems to have been removed from the Cairo API:
Status Surface::write_to_png(const std::string& filename)
{
  return (Status)cairo_surface_write_to_png(m_cobject, filename.c_str());
}

Status Surface::write_to_png_stream(cairo_write_func_t write_func, void *closure)
{
  return (Status)cairo_surface_write_to_png_stream(m_cobject, write_func, closure);
}
*/

void* Surface::get_user_data(const cairo_user_data_key_t *key)
{
  void* result = cairo_surface_get_user_data(m_cobject, key);
  check_object_status_and_throw_exception(*this);
  return result;
}

void Surface::set_user_data(const cairo_user_data_key_t* key, void *user_data, cairo_destroy_func_t destroy)
{
  const Status status = (Status)cairo_surface_set_user_data(m_cobject, key, user_data, destroy);
  check_status_and_throw_exception(status);
}

void Surface::get_font_options(FontOptions& options)
{
  cairo_font_options_t* cfontoptions = cairo_font_options_create();
  cairo_surface_get_font_options(m_cobject, cfontoptions);
  options = FontOptions(cfontoptions);
  cairo_font_options_destroy(cfontoptions);
  check_object_status_and_throw_exception(*this);
}

void Surface::flush()
{
  cairo_surface_flush(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Surface::mark_dirty()
{
  cairo_surface_mark_dirty(m_cobject);
  check_object_status_and_throw_exception(*this);
}

void Surface::mark_dirty(int x, int y, int width, int height)
{
  cairo_surface_mark_dirty_rectangle(m_cobject, x, y, width, height);
  check_object_status_and_throw_exception(*this);
}

void Surface::set_device_offset(double x_offset, double y_offset)
{
  cairo_surface_set_device_offset(m_cobject, x_offset, y_offset);
  check_object_status_and_throw_exception(*this);
}

int Surface::get_width() const
{
  const int result = cairo_image_surface_get_width(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

int Surface::get_height() const
{
  const int result = cairo_image_surface_get_height(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

} //namespace Cairo