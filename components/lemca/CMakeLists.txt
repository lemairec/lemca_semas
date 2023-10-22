# Edit following two lines to set component requirements (see docs)



set(COMPONENT_SRCS 
    "uart/my_uart.c"
    "common/util.c"
    "isobus_message.c"
    "lemca.c"
    "gpio.c"
   
)

set(COMPONENT_ADD_INCLUDEDIRS 
    "."
)

set(COMPONENT_REQUIRES
    lib_cci
    IsoConfig
    AppCommon
    AppIso
)

set(COMPONENT_PRIV_REQUIRES 
)

register_component()

