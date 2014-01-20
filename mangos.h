/**
 * Name: Mangos Programming Library
 * Author: Andrew Lee
 * Website: http://wildandrewlee.com/
 * Email: hello@wildandrewlee.com
 * License: WTFPL (http://www.wtfpl.net)
 * Last Revised: 1/9/2014
 */

#include <assert.h>
#include <string>
#include <vector>

#ifndef MANGOS
#define MANGOS

namespace mangos {
	//==========================
	// CLASS INVARIANTS
	//==========================
	
	#define ASSERT(x) assert(x)
	#define REQUIRES(x) assert(x)
	#define ENSURES(x) assert(x)

	//==========================
	// CONSTANTS
	//==========================

	#define __WHITESPACE__ " \t\n\r"

	//==========================
	// ARRAY
	//==========================

	class array {
		/**
		 * Returns the size of any fixed array.
		 *
		 * @args arr The array to measure the size of.
		 */
		public:
			template <typename T, size_t size>
			static size_t get_length(T (&arr)[size]){
				return size;
			}

		/**
		 * Reverse the order of elements in a given array.
		 *
		 * @args arr The array to reverse.
		 */
		public:
			template <typename T, size_t size>
			static void reverse(T (&arr)[size]){
				for(size_t n = 0; n < size / 2; n++)
					std::swap(arr[n], arr[size - n - 1]);
			}

		/**
		 * Calls the function func on every element of
		 * the given array.
		 *
		 * @args arr The array to use.
		 * @args func The function to use.
		 * @returns The transformed string.
		 */
		public:
			template <typename A, size_t size, typename B, typename C>
			static void transform(A (&arr)[size], B (*func)(C)){
				for(size_t n = 0; n < size; n++)
					arr[n] = func(arr[n]);
			}

		/**
		 * Converts any array into a vector.
		 *
		 * @args arr The array to convert.
		 * @returns The corresponding vector object.
		 */
		public:
			template <typename T, size_t size>
			static std::vector<T> to_vector(T (&arr)[size]){
				std::vector<T> v(arr, arr + size);
				return v;
			}
	};

	//==========================
	// STRING
	//==========================
	
	class string {
		/**
		 * Calls func on every character in str and returns
		 * the result.
		 *
		 * @args str The string to use.
		 * @args func The function to use.
		 * @returns The transformed string.
		 */
		public:
			template <typename A, typename B>
			static std::string transform(std::string str, A (*func)(B)){
				for(size_t n = 0; n < str.length(); n++)
					str[n] = func(str[n]);

				return str;
			}

		/**
		 * Splits a string based on a delimiter.
		 *
		 * @requires del.length() > 0
		 * @args str The string to split.
		 * @args del The delimiter to use.
		 * @args multiple Whether or not multiple delimiters
		 *       were passed.
		 * @returns A vector container filled with tokens.
		 */
		public:
			static std::vector<std::string> split(std::string str, std::string del = " ", bool multiple = false){
				REQUIRES(str.length() > 0);
				REQUIRES(del.length() > 0);

				std::vector<std::string> tokens;

				while(str.length() > 0){
					int found = multiple ? str.find_first_of(del) : str.find(del);
					std::string token = found == -1 ? str : str.substr(0, found);
					str = found == -1 ? "" : str.substr(found + (multiple ?: del.length()));

					if(token.length())
						tokens.push_back(token);
				}

				return tokens;
			}

		/**
		 * Combines every string in a given vector using
		 * a given separator.
		 *
		 * @args list The vector containing the strings to use.
		 * @args sep The string separator to use.
		 * @returns A string consisting of every string in the vector.
		 */
		public:
			static std::string join(std::vector<std::string> list, std::string sep = ""){
				std::string joined;

				for(size_t n = 0; n < list.size(); n++)
					joined += list[n] + (n + 1 < list.size() ? sep : "");

				return joined;
			}

		/**
		 * Combines every string in a given array using
		 * a given separator.
		 *
		 * @args list The array containing the strings to use.
		 * @args sep The string separator to use.
		 * @returns A string consisting of every string in the array.
		 */
		public:
			template<size_t size>
			static std::string join(std::string arr[size], std::string sep = ""){
				std::string joined;

				for(size_t n = 0; n < size; n++)
					joined += arr[n] + (n + 1 < size ? sep : "");

				return joined;
			}

		/**
		 * Trims leading and trailing whitespace from
		 * a given string.
		 *
		 * @args str The string to trim.
		 * @returns The string with whitespace trimmed.
		 */
		public:
			static std::string trim(std::string str){
				str = str.substr(str.find_first_not_of(__WHITESPACE__));
				str = str.substr(0, str.find_last_not_of(__WHITESPACE__) + 1);
				return str;
			}

		/**
		 * Returns the string str with every character
		 * in its uppercase form if possible.
		 *
		 * @args str The string to transform.
		 * @returns The string with its characters in
		 *          uppercase.
		 */
		public:
			static std::string to_upper(std::string str){
				return transform(str, ::toupper);
			}

		/**
		 * Returns the string str with every character
		 * in its lowercase form if possible.
		 *
		 * @args str The string to transform.
		 * @returns The string with its characters in
		 *          lowercase.
		 */
		public:
			static std::string to_lower(std::string str){
				return transform(str, ::tolower);
			}

		/**
		 * Returns the string reversed.
		 *
		 * @args str The string to reverse.
		 * @returns The string with its characters in
		 *          reverse order.
		 */
		public:
			static std::string reverse(std::string str){
				for(size_t n = 0; n < str.length() / 2; n++)
					std::swap(str[n], str[str.length() - n - 1]);

				return str;
			}
	};
}

#endif