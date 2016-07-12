// Copyright (C) 2016 by Rage MP Team

#ifdef BEGIN_OFFSET_NAMESPACE
#error Before including OffsetsHelpersBegin.h again you need to include OffsetsHelpersEnd.h before.
#endif

#define BEGIN_OFFSET_NAMESPACE(name) class name { public:
#define DECLARE_OFFSET(name) static Address_t name
#define SETUP_OFFSET(ns, name) Address_t Offsets::ns::name = 0
#define SET_OFFSET_ADDRESS(ns, name, address) Offsets::ns::name = baseAddress + address
#define END_OFFSET_NAMESPACE() };

/* eof */
