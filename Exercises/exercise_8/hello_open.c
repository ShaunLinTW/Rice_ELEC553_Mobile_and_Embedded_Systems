#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
//do a hash define string for DEVICE_NAME (choose a name)
#define DEVICE_NAME "shaun"
//do a hash define string for CLASS_NAME (choose  a name)
#define CLASS_NAME "hl116"
// Choose a variable name to describe the major number; don't initialize the
// value
static int majorNUmber;

// Choose variable names to describe the class and device pointers
// Set both equal to NULL
static struct class* cls;
static struct device* dev;

// Here we declare the device_open function that will be called by the open
// system call; No need to change anything here
static int device_open(struct inode *, struct file *);

static struct file_operations fops =
{
	.open = device_open
  //Throw the device_open function reference here - this may help:
					//https://stackoverflow.com/a/46138031
};

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abraham Lincoln");
MODULE_DESCRIPTION("Greatest module in the world!");
MODULE_VERSION("0.000001");

static int multiplier = 10;
module_param(multiplier, int, S_IRUGO);

static int __init hello_init(void){
	  // Replace DONKEY with major number variable and
		// HAHA with device name macro defined earlierl
    majorNUmber = register_chrdev(0, DEVICE_NAME, &fops);
		// Replace DOGE with class pointer
		// Replace YOLO with class name macro defined earlier
    cls = class_create(THIS_MODULE, CLASS_NAME);
		// Replace TOM with device pointer
		// Replace DOGE with class pointer, DONKEY with major number variable, and
		// HAHA with device name macro defined earlier
    dev = device_create(cls, NULL, MKDEV(majorNUmber, 0), NULL, DEVICE_NAME);
    printk(KERN_INFO "Oh hi mark - I love Lisa %dX more than you do\n", multiplier);
    return 0;
}

static void __exit hello_exit(void){
	  // Replace DOGE with class pointer, DONKEY with major number variable, and
		// HAHA with device name macro defined earlier
    device_destroy(cls, MKDEV(majorNUmber,0));
    class_unregister(cls);
    class_destroy(cls);
    unregister_chrdev(majorNUmber, DEVICE_NAME);
    printk(KERN_INFO "sad, but still love Lisa %dX more than you\n", multiplier);
}

static int device_open(struct inode *inodep, struct file *filep){
    printk(KERN_INFO "You’re tearing me apart, Lisa!\n");
    return 0;
}

module_init(hello_init);
module_exit(hello_exit);
