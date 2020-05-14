#pragma once

template <class class_name> using move_constructor = class_name(class_name &&input);
template <class class_name> using move_assignment = class_name &class_name::operator=(class_name &&input);
template <class class_name> using copy_assignment = class_name &class_name::operator=(const class_name &input);
template <class class_name> using copy_constructor = class_name(const class_name &input);
