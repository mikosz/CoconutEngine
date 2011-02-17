/*
 * settings.hpp
 *
 *  Created on: Sep 4, 2008
 *      Author: mikosz
 */

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <boost/call_traits.hpp>
#include <boost/any.hpp>

namespace coconutengine
{

template <class Key>
class Settings
{
public:

    virtual ~Settings()
    {}

    typedef typename boost::call_traits<Key>::param_type KeyType;

    virtual boost::any get(KeyType arg) const = 0;

    virtual boost::any get(KeyType arg, boost::any defaultValue) const = 0;

};

template <class ResultType, class KeyType>
inline ResultType getSetting(const Settings<KeyType>& settings,
    typename Settings<KeyType>::KeyType key)
{
    return boost::any_cast<ResultType>(settings.get(key));
}

template <class ResultType, class KeyType>
inline ResultType getSetting(const Settings<KeyType>& settings,
    typename Settings<KeyType>::KeyType key,
    ResultType defaultValue)
{
    return boost::any_cast<ResultType>(settings.get(key, defaultValue));
}

} // namespace coconutengine

#endif /* SETTINGS_HPP_ */
