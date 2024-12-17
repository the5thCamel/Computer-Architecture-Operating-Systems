#include <linux/module.h>
#include <linux/init.h>

//Meta information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("C");

//This function is called when the module is loaded into the kernel
static int __init ModuleInit(void) {
	printk("Hi! This is my first kernel module \n");
	return 0;
}

//This function is called when the module is unloaded or removed from the kernel
static void __exit ModuleExit(void) {
	printk("Bye! Keep writing more kernel modules \n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
