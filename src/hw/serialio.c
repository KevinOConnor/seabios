// Low-level serial (and serial-like) device access.
//
// Copyright (C) 2008-1013  Kevin O'Connor <kevin@koconnor.net>
//
// This file may be distributed under the terms of the GNU LGPLv3 license.

#include "config.h" // CONFIG_DEBUG_SERIAL
#include "fw/paravirt.h" // RunningOnQEMU
#include "output.h" // dprintf
#include "serialio.h" // serial_debug_preinit
#include "x86.h" // outb


static struct {
    u32 base_addr;
    u8 reg_width;
    u8 is_io_mapped;
} serial = {
    .is_io_mapped = 1,
    .base_addr = CONFIG_DEBUG_SERIAL_PORT,
    .reg_width = 1,
};

/****************************************************************
 * Serial port debug output
 ****************************************************************/

#define DEBUG_TIMEOUT 100000

static inline u8 serial_read(u8 reg)
{
    u32 reg_base = serial.base_addr + reg * serial.reg_width;

    if (serial.is_io_mapped)
        return inb(reg_base);
    else
        return readb((void *)reg_base);
}

static inline void serial_write(u8 reg, u8 val)
{
    u32 reg_base = serial.base_addr + reg * serial.reg_width;

    if (serial.is_io_mapped)
        outb(reg_base, val);
    else
        writeb((void *)reg_base, val);
}

void serial_update_params(u32 base_addr, u8 reg_width, u8 is_io_mapped)
{
    serial.base_addr = base_addr;
    serial.reg_width = reg_width;
    serial.is_io_mapped = is_io_mapped;
}

// Setup the debug serial port for output.
void
serial_debug_preinit(void)
{
    if (!CONFIG_DEBUG_SERIAL)
        return;
    // setup for serial logging: 8N1
    u8 oldparam, newparam = 0x03;
    oldparam = serial_read(SEROFF_LCR);
    serial_write(SEROFF_LCR, newparam);
    // Disable irqs
    u8 oldier, newier = 0;
    oldier = serial_read(SEROFF_IER);
    serial_write(SEROFF_IER, newier);

    if (oldparam != newparam || oldier != newier)
        dprintf(1, "Changing serial settings was %x/%x now %x/%x\n"
                , oldparam, oldier, newparam, newier);
}

// Write a character to the serial port.
static void
serial_debug(char c)
{
    if (!CONFIG_DEBUG_SERIAL)
        return;
    int timeout = DEBUG_TIMEOUT;
    while ((serial_read(SEROFF_LSR) & 0x20) != 0x20)
        if (!timeout--)
            // Ran out of time.
            return;
    serial_write(SEROFF_DATA, c);
}

void
serial_debug_putc(char c)
{
    if (c == '\n')
        serial_debug('\r');
    serial_debug(c);
}

// Make sure all serial port writes have been completely sent.
void
serial_debug_flush(void)
{
    if (!CONFIG_DEBUG_SERIAL)
        return;
    int timeout = DEBUG_TIMEOUT;
    while ((serial_read(SEROFF_LSR) & 0x60) != 0x60)
        if (!timeout--)
            // Ran out of time.
            return;
}


/****************************************************************
 * QEMU debug port
 ****************************************************************/

u16 DebugOutputPort VARFSEG = 0x402;

// Write a character to the special debugging port.
void
qemu_debug_putc(char c)
{
    if (CONFIG_DEBUG_IO && runningOnQEMU())
        // Send character to debug port.
        outb(c, GET_GLOBAL(DebugOutputPort));
}
