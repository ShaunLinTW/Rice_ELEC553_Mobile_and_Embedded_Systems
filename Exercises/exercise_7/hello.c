// Author: Shaun Lin (hl116)

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abraham Lincoln");
MODULE_DESCRIPTION("Does something useful?");
MODULE_VERSION("0.000000000001");

static int multiplier = 10;
module_param(multiplier, int, S_IRUGO);

static int __init  hello_init(void){
        for (int i = 0; i < multiplier; i++){
                printk(KERN_INFO "Oh hi hl116\n");
        }
        return 0;
}

static void __exit hello_exit(void){
        for (int i = 0; i < multiplier; i++){
                printk(KERN_INFO "sad, but still love you\n");
        }
}

module_init(hello_init);
module_exit(hello_exit);