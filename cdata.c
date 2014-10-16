/*
 * =====================================================================================
 *
 *       Filename:  cdata.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/15/2013 06:43:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <linux/input.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#define MSG(m...) printk(KERN_INFO "CDATA:" m "\n")
#define DEV_MAJOR  121
#define DEV_NAME   "cdata"

static int cdata_open(struct inode *inode, struct file *filp)
{
	int minor;
	
	MSG("Opened.");
	minor = MINOR(inode->i_rdev);
	printk(KERN_INFO "CDATA: minor=%d\n", minor);

	return 0;
}

ssize_t cdata_write(struct file *filp, const char *buf, size_t size, 
                      loff_t *off)
{
	MSG("Writed.");
	return 0;
}

ssize_t cdata_read(struct file *filp, char *buf, size_t size,
			loff_t *off)
{
	MSG("Read.");
	return 0;
}
	
int cdata_close(struct inode *inode, struct file *filp)
{
	MSG("Closed.");
	return 0;
}

static struct file_operations cdata_fops = {
	owner:		THIS_MODULE,
	open:		cdata_open,
	release:	cdata_close,
	write:		cdata_write,
	read:		cdata_read,
};

int cdata_init_module(void)
{
	if(register_chrdev(DEV_MAJOR, DEV_NAME, &cdata_fops) < 0){
		MSG("Can't register device.");
		return -1;
	}
	MSG("Module Initialize.");
	return 0;
}

void cdata_cleanup_module(void)
{
	unregister_chrdev(DEV_MAJOR, DEV_NAME);
	MSG("module Exit.");
}

module_init(cdata_init_module);
module_exit(cdata_cleanup_module);

MODULE_LICENSE("GPL");
