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
    {USB_DEVICE(0x0a46,0x9601)},
    {}
};



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
void submit_work(DEVICE_DATA *nic, int flag)
{
    int err;
    err = usb_submit_urb(nic->urb, flag);
    if (err) {
        printk("Something unexpected happened = %d\n", err);
    }
 

}

static void intr_callback(struct urb *urb)
{
    DEVICE_DATA *nic = urb->context;
    int status = urb->status;
    
    printk("Callback dude\n");
    /*  sync/async unlink faults aren't errors */
    if (status && !(status == -ENOENT ||
                status == -ECONNRESET ||
                status == -ESHUTDOWN))
        printk("nonzero write interrupt status received: %d\n", status);
    
    signed char *data = nic->data; 
    printk("l = %d, r - %d, m - %d, s - %d, e - %d \n", data[0]& 0x01, data[0] & 0x02, data[0] & 0x4, data[0] &0x8,
            data[0] & 0x10);
    printk("x - %d, y - %d, wheel - %d \n", data[1], data[2], data[3]);     
    submit_work(nic, GFP_ATOMIC);    

}


static int uien_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
    int num_endpts;
    struct usb_endpoint_descriptor endpt_desc;
    int i;
    int retval;
    DEVICE_DATA *nic;
    int err;

    int int_data;
    int actual_len;
   
    printk("Device connected \n");
    printk("num_altsettings = %d \n", intf->num_altsetting);
    printk("vendor = 0x%04x , device = 0x%04x \n", id->idVendor, id->idProduct);
    printk("device class = %d \n", id->bDeviceClass);
    printk("number of endpoints = %d \n", intf->cur_altsetting->desc.bNumEndpoints);
    
    nic = kmalloc(sizeof(*nic), GFP_KERNEL);
    if (!nic)
        return -ENOMEM; 

    nic->usb_dev    = interface_to_usbdev(intf);
    nic->usb_intf   = intf;
    usb_set_intfdata(intf, nic);
    


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
                nic->in_endpt_addr = endpt_desc.bEndpointAddress;
                nic->in_endpt_interval = endpt_desc.bInterval;
                nic->in_endpt_maxpktsize = endpt_desc.wMaxPacketSize;
            }
            else
            if (usb_endpoint_dir_out(&endpt_desc)) {
                nic->out_endpt_addr = endpt_desc.bEndpointAddress;
                nic->out_endpt_interval = endpt_desc.bInterval;
                nic->out_endpt_maxpktsize = endpt_desc.wMaxPacketSize;
            }
        }
    }

    nic->data = usb_alloc_coherent(nic->usb_dev, nic->in_endpt_maxpktsize, GFP_ATOMIC, &nic->dma_handle);
    if (!nic->data){
        kfree(nic);
        return -ENOMEM;
    }
 
    nic->urb = usb_alloc_urb(0, GFP_KERNEL);
    if (!nic->urb){
        kfree(nic);
        usb_free_coherent(nic->usb_dev, nic->in_endpt_maxpktsize, nic->data, nic->dma_handle);
        return -ENOMEM;
    }

    nic->in_pipe = usb_rcvintpipe(nic->usb_dev, nic->in_endpt_addr);
    usb_fill_int_urb(nic->urb, nic->usb_dev, nic->in_pipe, 
            nic->data, nic->in_endpt_maxpktsize, intr_callback, 
            nic, nic->in_endpt_interval);  

    nic->urb->transfer_dma      = nic->dma_handle;
    nic->urb->transfer_flags    |= URB_NO_TRANSFER_DMA_MAP;

    submit_work(nic, GFP_KERNEL);
    return 0;

}

static void uien_disconnect(struct usb_interface *intf)
{
    DEVICE_DATA  *nic;
    printk("Device disconnected\n");
    nic = usb_get_intfdata(intf);
    usb_set_intfdata(intf, NULL);
    if (nic) {
        usb_kill_urb(nic->urb);
        usb_free_urb(nic->urb);
        usb_free_coherent(nic->usb_dev, nic->in_endpt_maxpktsize, nic->data, nic->dma_handle);
        kfree(nic);
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
