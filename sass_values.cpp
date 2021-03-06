#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#include <cstdlib>
#include <cstring>
#include "sass_values.h"

extern "C" {
  using namespace std;

  struct Sass_Unknown {
    enum Sass_Tag tag;
  };

  struct Sass_Boolean {
    enum Sass_Tag tag;
    bool          value;
  };

  struct Sass_Number {
    enum Sass_Tag tag;
    double        value;
    char*         unit;
  };

  struct Sass_Color {
    enum Sass_Tag tag;
    double        r;
    double        g;
    double        b;
    double        a;
  };

  struct Sass_String {
    enum Sass_Tag tag;
    char*         value;
  };

  struct Sass_List {
    enum Sass_Tag       tag;
    enum Sass_Separator separator;
    size_t              length;
    // null terminated "array"
    union Sass_Value**  values;
  };

  struct Sass_Map {
    enum Sass_Tag        tag;
    size_t               length;
    struct Sass_MapPair* pairs;
  };

  struct Sass_Null {
    enum Sass_Tag tag;
  };

  struct Sass_Error {
    enum Sass_Tag tag;
    char*         message;
  };

  struct Sass_Warning {
    enum Sass_Tag tag;
    char*         message;
  };

  union Sass_Value {
    struct Sass_Unknown unknown;
    struct Sass_Boolean boolean;
    struct Sass_Number  number;
    struct Sass_Color   color;
    struct Sass_String  string;
    struct Sass_List    list;
    struct Sass_Map     map;
    struct Sass_Null    null;
    struct Sass_Error   error;
    struct Sass_Warning   warning;
  };

  struct Sass_MapPair {
    union Sass_Value* key;
    union Sass_Value* value;
  };

  // Return the sass tag for a generic sass value
  enum Sass_Tag ADDCALL sass_value_get_tag(const union Sass_Value* v) { return v->unknown.tag; }

  // Check value for specified type
  bool ADDCALL sass_value_is_null(const union Sass_Value* v) { return v->unknown.tag == SASS_NULL; }
  bool ADDCALL sass_value_is_number(const union Sass_Value* v) { return v->unknown.tag == SASS_NUMBER; }
  bool ADDCALL sass_value_is_string(const union Sass_Value* v) { return v->unknown.tag == SASS_STRING; }
  bool ADDCALL sass_value_is_boolean(const union Sass_Value* v) { return v->unknown.tag == SASS_BOOLEAN; }
  bool ADDCALL sass_value_is_color(const union Sass_Value* v) { return v->unknown.tag == SASS_COLOR; }
  bool ADDCALL sass_value_is_list(const union Sass_Value* v) { return v->unknown.tag == SASS_LIST; }
  bool ADDCALL sass_value_is_map(const union Sass_Value* v) { return v->unknown.tag == SASS_MAP; }
  bool ADDCALL sass_value_is_error(const union Sass_Value* v) { return v->unknown.tag == SASS_ERROR; }
  bool ADDCALL sass_value_is_warning(const union Sass_Value* v) { return v->unknown.tag == SASS_WARNING; }

  // Getters and setters for Sass_Number
  double ADDCALL sass_number_get_value(const union Sass_Value* v) { return v->number.value; }
  void ADDCALL sass_number_set_value(union Sass_Value* v, double value) { v->number.value = value; }
  const char* ADDCALL sass_number_get_unit(const union Sass_Value* v) { return v->number.unit; }
  void ADDCALL sass_number_set_unit(union Sass_Value* v, char* unit) { v->number.unit = unit; }

  // Getters and setters for Sass_String
  const char* ADDCALL sass_string_get_value(const union Sass_Value* v) { return v->string.value; }
  void ADDCALL sass_string_set_value(union Sass_Value* v, char* value) { v->string.value = value; }

  // Getters and setters for Sass_Boolean
  bool ADDCALL sass_boolean_get_value(const union Sass_Value* v) { return v->boolean.value; }
  void ADDCALL sass_boolean_set_value(union Sass_Value* v, bool value) { v->boolean.value = value; }

  // Getters and setters for Sass_Color
  double ADDCALL sass_color_get_r(const union Sass_Value* v) { return v->color.r; }
  void ADDCALL sass_color_set_r(union Sass_Value* v, double r) { v->color.r = r; }
  double ADDCALL sass_color_get_g(const union Sass_Value* v) { return v->color.g; }
  void ADDCALL sass_color_set_g(union Sass_Value* v, double g) { v->color.g = g; }
  double ADDCALL sass_color_get_b(const union Sass_Value* v) { return v->color.b; }
  void ADDCALL sass_color_set_b(union Sass_Value* v, double b) { v->color.b = b; }
  double ADDCALL sass_color_get_a(const union Sass_Value* v) { return v->color.a; }
  void ADDCALL sass_color_set_a(union Sass_Value* v, double a) { v->color.a = a; }

  // Getters and setters for Sass_List
  size_t ADDCALL sass_list_get_length(const union Sass_Value* v) { return v->list.length; }
  enum Sass_Separator ADDCALL sass_list_get_separator(const union Sass_Value* v) { return v->list.separator; }
  void ADDCALL sass_list_set_separator(union Sass_Value* v, enum Sass_Separator separator) { v->list.separator = separator; }
  // Getters and setters for Sass_List values
  union Sass_Value* ADDCALL sass_list_get_value(const union Sass_Value* v, size_t i) { return v->list.values[i]; }
  void ADDCALL sass_list_set_value(union Sass_Value* v, size_t i, union Sass_Value* value) { v->list.values[i] = value; }

  // Getters and setters for Sass_Map
  size_t ADDCALL sass_map_get_length(const union Sass_Value* v) { return v->map.length; }
  // Getters and setters for Sass_List keys and values
  union Sass_Value* ADDCALL sass_map_get_key(const union Sass_Value* v, size_t i) { return v->map.pairs[i].key; }
  union Sass_Value* ADDCALL sass_map_get_value(const union Sass_Value* v, size_t i) { return v->map.pairs[i].value; }
  void ADDCALL sass_map_set_key(union Sass_Value* v, size_t i, union Sass_Value* key) { v->map.pairs[i].key = key; }
  void ADDCALL sass_map_set_value(union Sass_Value* v, size_t i, union Sass_Value* val) { v->map.pairs[i].value = val; }

  // Getters and setters for Sass_Error
  char* ADDCALL sass_error_get_message(const union Sass_Value* v) { return v->error.message; };
  void ADDCALL sass_error_set_message(union Sass_Value* v, char* msg) { v->error.message = msg; };

  // Getters and setters for Sass_Warning
  char* ADDCALL sass_warning_get_message(const union Sass_Value* v) { return v->warning.message; };
  void ADDCALL sass_warning_set_message(union Sass_Value* v, char* msg) { v->warning.message = msg; };

  // Creator functions for all value types

  union Sass_Value* ADDCALL sass_make_boolean(bool val)
  {
    Sass_Value* v = (Sass_Value*) calloc(1, sizeof(Sass_Value));
    if (v == 0) return 0;
    v->boolean.tag = SASS_BOOLEAN;
    v->boolean.value = val;
    return v;
  }

  union Sass_Value* ADDCALL sass_make_number(double val, const char* unit)
  {
    Sass_Value* v = (Sass_Value*) calloc(1, sizeof(Sass_Value));
    if (v == 0) return 0;
    v->number.tag = SASS_NUMBER;
    v->number.value = val;
    v->number.unit = unit ? strdup(unit) : 0;
    if (v->number.unit == 0) { free(v); return 0; }
    return v;
  }

  union Sass_Value* ADDCALL sass_make_color(double r, double g, double b, double a)
  {
    Sass_Value* v = (Sass_Value*) calloc(1, sizeof(Sass_Value));
    if (v == 0) return 0;
    v->color.tag = SASS_COLOR;
    v->color.r = r;
    v->color.g = g;
    v->color.b = b;
    v->color.a = a;
    return v;
  }

  union Sass_Value* ADDCALL sass_make_string(const char* val)
  {
    Sass_Value* v = (Sass_Value*) calloc(1, sizeof(Sass_Value));
    if (v == 0) return 0;
    v->string.tag = SASS_STRING;
    v->string.value = val ? strdup(val) : 0;
    if (v->string.value == 0) { free(v); return 0; }
    return v;
  }

  union Sass_Value* ADDCALL sass_make_list(size_t len, enum Sass_Separator sep)
  {
    Sass_Value* v = (Sass_Value*) calloc(1, sizeof(Sass_Value));
    if (v == 0) return 0;
    v->list.tag = SASS_LIST;
    v->list.length = len;
    v->list.separator = sep;
    v->list.values = (union Sass_Value**) calloc(len, sizeof(union Sass_Value));
    if (v->list.values == 0) { free(v); return 0; }
    return v;
  }

  union Sass_Value* ADDCALL sass_make_map(size_t len)
  {
    Sass_Value* v = (Sass_Value*) calloc(1, sizeof(Sass_Value));
    if (v == 0) return 0;
    v->map.tag = SASS_MAP;
    v->map.length = len;
    v->map.pairs = (struct Sass_MapPair*) calloc(len, sizeof(struct Sass_MapPair));
    if (v->map.pairs == 0) { free(v); return 0; }
    return v;
  }

  union Sass_Value* ADDCALL sass_make_null(void)
  {
    Sass_Value* v = (Sass_Value*) calloc(1, sizeof(Sass_Value));
    if (v == 0) return 0;
    v->null.tag = SASS_NULL;
    return v;
  }

  union Sass_Value* ADDCALL sass_make_error(const char* msg)
  {
    Sass_Value* v = (Sass_Value*) calloc(1, sizeof(Sass_Value));
    if (v == 0) return 0;
    v->error.tag = SASS_ERROR;
    v->error.message = msg ? strdup(msg) : 0;
    if (v->error.message == 0) { free(v); return 0; }
    return v;
  }

  union Sass_Value* ADDCALL sass_make_warning(const char* msg)
  {
    Sass_Value* v = (Sass_Value*) calloc(1, sizeof(Sass_Value));
    if (v == 0) return 0;
    v->warning.tag = SASS_WARNING;
    v->warning.message = msg ? strdup(msg) : 0;
    if (v->warning.message == 0) { free(v); return 0; }
    return v;
  }

  // will free all associated sass values
  void ADDCALL sass_delete_value(union Sass_Value* val) {

    size_t i;
    if (val == 0) return;
    switch(val->unknown.tag) {
        case SASS_NULL: {
        }   break;
        case SASS_BOOLEAN: {
        }   break;
        case SASS_NUMBER: {
                free(val->number.unit);
        }   break;
        case SASS_COLOR: {
        }   break;
        case SASS_STRING: {
                free(val->string.value);
        }   break;
        case SASS_LIST: {
                for (i=0; i<val->list.length; i++) {
                    sass_delete_value(val->list.values[i]);
                }
                free(val->list.values);
        }   break;
        case SASS_MAP: {
                for (i=0; i<val->map.length; i++) {
                    sass_delete_value(val->map.pairs[i].key);
                    sass_delete_value(val->map.pairs[i].value);
                }
                free(val->map.pairs);
        }   break;
        case SASS_ERROR: {
                free(val->error.message);
        }   break;
        case SASS_WARNING: {
                free(val->error.message);
        }   break;
    }

    free(val);

    }

  // Make a deep cloned copy of the given sass value
  union Sass_Value* ADDCALL sass_clone_value (const union Sass_Value* val)
  {

    size_t i;
    if (val == 0) return 0;
    switch(val->unknown.tag) {
        case SASS_NULL: {
                return sass_make_null();
        }   break;
        case SASS_BOOLEAN: {
                return sass_make_boolean(val->boolean.value);
        }   break;
        case SASS_NUMBER: {
                return sass_make_number(val->number.value, val->number.unit);
        }   break;
        case SASS_COLOR: {
                return sass_make_color(val->color.r, val->color.g, val->color.b, val->color.a);
        }   break;
        case SASS_STRING: {
                return sass_make_string(val->string.value);
        }   break;
        case SASS_LIST: {
                union Sass_Value* list = sass_make_list(val->list.length, val->list.separator);
                for (i = 0; i < list->list.length; i++) {
                    list->list.values[i] = sass_clone_value(val->list.values[i]);
                }
                return list;
        }   break;
        case SASS_MAP: {
                union Sass_Value* map = sass_make_map(val->map.length);
                for (i = 0; i < val->map.length; i++) {
                    map->map.pairs[i].key = sass_clone_value(val->map.pairs[i].key);
                    map->map.pairs[i].value = sass_clone_value(val->map.pairs[i].value);
                }
                return map;
        }   break;
        case SASS_ERROR: {
                return sass_make_error(val->error.message);
        }   break;
        case SASS_WARNING: {
                return sass_make_warning(val->warning.message);
        }   break;
    }

    return 0;

  }

}
