#ifndef JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PYTHON_BRIDGE_HPP_
#define JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PYTHON_BRIDGE_HPP_

#include <Python.h>
#include <jubatus/util/concurrent/lock.h>
#include <jubatus/util/concurrent/mutex.h>

#include <string>
#include <map>

#define USE_PYTHON_RUNTIME \
    jubatus::util::concurrent::scoped_lock lk(mutex_);

namespace jubatus {
namespace plugin {
namespace fv_converter {
namespace python {

// TODO just using Python GIL is fine?
static jubatus::util::concurrent::mutex mutex_;

void initialize();
PyObject* setup(const std::map<std::string, std::string>&);

}  // namespace python
}  // namespace fv_converter
}  // namespace plugin
}  // namespace jubatus

#endif  // JUBATUS_PLUGIN_FV_CONVERTER_PYTHON_PYTHON_BRIDGE_HPP_
