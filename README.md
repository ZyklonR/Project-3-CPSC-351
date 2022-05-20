# Project-3-CPSC-351
Answer the following briefly in a few sentences in answer.txt.
Are the files in your program sharing the same memory region ?
- They are not sharing the same memory region.

Should they ? Justify your answer.
- They should not share the same memory region because there is a separate mmap() for the open file and the close file. 

