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


#define BULK 0
#define INTR 1
struct DEVICE_DATA;
typedef struct {
    int addr;
    int interval;
    int maxpktsize;
    int pipe;
    void (*callback)(struct urb *);
    struct urb *urb;
    char *data;
    dma_addr_t handle;
    struct DEVICE_DATA  *nic;
    char alloced;
}EP_DATA;


typedef struct DEVICE_DATA{
    struct usb_device *usb_dev;    
    struct usb_interface *usb_intf;
    EP_DATA bulk_in_ep;
    EP_DATA bulk_out_ep;
    EP_DATA intr_in_ep;
    EP_DATA ctrl_in_ep;
    EP_DATA ctrl_out_ep;
}DEVICE_DATA;


MODULE_DEVICE_TABLE (usb, uien_table);


#if 0
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

#endif
char *ep_type(struct usb_endpoint_descriptor *ep_desc)
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

char *ep_dir(struct usb_endpoint_descriptor *ep_desc)
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

void submit_work(EP_DATA *ep, int flag)
{
    int err;
    err = usb_submit_urb(ep->urb, flag);
    if (err) {
        printk("Something unexpected happened = %d\n", err);
    }
    submit_work(&(ep->nic->bulk_in_ep), GFP_ATOMIC);    
}

static void rx_callback(struct urb *urb)
{
    int i;
    EP_DATA *ep;
    printk("Received data \n");
    ep = urb->context;
    for (i = 0; i < ep->maxpktsize; i++){
        printk("%x ", ep->data[i]);
        if (i % 15 == 0)
            printk("\n");
    }
    printk("\n");

}

static void intr_callback(struct urb *urb)
{
    int i;
    EP_DATA *ep = urb->context;
    int status = urb->status;
    
    printk("Callback dude\n");
    /*  sync/async unlink faults aren't errors */
    if (status && !(status == -ENOENT ||
                status == -ECONNRESET ||
                status == -ESHUTDOWN))
        printk("nonzero write interrupt status received: %d\n", status);
    
//    for (i = 0; i < 8; i++) {
 //       printk("%d - %x\n", i, ep->data[i]);
  //  }
    if (ep->data[1] & 0x01) {
 //       submit_work(&(ep->nic->bulk_in_ep), GFP_ATOMIC);    
    }
 //   submit_work(ep, GFP_ATOMIC);    

}


int create_urb(EP_DATA *ep, int type)
{    
    
    ep->data = usb_alloc_coherent(ep->nic->usb_dev, ep->maxpktsize, GFP_ATOMIC, &ep->handle);
    if (!ep->data)
        return -ENOMEM;

    ep->urb = usb_alloc_urb(0, GFP_KERNEL);
    if (!ep->urb){
        usb_free_coherent(ep->nic->usb_dev, ep->maxpktsize, ep->data, ep->handle);
        return -ENOMEM;
    }

    if (type == BULK) {
        usb_fill_bulk_urb(ep->urb, ep->nic->usb_dev, ep->pipe, 
            ep->data, ep->maxpktsize, ep->callback, 
            ep);  
    }
    if (type  == INTR) {
        usb_fill_int_urb(ep->urb, ep->nic->usb_dev, ep->pipe, 
            ep->data, ep->maxpktsize, ep->callback, 
            ep, ep->interval);  
    }

    ep->urb->transfer_dma      = ep->handle;
    ep->urb->transfer_flags    |= URB_NO_TRANSFER_DMA_MAP;
    ep->alloced = 1;
    return 0;
}

void reg_write(EP_DATA *ep, int off, unsigned char value)
{
    usb_control_msg(ep->nic->usb_dev, ep->pipe, 0, 0xC0, 0, off, &value, sizeof(value), ep->interval);
}
// request = 0, 
// request type = C0, 
// value = 0
// index = reg offset 
// data = return value,
// size = data len
// timeout = ctrl timeout
//  extern int usb_control_msg(struct usb_device *dev, unsigned int pipe,
//  1499         __u8 request, __u8 requesttype, __u16 value, __u16 index,
//  1500         void *data, __u16 size, int timeout);
int reg_read(EP_DATA *ep, int off)
{
    unsigned char value;
    value = 0;
    if (!ep)     {
        printk("Error ep is null\n");
    } else
    if (!ep->nic) {
        printk("Error ep->nic is null\n");
    } else
    usb_control_msg(ep->nic->usb_dev, ep->pipe, 0, 0xC0, 0, off, &value, sizeof(value), ep->interval);
    //usb_control_msg(nic->usb_dev, nic->ctrl_in_ep.pipe, 0, USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE, 0, off, &value, sizeof(value), nic->intr_in_ep.interval);
    return value;
}


