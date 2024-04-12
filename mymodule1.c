#include <linux/module.h>
#include <linux/init.h>

//Meta information
MODULE_LICENSE("GPL");


//This function is called when the module is loaded into the kernel
static int __init ModuleInit(void) {
	printk("Hi! I am Christopher Stephens with ID number 5439371 \n");
	return 0;
}

//This function is called when the module is unloaded or removed from the kernel
static void __exit ModuleExit(void) {
	printk("Bye! I am Christopher Stephens with ID number 5439371 \n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
