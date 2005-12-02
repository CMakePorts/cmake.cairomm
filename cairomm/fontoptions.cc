#include <cairomm/fontoptions.h>
#include <cairomm/private.h>

namespace Cairo
{

FontOptions::FontOptions()
: m_cobject(0)
{
  m_cobject = cairo_font_options_create();
}

FontOptions::FontOptions(cairo_font_options_t* cobject, bool take_ownership)
: m_cobject(0)
{
  if(take_ownership)
    m_cobject = cobject;
  else
    m_cobject = cairo_font_options_copy(cobject);
}

FontOptions::FontOptions(const FontOptions& src)
{
  //Reference-counting, instead of copying by value:
  if(!src.m_cobject)
    m_cobject = 0;
  else
    m_cobject = cairo_font_options_copy(src.m_cobject);
}

FontOptions::~FontOptions()
{
  if(m_cobject)
    cairo_font_options_destroy(m_cobject);
}


FontOptions& FontOptions::operator=(const FontOptions& src)
{
  //Reference-counting, instead of copying by value:

  if(this == &src)
    return *this;

  if(m_cobject == src.m_cobject)
    return *this;

  if(m_cobject)
  {
    cairo_font_options_destroy(m_cobject);
    m_cobject = 0;
  }

  if(!src.m_cobject)
    return *this;

  m_cobject = cairo_font_options_copy(src.m_cobject);

  return *this;
}

bool FontOptions::operator==(const FontOptions& src) const
{
  return cairo_font_options_equal(m_cobject, src.cobj());
}

void FontOptions::merge(const FontOptions& src)
{
  cairo_font_options_merge(m_cobject, src.cobj());
  check_object_status_and_throw_exception(*this);
}

unsigned long FontOptions::hash() const
{
  const unsigned long result = cairo_font_options_hash(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

void FontOptions::set_antialias(Antialias antialias)
{
  cairo_font_options_set_antialias(m_cobject, (cairo_antialias_t)antialias);
  check_object_status_and_throw_exception(*this);
}

Antialias FontOptions::get_antialias() const
{
  const Antialias result = cairo_font_options_get_antialias(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

void FontOptions::set_subpixel_order(SubpixelOrder subpixel_order)
{
  cairo_font_options_set_subpixel_order(m_cobject, (cairo_subpixel_order_t)subpixel_order);
  check_object_status_and_throw_exception(*this);
}

SubpixelOrder FontOptions::get_subpixel_order() const
{
  const SubpixelOrder result = cairo_font_options_get_subpixel_order(m_cobject);
  check_object_status_and_throw_exception(*this); 
  return result;
}

void FontOptions::set_hint_style(HintStyle hint_style)
{
  cairo_font_options_set_hint_style(m_cobject, (cairo_hint_style_t)hint_style);
  check_object_status_and_throw_exception(*this);
}

HintStyle FontOptions::get_hint_style() const
{
  const HintStyle result = cairo_font_options_get_hint_style(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

void FontOptions::set_hint_metrics(HintMetrics hint_metrics)
{
  cairo_font_options_set_hint_metrics(m_cobject, (cairo_hint_metrics_t)hint_metrics);
  check_object_status_and_throw_exception(*this);
}

HintMetrics FontOptions::get_hint_metrics() const
{
  const HintMetrics result = cairo_font_options_get_hint_metrics(m_cobject);
  check_object_status_and_throw_exception(*this);
  return result;
}

} //namespace Cairo