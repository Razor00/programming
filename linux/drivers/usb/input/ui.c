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
#include <linux/slab.h>

#include <linux/hid.h>

static struct usb_device_id uien_table[] = {
//    {USB_DEVICE(0x0079,0x0006)},
    {USB_DEVICE(0x15d9,0x0a4c)},
    {}
};

typedef struct {
    unsigned char rx, ry, x, y;
    unsigned int hatch:4;
    unsigned int button:12;
} JOYSTICK_DATA;

typedef struct {
    unsigned char *data; //unsigned char unused, x, y;
}MOUSE_DATA;


typedef struct {
    struct usb_device *usb_dev;    
    struct usb_interface *usb_intf;
    int in_endpt_addr;
    int in_endpt_interval;
    int in_endpt_maxpktsize;
    int in_pipe;
    int out_endpt_addr;
    int out_endpt_interval;
    int out_endpt_maxpktsize;
    struct urb *urb;
    signed char *data;
    dma_addr_t dma_handle;
}DEVICE_DATA;


MODULE_DEVICE_TABLE (usb, uien_table);



static int uien_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int uien_close(struct inode *inode, struct file *file)
{
    return 0;
}
 
static ssize_t uien_read(struct file *file, char *buff, size_t count, loff_t *pos)
{
    return 0;
}


static ssize_t uien_write(struct file *file, const char *buff, size_t count, loff_t *ppos)
{
    return 0;
}
static const struct file_operations uien_fops = {
    .open       = uien_open,
    .release    = uien_close,
    .read       = uien_read,
    .write      = uien_write,
};
static struct usb_class_driver uien_class = {
        .name = "uien%d",
        .fops = &uien_fops,
};


char *end_point_type(struct usb_endpoint_descriptor *ep_desc)
{
    char *s="";
    switch (usb_endpoint_type(ep_desc)) 
    {
        case USB_ENDPOINT_XFER_CONTROL:
            s = "control"; 
            break;
        case USB_ENDPOINT_XFER_BULK:
            s = "bulk"; 
            break;
        case USB_ENDPOINT_XFER_INT:
            s = "intr"; 
            break;
        case USB_ENDPOINT_XFER_ISOC:
            s = "iso"; 
            break;
    }
    return s;
}

char *end_point_dir(struct usb_endpoint_descriptor *ep_desc)
{
    char *s="";
    switch (ep_desc->bEndpointAddress & USB_ENDPOINT_DIR_MASK) 
    {
        case USB_DIR_IN:
            s = "in"; 
            break;
        case USB_DIR_OUT:
            s = "out"; 
            break;
    }
    return s;
}


static void intr_callback(struct urb *urb);
void submit_work(DEVICE_DATA *mouse, int flag)
{
    int err;
    err = usb_submit_urb(mouse->urb, flag);
    if (err) {
        printk("Something unexpected happened = %d\n", err);
    }
 

}

static void intr_callback(struct urb *urb)
{
    DEVICE_DATA *mouse = urb->context;
    int status = urb->status;
    
    printk("Callback dude\n");
    /*  sync/async unlink faults aren't errors */
    if (status && !(status == -ENOENT ||
                status == -ECONNRESET ||
                status == -ESHUTDOWN))
        printk("nonzero write interrupt status received: %d\n", status);
    
    signed char *data = mouse->data; 
    printk("l = %d, r - %d, m - %d, s - %d, e - %d \n", data[0]& 0x01, data[0] & 0x02, data[0] & 0x4, data[0] &0x8,
            data[0] & 0x10);
    printk("x - %d, y - %d, wheel - %d \n", data[1], data[2], data[3]);     
    submit_work(mouse, GFP_ATOMIC);    

}


