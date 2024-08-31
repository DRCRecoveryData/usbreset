#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/usbdevice_fs.h>

int main(int argc, char **argv)
{
    const char *filename;
    int fd;
    int rc;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <device-filename>\n", argv[0]);
        return 1;
    }

    filename = argv[1];

    // Open the device file
    fd = open(filename, O_WRONLY);
    if (fd < 0) {
        perror("Error opening device file");
        return 1;
    }

    // Send the USB reset command
    printf("Resetting USB device %s\n", filename);
    rc = ioctl(fd, USBDEVFS_RESET, 0);
    if (rc < 0) {
        perror("Error resetting USB device");
        close(fd);
        return 1;
    }

    printf("USB reset successful\n");

    // Close the device file
    close(fd);
    return 0;
}
