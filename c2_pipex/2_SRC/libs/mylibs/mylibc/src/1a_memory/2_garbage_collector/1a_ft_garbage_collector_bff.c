/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_garbage_collector_bff_dbg.c					 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dinepomu <dinepomu@student.42berlin.de>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/24 18:57:56 by dinepomu		  #+#	#+#			 */
/*   Updated: 2025/01/26 11:26:33 by dinepomu		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "mylibc.h"
//#define TEST_FILENAME "allocation_log.txt"
//#define TEST_FILENAME "0"

/* static void	*ft_memncpy_null_local(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	if (n > 0)
		d[n - 1] = '\0';
	return (dst);
} */

/* void	ft_free_fd(char *filename)
{
	int		fd;
	char	*line;
	void	*pointers[MAX_ALLOCATIONS];
	int		num_pointers;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(1, "Alloc Error6\n", 13);
		return ;
	}
	line = NULL;
	num_pointers = 0;
	while (ft_fgets(&line, fd))
	{
		ft_scanf(filename, line, pointers, &num_pointers);
		free(line);
	}
	num_pointers--;
	while (num_pointers >= 0)
		free(pointers[num_pointers--]);
	close(fd);
	if (unlink(filename) == -1)
		write(2, "Error deleting file\n", 20);
} */

/*
void	ft_free_fd_first_one(const char *filename)
{
	FILE	*file;
	char	line[1024];
	void	*pointers[MAX_ALLOCATIONS];
	int		num_pointers;

	file = fopen(filename, "r");
	if (file == NULL)
		return ;
	num_pointers = 0;
	while (fgets(line, sizeof(line), file) != NULL)
	{
		if (sscanf(line, "%p;", &pointers[num_pointers]) == 1)
			num_pointers++;
		else
			write(2, "Parse Error\n", 13);
	}
	num_pointers--;
	while (num_pointers >= 0)
	{
		free(pointers[num_pointers]);
		num_pointers--;
	}
	if (unlink(filename) == -1)
		write(2, "Error deleting file\n", 20);
	fclose(file);
}
*/
//tester for the garbage collector with buffer file

//clang *.c -I../../../include -L../../../../ -lft_mylib -o garbage.out
//clang *.c -I../../../../include -L../../../../../ -lft_mylib -o garbage.out

/*
int	main() 
{
	// Test 1: Basic Allocation and Freeing
	printf("Test 1: Basic Allocation and Freeing\n");
	char	*str = (char *)ft_calloc_fd(TEST_FILENAME, 10, sizeof(char));
	if (str != NULL) {
		strcpy(str, "Testing");
		printf("Allocated and wrote: %s\n", str);
	}
	ft_free_fd(TEST_FILENAME); // Free all allocated memory
	printf("Freed allocations\n");

	// Test 2: Multiple Allocations
	printf("\nTest 2: Multiple Allocations\n");
	int	*numbers = (int *)ft_calloc_fd(TEST_FILENAME, 5, sizeof(int));
	double *doubles = (double *)ft_calloc_fd(TEST_FILENAME, 3, sizeof(double));
	char	*anotherStr = (char *)ft_calloc_fd(TEST_FILENAME, 20, sizeof(char));

	if (numbers != NULL) {
		for (int i = 0; i < 5; i++) {
			numbers[i] = i * 10;
			printf("numbers[%d] = %d\n", i, numbers[i]);
		}
	}
	if (doubles != NULL) {
		for (int i = 0; i < 3; i++) {
			doubles[i] = i * 1.1;
			printf("doubles[%d] = %f\n", i, doubles[i]);
		}
	}

	if (anotherStr != NULL) {
		strcpy(anotherStr, "Another test string");
		printf("Allocated and wrote: %s\n", anotherStr);
	}

	ft_free_fd(TEST_FILENAME);
	printf("Freed allocations\n");

	// Test 3: Reallocation (illustrative, doesn't use ft_realloc_fd)
	printf("\nTest 3: Reallocation (Illustrative)\n");
	char	*reallocStr = (char *)ft_calloc_fd(TEST_FILENAME, 10, sizeof(char));
	if (reallocStr != NULL) {
	  strcpy(reallocStr, "Short");
	  printf("Initial string: %s\n", reallocStr);
	}

	// We can't really "reallocate" using the existing functions, 
	//but we can free and allocate again
	ft_free_fd(TEST_FILENAME); // Free

	reallocStr = (char *)ft_calloc_fd(TEST_FILENAME, 20, sizeof(char));
	if (reallocStr != NULL) {
	  strcpy(reallocStr, "This is a longer string");
	  printf("New string after 'reallocation': %s\n", reallocStr);
	}

	ft_free_fd(TEST_FILENAME);
	printf("Freed allocations\n");

	// Test 4: Error Handling (Illustrative - allocation failure)
	// To make this test truly effective, you'd need to temporarily 
	//imit available memory,
	// which is more complex and OS-dependent.
	printf("\nTest 4: Error Handling (Illustrative - Allocation Failure)\n");

	// Assuming a function that allocates a very large size to simulate failure
	// This is just illustrative, as simulating failure is tricky
//	void *largeAlloc = ft_calloc_fd(TEST_FILENAME, SIZE_MAX, 1);
//	if (largeAlloc == NULL)
//		{
//		printf("Allocation failed as expected (or if it didn't, \
//				consider reducing the allocation size\n");
//		}

	// Clean up if the large allocation somehow succeeded
	ft_free_fd(TEST_FILENAME);
	printf("Freed allocations (if any)\n");

	printf("\nAll tests completed.\n");

	// Optional: Check the contents of TEST_FILENAME to see the log
	printf("\nOptional: Check the contents of '%s' to see \
			the allocation log.\n", TEST_FILENAME);

	return 0;
}*/

/*
	if (truncate(filename, 0) == -1)
		return;
*/