static int uien_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
    int num_endpts;
    struct usb_endpoint_descriptor endpt_desc;
    int i;
    DEVICE_DATA *nic;

   
    printk("Device connected \n");
    printk("num_altsettings = %d \n", intf->num_altsetting);
    printk("vendor = 0x%04x , device = 0x%04x \n", id->idVendor, id->idProduct);
    printk("device class = %d \n", id->bDeviceClass);
    printk("number of endpoints = %d \n", intf->cur_altsetting->desc.bNumEndpoints);
    
    nic = kzalloc(sizeof(*nic), GFP_KERNEL);
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
                ep_type(&endpt_desc),                                  \
                ep_dir(&endpt_desc), endpt_desc.bLength,                \
                endpt_desc.bEndpointAddress, endpt_desc.wMaxPacketSize, endpt_desc.bInterval);
    
        if (usb_endpoint_xfer_int(&endpt_desc)) {
            if (usb_endpoint_dir_in(&endpt_desc)){
                nic->intr_in_ep.addr        = endpt_desc.bEndpointAddress;
                nic->intr_in_ep.interval    = endpt_desc.bInterval;
                nic->intr_in_ep.maxpktsize  = endpt_desc.wMaxPacketSize;
            }
        }
        if (usb_endpoint_xfer_bulk(&endpt_desc)) {
            if (usb_endpoint_dir_in(&endpt_desc)){
                nic->bulk_in_ep.addr        = endpt_desc.bEndpointAddress;
                nic->bulk_in_ep.interval    = endpt_desc.bInterval;
                nic->bulk_in_ep.maxpktsize  = endpt_desc.wMaxPacketSize;
            }
            else 
                if (usb_endpoint_dir_out(&endpt_desc)){
                    nic->bulk_out_ep.addr        = endpt_desc.bEndpointAddress;
                    nic->bulk_out_ep.interval    = endpt_desc.bInterval;
                    nic->bulk_out_ep.maxpktsize  = endpt_desc.wMaxPacketSize;
                }
        }
    }
    nic->ctrl_in_ep.addr        =  0;
    nic->ctrl_in_ep.interval    =  USB_CTRL_GET_TIMEOUT;
    nic->ctrl_in_ep.maxpktsize  =  0;
    
    nic->ctrl_out_ep.addr       =  0;
    nic->ctrl_out_ep.interval   =  USB_CTRL_SET_TIMEOUT;
    nic->ctrl_out_ep.maxpktsize =  0;
    
    nic->ctrl_in_ep.pipe    = usb_rcvctrlpipe(nic->usb_dev, nic->ctrl_in_ep.addr);
    nic->ctrl_out_ep.pipe   = usb_sndctrlpipe(nic->usb_dev, nic->ctrl_out_ep.addr);
    
    nic->bulk_in_ep.pipe    = usb_rcvctrlpipe(nic->usb_dev, nic->bulk_in_ep.addr);
    nic->bulk_out_ep.pipe   = usb_sndctrlpipe(nic->usb_dev, nic->bulk_out_ep.addr);
    nic->intr_in_ep.pipe    = usb_rcvctrlpipe(nic->usb_dev, nic->intr_in_ep.addr);

    
    
    nic->intr_in_ep.callback = intr_callback;
    nic->bulk_in_ep.callback = rx_callback;
    nic->intr_in_ep.nic = nic;
    nic->bulk_in_ep.nic = nic;
    nic->bulk_out_ep.nic = nic;
    nic->ctrl_in_ep.nic = nic;
    nic->ctrl_out_ep.nic = nic;
    create_urb(&nic->intr_in_ep, INTR);   
    create_urb(&nic->bulk_in_ep, BULK);   
    create_urb(&nic->bulk_out_ep, BULK);   

     for (i = 0; i <= 0x2C; i++) {
        printk("off = %x, value = 0x%02x \n", i, reg_read(&nic->ctrl_in_ep, i));
    }

    i  = reg_read(&nic->ctrl_in_ep, 0x5)|0x01;
    reg_write(&nic->ctrl_out_ep, 0x5, i);
     
    submit_work(&nic->intr_in_ep, GFP_KERNEL);
    submit_work(&nic->bulk_in_ep, GFP_ATOMIC);    

    return 0;

}


void free_ep_data(EP_DATA *ep)
{

    if (ep->alloced) {
        usb_kill_urb(ep->urb);
        usb_free_urb(ep->urb);
        usb_free_coherent(ep->nic->usb_dev, ep->maxpktsize, ep->data, ep->handle);
    }
}

void free_resources(DEVICE_DATA *nic)
{
    EP_DATA *ep;
    if (nic) {
        ep = &nic->intr_in_ep;
        free_ep_data(ep);
        ep = &nic->bulk_in_ep;
        free_ep_data(ep);
        ep = &nic->bulk_out_ep;
        free_ep_data(ep);
        kfree(nic);
    }

}
static void uien_disconnect(struct usb_interface *intf)
{
    DEVICE_DATA  *nic;
    printk("Device disconnected\n");
    nic = usb_get_intfdata(intf);
    usb_set_intfdata(intf, NULL);
    free_resources(nic);

    //usb_deregister_dev(intf, &uien_class);
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
