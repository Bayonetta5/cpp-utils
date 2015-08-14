#include <utils/json/Value.hpp>
#include <utils/json/Array.hpp>
#include <utils/json/Object.hpp>

#include <cassert>

namespace utils
{
    namespace json
    {
        Value::Value(std::string* v) : v_string(v),type(STRING)
        {
        }

        Value::Value(long long int v) : v_int(v), type(INT)
        {
        }

        Value::Value(long int v) : v_int(v), type(INT)
        {
        }

        Value::Value(int v) : v_int(v), type(INT)
        {
        }

        Value::Value(long double v) : v_float(v), type(FLOAT)
        {
        }

        Value::Value(double v) : v_float(v), type(FLOAT)
        {
        }

        Value::Value(float v): v_float(v), type(FLOAT)
        {
        }

        Value::Value(Array* v) : v_array(v), type(ARRAY)
        {
        }

        Value::Value(Object* v) : v_object(v), type(OBJECT)
        {
        }

        Value::Value(bool v) : v_bool(v), type(BOOL)
        {
        }

        Value::Value() : type(NIL)
        {
        }

        Value::Value(Value&& other)
        {
            type = other.type;
            other.type = UNDEFINE;

            switch(type)
            {
                case Value::Type::STRING:
                    v_string = other.v_string;
                    other.v_string = nullptr;
                    break;
                case Value::Type::INT:
                    v_int = other.v_int;
                    break;
                case Value::Type::FLOAT:
                    v_float = other.v_float;
                    break;
                case Value::Type::ARRAY:
                    v_array = other.v_array;
                    other.v_array = nullptr;
                    break;
                case Value::Type::OBJECT:
                    v_object = other.v_object;
                    other.v_object = nullptr;
                    break;
                case Value::Type::BOOL:
                    v_bool = other.v_bool;
                    break;
                case Value::Type::NIL:
                    break;
                default:
                    break;
            }

        }
        Value& Value::operator=(Value&& other)
        {
            type = other.type;
            other.type = UNDEFINE;

            switch(type)
            {
                case Value::Type::STRING:
                    v_string = other.v_string;
                    other.v_string = nullptr;
                    break;
                case Value::Type::INT:
                    v_int = other.v_int;
                    break;
                case Value::Type::FLOAT:
                    v_float = other.v_float;
                    break;
                case Value::Type::ARRAY:
                    v_array = other.v_array;
                    other.v_array = nullptr;
                    break;
                case Value::Type::OBJECT:
                    v_object = other.v_object;
                    other.v_object = nullptr;
                    break;
                case Value::Type::BOOL:
                    v_bool = other.v_bool;
                    break;
                case Value::Type::NIL:
                    break;
                default:
                    break;
            }
            return *this;
        }

        Value::~Value()
        {
            switch(type)
            {
                case Value::Type::STRING:
                    delete v_string;
                    break;
                case Value::Type::ARRAY:
                    delete v_array;
                    break;
                case Value::Type::OBJECT:
                    delete v_object;
                    break;
                default:
                    break;
            }
        }

        Value::Type Value::getType()const
        {
            return type;
        }

        ///////// HELPERS ///////////////
        bool Value::isString()const
        {
            return type == STRING;
        }

        bool Value::isInt()const
        {
            return type == INT;
        }

        bool Value::isFloat()const
        {
            return type == FLOAT;
        }

        bool Value::isArray()const
        {
            return type == ARRAY;
        }

        bool Value::isObject()const
        {
            return type == OBJECT;
        }

        bool Value::isBool()const
        {
            return type == BOOL;
        }

        bool Value::isNull()const
        {
            return type == NIL;
        }



        std::ostream& operator<<(std::ostream& stream, const Value& self)
        {
            self.print_ident(stream,0);
            return stream;
        }

        void Value::print_ident(std::ostream& stream, int i)const
        {
            switch(type)
            {
                case Value::Type::STRING:
                    stream<<"\""<<*v_string<<"\"";
                    break;
                case Value::Type::INT:
                    stream<<v_int;
                    break;
                case Value::Type::FLOAT:
                    stream<<v_float;
                    break;
                case Value::Type::ARRAY:
                    v_array->print_ident(stream,i);
                    break;
                case Value::Type::OBJECT:
                    v_object->print_ident(stream,i);
                    break;
                case Value::Type::BOOL:
                    stream<<(v_bool?"true":"false");
                    break;
                case Value::Type::NIL:
                    stream<<"null";
                    break;
                default:
                    stream<<"UNKNOW TYPE";
                    break;
            }
        }

        long double& Value::as_float()
        {
            assert(isFloat());
            return v_float;
        }

        const long double& Value::as_float()const 
        {
            assert(isFloat());
            return v_float;
        }
        
        long long int& Value::as_int()
        {
            assert(isInt());
            return v_int;
        }

        const long long int& Value::as_int()const 
        {
            assert(isInt());
            return v_int;
        }

        bool& Value::as_bool()
        {
            assert(isBool());
            return v_bool;
        }

        const bool& Value::as_bool()const 
        {
            assert(isBool());
            return v_bool;
        }

        std::string& Value::as_string()
        {
            assert(isString());
            return *v_string;
        }

        const std::string& Value::as_string()const
        {
            assert(isString());
            return *v_string;
        }

        Object& Value::as_object()
        {
            assert(isObject());
            return *v_object;
        }

        const Object& Value::as_object()const
        {
            assert(isObject());
            return *v_object;
        }

        Array& Value::as_array()
        {
            assert(isArray());
            return *v_array;
        }

        const Array& Value::as_array()const
        {
            assert(isArray());
            return *v_array;
        }
        
    }
}
