#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define BLINK_PERIOD_MS 1000
#define MESSAGE         "blink"

int main(void)
{
	int counter = 0;
	while (1) {
		printk("%s %d\n", MESSAGE, counter++);
		k_msleep(BLINK_PERIOD_MS);
	}
	return 0;
}
