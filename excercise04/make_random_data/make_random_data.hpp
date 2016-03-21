#ifndef __MAKE_RANDOM_DATA_HPP
#define __MAKE_RANDOM_DATA_HPP  1

int *make_random_data(const int size);
int *make_random_data(const int size, const int max);

void free_random_data(int *data);

#endif /* !__MAKE_RANDOM_DATA_HPP */

