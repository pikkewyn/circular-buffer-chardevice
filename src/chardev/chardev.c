#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>

#include<linux/slab.h>
#include<linux/cdev.h>
#include<linux/mutex.h>

#include "chardev.h"
#include "../circularbuffer/circularbuffer.h"

#define SUCCESS 0
#define DEVICE_NAME "chardev"
#define BUF_LEN 4
#define DEVICES 1

struct CircularBuffer cb;

static int charamount;

static int Major = 122;
DEFINE_MUTEX( Device_Open );
static char* msg_Ptr;

static struct cdev* chcdev;
static char* buffer;
static int buffer_size = 4;

static struct file_operations fops =
{
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};


static int __init chardev_init( void )
{
    int ret;
    dev_t num;
    buffer = kmalloc( buffer_size, GFP_KERNEL );
    num = MKDEV( Major, 0 );
    
    cbInit( &cb, 2 );
    
    ret = register_chrdev_region( num, DEVICES, DEVICE_NAME );

    if( ret < 0 )
    {
        printk( KERN_ALERT "Nieudana proba przydzialu obszaru urzadzenia" " w jadrze - zwrocony numer %d\n", ret );
        return ret;
    }
    
    chcdev = cdev_alloc();
    chcdev->owner = THIS_MODULE;
    chcdev->ops = &fops;
    ret = cdev_add( chcdev, num, DEVICES );

    if( ret < 0 )
    {
        printk( KERN_ALERT "Nieudana proba zarejestrowania urzadzenia" "w jadrze - zwrocony numer %d\n", ret );
        return ret;
    }

    printk( KERN_INFO "Przydzielono mi numer urzadzenia %d. Otworz plik\n", Major );
    printk( KERN_INFO "urzadzenia za pomoca"
            "'mknod /dev/%s c %d 0'\n", DEVICE_NAME, Major );;
    printk( KERN_INFO "urzadzenia. Po usunieciu urzadzenia usun i plik\n" );
    
    return SUCCESS;
}

static void __exit chardev_exit( void )
{
    dev_t num;
    kfree( buffer );
   
    num = MKDEV( Major, 0 );
    
    cdev_del( chcdev );
    unregister_chrdev_region( num, DEVICES );
    printk( KERN_INFO "Zegnaj, swiecie!\n" );
}

module_init( chardev_init );
module_exit( chardev_exit );

MODULE_LICENSE( "GPL v2" );
MODULE_AUTHOR( "Dariusz Biszmor <Dariusz.Bismor[at]polsl.pl>" );
MODULE_DESCRIPTION( "Przyklad modulu z plikiem urzadzenia" );
MODULE_SUPPORTED_DEVICE( DEVICE_NAME );



static int device_open( struct inode* inoda, struct file* plik )
{
    printk( KERN_INFO "Otwarcie pliku urzadzenia o numerze pobocznym" " %d\n", iminor( inoda ) );

    if( mutex_lock_interruptible( &Device_Open ) )
    {
        printk( KERN_INFO "Proba przejecia semafora przerwana!\n" );
        return -ERESTARTSYS;
    }

    try_module_get( THIS_MODULE );
    msg_Ptr = buffer;
  
    charamount = strlen( buffer );
  
    return SUCCESS;
}

static int device_release( struct inode* inoda, struct file* plik )
{
    mutex_unlock( &Device_Open );
    module_put( THIS_MODULE );
    
    return 0;
}

static ssize_t device_read( struct file* plik, char* buforUz, size_t lenght, loff_t* offset )
{
    int zmienna;    //ilosc zanakow mieszczaca sie w zadanym buforze

    printk( KERN_INFO "dlugosc" " %ld\n", lenght );

    if( *offset == charamount ) //offset = ilosc znakow -> zakoncz
    {
        return 0;
    }

    if( lenght < charamount )
    {
        zmienna = lenght;
    }

    if( lenght >= charamount )
    {
        zmienna = charamount;
    }

  
    copy_to_user( buforUz, msg_Ptr + *offset, zmienna ); //(u space, k space, l.bytow)
    *offset += zmienna;

    return zmienna;
}

static ssize_t device_write( struct file* plik, const char* bufor, size_t length, loff_t* offset )
{
    if( length > buffer_size ) 
    {
        length = buffer_size;
        copy_from_user( buffer + *offset, bufor , length );
        *offset += length;    
    }
    else
    {
        copy_from_user( buffer + *offset , bufor , length ); 
    }
    
    printk( KERN_INFO "offset" " %lld\n", *offset );
    printk( KERN_INFO "dlugosc" " %ld\n", length );
    
    return length;
}

