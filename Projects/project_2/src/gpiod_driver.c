#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/kernel.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>

// declare GPIOs and IRQs
static struct gpio_desc *led_gpio, *button_gpio;
static int irq_num;

// ISR
static irq_handler_t button_isr(unsigned int irq, void *dev_id, struct pt_regs *regs) {
	// Toggle LED
	int led_value = gpiod_get_value(led_gpio);
	gpiod_set_value(led_gpio, !led_value);

	printk(KERN_INFO "Interrupt was triggered and ISR was called!\n");
	
	return (irq_handler_t) IRQ_HANDLED;
}

// probe function
static int led_probe(struct platform_device *pdev) {
	// print initialization message
	printk(KERN_INFO "gpiod_driver initializing...\n");

	// Get GPIO descriptors
	led_gpio = devm_gpiod_get(&pdev->dev, "led", GPIOD_OUT_LOW);
	button_gpio = devm_gpiod_get(&pdev->dev, "button", GPIOD_IN);

	// print button state
	printk(KERN_INFO "Button value: %d\n", gpiod_get_value(button_gpio));
	printk(KERN_INFO "button_detected\n");

	// Request IRQ for button GPIO
	printk(KERN_INFO "gpiod_to_irq going to be called\n");
	irq_num = gpiod_to_irq(button_gpio);
	if (irq_num < 0) {
		printk(KERN_ERR "Unable to request IRQ: %d\n", irq_num);
		free_irq(irq_num, NULL);
	}
	else {
		printk(KERN_INFO "gpiod_to_irq called\n");
	}

	// Register ISR
	request_irq(irq_num, (irq_handler_t) button_isr, IRQF_TRIGGER_FALLING, "button_isr", NULL);

	printk(KERN_INFO "gpiod_driver loaded!\n");
	
	return 0;
}

// remove function
static int led_remove(struct platform_device *pdev) {
	// print free IRQ message
	printk(KERN_INFO "free IRQ\n");
	free_irq(irq_num, NULL);
	printk(KERN_INFO "free IRQ done\n");

	// print exit message
	printk(KERN_INFO "gpiod_driver unloaded!\n");
	return 0;
}

static const struct of_device_id matchy_match[] = {
    { .compatible = "hl116,gpios" },
    {/* leave alone - keep this here (end node) */},
};

// platform driver object
static struct platform_driver gpiod_driver = {
	.probe	 = led_probe,
	.remove	 = led_remove,
	.driver	 = {
	       .name  = "gpiod_driver",
	       .owner = THIS_MODULE,
	       .of_match_table = matchy_match,
	},
};

module_platform_driver(gpiod_driver);

MODULE_DESCRIPTION("Project 2 - gpiod");
MODULE_AUTHOR("Shaun Lin (hl116) <hl116@rice.edu>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform: gpiod_driver");