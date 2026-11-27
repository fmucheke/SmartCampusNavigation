// File: FileUtils.h
// Author: Franklin Mucheke
// Purpose: Declares shared string trimming and uppercase normalization functions.
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>

std::string StandardizeName(const std:: string& name); //converts letters to uppercase and removes trailing & leading whitespace
std::string TrimWhiteSpace(const std:: string& name); //removes trailing & leading white space


#endif