static int uien_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
    int num_endpts;
    struct usb_endpoint_descriptor endpt_desc;
    int i;
    int retval;
    DEVICE_DATA *mouse;
    int err;

    int int_data;
    int actual_len;
   
    printk("Device connected \n");
    printk("num_altsettings = %d \n", intf->num_altsetting);
    printk("vendor = 0x%04x , device = 0x%04x \n", id->idVendor, id->idProduct);
    printk("device class = %d \n", id->bDeviceClass);
    printk("number of endpoints = %d \n", intf->cur_altsetting->desc.bNumEndpoints);
    
    mouse = kmalloc(sizeof(*mouse), GFP_KERNEL);
    if (!mouse)
        return -ENOMEM; 

    mouse->usb_dev    = interface_to_usbdev(intf);
    mouse->usb_intf   = intf;
    usb_set_intfdata(intf, mouse);
    


    num_endpts = intf->cur_altsetting->desc.bNumEndpoints;

    for (i = 0; i < num_endpts; i++) {
        endpt_desc = intf->cur_altsetting->endpoint[i].desc;
        printk("type: %7s, dir = %4s, len = %d, addr = %4x, pkt_size = %3d, \
                interval = %3d\n",                                           \
                end_point_type(&endpt_desc),                                  \
                end_point_dir(&endpt_desc), endpt_desc.bLength,                \
                endpt_desc.bEndpointAddress, endpt_desc.wMaxPacketSize, endpt_desc.bInterval);
    
        if (usb_endpoint_xfer_int(&endpt_desc)) {
            if (usb_endpoint_dir_in(&endpt_desc)){
                mouse->in_endpt_addr = endpt_desc.bEndpointAddress;
                mouse->in_endpt_interval = endpt_desc.bInterval;
                mouse->in_endpt_maxpktsize = endpt_desc.wMaxPacketSize;
            }
            else
            if (usb_endpoint_dir_out(&endpt_desc)) {
                mouse->out_endpt_addr = endpt_desc.bEndpointAddress;
                mouse->out_endpt_interval = endpt_desc.bInterval;
                mouse->out_endpt_maxpktsize = endpt_desc.wMaxPacketSize;
            }
        }
    }

    mouse->data = usb_alloc_coherent(mouse->usb_dev, mouse->in_endpt_maxpktsize, GFP_ATOMIC, &mouse->dma_handle);
    if (!mouse->data){
        kfree(mouse);
        return -ENOMEM;
    }
 
    mouse->urb = usb_alloc_urb(0, GFP_KERNEL);
    if (!mouse->urb){
        kfree(mouse);
        usb_free_coherent(mouse->usb_dev, mouse->in_endpt_maxpktsize, mouse->data, mouse->dma_handle);
        return -ENOMEM;
    }

    mouse->in_pipe = usb_rcvintpipe(mouse->usb_dev, mouse->in_endpt_addr);
    usb_fill_int_urb(mouse->urb, mouse->usb_dev, mouse->in_pipe, 
            mouse->data, mouse->in_endpt_maxpktsize, intr_callback, 
            mouse, mouse->in_endpt_interval);  

    mouse->urb->transfer_dma      = mouse->dma_handle;
    mouse->urb->transfer_flags    |= URB_NO_TRANSFER_DMA_MAP;

    submit_work(mouse, GFP_KERNEL);
    return 0;

}

static void uien_disconnect(struct usb_interface *intf)
{
    DEVICE_DATA  *mouse;
    printk("Device disconnected\n");
    mouse = usb_get_intfdata(intf);
    usb_set_intfdata(intf, NULL);
    if (mouse) {
        usb_kill_urb(mouse->urb);
        usb_free_urb(mouse->urb);
        usb_free_coherent(mouse->usb_dev, mouse->in_endpt_maxpktsize, mouse->data, mouse->dma_handle);
        kfree(mouse);
    }
    
    usb_deregister_dev(intf, &uien_class);
}

static struct usb_driver uien_driver = {
    .name       = "uien_driver",
    .id_table   = uien_table,
    .probe      = uien_probe,
    .disconnect = uien_disconnect
};
 


static int __init uien_init(void)
{
    return usb_register(&uien_driver);
}

static void __exit uien_exit(void)
{
    usb_deregister(&uien_driver);
}
module_init(uien_init);
module_exit(uien_exit);
MODULE_LICENSE("GPL");
