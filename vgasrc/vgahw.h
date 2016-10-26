#ifndef __VGAHW_H
#define __VGAHW_H

#include "bochsvga.h" // bochsvga_set_mode
#include "config.h" // CONFIG_*
#include "geodevga.h" // geodevga_setup
#include "stdvga.h" // stdvga_set_mode
#include "vgafb.h" // vgafb_scroll
#include "vgautil.h" // stdvga_list_modes

static inline struct vgamode_s *vgahw_find_mode(int mode) {
    if (CONFIG_VGA_CIRRUS)
        return clext_find_mode(mode);
    if (CONFIG_VGA_BOCHS)
        return bochsvga_find_mode(mode);
    if (CONFIG_VGA_COREBOOT)
        return cbvga_find_mode(mode);
    if (CONFIG_VGA_SERCON)
        return sercon_find_mode(mode);
    return stdvga_find_mode(mode);
}

static inline int vgahw_set_mode(struct vgamode_s *vmode_g, int flags) {
    if (CONFIG_VGA_CIRRUS)
        return clext_set_mode(vmode_g, flags);
    if (CONFIG_VGA_BOCHS)
        return bochsvga_set_mode(vmode_g, flags);
    if (CONFIG_VGA_COREBOOT)
        return cbvga_set_mode(vmode_g, flags);
    if (CONFIG_VGA_SERCON)
        return sercon_set_mode(vmode_g, flags);
    return stdvga_set_mode(vmode_g, flags);
}

static inline void vgahw_list_modes(u16 seg, u16 *dest, u16 *last) {
    if (CONFIG_VGA_CIRRUS)
        clext_list_modes(seg, dest, last);
    else if (CONFIG_VGA_BOCHS)
        bochsvga_list_modes(seg, dest, last);
    else if (CONFIG_VGA_COREBOOT)
        cbvga_list_modes(seg, dest, last);
    else if (CONFIG_VGA_SERCON)
        sercon_list_modes(seg, dest, last);
    else
        stdvga_list_modes(seg, dest, last);
}

static inline int vgahw_setup(void) {
    if (CONFIG_VGA_CIRRUS)
        return clext_setup();
    if (CONFIG_VGA_BOCHS)
        return bochsvga_setup();
    if (CONFIG_VGA_GEODEGX2 || CONFIG_VGA_GEODELX)
        return geodevga_setup();
    if (CONFIG_VGA_COREBOOT)
        return cbvga_setup();
    if (CONFIG_VGA_SERCON)
        return sercon_setup();
    return stdvga_setup();
}

static inline int vgahw_get_window(struct vgamode_s *vmode_g, int window) {
    if (CONFIG_VGA_CIRRUS)
        return clext_get_window(vmode_g, window);
    if (CONFIG_VGA_BOCHS)
        return bochsvga_get_window(vmode_g, window);
    if (CONFIG_VGA_COREBOOT)
        return cbvga_get_window(vmode_g, window);
    if (CONFIG_VGA_SERCON)
        return sercon_get_window(vmode_g, window);
    return stdvga_get_window(vmode_g, window);
}

static inline int vgahw_set_window(struct vgamode_s *vmode_g, int window
                                   , int val) {
    if (CONFIG_VGA_CIRRUS)
        return clext_set_window(vmode_g, window, val);
    if (CONFIG_VGA_BOCHS)
        return bochsvga_set_window(vmode_g, window, val);
    if (CONFIG_VGA_COREBOOT)
        return cbvga_set_window(vmode_g, window, val);
    if (CONFIG_VGA_SERCON)
        return sercon_set_window(vmode_g, window, val);
    return stdvga_set_window(vmode_g, window, val);
}

static inline int vgahw_get_linelength(struct vgamode_s *vmode_g) {
    if (CONFIG_VGA_CIRRUS)
        return clext_get_linelength(vmode_g);
    if (CONFIG_VGA_BOCHS)
        return bochsvga_get_linelength(vmode_g);
    if (CONFIG_VGA_COREBOOT)
        return cbvga_get_linelength(vmode_g);
    if (CONFIG_VGA_SERCON)
        return sercon_get_linelength(vmode_g);
    return stdvga_get_linelength(vmode_g);
}

