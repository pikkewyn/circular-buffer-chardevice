#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/types.h>

static int __init chardev_init( void );
static void __exit chardev_exit( void );
static int device_open( struct inode*, struct file* );
static int device_release( struct inode*, struct file* );
static ssize_t device_read( struct file*, char*, size_t, loff_t* );
static ssize_t device_write( struct file*, const char*, size_t, loff_t* );

#endif
