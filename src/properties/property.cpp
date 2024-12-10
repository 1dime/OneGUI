#include <properties/property.hpp>

using json = nlohmann::json;
/*
Property: default property constructor
*/
Property::Property()
{
    //Define head pointer
    this->head = new ListItem();
}

/*
Property: constructor that creates properties from a JSON file
@param path: path of properties file
*/
Property::Property(const char *path)
{
    //Try to read the properties file
    json propertiesData = this->parseProperties(path);
    if(!this->readProperties(propertiesData))
    {
        //Failed to read configuration
        std::cout << "property.o: Property: Failed to open '" << path << "'" << std::endl;
        exit(1);
    }
}

/*
Property: constructor that sets item using key and value
@param key: property key
@param value: property value
*/
Property::Property(const char *key, void *value)
{
    std::string k(key);
    this->head = new ListItem((void *) new DictItem(k, value));
}

/*
Property: constructor that sets item using dict item
*/
Property::Property(DictItem *item)
{
    this->head = new ListItem((void *) item);
}

/*
key: gets property key
@returns key
*/
char *Property::key()
{
    return (char *) ((DictItem *) this->getItem())->k.c_str();
}

/*
value: gets property value
@returns value
*/
void *Property::value()
{
    return ((DictItem *) this->getItem())->v;
}

/*
parseProperties: parses properties file
@param path: path of properties file
@returns json configuration
*/
json Property::parseProperties(const char *path)
{
    //Read properties data from properties file
    std::ifstream propFile(path);
    if((!propFile.is_open()) || (propFile.fail()))
    {
        std::cout << "Could not open '" << path << "'" << std::endl;
        exit(1);
    }

    //Read json data from the file
    return json::parse(propFile);
}

/*
readProperties: reads properties from json properties
@param propertiesData: properties data
@returns true if read succeeded, false if not
*/
bool Property::readProperties(json propertiesData)
{
    //Read entire configuration data, ignoring objects
    for(auto it = propertiesData.begin(); it != propertiesData.end(); ++it)
    {
        //Get both key and value
        auto k = it.key();
        auto v = it.value();

        void *val = nullptr;

        //Set value to string if value is a string
        if(v.is_string())
        {
            std::string *valStr = new std::string(v.get<std::string>());
            val = static_cast<void *>(valStr);
        }

        //Do the same if it is an integer
        else if(v.is_number_integer())
        {
            int *valInt = new int(v.get<int>());
            val = static_cast<void *>(valInt);
        }

        //And the same for floats
        else if(v.is_number_float())
        {
            float *valFloat = new float(v.get<float>());
            val = static_cast<void *>(valFloat);
        }

        //And for booleans
        else if(v.is_boolean())
        {
            bool *valBool = (bool *) v.get<bool>();
            val = static_cast<bool *>(valBool);
        }

        json element = propertiesData.at(k);
        //Recurse on objects
        if(element.is_object())
        {
            //Read the data in this object
            return this->readProperties(element);
        }
        else
        {
            //Add both key and value to properties
            this->addItem(new DictItem(k, val));
        }
    }

    return true;
}

/*
valueAsString: gets value as a string
@returns value as string
*/
std::string Property::valueAsString()
{
    //Convert value to string
    std::string *val = static_cast<std::string *>(this->value());
    return *val;
}

/*
valueAsInt: gets value as integer
@returns integer value
*/
int Property::valueAsInt()
{
    //Convert value to integer
    int *val = static_cast<int *>(this->value());
    return *val;
}

/*
valueAsFloat: gets value as float
@returns float value
*/
float Property::valueAsFloat()
{
    //Convert value to float
    float *val = static_cast<float *>(this->value());
    return *val;
}

/*
valueAsBoolean: gets value as boolean
@returns boolean value
*/
bool Property::valueAsBoolean()
{
    //Convert value to boolean type
    bool *val = static_cast<bool *>(this->value());
    return *val;
}