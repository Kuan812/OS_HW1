#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define BUFFER SIZE 128
#define PROC NAME "hello"

ssize_t proc_read(struct file* file, char __user* usr_buf,
    size_t count, loff_t* pos);

static struct file_operations proc_ops = {
 .owner = THIS_MODULE,
 .read = proc_read,
};

/* This function is called when the module is loaded. */
int proc_init(void)
{
    /* creates the /proc/hello entry */
    proc_create(PROC_NAME, 0666, NULL, &proc_ops);
    return 0;
}

/* This function is called when the module is removed. */
void proc_exit(void)
{
    /* removes the /proc/hello entry */
    remove_proc_entry(PROC_NAME, NULL);
}

/* This function is called each time /proc/hello is read */
ssize_t proc_read(struct file* file, char __user* usr_buf,
    size_t count, loff_t* pos)
{
    int rv = 0;
    char buffer[BUFFER_SIZE];
    static int completed = 0;

    if (completed) {
        completed = 0;
        return 0;
    }

    completed = 1;
    rv = sprintf(buffer, "Hello World A1115548\n");

    /* copies kernel space buffer to user space usr_buf */
    if (rv > count) {
        rv = count; // Avoid buffer overflow in user space
    }
    if (copy_to_user(usr_buf, buffer, rv)) {
        return -EFAULT; // Indicate failure to copy
    }

    return rv;
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello Module");
MODULE_AUTHOR("SGG");