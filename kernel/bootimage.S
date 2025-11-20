# first program in uspace. must be embedded in kernel as we have no fs yet
# will start all user servers.

    .section .rodata
    .global __bootimage
__bootimage:
    .incbin "../build/uspace/servers/pm/pm"
