// Module: Array operations

void array_insert(int* a, int *size, int insert_position, int value);
/* Add a number into array
    Input: array, &size of array, position to insert, value to insert
    Output: altered array, new size
*/

void array_delete(int* a, int *size, int position);
/* Delete a number from array
    Input: array, &size of array, index of element that need to be deleted
    Output: altered array, new size
*/

void array_sort_ascending(int* a, int *size);
/* Sort in ascending order
    Input: array, &size of array
    Output: altered array
*/

void array_sort_decending(int* a, int *size);
/* Sort in descending order
    Input: array, &size of array
    Output: altered array
*/

int array_search(int* a, int *size, int value);
/* Search an element
    Input: array, &size of array, value to search
    Output: return index of value (=-1 if not found)
*/

int array_max(int* a, int *size);
/* Get maximum
    Input: array, &size of array
    Output: return maximum
*/

int array_min(int* a, int *size);
/* Get minimum
    Input: array, &size of array
    Output: return minimum
*/