static inline int vgahw_set_linelength(struct vgamode_s *vmode_g, int val) {
    if (CONFIG_VGA_CIRRUS)
        return clext_set_linelength(vmode_g, val);
    if (CONFIG_VGA_BOCHS)
        return bochsvga_set_linelength(vmode_g, val);
    if (CONFIG_VGA_COREBOOT)
        return cbvga_set_linelength(vmode_g, val);
    if (CONFIG_VGA_SERCON)
        return sercon_set_linelength(vmode_g, val);
    return stdvga_set_linelength(vmode_g, val);
}

static inline int vgahw_get_displaystart(struct vgamode_s *vmode_g) {
    if (CONFIG_VGA_CIRRUS)
        return clext_get_displaystart(vmode_g);
    if (CONFIG_VGA_BOCHS)
        return bochsvga_get_displaystart(vmode_g);
    if (CONFIG_VGA_COREBOOT)
        return cbvga_get_displaystart(vmode_g);
    if (CONFIG_VGA_SERCON)
        return sercon_get_displaystart(vmode_g);
    return stdvga_get_displaystart(vmode_g);
}

static inline int vgahw_set_displaystart(struct vgamode_s *vmode_g, int val) {
    if (CONFIG_VGA_CIRRUS)
        return clext_set_displaystart(vmode_g, val);
    if (CONFIG_VGA_BOCHS)
        return bochsvga_set_displaystart(vmode_g, val);
    if (CONFIG_VGA_COREBOOT)
        return cbvga_set_displaystart(vmode_g, val);
    if (CONFIG_VGA_SERCON)
        return sercon_set_displaystart(vmode_g, val);
    return stdvga_set_displaystart(vmode_g, val);
}

static inline int vgahw_get_dacformat(struct vgamode_s *vmode_g) {
    if (CONFIG_VGA_BOCHS)
        return bochsvga_get_dacformat(vmode_g);
    if (CONFIG_VGA_COREBOOT)
        return cbvga_get_dacformat(vmode_g);
    if (CONFIG_VGA_SERCON)
        return sercon_get_dacformat(vmode_g);
    return stdvga_get_dacformat(vmode_g);
}

static inline int vgahw_set_dacformat(struct vgamode_s *vmode_g, int val) {
    if (CONFIG_VGA_BOCHS)
        return bochsvga_set_dacformat(vmode_g, val);
    if (CONFIG_VGA_COREBOOT)
        return cbvga_set_dacformat(vmode_g, val);
    if (CONFIG_VGA_SERCON)
        return sercon_set_dacformat(vmode_g, val);
    return stdvga_set_dacformat(vmode_g, val);
}

static inline int vgahw_save_restore(int cmd, u16 seg, void *data) {
    if (CONFIG_VGA_CIRRUS)
        return clext_save_restore(cmd, seg, data);
    if (CONFIG_VGA_BOCHS)
        return bochsvga_save_restore(cmd, seg, data);
    if (CONFIG_VGA_COREBOOT)
        return cbvga_save_restore(cmd, seg, data);
    if (CONFIG_VGA_SERCON)
        return sercon_save_restore(cmd, seg, data);
    return stdvga_save_restore(cmd, seg, data);
}

static inline void vgahw_scroll(struct cursorpos win, struct cursorpos winsize
                                , int lines, struct carattr ca)
{
    if (CONFIG_VGA_SERCON)
        sercon_scroll(win, winsize, lines, ca);
    else
        vgafb_scroll(win, winsize, lines, ca);
}

static inline void vgahw_write_char(struct cursorpos cp, struct carattr ca)
{
    if (CONFIG_VGA_SERCON)
        sercon_write_char(cp, ca);
    else
        vgafb_write_char(cp, ca);
}

static inline struct carattr vgahw_read_char(struct cursorpos cp)
{
    if (CONFIG_VGA_SERCON)
        return sercon_read_char(cp);
    return vgafb_read_char(cp);
}

static inline void vgahw_write_pixel(u8 color, u16 x, u16 y)
{
    if (CONFIG_VGA_SERCON)
        sercon_write_pixel(color, x, y);
    else
        vgafb_write_pixel(color, x, y);
}

static inline u8 vgahw_read_pixel(u16 x, u16 y)
{
    if (CONFIG_VGA_SERCON)
        return sercon_read_pixel(x, y);
    return vgafb_read_pixel(x, y);
}

#endif // vgahw.h
