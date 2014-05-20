#include <utils/json/Value.hpp>
#include <utils/json/Array.hpp>
#include <utils/json/Object.hpp>

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

        Value::~Value()
        {
            switch(type)
            {
                case Value::Type::STRING:
                    delete v_string;
                    break;
                case Value::Type::INT:
                    break;
                case Value::Type::FLOAT:
                    break;
                case Value::Type::ARRAY:
                    delete v_array;
                    break;
                case Value::Type::OBJECT:
                    delete v_object;
                    break;
                case Value::Type::BOOL:
                    break;
                case Value::Type::NIL:
                    break;
                default:
                    break;
            }
        }

        /** Cast operator for float */
        Value::operator long double() const
        {
            return v_float;
        }
    
        /** Cast operator for int */
        Value::operator long long int() const
        {
            return v_int;
        }
    
        /** Cast operator for bool */
        Value::operator bool() const
        {
            return v_bool;
        }
    
        /** Cast operator for string */
        Value::operator const std::string&() const
        {
            return *v_string;
        }
    
        /** Cast operator for Object */
        Value::operator const Object&() const
        {
            return *v_object;
        }
    
        /** Cast operator for Object */
        Value::operator const Array&() const
        {
            return *v_array;
        }
        
        Value::operator long double&()
        {
            return v_float;
        }

        Value::operator long long int&()
        {
            return v_int;
        }

        Value::operator bool&()
        {
            return v_bool;
        }

        Value::operator std::string&()
        {
            return *v_string;
        }

        Value::operator Object&()
        {
            return *v_object;
        }

        Value::operator Array&()
        {
            return *v_array;
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
            switch(self.type)
            {
                case Value::Type::STRING:
                    stream<<"\""<<*self.v_string<<"\"";break;
                case Value::Type::INT:
                    stream<<self.v_int;break;
                case Value::Type::FLOAT:
                    stream<<self.v_float;break;
                case Value::Type::ARRAY:
                    stream<<*self.v_array;break;
                case Value::Type::OBJECT:
                    stream<<*self.v_object;break;
                case Value::Type::BOOL:
                    stream<<(self.v_bool?"true":"false");break;
                case Value::Type::NIL:
                    stream<<"null";break;
                default:
                    stream<<"UNKNOW TYPE";break;
            }
            return stream;
        }

        long double& Value::as_float()
        {
            return v_float;
        }
        
        long long int& Value::as_int()
        {
            return v_int;
        }

        bool& Value::as_bool()
        {
            return v_bool;
        }

        std::string& Value::as_string()
        {
            return *v_string;
        }

        Object& Value::as_object()
        {
            return *v_object;
        }

        Array& Value::as_array()
        {
            return *v_array;
        }
        
    }
}
