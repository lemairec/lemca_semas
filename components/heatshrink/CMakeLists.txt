set(COMPONENT_SRCS 
  "heatshrink_decoder.c"
  "heatshrink_encoder.c"
)

set(COMPONENT_ADD_INCLUDEDIRS 
  "."
  ".."
)

set(COMPONENT_REQUIRES 
)

set(COMPONENT_PRIV_REQUIRES 
	lib_cci 
	Settings 
	IsoConfig
)

register_component()

