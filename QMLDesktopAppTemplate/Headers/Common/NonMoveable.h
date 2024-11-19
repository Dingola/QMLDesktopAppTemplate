#pragma once

/** @file
 *  @brief This file contains the definition of the NonMoveable class.
 */

namespace QmlApp
{
	/**
	 * @class NonMoveable
	 * @brief A base class to prevent moving of derived classes.
	 *
	 * This class is used to prevent moving of derived classes by deleting
	 * the move constructor and move assignment operator.
	 */
	class NonMoveable
	{
	protected:
		/**
		 * @brief Constructs a NonMoveable object.
		 *
		 * The constructor is protected to allow derived classes to construct the object.
		 */
		NonMoveable() = default;

		/**
		 * @brief Destroys the NonMoveable object.
		 *
		 * The destructor is virtual to ensure proper cleanup of derived classes.
		 */
		virtual ~NonMoveable() = default;

	public:
		/**
		 * @brief Deleted move constructor.
		 *
		 * Prevents moving of the object.
		 *
		 * @param other The object to move from.
		 */
		NonMoveable(NonMoveable&&) = delete;

		/**
		 * @brief Deleted move assignment operator.
		 *
		 * Prevents moving of the object.
		 *
		 * @param other The object to move from.
		 * @return A reference to this object.
		 */
		NonMoveable& operator= (NonMoveable&&) = delete;
	};
} // namespace QmlApp
