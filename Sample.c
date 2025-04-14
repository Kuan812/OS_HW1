#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

/* This function is called when the module is loaded. */
static int __init simple_init(void)
{
	printk(KERN_INFO "Loading Kernel Module A1105501\n");
	return 0;
}

/* This function is called when the module is removed. */
static void __exit simple_exit(void)
{
	printk(KERN_INFO "Removing Kernel Module A1105501\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");