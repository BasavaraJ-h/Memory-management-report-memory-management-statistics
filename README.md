# Memory-management-report-memory-management-statistics
Abstract
The memory management subsystem is one of the most important parts of the operating system. Since the early days of computing, there has been a need for more memory than exists physically in a system. Strategies have been developed to overcome this limitation and the most successful of these is virtual memory. Virtual memory makes the system appear to have more memory than it actually has by sharing it between competing processes as they need it. Linux memory management subsystem is responsible, as the name implies, for managing the memory in the system. This includes implementation of virtual memory and demand paging, memory allocation both for kernel internal structures and user space programs, mapping of files into processes address space and many other cool things. 

Introduction  

The outcome of this project is to implement a series of system calls in Linux kernel to report memory management statistics. The objective of this project is to get familiar with the following memory management components:
1.	Process virtual address space.
2.	Page tables.
3.	Linux page cache
main challenges will be the gathering of different memory usage statistical reports, and changing the LRU approximation algorithm values (Configuration) in the Linux machine. And observe the respected results. Our project is unique in the sense that we are analyzing the memory management in the Linux machine. Which can be useful to get new memory management algorithm. The major challenge in this is building the kernel with proper configuration.
 

Approach
This project is implemented in C coding language and the main challenge in this project is that, building the kernel and making the Our functions as the new system calls. In this project, we tried to attract the process by taking PID as input, after getting the process task we are able to display the memory statistics of that process. In This project we worked on kernel 4.17, we took the source code of kernel and added our code it to and build it to x86 architecture machine. The major drawback we faced in this is that missing of function call in the kernel code, which we have added, for our requirements.  Adding the system call to the kernel is explained in the next section.


Experiment / Implementation 

In this section, we would like to explain the implementation in Detail
This project implementation constates of following stages:

1.	Implementing the System call
2.	Adding System call to kernel source code
3.	Building the kernel to respected configuration
4.	Implementing the test code and verify


Implementing the System call

In this Stage we wrote the functions which will  be added to the kernel code.
Here we used C coding language because the kernel code is in C so we are writing it C.
These functions will not have the main functions in them. We imported kernel modules into  our code. The kernel modules which we used are explained below.

	1) The Linux kernel uses the memory descriptor data structure to represent a process’s address space. The memory descriptor `struct mm_struct` is defined in `<linux/mm_types.h>` and included in a process’s `task_struct`. In `mm_struct` the `mm_users` field is the number of processes using this address space and the `mm_count` field is the reference count for this `mm_struct`. The `vm_area_struct` describes a single memory area over a contiguous interval in an address space. All the virtual memory areas together form a process’s virtual address space. To calculate the size of a virtual address space, one only needs to sum the sizes of individual virtual
memory areas (VMA). The VMAs in a process can be accessed in two ways. `mmap` in `mm_struct` points to a sorted linked list of all VMAs of a process. `mm_rb` points to a red-black tree of VMAs, which can be used to search for a given VMA. You can verify your result using `pmap`.

2) The page descriptor `struct page` defined in `linux/mm_types.h` contains information (i.e., the `flags` field) about the page. You need to figure out how to obtain a reference to the page descriptor given a virtual address and read to information from the page descriptor. To test if an address is in memory, you need to test the `present` flag of the address’s corresponding page table entry. Note that Linux uses multi-level page tables, you might need multiple steps to reach the page table entry of a given virtual address.

3) The memory zone descriptor `struct zone` defined in `linux/mmzone.h` contains pointers to the two LRU lists. First, you need to get a reference to the individual memory zones, from where you can access the LRU lists. On NUMA machines, function `policy_zonelist` defined in `mm/mempolicy.c` returns a list of memory zones given the current memory policy. The current memory policy can be obtained via `current->mempolicy` in the current process’s `task_struct`. For UMA machines, you can get a reference to the list of zones via macro `NODE_DATA(nid)` with numa node id set to 0. A page’s status is saved in its page flags defined in `linux/page-flags.h`. 



Adding System call to kernel source code:

	Follow below steps to add system call to kernel
•	Download the kernel source
wget https://www.kernel.org/pub/linux/kernel/v3.x/linux-4.17.tar.xz

•	Extract the kernel source code
sudo tar -xvf linux-4.17.tar.xz -C/usr/src/

•	After changing current directory into kernel source files,  create another folder for new system call and copy one system call .C file into it and change to that directory.

mkdir Newsyscalldir 

cd  Newsyscalldir

•	Create a Makefile  in Newsyscalldir and add the object file compilation

 vim Makefile

obj-y := newsys.o


•	Go back to the kernel source folder and edit Makefile:

cd.. 
vim Makefile

•	Find the line with the core-y, it should be similar to this:

core-y += kernel/ certs/ mm/ fs/ ipc/ security/ crypto/ block/


•	and append the hello/ directory to the variable so it looks like

core-y += kernel/ certs/ mm/ fs/ ipc/ security/ crypto/ block/ Newsyscalldir/

•	add the new system call into system Call table

 		vim arch/x86/entry/syscalls/syscall_64.tbl

Scroll down till I find the number of the last system call before those starting from 512. In my case, that’s 328. So my new System Call’s number should be 329.Now add the line 329 64 syscall sys_newcall after the 328th System Call to provision our newly created System Call. Remember this number 329 cause we’ll need it in a few minutes
 
•	Add the new System Call in the System Call header file
Now head back to the source directory linux-4.7.1 and change directories with cd include/linux/ Furthermore, nano syscalls.h and add the line asmlinkage long sys_newapi(void); at the end of the file just before the #endif statement. This defines the prototype of the function of our System Call. asmlinkage is a keyword used to indicate that all parameters of the function would be available on the stack..
 

•	Recompile the kernel 
Switch over to the source directory linux-4.7.1/ and execute the following command sudo make -j4 modules_install install and watch your terminal throw a bunch of INSTALL lines till you reach a successful quiet completion.For the system to now use the newly configured kernel, reboot.
•	Install/ update kernel 
Make module_install install

•	Reboot

Building the kernel to respected configuration

•	Configure the Linux kernel features and modules
Before start building the kernel, one must configure Linux kernel features. You must also specify which kernel modules (drivers) needed for your system. 

cd linux-5.6.9
cp -v /boot/config-$(uname -r) .config

•	Install the required compilers and other tools
sudo apt-get install build-essential libncurses-dev bison flex libssl-dev libelf-dev
	
•	Configuring the kernel

sudo make menuconfig


•	Compile the kernel
Make -j4


Implementing the test code and verify
	Basically, the testing of system calls done by calling the kernel space APIs from user space, so in our project we have developed a set of  C files (test files). Which calls the system calls which we have added in the kernel. 
	The test scripts will call the respected system call by its sys_call number which we defined in the syscalls.h file.  With required arguments. Usually the output of system call will appear in kernel space so we can’t see in the normal terminal so, we have to use the 
		dmesg

Implementation issues and challenges 

•	It is necessary to have knowledge of system architecture in order to configure the kernel
•	It is necessary to have knowledge of paging and virtual memory concepts in order to understand the project
•	It is necessary to have the kernel modules knowledge.
•	Major challenges we face during the implementation is finding the right API call at kernel level. Because as the kernel version changes the APIs may changes.
•	Building kernel needs as complete knowledge of make file working
•	Understanding the user space and kernel space memory is very much needed in  this project

Conclusion  
To conclude, this project gave the in detailed report of memory management in the Linux machine. This project helped us in understanding the Linux memory management system in deep. As a future work we can use this report to optimize the memory management in Linux machine.
References 
None

