/*
 * hn_utils.h
 *
 *  Created on: Jan 4, 2017
 *      Author: root
 */

#ifndef COMMON_H_
#define COMMON_H_

#ifdef __WIN32
#	ifdef EXPORT_COMMON
#		define EXPORT_CLASS_API __declspec(dllexport)
#	else
#		define EXPORT_CLASS_API __declspec(dllimport)
#	endif
#else
#	define EXPORT_CLASS_API
#endif

#endif /* COMMON_H_ */
