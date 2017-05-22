#include "py_binary_feature.hpp"

#include <string>
#include <vector>
#include <map>
#include <utility>

#include <Python.h>

#include "python_bridge.hpp"

namespace jubatus {
namespace plugin {
namespace fv_converter {
namespace python {

void py_binary_feature::add_feature(
    const std::string& key,
    const std::string& value,
    std::vector<std::pair<std::string, float> >& ret_fv) const {
  scoped_gil lk;

  PyObject* ret = PyObject_CallMethodObjArgs(
      ins_,
      method_,
      PyString_FromStringAndSize(key.c_str(), key.length()),
      PyString_FromStringAndSize(value.c_str(), value.length()),
      NULL);

  // TODO raise instead of assert.
  assert(ret != NULL);
  assert(PyList_CheckExact(ret));

  size_t size = PyList_Size(ret);
  for (size_t i = 0; i < size; ++i) {
      PyObject* bound = PyList_GetItem(ret, i);

      // TODO
      assert(bound != NULL);
      assert(PyTuple_CheckExact(bound));
      assert(PyTuple_Size(bound) == 2);

      PyObject* f_key = PyTuple_GetItem(bound, 0);
      PyObject* f_value = PyTuple_GetItem(bound, 1);

      // TODO f_key may be unicode instead of str?
      assert(PyString_CheckExact(f_key));
      assert(PyFloat_CheckExact(f_value));

      ret_fv.push_back(std::make_pair(std::string(PyString_AsString(f_key)), PyFloat_AsDouble(f_value)));
  }

  Py_DECREF(ret);
}

extern "C" {

jubatus::core::fv_converter::binary_feature* binary_feature(
    std::map <std::string, std::string>& params) {
  initialize();
  return new py_binary_feature(setup(params));
}

}  // extern "C"

}  // namespace python
}  // namespace fv_converter
}  // namespace plugin
}  // namespace jubatus
