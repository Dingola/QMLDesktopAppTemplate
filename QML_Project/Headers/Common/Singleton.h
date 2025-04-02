#pragma once

#include "NonCopyable.h"
#include "NonMoveable.h"

/** @file
 *  @brief This file contains the definition of the Singleton class.
 */

namespace QmlApp
{
/**
 * @class Singleton
 * @brief Meyers Singleton Pattern using CRTP
 *
 * This class implements the Meyers Singleton Pattern using the Curiously Recurring Template Pattern
 * (CRTP). Note: Derived classes need to declare 'friend class Singleton<T>'. Derived classes must
 * also have their constructor set to private to prevent instantiation.
 */
template<typename T>
class Singleton: public NonCopyable, public NonMoveable
{
    protected:
        /**
         * @brief Constructs a Singleton object.
         *
         * The constructor is protected to allow derived classes to construct the object.
         */
        Singleton() = default;

        /**
         * @brief Destroys the Singleton object.
         *
         * The destructor is virtual to ensure proper cleanup of derived classes.
         */
        virtual ~Singleton() = default;

    public:
        /**
         * @brief Returns the singleton instance of the class.
         *
         * This function returns the singleton instance of the class, creating it if it does not
         * already exist. The instance is created in a thread-safe manner.
         *
         * @return The singleton instance of the class.
         */
        static T& get_instance()
        {
            static T instance;  // Thread-safe in C++11 and later
            return instance;
        }
};
}  // namespace QmlApp
