////////////////////////////////////////////////////////////////////////
// json/wettkampf.cpp
// generated with ecppc
//

#include <tnt/ecpp.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <tnt/httpheader.h>
#include <tnt/http.h>
#include <tnt/data.h>
#include <tnt/componentfactory.h>
#include <cxxtools/log.h>
#include <stdexcept>

log_define("component.json.wettkampf")

// <%pre>
#line 5 "json/wettkampf.ecpp"


#include "wettkampfmanager.h"
#include "managercontext.h"
#include <cxxtools/json.h>


// </%pre>

namespace
{
class _component_ : public tnt::EcppComponent
{
    _component_& main()  { return *this; }

  protected:
    ~_component_();

  public:
    _component_(const tnt::Compident& ci, const tnt::Urlmapper& um, tnt::Comploader& cl);

    unsigned operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam);
};

static tnt::EcppComponentFactoryImpl<_component_> Factory("json/wettkampf");

// <%shared>
// </%shared>

// <%config>
// </%config>

#define SET_LANG(lang) \
     do \
     { \
       request.setLang(lang); \
       reply.setLocale(request.getLocale()); \
     } while (false)

_component_::_component_(const tnt::Compident& ci, const tnt::Urlmapper& um, tnt::Comploader& cl)
  : EcppComponent(ci, um, cl)
{
  // <%init>
  // </%init>
}

_component_::~_component_()
{
  // <%cleanup>
  // </%cleanup>
}

template <typename T>
inline void _tnt_ignore_unused(const T&) { }

unsigned _component_::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
  log_trace("json/wettkampf " << qparam.getUrl());


  // <%args>
unsigned vid = qparam.argt< unsigned >("vid", "unsigned");
bool beautify = qparam.argt< bool >("beautify", "bool");
  // </%args>

  // <%cpp>
#line 12 "json/wettkampf.ecpp"


ManagerContext ctx;
WettkampfManager wettkampfManager(ctx);

auto wettkaempfe = wettkampfManager.getWettkaempfe(vid);

reply.setContentType("application/json; charset=UTF-8");
reply.out() << cxxtools::Json(wettkaempfe).beautify(beautify);


  // <%/cpp>
  return DEFAULT;
}

} // namespace
