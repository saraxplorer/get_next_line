When looking at the code, first glance question: what is the use of variable storage in get_next_line fuction. I do not return it. so what is it's purpose?

The variable storage in the get_next_line function is used to retain data between calls to the function. Its purpose is to store any remaining characters after the newline character \n that were read in the current call. This way, the next call to get_next_line can start reading from where it left off, providing a continuous reading process from the file descriptor fd.

In essence, storage serves to:

a. Accumulate data read from the file descriptor across multiple calls.
b. Maintain the leftover data after a newline is found, so it can be used in the next call to get_next_line.
c. This allows get_next_line to return one line at a time, continuing from where it previously stopped.
