/*
 * =====================================================================================
 *
 *       Filename:  us.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/07/2012 04:26:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  madan (), madanpandiri@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/kernel.h>


static struct usb_device_id upen_table[] = {
    {USB_DEVICE(0x1005, 0xb113)},
    {}
};


MODULE_DEVICE_TABLE (usb, upen_table);



static int upen_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int upen_close(struct inode *inode, struct file *file)
{
    return 0;
}
 
static ssize_t upen_read(struct file *file, char *buff, size_t count, loff_t *pos)
{
    return 0;
}


static ssize_t upen_write(struct file *file, const char *buff, size_t count, loff_t *ppos)
{
    return 0;
}
static const struct file_operations upen_fops = {
    .open       = upen_open,
    .release    = upen_close,
    .read       = upen_read,
    .write      = upen_write,
};
static struct usb_class_driver upen_class = {
        .name = "upen%d",
        .fops = &upen_fops,
};


static int upen_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
    int num_endpts;
    struct usb_endpoint_descriptor endpt_desc;
    int i;
    int retval;

    printk("Device connected \n");
    printk("num_altsettings = %d \n", intf->num_altsetting);
    printk("vendor = %x , device = %x \n", id->idVendor, id->idProduct);
    printk("device class = %d \n", id->bDeviceClass);
    printk("number of endpoints = %d \n", intf->cur_altsetting->desc.bNumEndpoints);
    num_endpts = intf->cur_altsetting->desc.bNumEndpoints;
    for (i = 0; i < num_endpts; i++) {
        endpt_desc = intf->cur_altsetting->endpoint[i].desc;
        printk("len = %d, addr = %x, pkt_size = %d, interval = %d\n", endpt_desc.bLength, 
                                    endpt_desc.bEndpointAddress, endpt_desc.wMaxPacketSize, 
                                    endpt_desc.bInterval);
    }
    if ((retval = usb_register_dev(intf, &upen_class)) < 0) {
        err ("Not able to get a minor number for device \n");
    }
    else {
        printk(KERN_INFO "Minor number = %d \n", intf->minor);
    }
    
    return 0;

}

static void upen_disconnect(struct usb_interface *intf)
{
    printk("Device disconnected\n");
    usb_deregister_dev(intf, &upen_class);
}

static struct usb_driver upen_driver = {
    .name       = "upen_driver",
    .id_table   = upen_table,
    .probe      = upen_probe,
    .disconnect = upen_disconnect
};
 


static int __init upen_init(void)
{
    return usb_register(&upen_driver);
}

static void __exit upen_exit(void)
{
    usb_deregister(&upen_driver);
}
module_init(upen_init);
module_exit(upen_exit);
MODULE_LICENSE("GPL");
