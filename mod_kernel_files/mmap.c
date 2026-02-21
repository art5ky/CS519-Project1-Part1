/* Code to be inserted into mm/mmap.c */ 


/* Simple custom system call for copying from a user buffer to kernel buffer, modifying the bytes, and copying back to user buffer. */
SYSCALL_DEFINE2(app_helper, char __user *, u_buffer, size_t, size) {
	unsigned long uncopied_bytes;

	char *k_buffer = kmalloc(size, GFP_KERNEL);
	// Exit if failed to allocate memory to k_buffer.
	if (k_buffer == NULL) return -ENOMEM;

	// If copy_from_user returns values greater than 0, means there were uncopied bytes, means failure. 
	uncopied_bytes = copy_from_user(k_buffer, u_buffer, size);
	if (uncopied_bytes > 0) {
		kfree(k_buffer);
		return -EFAULT;
	} 

	memset(k_buffer, val, size);

	// Similar procedure to copy_from_user	
	uncopied_bytes = copy_to_user(u_buffer, k_buffer, size);
	if (uncopied_bytes > 0) {
		kfree(k_buffer);
		return -EFAULT;
	} 
	
	printk(KERN_INFO "Successfully ran app_helper system call!");

	kfree(k_buffer);
	return 0; 
}